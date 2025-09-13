#include "board.h"

namespace chess_solver
{
	Board::Board(char boardSize)
	{
		this->boardSize	= boardSize;
		this->tiles = new Tile**[boardSize];
		
		for (char i = 0; i < this->boardSize; i++)
		{
			this->tiles[i] = new Tile*[this->boardSize];
		}
		
		createTiles();
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
	
	unsigned char Board::getRowIndexFromCoordinate(const char row) const
	{
		return this->boardSize - row;
	}
	
	unsigned char Board::getColumnIndexFromCoordinate(const char column) const
	{
		return column - MINIMAL_COLUMN_NAME;
	}
	
//	Tile& Board::getTileByArrayCoordinates(short rowIndex, short columnIndex)
//	{
//		return *(tiles[rowIndex][columnIndex]);
//	}
	
	Tile& Board::getTileByCoordinates(const Coordinates& coordinates)
	{
		return *(tiles[getRowIndexFromCoordinate(coordinates.getRow())][getColumnIndexFromCoordinate(coordinates.getColumn())]);
	}
	
	Tile& Board::getTileByCoordinates(char column, char row)
	{
		return *(tiles[getRowIndexFromCoordinate(row)][getRowIndexFromCoordinate(column)]);
	}
	
//	std::ostream& operator<<(std::ostream& os, Board& board)
//	{
//		for (short row = 0; row < board.getBoardSize(); row++)
//		{
//			for (short column = 0; column < board.getBoardSize(); column++)
//			{
//				os << board.getTileByArrayCoordinates(row, column);
//			}
//			os << '\n';
//		}
//		
//		return os;
//	}
	
}
