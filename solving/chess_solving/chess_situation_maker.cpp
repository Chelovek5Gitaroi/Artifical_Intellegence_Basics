#include "chess_situation_maker.h"

namespace chess_solver
{
	AbstractSituation* ChessSituationMaker::getNextSituation(AbstractSituation* abstractSituation)
	{
		Situation* situation = reinterpret_cast<Situation*>(abstractSituation);
		Situation* result = new Situation(*situation);
		
		std::list<Figure*>* figures = &result->getWhiteFigures();
		std::list<Figure*>* otherFigures = &result->getBlackFigures();
		
		if (result->getCurrentPlayer() == FigureColor::BLACK)
		{
			figures = &result->getBlackFigures();
			otherFigures = &result->getWhiteFigures();
		}

		if (!situation->getPotentialMoves()->empty())
		{
			executor.executeCommand(situation->getPotentialMoves()->front(), result->getBoard(), figures, otherFigures);
			
			result->setPotentialMoves(getAllSituationMoves(*result));
			
			if (result->getCurrentPlayer() == FigureColor::WHITE)
			{
				result->setCurrentPlayer(FigureColor::BLACK);
			}
			else
			{
				result->setCurrentPlayer(FigureColor::WHITE);
			}
		}
		else
		{
			delete result;
			result = nullptr;
		}

		return result;
	}
	
	void ChessSituationMaker::prepareStartSituationMoves(Situation* startSituation)
	{
		startSituation->setPotentialMoves(getAllSituationMoves(*startSituation));
	}
	
	Command* ChessSituationMaker::createValidCommand(Figure* figure, Board& board, const Coordinates& finishCoordinates, CommandType type,
		const Coordinates& kingCoordinates, std::list<Figure*>* figures, FigureColor otherColor, std::list<Figure*>* otherFigures)
	{
		Command* result = new Command(figure, finishCoordinates, type);
		
		bool isValid = MovingValidator::isMoveValid(result, *otherFigures, board);
		
		if (isValid)
		{
			executor.executeCommand(result, board, figures, otherFigures);
			
			isValid = !MovingValidator::hasCheck(board, kingCoordinates, otherColor, *otherFigures);
			
			executor.undoCommand(result, board, figures, otherFigures);
			
			if (!isValid)
			{
				delete result;
				result = nullptr;
			}
		}
		else
		{
			delete result;
			result = nullptr;
		}
		
		return result;
	}
	
	bool ChessSituationMaker::createValidTransformationCommands(Figure* figure, Board& board, const Coordinates& finishCoordinates, CommandType type,
		const Coordinates& kingCoordinates, std::list<Figure*>* figures, FigureColor otherColor, std::list<Figure*>* otherFigures, std::list<Command*>* commands)
	{
		Command* command = new CommandTransformation(figure, finishCoordinates, FigureType::BISHOP, type);
		
		bool isValid = MovingValidator::isMoveValid(command, *otherFigures, board);
		
		if (isValid)
		{
			executor.executeCommand(command, board, figures, otherFigures);
			
			isValid = !MovingValidator::hasCheck(board, kingCoordinates, otherColor, *otherFigures);
			
			executor.undoCommand(command, board, figures, otherFigures);
			
			if (isValid)
			{
				commands->push_back(command);
				commands->push_back(new CommandTransformation(figure, finishCoordinates, FigureType::KNIGHT, type));
				commands->push_back(new CommandTransformation(figure, finishCoordinates, FigureType::ROCK, type));
				commands->push_back(new CommandTransformation(figure, finishCoordinates, FigureType::QUEEN, type));
			}
			else
			{
				delete command;
			}
		}
		else
		{
			delete command;
		}
		
		return isValid;
	}
	
	std::list<Command*>* ChessSituationMaker::getFigurePotentialMoves(Board& board, Figure* figure, const Coordinates& kingCoordinates, std::list<Figure*>* figures, std::list<Figure*>* otherFigures)
	{
		std::list<Command*>* result = new std::list<Command*>();
		
		Coordinates startCoordinates = figure->getCoordinates();
		
		FigureColor otherColor = FigureColor::BLACK;
		
		if (figure->getColor() == FigureColor::BLACK)
		{
			otherColor = FigureColor::WHITE;
		}
		
		std::list<Coordinates>* coordinates = MovingPreparator::getPotentialPossibleCoordinates(startCoordinates, figure->getType(), figure->getColor(), board.getBoardSize());
		
		Command* command = nullptr;
		
		bool wasCreated = false;
		
		for (auto iter = coordinates->begin(); iter != coordinates->end(); iter++)
		{
			command = createValidCommand(figure, board, *iter, CommandType::MOVE, kingCoordinates, figures, otherColor, otherFigures);
			
			if (command)
			{
				result->push_back(command);
			}
			else
			{
				command = createValidCommand(figure, board, *iter, CommandType::BEAT, kingCoordinates, figures, otherColor, otherFigures);
				
				if (command)
				{
					result->push_back(command);
				}
				else if (figure->getType() == FigureType::PAWN)
				{
					wasCreated = createValidTransformationCommands(figure, board, *iter, CommandType::TRANSFORMATION, kingCoordinates, figures, otherColor, otherFigures, result);
					
					if (!wasCreated)
					{
						createValidTransformationCommands(figure, board, *iter, CommandType::BEAT_TRANSFORMATION, kingCoordinates, figures, otherColor, otherFigures, result);
					}
				}
			}
		}
		
		return result;
	}
	
	std::list<Command*>* ChessSituationMaker::getAllSituationMoves(Situation& situation)
	{
		std::list<Command*>* result = new std::list<Command*>();
		
		std::list<Figure*>* figures = &situation.getWhiteFigures();
		std::list<Figure*>* otherFigures = &situation.getBlackFigures();
		
		if (situation.getCurrentPlayer() == FigureColor::BLACK)
		{
			figures = &situation.getBlackFigures();
			otherFigures = &situation.getWhiteFigures();
		}
		
		const Coordinates& kingCoordinates = getKingFromList(figures)->getCoordinates();
		
		for (auto iter = figures->begin(); iter != figures->end(); iter++)
		{
			std::list<Command*>* moves = getFigurePotentialMoves(situation.getBoard(), *iter, kingCoordinates, figures, otherFigures);
			
			for (auto cmdIter = moves->begin(); cmdIter != moves->end(); cmdIter++)
			{
				result->push_back(*cmdIter);
			}
			
			delete moves;
		}
		
		return result;
	}

	Figure* ChessSituationMaker::getKingFromList(std::list<Figure*>* figures)
	{
		for (auto iter = figures->begin(); iter != figures->end(); iter++)
		{
			if ((*iter)->getType() == FigureType::KING)
			{
				return *iter;
			}
		}
		
		return nullptr;
	}

}
