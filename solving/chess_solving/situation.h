#ifndef SITUATION
#define SITUATION

#include <list>

#include "../abstract_situation.h"

#include "../../chess_entities/figure.h"
#include "../../chess_entities/board.h"


namespace chess_solver
{
	class Situation : public AbstractSituation
	{
	public:
		Situation(std::list<Figure*>& whiteFigures, std::list<Figure*>& blackFigures, Board& board, FigureColor currentPlayer, FigureColor targetPlayer);
		
		Situation(Situation& other);
		
		~Situation();
		
		std::list<Figure*>& getWhiteFigures() { return whiteFigures; }
		std::list<Figure*>& getBlackFigures() { return blackFigures; }
		
		void addFigure(Figure& figure);
		
		void removeFigure(Figure& figure);
		
		FigureColor getTargetPlayer() { return targetPlayer; }
		FigureColor getCurrentPlayer() { return currentPlayer; }
		Board& getBoard() { return board; }
		
		bool operator==(Situation& other);
		
		
	private:
		std::list<Figure*> whiteFigures;
		std::list<Figure*> blackFigures;
		
		FigureColor targetPlayer;
		FigureColor currentPlayer;
		Board board;
		
//		std::list<Figure>::iterator currentFigure;
		
		void insertListItemsToOtherList(std::list<Figure*>& sourceList, std::list<Figure*>& destList);
		
//		bool areFiguresInListsEqual(std::list<Figure*>& firstList, std::list<Figure*>& )
		
//		void addListItemsToMap(std::list<Figure*>& srcList, std::map<Coordinates, FigureType>& destMap);
	};	
}

#endif
