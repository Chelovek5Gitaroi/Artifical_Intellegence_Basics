#include "tile.h"

namespace chess_solver
{
	Tile::Tile(TileColor color)
	{
		this->color = color;
		this->occupied = false;
	}
	
	Tile::Tile(Tile& other)
	{
		this->color = other.color;
		this->occupied = other.occupied;		
	}
}
