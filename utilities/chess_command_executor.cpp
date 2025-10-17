#include "chess_command_executor.h"

namespace chess_solver
{
	ChessCommandExecutor::~ChessCommandExecutor()
	{
//		if (this->startCoordinates)
//		{
//			delete startCoordinates;
//			this->startCoordinates = nullptr;
//		}
	}
	
	void ChessCommandExecutor::executeCommand(Command* command, Board& board, std::list<Figure*>* figures, std::list<Figure*>* otherFigures)
	{
//		std::cout << "*Debug* executing ";
		
		Figure* figureToTake = getFigureFromList(command->getFinishCoordinates(), otherFigures);
		CommandTransformation* transCommand = nullptr;
		
		switch (command->getType())
		{
		case CommandType::MOVE:
			executeMove(board, command->getFigure(), command->getFinishCoordinates());
			break;
			
		case CommandType::BEAT:
//			this->takenFigurePosition = getFigurePosition(command->getFinishCoordinates(), otherFigures);
			executeTake(board, command->getFigure(), figureToTake, otherFigures);
			break;
			
		case CommandType::TRANSFORMATION:
			transCommand = reinterpret_cast<CommandTransformation*>(command);
			executeTransformation(board, command->getFigure(), command->getFinishCoordinates(), transCommand->getNewFigureType(), figures);
			break;
			
		case CommandType::BEAT_TRANSFORMATION:
			transCommand = reinterpret_cast<CommandTransformation*>(command);
//			this->takenFigurePosition = getFigurePosition(command->getFinishCoordinates(), otherFigures);
			
			executeBeatTransformation(board, command->getFigure(), figureToTake, transCommand->getNewFigureType(), figures, otherFigures);
			
			break;
		}
		
//		std::cout << " executed!\n";
	}
	
//	void ChessCommandExecutor::undoCommand(Command* command, Board& board, std::list<Figure*>* figures, std::list<Figure*>* otherFigures)
//	{
//		std::cout << "*Debug* undoing command ";
//		
//		switch (command->getType())
//		{
//		case CommandType::MOVE:
//			undoMove(board, command->getFigure());
//			break;
//			
//		case CommandType::BEAT:
//			undoTake(board, command->getFigure(), figures);
//			break;
//			
//		case CommandType::TRANSFORMATION:
//			undoTransformation(board, command->getFigure(), command->getFinishCoordinates(), figures);
//			break;
//			
//		case CommandType::BEAT_TRANSFORMATION:
//			undoBeatTransformation(board, command->getFigure(), figures, otherFigures);
//			break;
//		}
//		
//		std::cout << " undone!\n";
//	}
	
	void ChessCommandExecutor::executeMove(Board& board, Figure* figure, const Coordinates& finishCoordinates)
	{
//		std::cout << "move";
//		clearStartCoordinates();
		
//		this->startCoordinates = new Coordinates(figure->getCoordinates());
		
		board.setOccupancyByCoordinates(figure->getCoordinates(), false);
		board.setOccupancyByCoordinates(finishCoordinates, true);
		
		figure->move(finishCoordinates);
	}
	
//	void ChessCommandExecutor::undoMove(Board& board, Figure* figure)
//	{
////		std::cout << "move";
//		
//		board.setOccupancyByCoordinates(*startCoordinates, true);
//		board.setOccupancyByCoordinates(figure->getCoordinates(), false);
//		
//		figure->move(*startCoordinates);
//	}
	
	void ChessCommandExecutor::executeTake(Board& board, Figure* figure, Figure* figureToTake, std::list<Figure*>* otherFigures)
	{
//		std::cout << "take";
		
//		this->takenFigurePosition = getFigurePosition(figureToTake->getCoordinates(), otherFigures) ;
		
//		this->takenFigure = figureToTake;
		
		otherFigures->remove(figureToTake);
		
		executeMove(board, figure, figureToTake->getCoordinates());
	}
	
//	void ChessCommandExecutor::undoTake(Board& board, Figure* figure, std::list<Figure*>* otherFigures)
//	{
////		std::cout << "take";
//		undoMove(board, figure);
//		
//		otherFigures->insert(this->takenFigurePosition, takenFigure);
//		
////		otherFigures->push_back(this->takenFigure);
//		board.setOccupancyByCoordinates(this->takenFigure->getCoordinates(), true);
//	}
//	
	void ChessCommandExecutor::executeTransformation(Board& board, Figure* figure, const Coordinates& finishCoordinates, FigureType newFigureType, std::list<Figure*>* figures)
	{
//		std::cout << "trans";
//		clearStartCoordinates();
		
//		this->startCoordinates = new Coordinates(figure->getCoordinates());
		
//		this->figurePosition = getFigurePosition(figure->getCoordinates(), figures);
		
		figures->push_back(new Figure(newFigureType, figure->getColor(), finishCoordinates.getColumn(), finishCoordinates.getRow()));
//		figures->insert(this->figurePosition, new Figure(newFigureType, figure->getColor(), finishCoordinates.getColumn(), finishCoordinates.getRow()));
		
		figures->remove(figure);
		
		board.setOccupancyByCoordinates(figure->getCoordinates(), false);
	}
	
//	void ChessCommandExecutor::undoTransformation(Board& board, Figure* figure, const Coordinates& finishCoordinates, std::list<Figure*>* figures)
//	{
////		std::cout << "trans";
//		
//		Figure* figureToRemove = *getFigurePosition(finishCoordinates, figures);
//		
//		figures->insert(this->figurePosition, figure);
//		
//		figures->remove(figureToRemove);
//		
//		delete figureToRemove;
//		
//		board.setOccupancyByCoordinates(finishCoordinates, false);
//		board.setOccupancyByCoordinates(figure->getCoordinates(), true);
//	}
	
	void ChessCommandExecutor::executeBeatTransformation(Board& board, Figure* figure, Figure* figureToTake, FigureType newFigureType, std::list<Figure*>* figures, std::list<Figure*>* otherFigures)
	{
//		std::cout << "beat trans taken figure: " << figureToTake->toString() << " ";
		
//		this->takenFigure = figureToTake;
		
//		std::cout << " getting taken figure position... ";
//		this->takenFigurePosition = getFigurePosition(figureToTake->getCoordinates(), otherFigures);
		
//		std::cout << " getting figure position... ";
//		this->figurePosition = getFigurePosition(figure->getCoordinates(), figures);
		
//		std::cout << " taken figure removing... ";
		otherFigures->remove(figureToTake);
		
//		std::cout << " board marking... ";
		board.setOccupancyByCoordinates(figure->getCoordinates(), false);
		
//		std::cout << " clearing start coords... ";
//		clearStartCoordinates();
		
//		std::cout << " creating new start coords... ";
//		this->startCoordinates = new Coordinates(figure->getCoordinates());
		
		figures->push_back(new Figure(newFigureType, figure->getColor(), figureToTake->getCoordinates().getColumn(), figureToTake->getCoordinates().getRow()));
		
//		std::cout << " removing old figure... ";
		figures->remove(figure);
	}
	
//	void ChessCommandExecutor::undoBeatTransformation(Board& board, Figure* figure, std::list<Figure*>* figures, std::list<Figure*>* otherFigures)
//	{
//		std::cout << " ubeat trans";
//		
//		
//		otherFigures->insert(this->takenFigurePosition, this->takenFigure);
//		
////		otherFigures->push_back(this->takenFigure);
//		
//		Figure* createdFigure = *getFigurePosition(this->takenFigure->getCoordinates(), figures);
//		
//		figures->insert(this->figurePosition, figure);
//		
//		figures->remove(createdFigure);
//		delete createdFigure;
//		
////		figures->push_back(figure);
//		
//		board.setOccupancyByCoordinates(figure->getCoordinates(), true);
//	}
	
//	void ChessCommandExecutor::clearStartCoordinates()
//	{
//		if (this->startCoordinates)
//		{
//			delete this->startCoordinates;
//		}
//		
//		this->startCoordinates = nullptr;
//	}
	
//	std::list<Figure*>::iterator ChessCommandExecutor::getFigurePosition(const Coordinates& coordinates, std::list<Figure*>* figures)
//	{
//		std::list<Figure*>::iterator result = figures->begin();
//		
//		for (result; result != figures->end(); result++)
//		{
//			
//			if ((*result)->getCoordinates() == coordinates)
//			{
//				return result;
//			}
//		}
//		
//		return result;
//	}
	
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
