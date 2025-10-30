#ifndef CHESS_COMMAND_EXECUTOR
#define CHESS_COMMAND_EXECUTOR

#include <list>

#include "command.h"
#include "../chess_entities/board.h"
#include "../chess_entities/figure.h"

namespace chess_solver
{
	class ChessCommandExecutor
	{
	public:
		void executeCommand(Command* command, Board& board, std::list<Figure*>* figures, std::list<Figure*>* otherFigures);
		
	private:
		void executeMove(Board& board, Figure* figure, const Coordinates& finishCoordinates);
		
		void executeTake(Board& board, Figure* figure, Figure* figureToTake, std::list<Figure*>* otherFigures);
		
		void executeTransformation(Board& board, Figure* figure, const Coordinates& finishCoordinates, FigureType newFigureType, std::list<Figure*>* figures);
		
		void executeBeatTransformation(Board& board, Figure* figure, Figure* figureToTake, FigureType newFigureType, std::list<Figure*>* figures, std::list<Figure*>* otherFigures);

		Figure* getFigureFromList(const Coordinates& coordinates, std::list<Figure*>* figures);
	};
}

#endif
