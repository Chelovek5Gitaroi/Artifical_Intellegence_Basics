#include "figure.h"

#include <iostream>

namespace chess_solver
{
	Figure::Figure(FigureType type, FigureColor color, char column, char row) : coordinates(column, row)
	{
		this->color = color;
		this->type = type;
	}
	
	Figure::Figure(Figure& other) : coordinates(other.coordinates)
	{
		this->color = other.color;
		this->type = other.type;
	}
	
	Figure* Figure::move(const Coordinates& coordinates)
	{
		this->coordinates = Coordinates(coordinates);
		
		return this;
	}

	bool Figure::operator==(Figure& other)
	{
		return this->color == other.color && this->getType() == other.type && this->coordinates == other.coordinates;
	}
	
}
