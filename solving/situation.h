#ifndef SITUATION
#define SITUATION

#include <map>
#include <list>
#include "../chess_entities/figure.h"
#include "../chess_entities/board.h"


namespace chess_solver
{
	class Situation
	{
	public:
		Situation(std::list<Figure*>& whiteFigures, std::list<Figure*>& blackFigures, Board& board, FigureColor currentPlayer);
		
		std::map<Coordinates, FigureType>& getWhiteFigures() { return whiteFigures; }
		std::map<Coordinates, FigureType>& getBlackFigures() { return blackFigures; }
		
		FigureColor getCurrentPlayer() { return currentPlayer; }
		Board& getBoard() { return board; }
		
	private:
		std::map<Coordinates, FigureType> whiteFigures;
		std::map<Coordinates, FigureType> blackFigures;
		
		FigureColor currentPlayer;
		Board board;
		
		void addListItemsToMap(std::list<Figure*>& srcList, std::map<Coordinates, FigureType>& destMap);
	};	
}

#endif
