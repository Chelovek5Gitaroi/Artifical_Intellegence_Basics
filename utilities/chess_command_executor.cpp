#include "chess_command_executor.h"

namespace chess_solver
{
	ChessCommandExecutor::~ChessCommandExecutor()
	{
		if (this->startCoordinates)
		{
			delete startCoordinates;
			this->startCoordinates = nullptr;
		}
	}
	
	void ChessCommandExecutor::executeCommand(Command* command, Board& board, std::list<Figure*>* figures, std::list<Figure*>* otherFigures)
	{
		Figure* figureToTake = nullptr;
		CommandTransformation* transCommand = nullptr;
		
		
		switch (command->getType())
		{
		case CommandType::MOVE:
			executeMove(board, command->getFigure(), command->getFinishCoordinates());
			break;
			
		case CommandType::BEAT:
			figureToTake = getFigureFromList(command->getFinishCoordinates(), otherFigures);
			executeTake(board, command->getFigure(), figureToTake, otherFigures);
			break;
			
		case CommandType::TRANSFORMATION:
			transCommand = reinterpret_cast<CommandTransformation*>(command);
			executeTransformation(board, command->getFigure(), transCommand->getNewFigureType(), figures);
			break;
			
		case CommandType::BEAT_TRANSFORMATION:
			transCommand = reinterpret_cast<CommandTransformation*>(command);
			figureToTake = getFigureFromList(command->getFinishCoordinates(), otherFigures);
			executeBeatTransformation(board, command->getFigure(), figureToTake, transCommand->getNewFigureType(), figures, otherFigures);
			break;
		}
	}
	
	void ChessCommandExecutor::undoCommand(Command* command, Board& board, std::list<Figure*>* figures, std::list<Figure*>* otherFigures)
	{
		switch (command->getType())
		{
		case CommandType::MOVE:
			undoMove(board, command->getFigure());
			break;
			
		case CommandType::BEAT:
			undoTake(board, command->getFigure(), figures);
			break;
			
		case CommandType::TRANSFORMATION:
			undoTransformation(board, command->getFigure(), command->getFinishCoordinates(), figures);
			break;
			
		case CommandType::BEAT_TRANSFORMATION:
			undoBeatTransformation(board, command->getFigure(), figures, otherFigures);
			break;
		}
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
	
	void ChessCommandExecutor::undoTake(Board& board, Figure* figure, std::list<Figure*>* otherFigures)
	{
		undoMove(board, figure);
		
		otherFigures->push_back(this->takenFigure);
		board.setOccupancyByCoordinates(this->takenFigure->getCoordinates(), true);
	}
	
	void ChessCommandExecutor::executeTransformation(Board& board, Figure* figure, FigureType newFigureType, std::list<Figure*>* figures)
	{
		clearStartCoordinates();
		
		this->startCoordinates = new Coordinates(figure->getCoordinates());
		
		figures->push_back(new Figure(newFigureType, figure->getColor(), figure->getCoordinates().getColumn(), figure->getCoordinates().getRow()));
		
		board.setOccupancyByCoordinates(figure->getCoordinates(), false);
		
		figures->remove(figure);
	}
	
	void ChessCommandExecutor::undoTransformation(Board& board, Figure* figure, const Coordinates& finishCoordinates, std::list<Figure*>* figures)
	{
		Figure* figureToRemove = getFigureFromList(finishCoordinates, figures);
		figures->remove(figureToRemove);
		
		delete figureToRemove;
		
		board.setOccupancyByCoordinates(finishCoordinates, false);
		board.setOccupancyByCoordinates(figure->getCoordinates(), true);
		
		figures->push_back(figure);
	}
	
	void ChessCommandExecutor::executeBeatTransformation(Board& board, Figure* figure, Figure* figureToTake, FigureType newFigureType, std::list<Figure*>* figures, std::list<Figure*>* otherFigures)
	{
		this->takenFigure = figureToTake;
		otherFigures->remove(figureToTake);
		
		board.setOccupancyByCoordinates(figure->getCoordinates(), false);
		
		clearStartCoordinates();
		
		this->startCoordinates = new Coordinates(figure->getCoordinates());
		
		figures->remove(figure);
		
		figures->push_back(new Figure(newFigureType, figure->getColor(), figure->getCoordinates().getColumn(), figure->getCoordinates().getRow()));
	}
	
	void ChessCommandExecutor::undoBeatTransformation(Board& board, Figure* figure, std::list<Figure*>* figures, std::list<Figure*>* otherFigures)
	{
		otherFigures->push_back(this->takenFigure);
		
		Figure* createdFigure = getFigureFromList(this->takenFigure->getCoordinates(), figures);
		figures->remove(createdFigure);
		delete createdFigure;
		
		figures->push_back(figure);
		
		board.setOccupancyByCoordinates(figure->getCoordinates(), true);
	}
	
	void ChessCommandExecutor::clearStartCoordinates()
	{
		if (this->startCoordinates)
		{
			delete this->startCoordinates;
		}
		
		this->startCoordinates = nullptr;
	}
	
	Figure* ChessCommandExecutor::getFigureFromList(const Coordinates& coordinates, std::list<Figure*>* figures)
	{
		for (auto iter = figures->begin(); iter != figures->begin(); iter++)
		{
			if ((*iter)->getCoordinates() == coordinates)
			{
				return *iter;
			}
		}
		
		return nullptr;
	}
}
