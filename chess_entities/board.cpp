#include "board.h"

namespace chess_solver
{
	std::string Board::toString() const
	{
		std::string result;
		
		for (short row = 0; row < this->boardSize; row++)
		{
			for (short col = 0; col < this->boardSize; col++)
			{
				if (this->tilesOccupancy[row][col])
				{
					result += '+';
				}
				else
				{
					result += '-';
				}
			}
			
			result += '\n';
		}
		
		return result;
	}
	
	Board::Board(char boardSize)
	{
		this->boardSize	= boardSize;
		
		createEmptyTileOccupancyArray();
	}
	
	Board::Board(const Board& other)
	{
		this->boardSize = other.boardSize;
		
		createEmptyTileOccupancyArray();
		
		for (char row = 0; row < this->boardSize; row++)
		{
			for (char column = 0; column < this->boardSize; column++)
			{
				this->tilesOccupancy[row][column] = other.tilesOccupancy[row][column];
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
		return tilesOccupancy[CoordinatesConverter::getRowIndexFromCoordinate(row, this->boardSize)][CoordinatesConverter::getColumnIndexFromCoordinate(column)];
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
	
	bool Board::operator==(const Board& other) const
	{
		bool result = true;
		
		if (this->boardSize != other.boardSize)
		{
			result = false;
		}
		else
		{
			for (char row = 0; row < this->boardSize && result; row++)
			{
				for (char column = 0; column < this->boardSize && result; column++)
				{
					result = this->tilesOccupancy[row][column] == other.tilesOccupancy[row][column];
				}
			}
		}
		
		return result;
	}
	
}


