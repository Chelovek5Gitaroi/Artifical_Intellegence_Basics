#include "coordinates.h"

namespace chess_solver
{
	Coordinates::Coordinates(const Coordinates& other)
	{
		//std::cout << "*Debug* copy c-tor\n";
		this->column = other.column;
		this->row = other.row;
	}
	
	Coordinates::Coordinates(char column, char row)
	{
		//std::cout << "*Debug* c-tor\n";
		this->column = column;
		this->row = row;
	}
	
	Coordinates& Coordinates::operator=(const Coordinates& other)
	{
		//std::cout << "*Debug* operator=\n";
		this->column = other.column;
		this->row = other.row;
		
		return *this;
	}
	
	std::string Coordinates::toString() const
	{
		std::string result = "";
		
		result += this->column;
		result += std::to_string(static_cast<short>(this->row));
		
		return result;
	}
	
	bool Coordinates::operator==(const Coordinates& other) const
	{
		return this->column == other.column && this->row == other.row;
	}
	
	bool Coordinates::operator!=(const Coordinates& other) const
	{
		return !(*this == other);
	}
	
	std::ostream& operator<<(std::ostream& stream, Coordinates& coordinates)
	{
		stream << coordinates.toString();
		return stream;
	}
}
