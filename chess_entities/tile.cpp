#include "tile.h"

namespace chess_solver
{
	Tile::Tile(TileColor color)
	{
		this->color = color;
		this->occupied = false;
	}
}
