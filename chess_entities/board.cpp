#include "board.h"

namespace chess_solver
{
	Board::Board(char boardSize)
	{
		this->boardSize	= boardSize;
		
		createEmptyTileBusynessArray();
	}
	
	Board::Board(Board& other)
	{
		this->boardSize = other.boardSize;
		
		createEmptyTileBusynessArray();
		
		for (char row = 0; row < this->boardSize; row++)
		{
			for (char column = 0; column < this->boardSize; column++)
			{
				if (other.tilesOccupancy[row][column])
				{
					this->tilesOccupancy[row][column] = true;
				}
			}
		}
	}
	
	Board::~Board()
	{
		for (char i = 0; i < this->boardSize; i++)
		{	
			delete[] tilesOccupancy[i];
		}
		
		delete[] tilesOccupancy;
	}
	
//	void Board::createTiles()
//	{
//		for (char row = 0; row < this->boardSize; row++)
//		{
//			for (char column = 0; column < this->boardSize; column++)
//			{
//				TileColor color;
//				
//				if ((row % 2 == 0 && column % 2 == 0) || (row % 2 != 0 && column % 2 != 0))
//				{
//					color = TileColor::WHITE;
//				}
//				else
//				{
//					color = TileColor::BLACK;
//				}
//				
//				//this->tiles[row][column] = new Tile(color);
//			}
//		}
//	}
//	
	char Board::getRowIndexFromCoordinate(const char row) const
	{
		return this->boardSize - row;
	}
	
	char Board::getColumnIndexFromCoordinate(const char column) const
	{
		return column - MINIMAL_COLUMN_NAME;
	}

	bool Board::getTileOccupancyByCoordinates(const Coordinates& coordinates)
	{
		return tilesOccupancy[getRowIndexFromCoordinate(coordinates.getRow())][getColumnIndexFromCoordinate(coordinates.getColumn())];
	}
		
	bool Board::getTileOccupancyByCoordinates(char column, char row)
	{
		return tilesOccupancy[getRowIndexFromCoordinate(row)][getRowIndexFromCoordinate(column)];
	}

	void Board::setOccupancyByCoordinates(const Coordinates& coordinates, bool occupancy)
	{
		this->tilesOccupancy[getRowIndexFromCoordinate(coordinates.getRow())][getColumnIndexFromCoordinate(coordinates.getColumn())] = occupancy;
	}

//	Tile& Board::getTileByCoordinates(const Coordinates& coordinates)
//	{
//		return *(tiles[getRowIndexFromCoordinate(coordinates.getRow())][getColumnIndexFromCoordinate(coordinates.getColumn())]);
//	}
//	
//	Tile& Board::getTileByCoordinates(char column, char row)
//	{
//		return *(tiles[getRowIndexFromCoordinate(row)][getRowIndexFromCoordinate(column)]);
//	}
	
	void Board::createEmptyTileBusynessArray()
	{
		this->tilesOccupancy = new bool*[this->boardSize];
		
		for (char row = 0; row < this->boardSize; row++)
		{
			this->tilesOccupancy[row] = new bool[this->boardSize];
			
			for (char column = 0; column < this->boardSize; column++)
			{
				this->tilesOccupancy[row][column] = false;
			}
			
		}
	}
}
