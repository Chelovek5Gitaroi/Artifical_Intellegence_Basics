#include "chess_command_executor.h"

namespace chess_solver
{
	void ChessCommandExecutor::executeCommand(Command* command, Board& board, std::list<Figure*>* figures, std::list<Figure*>* otherFigures)
	{
//		std::cout << "*Debug* executing ";
		Figure* figureToTake = getFigureFromList(command->getFinishCoordinates(), otherFigures);
		CommandTransformation* transCommand = nullptr;
		
		Figure* figure = getFigureFromList(command->getStartCoordinates(), figures);
		
		switch (command->getType())
		{
		case CommandType::MOVE:
			executeMove(board, figure, command->getFinishCoordinates());
			break;
			
		case CommandType::BEAT:
			executeTake(board, figure, figureToTake, otherFigures);
			break;
			
		case CommandType::TRANSFORMATION:
			transCommand = reinterpret_cast<CommandTransformation*>(command);
			executeTransformation(board, figure, command->getFinishCoordinates(), transCommand->getNewFigureType(), figures);
			break;
			
		case CommandType::BEAT_TRANSFORMATION:
			transCommand = reinterpret_cast<CommandTransformation*>(command);
			executeBeatTransformation(board, figure, figureToTake, transCommand->getNewFigureType(), figures, otherFigures);
			break;
		}
		
//		std::cout << " executed!\n";
	}
	
	void ChessCommandExecutor::executeMove(Board& board, Figure* figure, const Coordinates& finishCoordinates)
	{
//		std::cout << "move";
		board.setOccupancyByCoordinates(figure->getCoordinates(), false);
		board.setOccupancyByCoordinates(finishCoordinates, true);
		
		figure->move(finishCoordinates);
	}
	
	void ChessCommandExecutor::executeTake(Board& board, Figure* figure, Figure* figureToTake, std::list<Figure*>* otherFigures)
	{
//		std::cout << "take";
		
		otherFigures->remove(figureToTake);
		executeMove(board, figure, figureToTake->getCoordinates());
	}
	
	void ChessCommandExecutor::executeTransformation(Board& board, Figure* figure, const Coordinates& finishCoordinates, FigureType newFigureType, std::list<Figure*>* figures)
	{
//		std::cout << "trans";
		figures->push_back(new Figure(newFigureType, figure->getColor(), finishCoordinates.getColumn(), finishCoordinates.getRow()));
		figures->remove(figure);
		
		board.setOccupancyByCoordinates(figure->getCoordinates(), false);
		board.setOccupancyByCoordinates(finishCoordinates, true);
	}
	
	void ChessCommandExecutor::executeBeatTransformation(Board& board, Figure* figure, Figure* figureToTake, FigureType newFigureType, std::list<Figure*>* figures, std::list<Figure*>* otherFigures)
	{
//		std::cout << "beat trans taken figure: " << figureToTake->toString() << " ";
		
//		std::cout << " taken figure removing... ";
		otherFigures->remove(figureToTake);
		
//		std::cout << " board marking... ";
		board.setOccupancyByCoordinates(figure->getCoordinates(), false);
		
		figures->push_back(new Figure(newFigureType, figure->getColor(), figureToTake->getCoordinates().getColumn(), figureToTake->getCoordinates().getRow()));
		
//		std::cout << " removing old figure... ";
		figures->remove(figure);
	}
	
	Figure* ChessCommandExecutor::getFigureFromList(const Coordinates& coordinates, std::list<Figure*>* figures)
	{
		for (auto iter = figures->begin(); iter != figures->end(); iter++)
		{
			if ((*iter)->getCoordinates() == coordinates)
			{
				return *iter;
			}
		}
		return nullptr;
	}
}
