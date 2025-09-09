#include "board.h"

namespace chess_solver
{
	Board::Board(unsigned char boardSize)
	{
		this->boardSize	= boardSize;
		this->tiles = new Tile**[boardSize];
		
		for (unsigned char i = 0; i < this->boardSize; i++)
		{
			this->tiles[i] = new Tile*[this->boardSize];
		}
		
		createTiles();
	}
	
	Board::~Board()
	{
		for (unsigned char i = 0; i < this->boardSize; i++)
		{
			for (unsigned char j = 0; j < this->boardSize; j++)
			{
				delete tiles[i][j];
			}
			
			delete[] tiles[i];
		}
		
		delete[] tiles;
	}
	
	void Board::createTiles()
	{
		for (unsigned char row = this->boardSize - 1; row >= 0; row--)
		{
			for (unsigned char column = 0; column < this->boardSize; column++)
			{
				TileColor color;
				
				if (row % 2 == 0 && column % 2 != 0)
				{
					color = TileColor::WHITE;
				}
				else
				{
					color = TileColor::BLACK;
				}
				
				this->tiles[row][column] = new Tile(color);
			}
		}
	}
	
	unsigned char Board::getRowIndexFromCoordinate(const unsigned char row) const
	{
		return this->boardSize - row;
	}
	
	unsigned char Board::getColumnIndexFromCoordinate(const unsigned char column) const
	{
		return column - MINIMAL_COLUMN_NAME;
	}
	
	Tile& Board::getTileByCoordinates(Coordinates& coordinates) const
	{
		return *(tiles[getRowIndexFromCoordinate(coordinates.getRow())][getColumnIndexFromCoordinate(coordinates.getColumn())]);
	}
	
	Tile& Board::getTileByCoordinates(unsigned char column, unsigned char row) const
	{
		return *(tiles[getRowIndexFromCoordinate(row)][getRowIndexFromCoordinate(column)]);
	}
	
}
