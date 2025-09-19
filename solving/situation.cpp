#include "situation.h"


namespace chess_solver
{
	Situation::Situation(std::list<Figure*>& whiteFigures, std::list<Figure*>& blackFigures, Board& board, FigureColor currentPlayer) : board(board)
	{
		addListItemsToMap(whiteFigures, this->whiteFigures);
		addListItemsToMap(blackFigures, this->blackFigures);
		
		this->currentPlayer = currentPlayer;
	}
	
	void Situation::addListItemsToMap(std::list<Figure*>& srcList, std::map<Coordinates, FigureType>& destMap)
	{
		for (auto iter = srcList.begin(); iter != srcList.end(); iter++)
		{
			destMap.insert(std::pair<Coordinates, FigureType>((*iter)->getCoordinates(), (*iter)->getType()));
		}
	}
}
