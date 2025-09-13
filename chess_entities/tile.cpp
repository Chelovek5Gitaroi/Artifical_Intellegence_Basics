#include "tile.h"

namespace chess_solver
{
	Tile::Tile(TileColor color)
	{
		this->color = color;
		this->occupied = false;
	}
	
	
//	std::ostream& operator<<(std::ostream& os, Tile& tile)
//	{
//		if (tile.getColor() == TileColor::WHITE)
//		{
//			os << 'X';
//		}
//		else
//		{
//			os << '.';
//		}
//		
//		return os;
//	}
}
