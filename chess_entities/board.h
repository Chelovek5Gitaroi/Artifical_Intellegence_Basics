#ifndef BOARD
#define BOARD

#include "coordinates.h"
#include "tile.h"

namespace chess_solver
{
	const unsigned char MINIMAL_COLUMN_NAME = 'a';
	
	class Board
	{
	public:
		Board(unsigned char boardSize);
		~Board();
		
		unsigned char getBoardSize() const { return this->boardSize; };
		
		Tile& getTileByCoordinates(const Coordinates& coordinates);
		Tile& getTileByCoordinates(unsigned char column, unsigned char row);
			
	private:
		unsigned char boardSize;
		
		Tile*** tiles;
		
		void createTiles();
		
		unsigned char getRowIndexFromCoordinate(const unsigned char row) const;
		unsigned char getColumnIndexFromCoordinate(const unsigned char column) const;
		
	};
	
}

#endif
