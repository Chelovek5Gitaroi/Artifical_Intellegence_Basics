#include "coordinates.h"

namespace chess_solver
{
	Coordinates& Coordinates::operator=(const Coordinates& other)
	{
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
	
	bool Coordinates::operator==(const Coordinates& other)
	{
		return this->column == other.column && this->row == other.row;
	}
	
	bool Coordinates::operator!=(const Coordinates& other)
	{
		return !(*this == other);
	}
	
	bool Coordinates::operator<(const Coordinates& other)
	{
		return abs() < other.abs();
	}
	
	bool Coordinates::operator>(const Coordinates& other)
	{
		abs() > other.abs();
	}
	
	bool Coordinates::operator<=(const Coordinates& other)
	{
		return *this < other || *this == other;
	}
	
	bool Coordinates::operator>=(const Coordinates& other)
	{
		return *this > other || *this == other;
	}
	
	std::ostream& operator<<(std::ostream& stream, const Coordinates& coordinates)
	{
		stream << coordinates.toString();
		return stream;
	}
}
