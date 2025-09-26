#ifndef PREPARATOR
#define PREPARATOR


#include <list>


//#include "..\\chess_entities\\board.h"
#include "..\\chess_entities\\figure.h"



namespace chess_solver
{
	class MovingPreparator
	{
	public:
		
	private:
		
		std::list<Coordinates>* getPawnPotentialPossibleCoordinates(Coordinates& coordinates, char boardSize, FigureColor figureColor);
		std::list<Coordinates>* getBishopPotentialPossibleCoordinates(Coordinates& coordinates, char boardSize);
		std::list<Coordinates>* getKnightPotentialPossibleCoordinates(Coordinates& coordinates, char boardSize);
		std::list<Coordinates>* getRockPotentialPossibleCoordinates(Coordinates& coordinates, char boardSize);
		std::list<Coordinates>* getQueenPotentialPossibleCoordinates(Coordinates& coordinates, char boardSize);
		std::list<Coordinates>* getKingPotentialPossibleCoordinates(Coordinates& coordinates, char boardSize);
		
		//  оординаты клеток в виде индексов в массиве
		void addRowTilesToList(std::list<Coordinates>* destList, char chessColumnFirst, char chessColumnLast, char chessRow);
		void addColumnTilesToList(std::list<Coordinates>* destList, char chessColumn, char chessRowFirst, char chessRowLast);
		void addDiagonalTilesToList(std::list<Coordinates>* destList, char chessColumnFirst, char chessColumnLast, char chessRowFirst, char chessRowLast);
	};
}


#endif
