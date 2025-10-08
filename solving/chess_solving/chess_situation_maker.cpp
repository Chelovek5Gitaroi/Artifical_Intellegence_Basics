#include "chess_situation_maker.h"

namespace chess_solver
{
	AbstractSituation* ChessSituationMaker::getNextSituation(AbstractSituation* abstractSituation)
	{
		Situation* situation = reinterpret_cast<Situation*>(abstractSituation);
		Situation* result = nullptr;
		
		std::list<Command*>* commands = situation->getPotentialMoves();
		
		Command* nextCommand = nullptr;
		
		std::list<Figure*>* figures = &situation->getWhiteFigures();
		std::list<Figure*>* otherFigures = &situation->getBlackFigures();
		
		if (situation->getCurrentPlayer() == FigureColor::BLACK)
		{
			figures = &situation->getBlackFigures();
			otherFigures = &situation->getWhiteFigures();
		}
		
		std::list<Command*>::iterator iter = commands->begin();
		
//		while (iter != commands->end() && !nextCommand)
//		{
//			if (MovingValidator::isMoveValid(*iter, *otherFigures, situation->getBoard()))
//			{
//				result = new Situation(*situation);
//				
//				nextCommand = *iter;
//				
//				
//				
////				makeMove(*situation, nextCommand, figures, otherFigures);
//				
////				if (MovingValidator::hasCheck(situation->getBoard(), getKingFromList(figures)->getCoordinates(), *otherFigures))
////				{
////					delete result;
////					result = nullptr;
////				}
//////				else
////				{
//////					result->setPotentialMoves(getAllSituationMoves(*result));
////				}
//			}
//			
//			iter++;
//			commands->pop_front();
//		}
		
		return result;
	}
	
	void ChessSituationMaker::prepareStartSituationMoves(Situation* startSituation)
	{
//		startSituation->setPotentialMoves(getAllSituationMoves(*startSituation));
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
	
	std::list<Command*>* ChessSituationMaker::getFigurePotentialMoves(Board& board, Figure* figure, const Coordinates& kingCoordinates, std::list<Figure*>* figures, std::list<Figure*>* otherFigures)
	{
		std::list<Command*>* result = new std::list<Command*>();
		
		Coordinates startCoordinates = figure->getCoordinates();
		
		FigureColor otherColor = FigureColor::BLACK;
		
		Figure* king = getKingFromList(figures);
		
		if (figure->getColor() == FigureColor::BLACK)
		{
			otherColor = FigureColor::WHITE;
		}
		
		std::list<Coordinates>* coordinates = MovingPreparator::getPotentialPossibleCoordinates(startCoordinates, figure->getType(), figure->getColor(), board.getBoardSize());
		
		Command* command = nullptr;
		bool isValid = false;
		
		for (auto iter = coordinates->begin(); iter != coordinates->end(); iter++)
		{
//			command = new Command(figure, *iter, CommandType::MOVE);
			
//			isValid = MovingValidator::isMoveValid(command, *otherFigures, board);
//			if (isValid)
//			{
//				executor.executeCommand(command, board, figures, otherFigures);
//				
////				isValid = MovingValidator::hasCheck(board, king->getCoordinates(), otherColor, otherFigures);
//				
//				if (isValid)
//				{
//					result->push_back(command);
//				}
//				else
//				{
//					executor.undoCommand(command, board, figures, otherFigures);
//					delete command;
//				}
//			}
//			else
//			{
//				delete command;
//			}
			
//			if (!isValid)
//			{
//				command = new Command(figure, *iter, CommandType::BEAT);
//				
//				isValid = MovingValidator::isMoveValid(command, *otherFigures, board);
//				if (isValid)
//				{
//					executor.executeCommand(command, board, figures, otherFigures);
//				
////					isValid = MovingValidator::hasCheck(board, king->getCoordinates(), otherColor, otherFigures);
//				
//					if (isValid)
//					{
//						result->push_back(command);
//					}
//					else
//					{
//						executor.undoCommand(command, board, figures, otherFigures);
//						delete command;
//					}
//				}
//			}
		}
		
		delete coordinates;
		
		return result;
	}
	
	
	
	
//	void ChessSituationMaker::addAllTransformationCommandsToList(Figure* figure, Coordinates& finish, std::list<Command*>& commands, const Coordinates& kingCoordinates, std::list<Figure*>* otherFigures)
//	{
//		
//		
//		
////		commands.push_back(new CommandTransformation(figure, finish, FigureType::KNIGHT));
////		commands.push_back(new CommandTransformation(figure, finish, FigureType::KNIGHT, CommandType::BEAT_TRANSFORMATION));
////
////		commands.push_back(new CommandTransformation(figure, finish, FigureType::BISHOP));
////		commands.push_back(new CommandTransformation(figure, finish, FigureType::BISHOP, CommandType::BEAT_TRANSFORMATION));
////		
////		commands.push_back(new CommandTransformation(figure, finish, FigureType::ROCK));
////		commands.push_back(new CommandTransformation(figure, finish, FigureType::ROCK, CommandType::BEAT_TRANSFORMATION));
////		
////		commands.push_back(new CommandTransformation(figure, finish, FigureType::QUEEN));
////		commands.push_back(new CommandTransformation(figure, finish, FigureType::QUEEN, CommandType::BEAT_TRANSFORMATION));
//	}
	
	std::list<Command*>* ChessSituationMaker::getAllSituationMoves(Situation& situation, const Coordinates& kingCoordinates, std::list<Figure*>* otherFigures)
	{
		std::list<Command*>* result = new std::list<Command*>();
		
		std::list<Figure*>::iterator iter;
		std::list<Figure*>::iterator iterLast;
		
		if (situation.getCurrentPlayer() == FigureColor::WHITE)
		{
			iter = situation.getWhiteFigures().begin();
			iterLast = situation.getWhiteFigures().end();
		}
		else
		{
			iter = situation.getBlackFigures().begin();
			iterLast = situation.getBlackFigures().end();
		}
		
		for (iter; iter != iterLast; iter++)
		{
//			std::list<Command*>* moves = getFigurePotentialMoves(situation.getBoard(), *iter);
//			
//			for (auto cmdIter = moves->begin(); cmdIter != moves->end(); cmdIter++)
//			{
//				result->push_back(*cmdIter);
//			}
			
//			delete moves;
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
