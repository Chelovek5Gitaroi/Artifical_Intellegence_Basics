#ifndef VALIDATOR
#define VALIDATOR

#include <cstdlib>

#include "..\\chess_entities\\board.h"
#include "..\\chess_entities\\figure.h"
#include "..\\chess_entities\\player.h"

namespace chess_solver
{
	class MovingValidator
	{
	public:
		MovingValidator(Board* board);
		
		bool isMoveValid(Coordinates& start, Coordinates& finish, Player& firstPlayer, Player& secondPlayer);
		
	private:
		Board* board;
		
		bool isTakingValid(Figure& figure, Coordinates& finish, Player& firstPlayer, Player& secondPlayer);
		
		bool isMoveValid(Figure& figure, Coordinates& finish, Player& firstPlayer, Player& secondPlayer);
		
		bool isLineEmpty(const Coordinates& start, const Coordinates& finish);
		
		bool isHorizontalEmpty(const Coordinates& start, const Coordinates& finish);
		bool isVerticalEmpty(const Coordinates& start, const Coordinates& finish);
		bool isDiagonalEmpty(const Coordinates& start, const Coordinates& finish);
		
		bool isReachebleForPawn(Figure& pawn, const Coordinates& finish);
		bool isReachebleForPawnToTake(Figure& pawn, const Coordinates& finish);		
		
		bool isReachebleForKnight(const Coordinates& start, const Coordinates& finish);
		bool isReachebleForKing(const Coordinates& start, const Coordinates& finish);
		
		//bool isCastlingValid(bool isLong, FirstPlayer& player, SecondPlayer& finish);
		
		void climeTilesToCheck(const Coordinates& start, const Coordinates& finish);
		void unclimeTilesAfterCheck(const Coordinates& start, const Coordinates& finish);
				
		bool hasCheck(Coordinates& kingCoordinates, Player& firstPlayer, Player& secondPlayer);
		
	};
}

#endif
