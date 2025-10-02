#ifndef VALIDATOR
#define VALIDATOR

#include <cstdlib>
#include <map>

#include "..\\chess_entities\\board.h"
#include "..\\chess_entities\\figure.h"
#include "..\\chess_entities\\player.h"

#include "../utilities/command.h"

namespace chess_solver
{
	class MovingValidator
	{
	public:
		bool isMoveValid(const Coordinates& start, const Coordinates& finish, std::list<Figure*>& firstPlayerFigures, std::list<Figure*>& secondPlayerFigures, Board& board);
		
		bool hasCheck(const Board& board, const Coordinates& kingCoordinates, std::list<Figure*>& firstPlayerFigures, std::list<Figure*>& secondPlayerFigures);
		
		
	private:
		bool isMoveValid(Figure& figure, const Coordinates& finish, const Board& board);
		bool isTakingValid(Figure& figure, const Coordinates& finish, const Board& board);
		
		bool isLineEmpty(const Coordinates& start, const Coordinates& finish, const Board& board);
		
		bool isHorizontalEmpty(const Coordinates& start, const Coordinates& finish, const Board& board);
		bool isVerticalEmpty(const Coordinates& start, const Coordinates& finish, const Board& board);
		bool isDiagonalEmpty(const Coordinates& start, const Coordinates& finish, const Board& board);
		
		bool isReachebleForPawn(const Coordinates& start, const Coordinates& finish, const Board& board);
		bool isReachebleForPawnToTake(const Coordinates& start, const Coordinates& finish, const Board& board);
		
		bool isReachebleForKnight(const Coordinates& start, const Coordinates& finish, const Board& board);
		bool isReachebleForKing(const Coordinates& start, const Coordinates& finish, const Board& board);
		
		Figure* getFigureFromListByCoordinates(const Coordinates& coordinates, std::list<Figure*>& figures);
	};
}

#endif
