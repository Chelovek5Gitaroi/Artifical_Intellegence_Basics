#ifndef VALIDATOR
#define VALIDATOR

#include <cstdlib>
#include <map>

#include "..\\chess_entities\\board.h"
#include "..\\chess_entities\\figure.h"
#include "..\\chess_entities\\player.h"

namespace chess_solver
{
	class MovingValidator
	{
	public:
//		MovingValidator(Board* board);
		
//		bool isMoveValid(Coordinates& start, Coordinates& finish, std::map<Coordinates, FigureType>& firstPlayerFigures, std::map<Coordinates, FigureType>& secondPlayerFigures);
		
	private:
//		Board* board;
		
//		bool isTakingValid(Figure& figure, Coordinates& finish, std::map<Coordinates, FigureType>& firstPlayerFigures, std::map<Coordinates, FigureType>& secondPlayerFigures);
		
//		bool isMoveValid(Figure& figure, Coordinates& finish, std::map<Coordinates, FigureType>& firstPlayerFigures, std::map<Coordinates, FigureType>& secondPlayerFigures);
		
		bool isLineEmpty(const Coordinates& start, const Coordinates& finish);
		
		bool isHorizontalEmpty(const Coordinates& start, const Coordinates& finish);
		bool isVerticalEmpty(const Coordinates& start, const Coordinates& finish);
		bool isDiagonalEmpty(const Coordinates& start, const Coordinates& finish);
		
		bool isReachebleForPawn(Figure& pawn, const Coordinates& finish);
		bool isReachebleForPawnToTake(Figure& pawn, const Coordinates& finish);		
		
		bool isReachebleForKnight(const Coordinates& start, const Coordinates& finish);
		bool isReachebleForKing(const Coordinates& start, const Coordinates& finish);
		
		//bool isCastlingValid(bool isLong, FirstPlayer& player, SecondPlayer& finish);
		
//		void climeTilesToCheck(const Coordinates& start, const Coordinates& finish);
//		void unclimeTilesAfterCheck(const Coordinates& start, const Coordinates& finish);
				
		bool hasCheck(const Coordinates& kingCoordinates, Player& firstPlayer, Player& secondPlayer);
		
	};
}

#endif
