#ifndef TILE
#define TILE

#include <iostream>



namespace chess_solver
{
	enum class TileColor
	{
		WHITE,
		BLACK	
	};
	
	class Tile
	{
	public:
		Tile(TileColor color);
		
		Tile(Tile& other);
		
		TileColor getColor() const { return color; }
		bool isOccupied() const { return occupied; }
		
		void occupy() { occupied = true; }
		void free() { occupied = false; }
		
	private:
		TileColor color;
		bool occupied;
	};
	
//	std::ostream& operator<<(std::ostream& os, Tile& tile);
	
}

#endif
