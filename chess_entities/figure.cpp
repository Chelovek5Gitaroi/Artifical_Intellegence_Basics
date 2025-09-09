#include "figure.h"

#include <iostream>

namespace chess_solver
{
	Figure::Figure(FigureType type, FigureColor color, unsigned char column, unsigned char row) : coordinates(column, row)
	{
		//std::cout << "*Debug* figure c-tor\n";
		this->color = color;
		this->type = type;
		
		this->moved = false;
	}
	
	Figure* Figure::move(Coordinates& coordinates)
	{
		this->coordinates = coordinates;
		
		this->moved = true;
		
		return this;
	}

	bool Figure::operator==(const Figure& other)
	{
		return this->color == other.color && this->getType() == other.type && this->coordinates == other.coordinates;
		
	}
	
}
