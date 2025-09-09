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
		
	private:
		Board* board;
		
		bool isMoveValid(Coordinates& start, Coordinates& finish, Player& firstPlayer, Player& secondPlayer);
		
		bool isTakingValid(Coordinates& start, Coordinates& finish, Player& firstPlayer, Player& secondPlayer);
				
//		bool isPawnMoveValid(Coordinates& startCoordinates, Coordinates& finishCoordinates, Player& otherPlayer);
//		bool isKnightMoveValid(Coordinates& startCoordinates, Coordinates& finishCoordinates, Player& otherPlayer);
//		bool isBishopMoveValid(Coordinates& startCoordinates, Coordinates& finishCoordinates, Player& otherPlayer);
//		bool isRockMoveValid(Coordinates& startCoordinates, Coordinates& finishCoordinates, Player& otherPlayer);
//		bool isQueenMoveValid(Coordinates& startCoordinates, Coordinates& finishCoordinates, Player& otherPlayer);
//		bool isKingMoveValid(Coordinates& startCoordinates, Coordinates& finishCoordinates, Player& otherPlayer);
		
		bool isLineEmpty(const Coordinates& start, const Coordinates& finish);
		
		bool isHorizontalEmpty(const Coordinates& start, const Coordinates& finish);
		bool isVerticalEmpty(const Coordinates& start, const Coordinates& finish);
		bool isDiagonalEmpty(const Coordinates& start, const Coordinates& finish);
		
		bool isReachebleForKnight(const Coordinates& start, const Coordinates& finish);
		bool isReachebleForPawn(const Coordinates& start, const Coordinates& finish, Figure* figure);
		bool isReachebleForPawnToTake(const Coordinates& start, const Coordinates& finish, FigureColor color);		
		bool isReachebleForKing(const Coordinates& start, const Coordinates& finish, Player& firstPlayer, Player& secondPlayer);
		
		
//		char calcFiguresNumberOnHorizontal(const Coordinates& start, const Coordinates& finish);
//		char calcFiguresNumberOnVertical(const Coordinates& start, const Coordinates& finish);
//		char calcFiguresNumberOnDiagonal(const Coordinates& start, const Coordinates& finish);

		
		bool hasCheck(Coordinates& kingCoordinates, Player& firstPlayer, Player& secondPlayer);
		
		
		
//		std::list<Coordinates>* getPawnPotentialPossibleCoordinates(Coordinates& coordinates);
//		std::list<Coordinates>* getBishopPotentialPossibleCoordinates(Coordinates& coordinates);
//		std::list<Coordinates>* getKnightPotentialPossibleCoordinates(Coordinates& coordinates);
//		std::list<Coordinates>* getRockPotentialPossibleCoordinates(Coordinates& coordinates);
//		std::list<Coordinates>* getQueenPotentialPossibleCoordinates(Coordinates& coordinates);
//		std::list<Coordinates>* getKingPotentialPossibleCoordinates(Coordinates& coordinates);
		
	};
}

#endif
