#include "situation.h"


namespace chess_solver
{
	Situation::Situation(std::list<Figure*>& whiteFigures, std::list<Figure*>& blackFigures, Board& board, FigureColor currentPlayer, FigureColor targetPlayer) : board(board)
	{
		this->currentPlayer = currentPlayer;
		this->targetPlayer = targetPlayer;
		
		insertListItemsToOtherList(blackFigures, this->blackFigures);
		insertListItemsToOtherList(whiteFigures, this->whiteFigures);
	}
	
	Situation::Situation(Situation& other) : board(other.board)
	{
		this->currentPlayer = other.currentPlayer;
		this->targetPlayer = other.targetPlayer;
		
		insertListItemsToOtherList(other.blackFigures, this->blackFigures);
		insertListItemsToOtherList(other.whiteFigures, this->whiteFigures);
	}
	
	Situation::~Situation()
	{
		delete addedFigure;
	}
	
	void Situation::addFigure(Figure* figure)
	{
		this->addedFigure = figure;
		
		if (figure->getColor() == FigureColor::WHITE)
		{
			this->whiteFigures.push_back(figure);
		}
		else
		{
			this->blackFigures.push_back(figure);
		}
	}
	
	void Situation::insertListItemsToOtherList(std::list<Figure*>& sourceList, std::list<Figure*>& destList)
	{
		for (auto iter = sourceList.begin(); iter != sourceList.end(); iter++)
		{
			destList.push_back(*iter);
		}
	}

}
