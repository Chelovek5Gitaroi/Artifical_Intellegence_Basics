#ifndef COORDINATES
#define COORDINATES

#include <iostream>
#include <string>
#include <cmath>

namespace chess_solver
{
	
	
	class Coordinates
	{
	public:
		Coordinates(const Coordinates& other);
		Coordinates(char column, char row);
		
		char getRow() const { return row; }
		char getColumn() const { return column; }
		
		Coordinates& operator=(const Coordinates& other);
		
		std::string toString() const;		
		
		bool operator==(const Coordinates& other) const;
		bool operator!=(const Coordinates& other) const;
		bool operator<(const Coordinates& other) const;
		bool operator>(const Coordinates& other) const;
		bool operator<=(const Coordinates& other) const;
		bool operator>=(const Coordinates& other) const;
		
	private:
		Coordinates(){}
	
		char abs() const {	return std::sqrt(row * row + column * column); }
	
		char row;
		char column;	
	};
	
	std::ostream& operator<<(std::ostream& stream, Coordinates& coordinates);
		
}

#endif
