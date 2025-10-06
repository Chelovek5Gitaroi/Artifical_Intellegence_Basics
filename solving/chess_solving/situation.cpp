#include "situation.h"

#include "../../utilities/comparator.h"


namespace chess_solver
{
	Situation::Situation(std::list<Figure*>& whiteFigures, std::list<Figure*>& blackFigures, Board& board, FigureColor currentPlayer, FigureColor targetPlayer) : board(board)
	{
		this->currentPlayer = currentPlayer;
		this->targetPlayer = targetPlayer;
		
		this->potentialMoves = nullptr;
		
		insertListItemsToOtherList(blackFigures, this->blackFigures);
		insertListItemsToOtherList(whiteFigures, this->whiteFigures);
	}
	
	Situation::Situation(Situation& other) : board(other.board)
	{
		this->currentPlayer = other.currentPlayer;
		this->targetPlayer = other.targetPlayer;
		
		insertListItemsToOtherList(other.blackFigures, this->blackFigures);
		insertListItemsToOtherList(other.whiteFigures, this->whiteFigures);
		
		this->potentialMoves = nullptr;
	}
	
	Situation::~Situation()
	{
		for (auto iter = whiteFigures.begin(); iter != whiteFigures.end(); iter++)
		{
			delete *iter;
		}
		
		for (auto iter = blackFigures.begin(); iter != blackFigures.end(); iter++)
		{
			delete *iter;
		}
		
		for (auto iter = this->potentialMoves->begin(); iter != this->potentialMoves->end(); iter++)
		{
			delete *iter;
		}
		
		this->potentialMoves->clear();
		
		delete this->potentialMoves;
	}
	
//	void Situation::makeMove(Command* command)
//	{
//		Coordinates& finish = command->getFinishCoordinates();
//		
//		Figure* figure = command->getFigure();
//		Figure* figureToTake = getFigureFormList(finish, blackFigures);
//		
//		std::list<Figure*>* figures = &whiteFigures;
//		std::list<Figure*>* otherFigures = &blackFigures;
//		
//		if (currentPlayer == FigureColor::WHITE)
//		{
//			figureToTake = getFigureFormList(finish, whiteFigures);
//			figures = &blackFigures;
//			otherFigures = &whiteFigures;
//		}
//		
//		board.setOccupancyByCoordinates(figure->getCoordinates(), false);
//		CommandTransformation* transCommand = nullptr;
//		
//		switch (command->getType())
//		{
//		case CommandType::MOVE:
//			figure->move(command->getFinishCoordinates());
//			board.setOccupancyByCoordinates(finish, true);
//			break;
//			
//		case CommandType::BEAT:
//			figure->move(finish);
//			otherFigures->remove(figureToTake);
//			delete figureToTake;
//			break;
//			
//		case CommandType::TRANSFORMATION:
//			transCommand = reinterpret_cast<CommandTransformation*>(command);
//			figures->remove(figure);
//			figures->push_back(new Figure(transCommand->getNewFigureType(), figure->getColor(), finish.getColumn(), finish.getRow()));
//			delete figure;
//			break;
//			
//		case CommandType::BEAT_TRANSFORMATION:
//			transCommand = reinterpret_cast<CommandTransformation*>(command);
//			figures->remove(figure);
//			otherFigures->remove(figureToTake);
//			figures->push_back(new Figure(transCommand->getNewFigureType(), figure->getColor(), finish.getColumn(), finish.getRow()));
//			delete figure;
//			delete figureToTake;
//			break;
//		}			
//	}
	
	Figure* Situation::getFigureFormList(const Coordinates& coordinates, std::list<Figure*>& figures)
	{
		for (auto iter = figures.begin(); iter != figures.end(); iter++)
		{
			if ((*iter)->getCoordinates() == coordinates)
			{
				return *iter;
			}
		}
		
		return nullptr;
	}
	
	
	void Situation::insertListItemsToOtherList(std::list<Figure*>& sourceList, std::list<Figure*>& destList)
	{
		for (auto iter = sourceList.begin(); iter != sourceList.end(); iter++)
		{
			destList.push_back(new Figure(**iter));
		}
	}

	bool Situation::operator==(const Situation& other) const
	{
		bool result = this->targetPlayer == other.targetPlayer && this->board == other.board && this->currentPlayer == other.currentPlayer;
		
		if (result)
		{
			result = Comparator<Figure>::areListsEqual(this->whiteFigures, other.whiteFigures);
			
			if (result)
			{
				result = Comparator<Figure>::areListsEqual(this->blackFigures, other.blackFigures);
			}
		}
		
		return result;
	}

}
