#include "moving_validator.h"

namespace chess_solver
{
	bool MovingValidator::isMoveValid(const Coordinates& start, const Coordinates& finish, std::list<Figure*>& firstPlayerFigures, std::list<Figure*>& secondPlayerFigures, Board& board)
	{
		bool result = false;
		
		Figure* figure = getFigureFromListByCoordinates(start, firstPlayerFigures);
		
		if (board.getTileOccupancyByCoordinates(finish))
		{
			if (getFigureFromListByCoordinates(finish, secondPlayerFigures))
			{
				result = isTakingValid(*figure, finish, board);
			}
		}
		else
		{
			result = isMoveValid(*figure, finish, board);
		}
		
		return result;
	}
	
	bool MovingValidator::isMoveValid(Figure& figure, const Coordinates& finish, const Board& board)
	{
		bool result = false;
		
		const Coordinates& start = figure.getCoordinates();
		
		switch (figure.getType())
		{
		case FigureType::BISHOP:
		case FigureType::ROCK:
		case FigureType::QUEEN:
			result = isLineEmpty(start, finish, board);
			break;
			
		case FigureType::KING:
			result = isReachebleForKing(start, finish, board);
			break;
			
		case FigureType::KNIGHT:
			result = isReachebleForKnight(start, finish, board);
			break;
			
		case FigureType::PAWN:
			result = isReachebleForPawn(start, finish, board);
			break;
		}
		
		return result;
	}
	
	bool MovingValidator::isTakingValid(Figure& figure, const Coordinates& finish, const Board& board)
	{
		bool result = false;
		
		const Coordinates& start = figure.getCoordinates();
		
		switch (figure.getType())
		{
		case FigureType::BISHOP:
		case FigureType::ROCK:
		case FigureType::QUEEN:
			result = isLineEmpty(start, finish, board);
			break;
		
		case FigureType::KING:
			result = isReachebleForKing(start, finish, board);
			break;
			
		case FigureType::KNIGHT:
			result = isReachebleForKnight(start, finish, board);
			break;
			
		case FigureType::PAWN:
			result = isReachebleForPawnToTake(start, finish, board);
			break;
		}
		
		return result;
	}
	
	bool MovingValidator::isLineEmpty(const Coordinates& start, const Coordinates& finish, const Board& board)
	{
		bool result = false;
		
		if (start.getColumn() == finish.getColumn())
		{
			result = isVerticalEmpty(start, finish, board);
		}
		else if (start.getRow() == finish.getRow())
		{
			result = isHorizontalEmpty(start, finish, board);
		}
		else if (std::abs(finish.getColumn() - start.getColumn()) == std::abs(finish.getRow() - start.getRow()))
		{
			result = isDiagonalEmpty(start, finish, board);
		}
		
		return result;
	}
	
	bool MovingValidator::isHorizontalEmpty(const Coordinates& start, const Coordinates& finish, const Board& board)
	{
		char column = start.getColumn();
		char step = 1;
		
		if (start.getColumn() < finish.getColumn())
		{
			column++;
		}
		else
		{
			column--;
			step = -1;
		}
				
		for (column; column != finish.getColumn(); column += step)
		{
			if (board.getTileOccupancyByCoordinates(column, start.getRow()))
			{
				return false;
			}
		}
		
		return true;
	}
	
	bool MovingValidator::isVerticalEmpty(const Coordinates& start, const Coordinates& finish, const Board& board)
	{
		char row = start.getRow();
		char step = 1;
		
		if (start.getRow() < finish.getRow())
		{
			row++;
		}
		else
		{
			row--;
			step = -1;
		}
		
		for (row; row != finish.getRow(); row += step)
		{
			if (board.getTileOccupancyByCoordinates(start.getColumn(), row))
			{
				return false;
			}
		}
		
		return true;
	}
	
	bool MovingValidator::isDiagonalEmpty(const Coordinates& start, const Coordinates& finish, const Board& board)
	{
		char row = start.getRow();
		char column = start.getColumn();
		
		char rowStep = 1;
		char columnStep = 1;
		
		if (start.getRow() < finish.getRow())
		{
			row++;
		}
		else
		{
			row--;
			rowStep = -1;
		}
		
		if (start.getColumn() < finish.getColumn())
		{
			column++;
		}
		else
		{
			column--;
			columnStep = -1;
		}
		
		while (row != finish.getRow() && column != finish.getColumn())
		{
			if (board.getTileOccupancyByCoordinates(column, row))
			{
				return false;
			}
			
			row += rowStep;
			column += columnStep;
		}
		
		return  true;
	}
	
	bool MovingValidator::isReachebleForKnight(const Coordinates& start, const Coordinates& finish, const Board& board)
	{
		return ((finish.getRow() == start.getRow() - 2 || finish.getRow() == start.getRow() + 2) &&
					(finish.getColumn() == start.getColumn() - 1 || finish.getColumn() == start.getColumn() + 1)) ||
			   ((finish.getRow() == start.getRow() - 1 || finish.getRow() == start.getRow() + 1) &&
			   		(finish.getColumn() == start.getColumn() - 2 || finish.getColumn() == start.getColumn() + 2));
	}
	
	bool MovingValidator::isReachebleForPawn(const Coordinates& start, const Coordinates& finish, const Board& board)
	{
		return finish.getColumn() == start.getColumn() && std::abs(finish.getRow() - start.getRow()) == 1;
	}
	
	bool MovingValidator::isReachebleForPawnToTake(const Coordinates& start, const Coordinates& finish, const Board& board)
	{
		return std::abs(finish.getRow() - start.getRow()) == 1 && std::abs(finish.getColumn() - start.getColumn()) == 1;
	}
	
	bool MovingValidator::isReachebleForKing(const Coordinates& start, const Coordinates& finish, const Board& board)
	{
		return (finish.getRow() == start.getRow() + 1 && (finish.getColumn() == start.getColumn() - 1 || finish.getColumn() == start.getColumn() || finish.getColumn() == start.getColumn() + 1)) ||
			   (finish.getRow() == start.getRow() && (finish.getColumn() == start.getColumn() - 1 || finish.getColumn() == start.getColumn() + 1)) ||
			   (finish.getRow() == start.getRow() - 1 && (finish.getColumn() == start.getColumn() - 1 || finish.getColumn() == start.getColumn() || finish.getColumn() == start.getColumn() + 1));
	}
	
	
	bool MovingValidator::hasCheck(const Board& board, const Coordinates& kingCoordinates, std::list<Figure*>& firstPlayerFigures, std::list<Figure*>& secondPlayerFigures)
	{
		bool result = false;
		
		for (auto iter = secondPlayerFigures.begin(); iter != secondPlayerFigures.end() && !result; iter++)
		{
			switch ((*iter)->getType())
			{
			//breaks are not forgotten
			case FigureType::ROCK:
			case FigureType::BISHOP:
			case FigureType::QUEEN:
				result = isLineEmpty((*iter)->getCoordinates(), kingCoordinates, board);
				break;
			
			case FigureType::KNIGHT:
				result = isReachebleForKing((*iter)->getCoordinates(), kingCoordinates, board);
				break;
				
			case FigureType::KING:
				result = isReachebleForKing((*iter)->getCoordinates(), kingCoordinates, board);
				break;
				
			case FigureType::PAWN:
				result = isReachebleForPawnToTake((*iter)->getCoordinates(), kingCoordinates, board);
				break;
			}
		}
		
		return result;
	}
	
	Figure* MovingValidator::getFigureFromListByCoordinates(const Coordinates& coordinates, std::list<Figure*>& figures)
	{
		for (auto iter = figures.begin(); iter != figures.end(); iter++)
		{
			if ((*iter)->getCoordinates() == coordinates)
			{
				return *iter;
			}
		}
		
		return nullptr;
	}
}
