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
//		std::cout << "*Debug* preparing start moves...\n";
		
		startSituation->setPotentialMoves(getAllSituationMoves(*startSituation));
	}
	
	Command* ChessSituationMaker::createValidCommand(Figure* figure, Board& board, const Coordinates& finishCoordinates, CommandType type,
		const Coordinates& kingCoordinates, std::list<Figure*>* figures, std::list<Figure*>* otherFigures)
	{
//		std::cout << "*Debug* creating valid command...\n";
		
		Command* result = new Command(figure, finishCoordinates, type);
		
		bool isValid = MovingValidator::isMoveValid(result, *otherFigures, board);
		
		if (isValid)
		{
			isValid = !MovingValidator::hasCheck(result, board, kingCoordinates, *otherFigures);
			
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
		
//		std::cout << "*Debug* end valid command creating... ";
//		
//		if (result)
//		{
//			std::cout << "valid command...\n";
//		}
//		else
//		{
//			std::cout << "no command...\n";
//		}
		
		return result;
	}
	
	bool ChessSituationMaker::createValidTransformationCommands(Figure* figure, Board& board, const Coordinates& finishCoordinates, CommandType type,
		const Coordinates& kingCoordinates, std::list<Figure*>* figures, std::list<Figure*>* otherFigures, std::list<Command*>* commands)
	{
//		std::cout << "*Debug* creating valid transformation commands...\n";
		
		Command* command = new CommandTransformation(figure, finishCoordinates, FigureType::BISHOP, type);
		
		bool isValid = MovingValidator::isMoveValid(command, *otherFigures, board);
		
		if (isValid)
		{
			isValid = !MovingValidator::hasCheck(command, board, kingCoordinates, *otherFigures);
			
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
		
//		std::cout << "end creating valid trans commands... ";
//		
//		if (isValid)
//		{
//			std::cout << "valid\n";
//		}
//		else
//		{
//			std::cout << "non valid\n";
//		}
		
		return isValid;
	}
	
	std::list<Command*>* ChessSituationMaker::getFigurePotentialMoves(Board& board, Figure* figure, const Coordinates& kingCoordinates, std::list<Figure*>* figures, std::list<Figure*>* otherFigures)
	{
//		std::cout << "*Debug* preparing figure moves figure type: " << (int)figure->getType() << "\n";
		
		std::list<Command*>* result = new std::list<Command*>();
		
		Coordinates startCoordinates = figure->getCoordinates();
		
		std::list<Coordinates>* coordinates = MovingPreparator::getPotentialPossibleCoordinates(startCoordinates, figure->getType(), figure->getColor(), board.getBoardSize());
		
		Command* command = nullptr;
		
		bool wasCreated = false;
		
		for (auto iter = coordinates->begin(); iter != coordinates->end(); iter++)
		{
			command = createValidCommand(figure, board, *iter, CommandType::MOVE, kingCoordinates, figures, otherFigures);
			
			if (command)
			{
				result->push_back(command);
			}
			else
			{
				command = createValidCommand(figure, board, *iter, CommandType::BEAT, kingCoordinates, figures, otherFigures);
				
				if (command)
				{
					result->push_back(command);
				}
				else if (figure->getType() == FigureType::PAWN)
				{
					wasCreated = createValidTransformationCommands(figure, board, *iter, CommandType::TRANSFORMATION, kingCoordinates, figures, otherFigures, result);
					
					if (!wasCreated)
					{
						createValidTransformationCommands(figure, board, *iter, CommandType::BEAT_TRANSFORMATION, kingCoordinates, figures, otherFigures, result);
					}
				}
			}
		}
		
//		std::cout << "*Debug* figure moves prepared...\n";
		
		return result;
	}
	
	std::list<Command*>* ChessSituationMaker::getAllSituationMoves(Situation& situation)
	{
//		std::cout << "*Debug* making situation moves\n";
		
		std::list<Command*>* result = new std::list<Command*>();
		
		std::list<Figure*>* figures = &situation.getWhiteFigures();
		std::list<Figure*>* otherFigures = &situation.getBlackFigures();
		
		if (situation.getCurrentPlayer() == FigureColor::BLACK)
		{
			figures = &situation.getBlackFigures();
			otherFigures = &situation.getWhiteFigures();
		}
		
//		std::cout << "*Debug* getting king coordinates...\n";
		
		const Coordinates& kingCoordinates = getKingFromList(figures)->getCoordinates();
		
//		std::cout << "*Debug* preparing figures moves\n";
		
		for (auto iter = figures->begin(); iter != figures->end(); iter++)
		{
			std::list<Command*>* moves = getFigurePotentialMoves(situation.getBoard(), *iter, kingCoordinates, figures, otherFigures);
			
			for (auto cmdIter = moves->begin(); cmdIter != moves->end(); cmdIter++)
			{
				result->push_back(*cmdIter);
			}
			
			delete moves;
		}
		
//		std::cout << "*Debug* situation moves prepared...\n";
		
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
