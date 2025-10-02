#ifndef SITUATION
#define SITUATION

#include <list>

#include "abstract_situation.h"

#include "../chess_entities/figure.h"
#include "../chess_entities/board.h"


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
		
		Figure* getAddedFigure() { return addedFigure; }
		void addFigure(Figure* figure);
		
		FigureColor getTargetPlayer() { return targetPlayer; }
		FigureColor getCurrentPlayer() { return currentPlayer; }
		Board& getBoard() { return board; }
		
	private:
		std::list<Figure*> whiteFigures;
		std::list<Figure*> blackFigures;
		
		Figure* addedFigure;
		
		FigureColor targetPlayer;
		FigureColor currentPlayer;
		Board board;
		
		std::list<Figure*>::iterator currentFigure;
		
		void insertListItemsToOtherList(std::list<Figure*>& sourceList, std::list<Figure*>& destList);
		
//		void addListItemsToMap(std::list<Figure*>& srcList, std::map<Coordinates, FigureType>& destMap);
	};	
}

#endif
