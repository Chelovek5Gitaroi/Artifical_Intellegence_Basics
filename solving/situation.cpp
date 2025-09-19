#include "situation.h"


namespace chess_solver
{
	Situation::Situation(std::list<Figure*>& whiteFigures, std::list<Figure*>& blackFigures, Board& board, FigureColor currentPlayer) : board(board)
	{
		for (auto iter = whiteFigures.begin(); iter != whiteFigures.end(); iter++)
		{
			this->whiteFigures.insert(std::pair<Coordinates, FigureType>((*iter)->getCoordinates(), (*iter)->getType()));
		}
	}
}
