#ifndef FIGURE
#define FIGURE

#include "coordinates.h"

namespace chess_solver
{
	enum class FigureColor
	{
		WHITE,
		BLACK
	};
	
	enum class FigureType
	{
		PAWN,
		KNIGHT,
		BISHOP,
		ROCK,
		QUEEN,
		KING		
	};
	
	class Figure
	{
	public:
		Figure(FigureType type, FigureColor color, char column, char row);
		
		FigureType getType() const { return type; }
		FigureColor getColor() const { return color; }
		
		const Coordinates& getCoordinates() const { return this->coordinates; }
		
		
		bool wasMoved() { return moved;}
		
		Figure* move(Coordinates& coordinates);
		
		bool operator==(const Figure& other);
		
		
	private:
		FigureType type;
		FigureColor color;	
		
		bool moved;
		
		Coordinates coordinates;
	};
}

#endif
