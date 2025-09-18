#include "board.h"

namespace chess_solver
{
	Board::Board(char boardSize)
	{
		this->boardSize	= boardSize;
		
		prepareEmptyTilesArray();
		
		createTiles();
	}
	
	Board::Board(Board& other)
	{
		this->boardSize = other.boardSize;
		
		prepareEmptyTilesArray();
		
		for (char row = 0; row < this->boardSize; row++)
		{
			for (char column = 0; column < this->boardSize; column++)
			{
				this->tiles[row][column] = new Tile(*other.tiles[row][column]);
			}
		}
	}
	
	Board::~Board()
	{
		for (char i = 0; i < this->boardSize; i++)
		{
			for (char j = 0; j < this->boardSize; j++)
			{
				delete tiles[i][j];
			}
			
			delete[] tiles[i];
		}
		
		delete[] tiles;
	}
	
	void Board::createTiles()
	{
		for (char row = 0; row < this->boardSize; row++)
		{
			for (char column = 0; column < this->boardSize; column++)
			{
				TileColor color;
				
				if ((row % 2 == 0 && column % 2 == 0) || (row % 2 != 0 && column % 2 != 0))
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
	
	char Board::getRowIndexFromCoordinate(const char row) const
	{
		return this->boardSize - row;
	}
	
	char Board::getColumnIndexFromCoordinate(const char column) const
	{
		return column - MINIMAL_COLUMN_NAME;
	}

	Tile& Board::getTileByCoordinates(const Coordinates& coordinates)
	{
		return *(tiles[getRowIndexFromCoordinate(coordinates.getRow())][getColumnIndexFromCoordinate(coordinates.getColumn())]);
	}
	
	Tile& Board::getTileByCoordinates(char column, char row)
	{
		return *(tiles[getRowIndexFromCoordinate(row)][getRowIndexFromCoordinate(column)]);
	}
	
	void Board::prepareEmptyTilesArray()
	{
		this->tiles = new Tile**[boardSize];
		
		for (char i = 0; i < this->boardSize; i++)
		{
			this->tiles[i] = new Tile*[this->boardSize];
		}
	}
}
