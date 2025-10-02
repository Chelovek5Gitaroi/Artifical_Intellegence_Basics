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
		
		Figure(const Figure& other);
		
		FigureType getType() const { return type; }
		FigureColor getColor() const { return color; }
		
		const Coordinates& getCoordinates() const { return this->coordinates; }
		
		Figure* move(Coordinates& coordinates);
		
		bool operator==(const Figure& other);
		
		
	private:
		FigureType type;
		FigureColor color;	
		
		Coordinates coordinates;
	};
}

#endif
