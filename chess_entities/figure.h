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
		
		Figure(Figure& other);
		
		FigureType getType() { return type; }
		FigureColor getColor() { return color; }
		
		Coordinates& getCoordinates() { return this->coordinates; }
		
		Figure* move(Coordinates& coordinates);
		
		bool operator==(Figure& other);
		
		
	private:
		FigureType type;
		FigureColor color;	
		
		Coordinates coordinates;
	};
}

#endif
