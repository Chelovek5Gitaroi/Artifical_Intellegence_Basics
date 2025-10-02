#include "situation.h"

#include "../../utilities/comparator.h"


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
		for (auto iter = whiteFigures.begin(); iter != whiteFigures.end(); iter++)
		{
			delete *iter;
		}
		
		for (auto iter = blackFigures.begin(); iter != blackFigures.end(); iter++)
		{
			delete *iter;
		}
	}
	
	void Situation::addFigure(Figure& figure)
	{
		Figure* figureCopy = new Figure(figure);
		
		if (figure.getColor() == FigureColor::WHITE)
		{
			this->whiteFigures.push_back(figureCopy);
		}
		else
		{
			this->blackFigures.push_back(figureCopy);
		}
	}
	
	void Situation::removeFigure(Figure& figure)
	{
		Figure* figureToRemove = nullptr;
		
		if (figure.getColor() == FigureColor::WHITE)
		{
			for (auto iter = whiteFigures.begin(); iter != whiteFigures.end(); iter++)
			{
				if (**iter == figure)
				{
					figureToRemove = *iter;
				}
			}
			
			if (figureToRemove)
				whiteFigures.remove(figureToRemove);
		}
		else
		{
			for (auto iter = blackFigures.begin(); iter != blackFigures.end(); iter++)
			{
				if (**iter == figure)
				{
					figureToRemove = *iter;
				}
			}
			
			if (figureToRemove)
				blackFigures.remove(figureToRemove);
		}
		
		if (figureToRemove)
			delete figureToRemove;
	}
	
	void Situation::insertListItemsToOtherList(std::list<Figure*>& sourceList, std::list<Figure*>& destList)
	{
		for (auto iter = sourceList.begin(); iter != sourceList.end(); iter++)
		{
			destList.push_back(new Figure(**iter));
		}
	}

	bool Situation::operator==(Situation& other)
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
