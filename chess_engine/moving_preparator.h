#ifndef PREPARATOR
#define PREPARATOR


#include <list>


#include "..\\chess_entities\\figure.h"



namespace chess_solver
{
	class MovingPreparator
	{
	public:
		std::list<Coordinates>* getPotentialPossibleCoordinates(Coordinates& coordinates, FigureType type, FigureColor color, char boardSize);
		
		
	private:
		
		std::list<Coordinates>* getPawnPotentialPossibleCoordinates(const Coordinates& coordinates, char boardSize, FigureColor figureColor);
		std::list<Coordinates>* getBishopPotentialPossibleCoordinates(const Coordinates& coordinates, char boardSize);
		std::list<Coordinates>* getKnightPotentialPossibleCoordinates(const Coordinates& coordinates, char boardSize);
		std::list<Coordinates>* getRockPotentialPossibleCoordinates(const Coordinates& coordinates, char boardSize);
		std::list<Coordinates>* getQueenPotentialPossibleCoordinates(const Coordinates& coordinates, char boardSize);
		std::list<Coordinates>* getKingPotentialPossibleCoordinates(const Coordinates& coordinates, char boardSize);
		
		// Координаты клеток в шахматной нотации
		void addRowTilesToList(std::list<Coordinates>* destList, char chessColumnFirst, char chessColumnLast, char chessRow);
		void addColumnTilesToList(std::list<Coordinates>* destList, char chessColumn, char chessRowFirst, char chessRowLast);
		void addDiagonalTilesToList(std::list<Coordinates>* destList, char chessColumnFirst, char chessColumnLast, char chessRowFirst, char chessRowLast);

		void addNextTilesInRowToList(std::list<Coordinates>* destList, char chessColumn, char chessRow, char boardSize);
		
	};
}


#endif
