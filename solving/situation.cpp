#include "situation.h"


namespace chess_solver
{
	Situation::Situation(std::list<Figure*>& whiteFigures, std::list<Figure*>& blackFigures, Board& board, FigureColor currentPlayer) : board(board)
	{
		addListItemsToMap(whiteFigures, this->whiteFigures);
		addListItemsToMap(blackFigures, this->blackFigures);
		
		this->currentPlayer = currentPlayer;
	}
	
	Situation::Situation(Situation& other) : board(other.board)
	{
		this->currentPlayer = other.currentPlayer;
		
		for (auto iter = other.whiteFigures.begin(); iter != other.whiteFigures.end(); iter++)
		{
			this->whiteFigures.insert(*iter);
		}
		
		for (auto iter = other.blackFigures.begin(); iter != other.blackFigures.end(); iter++)
		{
			this->blackFigures.insert(*iter);
		}
	}
	
	void Situation::addListItemsToMap(std::list<Figure*>& srcList, std::map<Coordinates, FigureType>& destMap)
	{
		for (auto iter = srcList.begin(); iter != srcList.end(); iter++)
		{
			destMap.insert(std::pair<Coordinates, FigureType>((*iter)->getCoordinates(), (*iter)->getType()));
		}
	}
}
