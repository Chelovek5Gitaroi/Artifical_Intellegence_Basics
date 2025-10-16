#include "figure.h"

#include <iostream>

namespace chess_solver
{
	Figure::~Figure()
	{
		std::cout << "*debug* deleting figure: ";
		
//		if (color == FigureColor::WHITE)
//		{
//			std::cout << "white ";
//		}
//		else
//		{
//			std::cout << "black ";
//		}
//		
//		switch (type)
//		{
//		case FigureType::PAWN:
//			std::cout << "pawn";
//			break;
//		case FigureType::BISHOP:
//			std::cout << "bishop";
//			break;
//		case FigureType::KNIGHT:
//			std::cout << "knight";
//			break;
//		case FigureType::ROCK:
//			std::cout << "rock";
//			break;
//		case FigureType::QUEEN:
//			std::cout << "queen";
//			break;
//		case FigureType::KING:
//			std::cout << "king";
//			break;
//		}
//		
//		std::cout << " " << coordinates << "\n";
	}
	
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
	
	std::string Figure::toString()
	{
		std::string result;
		
		if (color == FigureColor::WHITE)
		{
			result += "white ";
		}
		else
		{
			result += "black ";
		}
		
		switch (type)
		{
		case FigureType::PAWN:
			result += "pawn";
			break;
		case FigureType::BISHOP:
			result += "bishop";
			break;
		case FigureType::KNIGHT:
			result += "knight";
			break;
		case FigureType::ROCK:
			result += "rock";
			break;
		case FigureType::QUEEN:
			result += "queen";
			break;
		case FigureType::KING:
			result += "king";
			break;
		}
		
		result += " " + coordinates.toString();
		
		return result;
	}
//	std::ostream& operator<<(std::ostream& os, Figure& figure)
//	{
//		
//	}
}
