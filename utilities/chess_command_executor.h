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
		void executeCommand(Command* command, Board& board, Figure* figure, std::list<Figure*>* figures, std::list<Figure*>* otherFigures);
		void undoCommand(Command* command, Board& board, Figure* figure, std::list<Figure*>* figures, std::list<Figure*>* otherFigures);
		
		ChessCommandExecutor();
		~ChessCommandExecutor();
		
	private:
		Figure* takenFigure = nullptr;
		Coordinates* startCoordinates = nullptr;
		
		
		void executeMove(Board& board, Figure* figure, const Coordinates& finishCoordinates);
		void undoMove(Board& board, Figure* figure);
		
		void executeTake(Board& board, Figure* figure, Figure* figureToTake, std::list<Figure*>* otherFigures);
		void undoTake(Command* command, Board& board, Figure* figure, Figure* figureToTake, std::list<Figure*>* otherFigures);
		
		void executeTransformation(CommandTransformation* command, Board& board, Figure* figure, std::list<Figure*>* figures);
		void undoTransformation(CommandTransformation* command, Board& board, Figure* figure, std::list<Figure*>* figures);
		
		void executeBeatTransformation(CommandTransformation* command, Board& board, Figure* figure, Figure* figureToTake, std::list<Figure*>* figures, std::list<Figure*>* otherFigures);
		void undoBeatTransformation(CommandTransformation* command, Board& board, Figure* figure, Figure* figureToTake, std::list<Figure*>* figures, std::list<Figure*>* otherFigures);
		
		void clearStartCoordinates();
	};
}

#endif
