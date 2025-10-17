#ifndef FIGURE
#define FIGURE

#include "coordinates.h"

//#include <iostream>
#include <string>

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
		
		~Figure();
		
		FigureType getType() { return type; }
		FigureColor getColor() { return color; }
		
		Coordinates& getCoordinates() { return this->coordinates; }
		
		Figure* move(const Coordinates& coordinates);
		
		bool operator==(Figure& other);
		
		std::string toString();
		
	private:
		FigureType type;
		FigureColor color;	
		
		Coordinates coordinates;
	};
	
//	std::ostream& operator<<(std::ostream& os, Figure& figure);
}

#endif
