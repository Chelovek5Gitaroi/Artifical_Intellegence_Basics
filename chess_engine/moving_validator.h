#ifndef VALIDATOR
#define VALIDATOR

#include <fstream>

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
		
		static bool isMoveValid(Command* command, std::list<Figure*>& firstPlayerFigures, std::list<Figure*>& secondPlayerFigures, Board& board, std::ofstream& fout);
		
		static bool hasCheck(Command* command, Board& board, const Coordinates& kingCoordinates, std::list<Figure*>& firstPlayerFigures, std::list<Figure*>& secondPlayerFigures, std::ofstream& fout);
		
		static bool hasCheck(Board& board, const Coordinates& kingCoordinates, std::list<Figure*>& firstPlayerFigures, std::list<Figure*>& secondPlayerFigures, std::ofstream& fout);
		
	private:
		static bool isMoveValid(Figure& figure, const Coordinates& finish, const Board& board, std::ofstream& fout);
		static bool isTakingValid(Figure& figure, const Coordinates& finish, std::list<Figure*>& secondPlayerFigures, const Board& board, std::ofstream& fout);
		static bool isTransformationValid(Figure& figure, FigureType newFigureType, const Coordinates& finish,
			std::list<Figure*>& secondPlayerFigures, bool isBeatTransformation, const Board& board, std::ofstream& fout);
		
		static bool isLineEmpty(const Coordinates& start, const Coordinates& finish, const Board& board, std::ofstream& fout);
		
		static bool isHorizontalEmpty(const Coordinates& start, const Coordinates& finish, const Board& board, std::ofstream& fout);
		static bool isVerticalEmpty(const Coordinates& start, const Coordinates& finish, const Board& board, std::ofstream& fout);
		static bool isDiagonalEmpty(const Coordinates& start, const Coordinates& finish, const Board& board, std::ofstream& fout);
		
		static bool isReachebleForPawn(const Coordinates& start, const Coordinates& finish, const Board& board, FigureColor color, bool isTaking, bool isTransformation, std::ofstream& fout);
		
		static bool isReachebleForKnight(const Coordinates& start, const Coordinates& finish, const Board& board, std::ofstream& fout);
		static bool isReachebleForKing(const Coordinates& start, const Coordinates& finish, const Board& board, std::ofstream& fout);
		
		static Figure* getFigureFromListByCoordinates(const Coordinates& coordinates, std::list<Figure*>& figures, std::ofstream& fout);
	};
}

#endif
