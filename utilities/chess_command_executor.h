#ifndef CHESS_COMMAND_EXECUTOR
#define CHESS_COMMAND_EXECUTOR

#include <list>

//#include <iostream>


#include "command.h"
#include "../chess_entities/board.h"
#include "../chess_entities/figure.h"

namespace chess_solver
{
	class ChessCommandExecutor
	{
	public:
		void executeCommand(Command* command, Board& board, std::list<Figure*>* figures, std::list<Figure*>* otherFigures);
//		void undoCommand(Command* command, Board& board, std::list<Figure*>* figures, std::list<Figure*>* otherFigures);
		
		~ChessCommandExecutor();
		
	private:
//		Coordinates* startCoordinates = nullptr;
//		Figure* takenFigure = nullptr;
		
//		std::list<Figure*>::iterator takenFigurePosition;
//		std::list<Figure*>::iterator figurePosition;
		
		void executeMove(Board& board, Figure* figure, const Coordinates& finishCoordinates);
//		void undoMove(Board& board, Figure* figure);
		
		void executeTake(Board& board, Figure* figure, Figure* figureToTake, std::list<Figure*>* otherFigures);
//		void undoTake(Board& board, Figure* figure, std::list<Figure*>* otherFigures);
		
		void executeTransformation(Board& board, Figure* figure, const Coordinates& finishCoordinates, FigureType newFigureType, std::list<Figure*>* figures);
//		void undoTransformation(Board& board, Figure* figure, const Coordinates& finishCoordinates, std::list<Figure*>* figures);
		
		void executeBeatTransformation(Board& board, Figure* figure, Figure* figureToTake, FigureType newFigureType, std::list<Figure*>* figures, std::list<Figure*>* otherFigures);
//		void undoBeatTransformation(Board& board, Figure* figure, std::list<Figure*>* figures, std::list<Figure*>* otherFigures);
		
//		void clearStartCoordinates();
		
//		std::list<Figure*>::iterator getFigurePosition(const Coordinates& coordinates, std::list<Figure*>* figures);
		Figure* getFigureFromList(const Coordinates& coordinates, std::list<Figure*>* figures);
	};
}

#endif
