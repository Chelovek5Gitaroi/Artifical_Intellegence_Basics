#include "moving_preparator.h"

namespace chess_solver
{
	std::list<Coordinates*>* MovingPreparator::getPawnPotentialPossibleCoordinates(Coordinates& coordinates, unsigned char boardSize)
	{
		
	}
	
	std::list<Coordinates*>* MovingPreparator::getBishopPotentialPossibleCoordinates(Coordinates& coordinates, unsigned char boardSize)
	{
		
	}
	
	std::list<Coordinates*>* MovingPreparator::getKnightPotentialPossibleCoordinates(Coordinates& coordinates, unsigned char boardSize)
	{
		
	}
	
	std::list<Coordinates*>* MovingPreparator::getRockPotentialPossibleCoordinates(Coordinates& coordinates, unsigned char boardSize)
	{
		std::list<Coordinates*>* result = new std::list<Coordinates*>();
		
		for (unsigned char row = coordinates.getRow() - 1; row != 0; row--)
		{
			result->push_back(new Coordinates(coordinates.getColumn(), row));
		}
		
//		for (unsigned )
//		{
//			
//		}
		
		return result;
	}
	
	std::list<Coordinates*>* MovingPreparator::getQueenPotentialPossibleCoordinates(Coordinates& coordinates, unsigned char boardSize)
	{
		
	}
	
	std::list<Coordinates*>* MovingPreparator::getKingPotentialPossibleCoordinates(Coordinates& coordinates, unsigned char boardSize)
	{
		
	}
		
}
