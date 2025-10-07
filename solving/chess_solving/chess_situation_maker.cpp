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
		
		while (iter != commands->end() && !nextCommand)
		{
			if (MovingValidator::isMoveValid(*iter, *otherFigures, situation->getBoard()))
			{
				result = new Situation(*situation);
				
				nextCommand = *iter;
				
				makeMove(*situation, nextCommand, figures, otherFigures);
				
				if (MovingValidator::hasCheck(situation->getBoard(), getKingFromList(figures)->getCoordinates(), *otherFigures))
				{
					delete result;
					result = nullptr;
				}
				else
				{
					result->setPotentialMoves(getAllSituationMoves(*result));
				}
			}
			
			iter++;
			commands->pop_front();
		}
		
		return result;
	}
	
	void ChessSituationMaker::prepareStartSituationMoves(Situation* startSituation)
	{
		startSituation->setPotentialMoves(getAllSituationMoves(*startSituation));
	}
	
	void ChessSituationMaker::makeMove(Situation& situation, Command* command, std::list<Figure*>* firstPlayerFigures, std::list<Figure*>* secondPlayerFigures)
	{
		Coordinates& finish = command->getFinishCoordinates();
		
		Figure* figure = command->getFigure();
		
		situation.getBoard().setOccupancyByCoordinates(figure->getCoordinates(), false);
		CommandTransformation* transCommand = nullptr;
		
		Figure* figureToTake = nullptr;
		
		switch (command->getType())
		{
		case CommandType::MOVE:
			makeMove(figure, finish, situation.getBoard());
			break;
			
		case CommandType::BEAT:
			figureToTake = getFigureFromList(finish, secondPlayerFigures);
			makeTaking(figure, finish, figureToTake, situation.getBoard(), secondPlayerFigures);
			break;
			
		case CommandType::TRANSFORMATION:
			transCommand = reinterpret_cast<CommandTransformation*>(command);
			makeTransformation(figure, finish, situation.getBoard(), transCommand->getNewFigureType(), firstPlayerFigures);
			break;
			
		case CommandType::BEAT_TRANSFORMATION:
			figureToTake = getFigureFromList(finish, secondPlayerFigures);
			transCommand = reinterpret_cast<CommandTransformation*>(command);
			makeBeatTransformation(figure, finish, figureToTake, situation.getBoard(), transCommand->getNewFigureType(), firstPlayerFigures, secondPlayerFigures);
			break;
		}
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
	
	void ChessSituationMaker::makeMove(Figure* figure, const Coordinates& finishCoordinates, Board& board)
	{
		board.setOccupancyByCoordinates(figure->getCoordinates(), false);
		figure->move(finishCoordinates);
		board.setOccupancyByCoordinates(finishCoordinates, true);
	}

	void ChessSituationMaker::makeTaking(Figure* figure, const Coordinates& finishCoordinates, Figure* figureToTake, Board& board, std::list<Figure*>* secondPlayerFigures)
	{
		makeMove(figure, finishCoordinates, board);
		
		secondPlayerFigures->remove(figureToTake);
		delete figureToTake;
		figureToTake = nullptr;
	}
	
	void ChessSituationMaker::makeTransformation(Figure* figure, const Coordinates& finishCoordinates, Board& board, FigureType newFigureType, std::list<Figure*>* figures)
	{
		board.setOccupancyByCoordinates(figure->getCoordinates(), false);
		
		figures->remove(figure);
		figures->push_back(new Figure(newFigureType, figure->getColor(), finishCoordinates.getColumn(), finishCoordinates.getRow()));
		
		delete figure;
		figure = nullptr;
	}
	
	void ChessSituationMaker::makeBeatTransformation(Figure* figure, const Coordinates& finishCoordinates, Figure* figureToTake, Board& board, FigureType newFigureType,
		std::list<Figure*>* figures, std::list<Figure*>* secondPlayerFigures)
	{
		makeTaking(figure, finishCoordinates, figureToTake, board, secondPlayerFigures);
		makeTransformation(figure, finishCoordinates, board, newFigureType, figures);
	}

	Figure* ChessSituationMaker::getFigureFromList(const Coordinates& coordinates, std::list<Figure*>* figures)
	{
		for (auto iter = figures->begin(); iter != figures->end(); iter++)
		{
			if ((*iter)->getCoordinates() == coordinates)
			{
				return *iter;
			}
		}
		
		return nullptr;
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
