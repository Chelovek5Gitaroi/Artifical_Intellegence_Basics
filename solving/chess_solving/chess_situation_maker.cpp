#include "chess_situation_maker.h"

namespace chess_solver
{
	
	ChessSituationMaker::~ChessSituationMaker()
	{
		
	}
	
	ChessSituationMaker::SituationMoves::~SituationMoves()
	{
		for (auto iter = this->moves->begin(); iter != this->moves->end(); iter++)
		{
			delete *iter;
		}
		
		delete moves;
	}
	
	AbstractSituation* ChessSituationMaker::getNextSituation(AbstractSituation* abstractSituation)
	{
		Situation* situation = reinterpret_cast<Situation*>(abstractSituation);
		Situation* result = new Situation(*situation);
		
		std::list<Command*>* commands = situation->getPotentialMoves();
		
		Command* nextCommand = nullptr;
		
		std::list<Command*>::iterator iter = commands->begin();
		
		while (iter != commands->end() && !command)
		{
			
			
		}
		
		
//		std::list<Command*>* moves = nullptr;
//		
//		if (!hasSituation(*situation))
//		{
//			moves = getAllSituationMoves(*situation);
//			
//			this->potentialMoves.push_back(SituationMoves(*situation, moves));
//		}
//		else
//		{
//			moves = getSituationMoves(*situation);
//		}
		
//		Command* command = nullptr;
//		
//		std::list<Figure*>* secondFigures = &situation->getBlackFigures();
//		
//		if (situation->getCurrentPlayer() == FigureColor::BLACK)
//		{
//			secondFigures = &situation->getWhiteFigures();
//		}
//		
//		std::list<Command*>::iterator iter = moves->begin();
//		
//		while (iter != moves->end() && !command)
//		{
//			if (MovingValidator::isMoveValid(*iter, *secondFigures, result->getBoard()))
//			{
//				command = *iter;
//				
//				result->makeMove(command);
//			
//			}
//			
//			iter++;
//			
//			moves->pop_front();
//		}
		
		return reinterpret_cast<AbstractSituation*>(result);
	}
	
	void ChessSituationMaker::makeMove(Situation& situation, Command* command)
	{
		
	}
	
	std::list<Command*>* ChessSituationMaker::getFigurePotentialMoves(Board& board, Figure* figure)
	{
		std::list<Command*>* result = new std::list<Command*>();
		
		Coordinates startCoordinates = figure->getCoordinates();
		
		std::list<Coordinates>* coordinates = MovingPreparator::getPotentialPossibleCoordinates(startCoordinates, figure->getType(), figure->getColor(), board.getBoardSize());
		
		for (auto iter = coordinates->begin(); iter != coordinates->end(); iter++)
		{
			addAllTransformationCommandsToList(figure, *iter, *result);
			
			result->push_back(new Command(figure, *iter, CommandType::MOVE));
			result->push_back(new Command(figure, *iter, CommandType::BEAT));
		}
		
		delete coordinates;
		
		return result;
	}
	
	void ChessSituationMaker::addAllTransformationCommandsToList(Figure* figure, Coordinates& finish, std::list<Command*>& commands)
	{
		commands.push_back(new CommandTransformation(figure, finish, FigureType::KNIGHT));
		commands.push_back(new CommandTransformation(figure, finish, FigureType::KNIGHT, CommandType::BEAT_TRANSFORMATION));

		commands.push_back(new CommandTransformation(figure, finish, FigureType::BISHOP));
		commands.push_back(new CommandTransformation(figure, finish, FigureType::BISHOP, CommandType::BEAT_TRANSFORMATION));
		
		commands.push_back(new CommandTransformation(figure, finish, FigureType::ROCK));
		commands.push_back(new CommandTransformation(figure, finish, FigureType::ROCK, CommandType::BEAT_TRANSFORMATION));
		
		commands.push_back(new CommandTransformation(figure, finish, FigureType::QUEEN));
		commands.push_back(new CommandTransformation(figure, finish, FigureType::QUEEN, CommandType::BEAT_TRANSFORMATION));
	}
	
	std::list<Command*>* ChessSituationMaker::getAllSituationMoves(Situation& situation)
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
			std::list<Command*>* moves = getFigurePotentialMoves(situation.getBoard(), *iter);
			
			for (auto cmdIter = moves->begin(); cmdIter != moves->end(); cmdIter++)
			{
				result->push_back(*cmdIter);
			}
			
			delete moves;
		}
		
		return result;
	}
	
//	bool ChessSituationMaker::hasSituation(Situation& situation)
//	{
//		bool result = false;
//		
//		for (auto iter = this->allPotentialMoves.begin(); iter != this->allPotentialMoves.end() && !result; iter++)
//		{
//			result = iter->situation == situation;
//		}
//		
//		return result;
//	}
	
//	std::list<Command*>* ChessSituationMaker::getSituationMoves(Situation& situation)
//	{
//		for (auto iter = this->allPotentialMoves.begin(); iter != this->allPotentialMoves.end(); iter++)
//		{
//			if (iter->situation == situation)
//			{
//				return iter->moves;
//			}
//		}
//		
//		return nullptr;
//	}
}
