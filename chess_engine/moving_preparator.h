#ifndef PREPARATOR
#define PREPARATOR


#include <list>

#include "..\\chess_entities\\figure.h"


namespace chess_solver
{
	class MovingPreparator final
	{
	public:
		MovingPreparator() = delete;
		
		static std::list<Coordinates>* getPotentialPossibleCoordinates(const Coordinates& coordinates, FigureType type, FigureColor color, char boardSize);
		
	private:
		
		static std::list<Coordinates>* getPawnPotentialPossibleCoordinates(const Coordinates& coordinates, char boardSize, FigureColor figureColor);
		static std::list<Coordinates>* getBishopPotentialPossibleCoordinates(const Coordinates& coordinates, char boardSize);
		static std::list<Coordinates>* getKnightPotentialPossibleCoordinates(const Coordinates& coordinates, char boardSize);
		static std::list<Coordinates>* getRockPotentialPossibleCoordinates(const Coordinates& coordinates, char boardSize);
		static std::list<Coordinates>* getQueenPotentialPossibleCoordinates(const Coordinates& coordinates, char boardSize);
		static std::list<Coordinates>* getKingPotentialPossibleCoordinates(const Coordinates& coordinates, char boardSize);
		
		// Координаты клеток в шахматной нотации
		static void addRowTilesToList(std::list<Coordinates>* destList, char chessColumnFirst, char chessColumnLast, char chessRow);
		static void addColumnTilesToList(std::list<Coordinates>* destList, char chessColumn, char chessRowFirst, char chessRowLast);
		static void addDiagonalTilesToList(std::list<Coordinates>* destList, char chessColumnFirst, char chessColumnLast, char chessRowFirst, char chessRowLast);

		static void addNextTilesInRowToList(std::list<Coordinates>* destList, char chessColumn, char chessRow, char boardSize);
		
	};
}


#endif
