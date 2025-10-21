#ifndef SITUATION
#define SITUATION

#include <list>

#include "../abstract_situation.h"

#include "../../chess_entities/figure.h"
#include "../../chess_entities/board.h"
#include "../../utilities/command.h"


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
		
		FigureColor getTargetPlayer() { return targetPlayer; }
		FigureColor getCurrentPlayer() { return currentPlayer; }
		Board& getBoard() { return board; }
		
		bool operator==(const Situation& other) const;
		
		void setCurrentPlayer(FigureColor currentPlayer) { this->currentPlayer = currentPlayer; }
		
//		std::list<Command*>* getPotentialMoves() { return potentialMoves; }
		
//		void setPotentialMoves(std::list<Command*>* potentialMoves);
		
		std::string toString();
		
	private:
		std::list<Figure*> whiteFigures;
		std::list<Figure*> blackFigures;
		
		FigureColor targetPlayer;
		FigureColor currentPlayer;
		Board board;
		
//		std::list<Command*>* potentialMoves;
		
		void insertListItemsToOtherList(std::list<Figure*>& sourceList, std::list<Figure*>& destList);
		
		Figure* getFigureFormList(const Coordinates& coordinates, std::list<Figure*>& figures);
		
//		void clearPotentialMoves();
		
	};	
}

#endif
