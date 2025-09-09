#ifndef PREPARATOR
#define PREPARATOR


#include <list>

#include "..\\chess_entities\\board.h"
#include "..\\chess_entities\\figure.h"


namespace chess_solver
{
	class MovingPreparator
	{
	public:
		
	private:
		std::list<Coordinates*>* getPawnPotentialPossibleCoordinates(Coordinates& coordinates, unsigned char boardSize);
		std::list<Coordinates*>* getBishopPotentialPossibleCoordinates(Coordinates& coordinates, unsigned char boardSize);
		std::list<Coordinates*>* getKnightPotentialPossibleCoordinates(Coordinates& coordinates, unsigned char boardSize);
		std::list<Coordinates*>* getRockPotentialPossibleCoordinates(Coordinates& coordinates, unsigned char boardSize);
		std::list<Coordinates*>* getQueenPotentialPossibleCoordinates(Coordinates& coordinates, unsigned char boardSize);
		std::list<Coordinates*>* getKingPotentialPossibleCoordinates(Coordinates& coordinates, unsigned char boardSize);
	};
}


#endif
