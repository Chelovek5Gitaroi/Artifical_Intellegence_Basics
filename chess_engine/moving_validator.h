#ifndef VALIDATOR
#define VALIDATOR

#include <iostream>

#include <cstdlib>

#include "..\\chess_entities\\board.h"
#include "..\\chess_entities\\figure.h"
#include "..\\chess_entities\\player.h"

#include "../utilities/command.h"

namespace chess_solver
{
	class MovingValidator final
	{
	public:
		MovingValidator() = delete;
		
		static bool isMoveValid(Command* command, std::list<Figure*>& secondPlayerFigures, Board& board);
		
		static bool hasCheck(Command* command, Board& board, const Coordinates& kingCoordinates, FigureColor otherPlayerColor, std::list<Figure*>& secondPlayerFigures);
		
	private:
		static bool isMoveValid(Figure& figure, const Coordinates& finish, const Board& board);
		static bool isTakingValid(Figure& figure, const Coordinates& finish, std::list<Figure*>& secondPlayerFigures, const Board& board);
		static bool isTransformationValid(Figure& figure, FigureType newFigureType, const Coordinates& finish, std::list<Figure*>& secondPlayerFigures, bool isBeatTransformation, const Board& board);
		
		static bool isLineEmpty(const Coordinates& start, const Coordinates& finish, const Board& board);
		
		static bool isHorizontalEmpty(const Coordinates& start, const Coordinates& finish, const Board& board);
		static bool isVerticalEmpty(const Coordinates& start, const Coordinates& finish, const Board& board);
		static bool isDiagonalEmpty(const Coordinates& start, const Coordinates& finish, const Board& board);
		
		static bool isReachebleForPawn(const Coordinates& start, const Coordinates& finish, const Board& board, FigureColor color, bool isTaking, bool isTransformation);
		
		static bool isReachebleForKnight(const Coordinates& start, const Coordinates& finish, const Board& board);
		static bool isReachebleForKing(const Coordinates& start, const Coordinates& finish, const Board& board);
		
		static Figure* getFigureFromListByCoordinates(const Coordinates& coordinates, std::list<Figure*>& figures);
	};
}

#endif
