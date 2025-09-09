#ifndef TILE
#define TILE

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
		
		TileColor getColor() const { return color; }
		bool isOccupied() const { return occupied; }
		
		void occupy() { occupied = true; }
		void free() { occupied = false; }
		
	private:
		TileColor color;
		bool occupied;
	};
}

#endif
