#ifndef BOARD
#define BOARD

#include "coordinates.h"
#include "tile.h"

namespace chess_solver
{
	class Board
	{
	public:
		static const char MINIMAL_COLUMN_NAME = 'a';	
		
		Board(char boardSize);
		~Board();
		
		unsigned char getBoardSize() const { return this->boardSize; };
		
		Tile& getTileByCoordinates(const Coordinates& coordinates);
		Tile& getTileByCoordinates(char column, char row);
		
	//	Tile& getTileByArrayCoordinates(short rowIndex, short columnIndex);
			
	private:
		char boardSize;
		
		Tile*** tiles;
		
		void createTiles();
		
		unsigned char getRowIndexFromCoordinate(const char row) const;
		unsigned char getColumnIndexFromCoordinate(const char column) const;
		
	};
	
}

#endif
