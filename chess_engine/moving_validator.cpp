#include "moving_validator.h"

namespace chess_solver
{
//	MovingValidator::MovingValidator(Board* board)
//	{
//	}
	
//	bool MovingValidator::isMoveValid(Coordinates& start, Coordinates& finish, std::map<Coordinates, FigureType>& firstPlayerFigures, std::map<Coordinates, FigureType>& secondPlayerFigures)
//	{
//		bool result = false;
//		
//		Figure* figure = firstPlayer.getFigureByCoordinates(start);
//		
//		if (figure != nullptr)
//		{
//			Figure* endFigure = firstPlayer.getFigureByCoordinates(finish);
//			
//			if (endFigure == nullptr)
//			{
//				endFigure = secondPlayer.getFigureByCoordinates(finish);
//				
//				if (endFigure == nullptr)
//				{
//					result = isMoveValid(*figure, finish, firstPlayer, secondPlayer);
//				}
//				else
//				{
//					result = isTakingValid(*figure, finish, firstPlayer, secondPlayer);
//				}
//				
//				if (result)
//				{
//					this->board->getTileByCoordinates(start).free();
//					this->board->getTileByCoordinates(finish).occupy();
//					
//					if (figure->getType() == FigureType::KING)
//					{
//						result = hasCheck(finish, firstPlayer, secondPlayer);
//					}
//					else
//					{
//						Figure* king = firstPlayer.getKing();
//						
//						result = hasCheck(king->getCoordinates(), firstPlayer, secondPlayer);
//					}
//					
//					this->board->getTileByCoordinates(start).occupy();
//					this->board->getTileByCoordinates(finish).free();
//				}
//			}
//		}
//		
//		return result;
//	}
	
//	bool MovingValidator::isTakingValid(Figure& figure, Coordinates& finish, std::map<Coordinates, FigureType>& firstPlayerFigures, std::map<Coordinates, FigureType>& secondPlayerFigures)
//	{
//		bool result = false;
		
//		switch (figure.getType())
//		{
//		case FigureType::ROCK:  	//break wasn`t forgot
//		case FigureType::BISHOP:	//break wasn`t forgot
//		case FigureType::QUEEN:
//			result = isLineEmpty(figure.getCoordinates(), finish);
//			break;
//			
//		case FigureType::KNIGHT:
//			result = isReachebleForKnight(figure.getCoordinates(), finish);
//			break;
//			
//		case FigureType::PAWN:
//			result = isReachebleForPawnToTake(figure, finish);
//			break;
//			
//		case FigureType::KING:
//			result = isReachebleForKing(figure.getCoordinates(), finish);
//			break;
//			
//		default:
//			break;
//		}
		
//		return result;
//	}
//	
//	bool MovingValidator::isMoveValid(Figure& figure, Coordinates& finish, std::map<Coordinates, FigureType>& firstPlayerFigures, std::map<Coordinates, FigureType>& secondPlayerFigures)
//	{
//		bool result = false;
		
//		if (figure.getType() == FigureType::ROCK || figure.getType() == FigureType::BISHOP || figure.getType() == FigureType::QUEEN)
//		{
//			result = isLineEmpty(figure.getCoordinates(), finish);
//		}
//		else if (figure.getType() == FigureType::KNIGHT)
//		{
//			result = isReachebleForKnight(figure.getCoordinates(), finish);
//		}
//		else if (figure.getType() == FigureType::PAWN)
//		{
//			result = isReachebleForPawn(figure, finish);
//		}
//		else if (figure.getType() == FigureType::KING)
//		{
//			result = isReachebleForKing(figure.getCoordinates(), finish);
//		}
//		
//		return result;
//	}
	
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
	
	bool MovingValidator::isReachebleForKnight(const Coordinates& start, const Coordinates& finish)
	{
		return ((finish.getRow() == start.getRow() - 2 || finish.getRow() == start.getRow() + 2) &&
					(finish.getColumn() == start.getColumn() - 1 || finish.getColumn() == start.getColumn() + 1)) ||
			   ((finish.getRow() == start.getRow() - 1 || finish.getRow() == start.getRow() + 1) &&
			   		(finish.getColumn() == start.getColumn() - 2 || finish.getColumn() == start.getColumn() + 2));
	}
	
	bool MovingValidator::isReachebleForPawn(Figure& pawn, const Coordinates& finish, const Board& board)
	{
		Coordinates start = pawn.getCoordinates();
		
		bool result = finish.getColumn() == start.getColumn();
		
		if (result)
		{
			if (std::abs(finish.getRow() - start.getRow()) <= 2)
			{
				if (std::abs(finish.getRow() - start.getRow()) == 2)
				{
					if (!pawn.wasMoved())
					{
						result = isVerticalEmpty(start, finish, board);
					}
					else
					{
						result = false;
					}
				}
				else
				{
					return true;
				}
			}
			else
			{
				result = false;
			}
		}
		
		return result;
	}
	
	bool MovingValidator::isReachebleForPawnToTake(Figure& pawn, const Coordinates& finish)
	{
		bool result = false;
		
		Coordinates start = pawn.getCoordinates();
		
		if (pawn.getColor() == FigureColor::WHITE)
		{
			result = (finish.getRow() == start.getRow() + 1 && (finish.getColumn() == start.getColumn() - 1 || finish.getColumn() == start.getColumn() + 1));
		}
		else
		{
			result = (finish.getRow() == start.getRow() - 1 && (finish.getColumn() == start.getColumn() - 1 || finish.getColumn() == start.getColumn() + 1));
		}
		
		return result;
	}
	
	bool MovingValidator::isReachebleForKing(const Coordinates& start, const Coordinates& finish)
	{
		return (finish.getRow() == start.getRow() + 1 && (finish.getColumn() == start.getColumn() - 1 || finish.getColumn() == start.getColumn() || finish.getColumn() == start.getColumn() + 1)) ||
			   (finish.getRow() == start.getRow() && (finish.getColumn() == start.getColumn() - 1 || finish.getColumn() == start.getColumn() + 1)) ||
			   (finish.getRow() == start.getRow() - 1 && (finish.getColumn() == start.getColumn() - 1 || finish.getColumn() == start.getColumn() || finish.getColumn() == start.getColumn() + 1));
	}
	
	
	bool MovingValidator::hasCheck(const Coordinates& kingCoordinates, Player& firstPlayer, Player& secondPlayer)
	{
		bool result = false;
		
//		for (auto iter = secondPlayer.getAllFigures().begin(); iter != secondPlayer.getAllFigures().end() && !result; iter++)
//		{
//			switch ((*iter)->getType())
//			{
//			case FigureType::ROCK:		//break wasn't forgot
//			case FigureType::BISHOP:	//break wasn't forgot
//			case FigureType::QUEEN:
//				result = isLineEmpty((*iter)->getCoordinates(), kingCoordinates);
//				break;
//				
//			case FigureType::PAWN:
//				result = isReachebleForPawnToTake(*(*iter), kingCoordinates);
//				break;
//				
//			case FigureType::KNIGHT:
//				result = isReachebleForKnight((*iter)->getCoordinates(), kingCoordinates);
//				break;
//				
//			case FigureType::KING:
//				result = isReachebleForKing((*iter)->getCoordinates(), kingCoordinates);
//				break;
//				
//			default:
//				break;
//			}
//		}
		
		return result;
	}
	
//	void MovingValidator::climeTilesToCheck(const Coordinates& start, const Coordinates& finish)
//	{
//		this->board->getTileByCoordinates(start).free();
//		this->board->getTileByCoordinates(finish).occupy();
//	}
//	
//	void MovingValidator::unclimeTilesAfterCheck(const Coordinates& start, const Coordinates& finish)
//	{
//		this->board->getTileByCoordinates(start).occupy();
//		this->board->getTileByCoordinates(finish).free();
//	}
	
}
