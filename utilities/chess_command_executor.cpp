#include "chess_command_executor.h"

namespace chess_solver
{
	ChessCommandExecutor::~ChessCommandExecutor()
	{
		this->takenFigure = nullptr;
		
		if (this->startCoordinates)
		{
			delete startCoordinates;
			this->startCoordinates = nullptr;
		}
	}
	
	void ChessCommandExecutor::executeCommand(Command* command, Board& board, Figure* figure, std::list<Figure*>* figures, std::list<Figure*>* otherFigures)
	{
		
	}
	
	void ChessCommandExecutor::undoCommand(Command* command, Board& board, Figure* figure, std::list<Figure*>* figures, std::list<Figure*>* otherFigures)
	{
		
	}
	
	void ChessCommandExecutor::executeMove(Board& board, Figure* figure, const Coordinates& finishCoordinates)
	{
		clearStartCoordinates();
		
		this->startCoordinates = new Coordinates(figure->getCoordinates());
		
		board.setOccupancyByCoordinates(figure->getCoordinates(), false);
		board.setOccupancyByCoordinates(finishCoordinates, true);
		
		figure->move(finishCoordinates);
	}
	
	void ChessCommandExecutor::undoMove(Board& board, Figure* figure)
	{
		board.setOccupancyByCoordinates(*startCoordinates, true);
		board.setOccupancyByCoordinates(figure->getCoordinates(), false);
		
		figure->move(*startCoordinates);
	}
	
	void ChessCommandExecutor::executeTake(Board& board, Figure* figure, Figure* figureToTake, std::list<Figure*>* otherFigures)
	{
		this->takenFigure = figureToTake;
		
		otherFigures->remove(figureToTake);
		
		executeMove(board, figure, figureToTake->getCoordinates());
	}
	
	void ChessCommandExecutor::undoTake(Command* command, Board& board, Figure* figure, Figure* figureToTake, std::list<Figure*>* otherFigures)
	{
		
	}
	
	void ChessCommandExecutor::executeTransformation(CommandTransformation* command, Board& board, Figure* figure, std::list<Figure*>* figures)
	{
		
	}
	
	void ChessCommandExecutor::undoTransformation(CommandTransformation* command, Board& board, Figure* figure, std::list<Figure*>* figures)
	{
		
	}
	
	void ChessCommandExecutor::executeBeatTransformation(CommandTransformation* command, Board& board, Figure* figure, Figure* figureToTake, std::list<Figure*>* figures, std::list<Figure*>* otherFigures)
	{
		
	}
	
	void ChessCommandExecutor::undoBeatTransformation(CommandTransformation* command, Board& board, Figure* figure, Figure* figureToTake, std::list<Figure*>* figures, std::list<Figure*>* otherFigures)
	{
		
	}
	
	void ChessCommandExecutor::clearStartCoordinates()
	{
		if (this->startCoordinates)
		{
			delete this->startCoordinates;
		}
		
		this->startCoordinates = nullptr;
	}
}
