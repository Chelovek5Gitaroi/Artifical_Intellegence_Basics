#include "moving_validator.h"

namespace chess_solver
{
	bool MovingValidator::isMoveValid(Command* command, std::list<Figure*>& secondPlayerFigures, Board& board)
	{
		bool result = false;
		
		Figure* figure = command->getFigure();
		
//		std::cout << "*Debug* validating move figure: " << figure->toString() << ", finish: " << command->getFinishCoordinates() << "... ";
		
		switch (command->getType())
		{
		case CommandType::MOVE:
			result = isMoveValid(*figure, command->getFinishCoordinates(), board);
			break;
			
		case CommandType::BEAT:
			result = isTakingValid(*figure, command->getFinishCoordinates(), secondPlayerFigures, board);
			break;
		
		case CommandType::TRANSFORMATION:
		case CommandType::BEAT_TRANSFORMATION:
			CommandTransformation* transCommand = reinterpret_cast<CommandTransformation*>(command);
			result = isTransformationValid(*figure, transCommand->getNewFigureType(), transCommand->getFinishCoordinates(), secondPlayerFigures, command->getType() == CommandType::BEAT_TRANSFORMATION, board);
			break;
		}
		
//		std::cout << " move validated...\n";
		
		return result;
	}
	
	bool MovingValidator::isMoveValid(Figure& figure, const Coordinates& finish, const Board& board)
	{
//		std::cout << " validating simple move... ";
		
		bool result = !board.getTileOccupancyByCoordinates(finish);
		
		if (result)
		{
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
				result = isReachebleForPawn(start, finish, board, figure.getColor(), false, false);
				break;
			}
		}
		
//		std::cout << " simple move validated... ";
		
		return result;
	}
	
	bool MovingValidator::isTransformationValid(Figure& figure, FigureType newFigureType, const Coordinates& finish, std::list<Figure*>& secondPlayerFigures, bool isBeatTransformation, const Board& board)
	{
//		std::cout << " validating transform... ";
		
		bool result = figure.getType() == FigureType::PAWN && newFigureType != FigureType::PAWN && newFigureType != FigureType::KING;
		
		if (result)
		{
			if (isBeatTransformation)
			{
				result = board.getTileOccupancyByCoordinates(finish);
				
				Figure* figureToTake = getFigureFromListByCoordinates(finish, secondPlayerFigures);
				
				if (figureToTake)
				{
					result = isReachebleForPawn(figure.getCoordinates(), finish, board, figure.getColor(), isBeatTransformation, true);
				}
				else
				{
					result = false;
				}
			}
			else
			{
				result = isReachebleForPawn(figure.getCoordinates(), finish, board, figure.getColor(), isBeatTransformation, true);
			}
		}
		
//		std::cout << " transform validated... ";
		
		return result;
	}
	
	bool MovingValidator::isTakingValid(Figure& figure, const Coordinates& finish, std::list<Figure*>& secondPlayerFigures, const Board& board)
	{
//		std::cout << " validate taking... ";
		
		bool result = false;
		
		if (board.getTileOccupancyByCoordinates(figure.getCoordinates()))
		{
			result = getFigureFromListByCoordinates(finish, secondPlayerFigures);
		}
		
		if (result)
		{
			const Coordinates& start = figure.getCoordinates();
		
			switch (figure.getType())
			{
			case FigureType::BISHOP:
				result = isDiagonalEmpty(start, finish, board);
				break;
				
			case FigureType::ROCK:
				result = isVerticalEmpty(start, finish, board) || isHorizontalEmpty(start, finish, board);
				break;
				
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
				result = isReachebleForPawn(start, finish, board, figure.getColor(), true, false);
				break;
			}
		}
		
//		std::cout << " taking validated... ";
		
		return result;
	}
	
	bool MovingValidator::isLineEmpty(const Coordinates& start, const Coordinates& finish, const Board& board)
	{
//		std::cout << " validate line emptyness " << start << "-" << finish << " ";
		
//		std::cout << "\n" << board.toString() << "\n";
		
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
		
//		std::cout << " line emptyness validated... ";
//		
//		if (result)
//		{
//			std::cout << "empty\n";
//		}
//		else
//		{
//			std::cout << "non empty\n";
//		}
		
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
		
//		std::cout << "*Debug* " << start << "-" << finish << "\n";
		
		for (row; row != finish.getRow(); row += step)
		{
//			std::cout << start.getColumn() << (short)row << " " << board.getTileOccupancyByCoordinates(start.getColumn(), row) << "\n";
			
			if (board.getTileOccupancyByCoordinates(start.getColumn(), row))
			{
				return false;
			}
		}
		
		return true;
	}
	
	bool MovingValidator::isDiagonalEmpty(const Coordinates& start, const Coordinates& finish, const Board& board)
	{
		if (std::abs(start.getColumn() - finish.getColumn()) != std::abs(start.getRow() - finish.getRow()))
		{
			return false;
		}
		
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
		
//		std::cout << "checking diagonal emptyness " << start << "-" << finish << "\n";
		
		while (row != finish.getRow() && column != finish.getColumn())
		{
//			std::cout << column << (short)row << " " << board.getTileOccupancyByCoordinates(column, row) << "\n";
			
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
	
	bool MovingValidator::isReachebleForPawn(const Coordinates& start, const Coordinates& finish, const Board& board, FigureColor color, bool isTaking, bool isTransformation)
	{
		bool result = std::abs(finish.getRow() - start.getRow()) == 1;
		
		if (result)
		{
			if (isTaking)
			{
				result = std::abs(finish.getColumn() - start.getColumn()) == 1;
			}
			else
			{
				result = finish.getColumn() == start.getColumn();
			}
			
			if (result)
			{
				if (color == FigureColor::WHITE)
				{
					result = finish.getRow() > start.getRow();
				}
				else
				{
					result = finish.getRow() < start.getRow();
				}
				
				if (result && isTransformation)
				{
					result = finish.getRow() == 1 || finish.getRow() == board.getBoardSize();
				}
				else
				{
					result = 1 < finish.getRow() && finish.getRow() < board.getBoardSize();
				}
			}
		}
		
		return result;
	}
	
	bool MovingValidator::isReachebleForKing(const Coordinates& start, const Coordinates& finish, const Board& board)
	{
		return (finish.getRow() == start.getRow() + 1 && (finish.getColumn() == start.getColumn() - 1 || finish.getColumn() == start.getColumn() || finish.getColumn() == start.getColumn() + 1)) ||
			   (finish.getRow() == start.getRow() && (finish.getColumn() == start.getColumn() - 1 || finish.getColumn() == start.getColumn() + 1)) ||
			   (finish.getRow() == start.getRow() - 1 && (finish.getColumn() == start.getColumn() - 1 || finish.getColumn() == start.getColumn() || finish.getColumn() == start.getColumn() + 1));
	}
	
	
	bool MovingValidator::hasCheck(Command* command, Board& board, const Coordinates& kingCoordinates, std::list<Figure*>& secondPlayerFigures)
	{
		bool result = false;
		
		Figure* takenFigure = nullptr;
		
		CommandType commandType = command->getType();
		
		if (commandType == CommandType::BEAT || commandType == CommandType::BEAT_TRANSFORMATION)
		{
			takenFigure = getFigureFromListByCoordinates(command->getFinishCoordinates(), secondPlayerFigures);
		}
		
		const Coordinates* coords = &kingCoordinates;
		
		if (command->getFigure()->getType() == FigureType::KING)
		{
			coords = &command->getFinishCoordinates();
		}
		
//		std::cout << "\nBoard:\n" << board.toString();
		
		board.setOccupancyByCoordinates(command->getFigure()->getCoordinates(), false);
		board.setOccupancyByCoordinates(command->getFinishCoordinates(), true);
		
//		std::cout << "\nBoard:\n" << board.toString();
		
		for (auto iter = secondPlayerFigures.begin(); iter != secondPlayerFigures.end() && !result; iter++)
		{
			if (*iter != takenFigure)
			{
//				std::cout << "checking check " << (*iter)->getCoordinates() << "-" << *coords << " ";
				
				switch ((*iter)->getType())
				{
				//breaks are not forgotten
				case FigureType::ROCK:
					result = isVerticalEmpty((*iter)->getCoordinates(), *coords, board) || isHorizontalEmpty((*iter)->getCoordinates(), *coords, board);
					break;
					
				case FigureType::BISHOP:
					result = isDiagonalEmpty((*iter)->getCoordinates(), *coords, board);
					break;
					
				case FigureType::QUEEN:
					result = isLineEmpty((*iter)->getCoordinates(), *coords, board);
					
//					std::cout << "line " << (*iter)->getCoordinates() << "-" << *coords << " is ";
//					
//					if (result)
//					{
//						std::cout << "empty\n";
//					}
//					else
//					{
//						std::cout << "not empty\n";
//					}
					
					break;
			
				case FigureType::KNIGHT:
					result = isReachebleForKing((*iter)->getCoordinates(), *coords, board);
					break;
				
				case FigureType::KING:
					result = isReachebleForKing((*iter)->getCoordinates(), *coords, board);
					break;
				
				case FigureType::PAWN:
					result = isReachebleForPawn((*iter)->getCoordinates(), *coords, board, (*iter)->getColor(), true, true) ||
						isReachebleForPawn((*iter)->getCoordinates(), *coords, board, (*iter)->getColor(), true, false);
					break;
				}
				
//				if (result)
//				{
//					std::cout << " check! ";
//				}
			}
		}
		
		board.setOccupancyByCoordinates(command->getFigure()->getCoordinates(), true);
		
		if (commandType != CommandType::BEAT && commandType != CommandType::BEAT_TRANSFORMATION)
		{
			board.setOccupancyByCoordinates(command->getFinishCoordinates(), false);
//			takenFigure = getFigureFromListByCoordinates(command->getFinishCoordinates(), secondPlayerFigures);
		}
	
		return result;
	}
	
	bool MovingValidator::hasCheck(Board& board, const Coordinates& kingCoordinates, std::list<Figure*>& secondPlayerFigures)
	{
		bool result = false;
		
		for (auto iter = secondPlayerFigures.begin(); iter != secondPlayerFigures.end() && !result; iter++)
		{
			switch ((*iter)->getType())
			{
			case FigureType::PAWN:
				result = isReachebleForPawn((*iter)->getCoordinates(), kingCoordinates, board, (*iter)->getColor(), true, false) ||
					isReachebleForPawn((*iter)->getCoordinates(), kingCoordinates, board, (*iter)->getColor(), true, true);
				break;
				
			case FigureType::BISHOP:
				result = isDiagonalEmpty((*iter)->getCoordinates(), kingCoordinates, board);
				break;
				
			case FigureType::KNIGHT:
				result = isReachebleForKnight((*iter)->getCoordinates(), kingCoordinates, board);
				break;
				
			case FigureType::ROCK:
				result = isVerticalEmpty((*iter)->getCoordinates(), kingCoordinates, board) || isHorizontalEmpty((*iter)->getCoordinates(), kingCoordinates, board);
				break;
				
			case FigureType::QUEEN:
				result = isLineEmpty((*iter)->getCoordinates(), kingCoordinates, board);
				break;
				
			case FigureType::KING:
				result = isReachebleForKing((*iter)->getCoordinates(), kingCoordinates, board);
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
