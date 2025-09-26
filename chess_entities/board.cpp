#include "board.h"

namespace chess_solver
{
	Board::Board(char boardSize)
	{
		this->boardSize	= boardSize;
		
		createEmptyTileOccupancyArray();
	}
	
	Board::Board(Board& other)
	{
		this->boardSize = other.boardSize;
		
		createEmptyTileOccupancyArray();
		
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

	bool Board::getTileOccupancyByCoordinates(const Coordinates& coordinates) const
	{
		return tilesOccupancy[CoordinatesConverter::getRowIndexFromCoordinate(coordinates.getRow(), this->boardSize)][CoordinatesConverter::getColumnIndexFromCoordinate(coordinates.getColumn())];
	}
		
	bool Board::getTileOccupancyByCoordinates(char column, char row) const
	{
		return tilesOccupancy[CoordinatesConverter::getRowIndexFromCoordinate(row, this->boardSize)][CoordinatesConverter::getRowIndexFromCoordinate(column, this->boardSize)];
	}

	void Board::setOccupancyByCoordinates(const Coordinates& coordinates, bool occupancy)
	{
		this->tilesOccupancy[CoordinatesConverter::getRowIndexFromCoordinate(coordinates.getRow(), this->boardSize)][CoordinatesConverter::getColumnIndexFromCoordinate(coordinates.getColumn())] = occupancy;
	}
	
	void Board::createEmptyTileOccupancyArray()
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
