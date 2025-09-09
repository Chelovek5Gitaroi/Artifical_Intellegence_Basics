#include "moving_validator.h"

namespace chess_solver
{
	bool MovingValidator::isMoveValid(Coordinates& start, Coordinates& finish, Player& firstPlayer, Player& secondPlayer)
	{
		bool result = false;
		
		Figure* figure = firstPlayer.getFigureByCoordinates(start);
		
		if (figure != nullptr)
		{
//			if (figure->getType() == FigureType::ROCK || figure->getType() == FigureType::BISHOP || figure->getType() == FigureType::QUEEN)
//			{
//				result = isLineEmpty(start, finish);
//			}
//			else if (figure->getType() == FigureType::KING)
//			{
//				result = isReachebleForKing(start, finish, firstPlayer, secondPlayer);
//			}
//			else if (figure->getType() == FigureType::KNIGHT)
//			{
//				result = isReachebleForKnight(start, finish);
//			}
//			else if (figure->getType() == FigureType::PAWN)
//			{
//				//result = isReac
//			}
			
		}
		
		return result;
	}
	
	bool MovingValidator::isTakingValid(Coordinates& start, Coordinates& finish, Player& firstPlayer, Player& secondPlayer)
	{
		
	}
	
	
	bool MovingValidator::isLineEmpty(const Coordinates& start, const Coordinates& finish)
	{
		bool result = false;
		
		if (start.getColumn() == finish.getColumn())
		{
			result = isVerticalEmpty(start, finish);
		}
		else if (start.getRow() == finish.getRow())
		{
			result = isHorizontalEmpty(start, finish);
		}
		else if (std::abs(finish.getColumn() - start.getColumn()) == std::abs(finish.getRow() - start.getRow()))
		{
			result = isDiagonalEmpty(start, finish);
		}
		
		return result;
	}
	
	bool MovingValidator::isHorizontalEmpty(const Coordinates& start, const Coordinates& finish)
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
			if (this->board->getTileByCoordinates(column, start.getRow()).isOccupied())
			{
				return false;
			}
		}
		
		return true;
	}
	
	bool MovingValidator::isVerticalEmpty(const Coordinates& start, const Coordinates& finish)
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
			if (this->board->getTileByCoordinates(start.getColumn(), row).isOccupied())
			{
				return false;
			}
		}
		
		return true;
	}
	
	bool MovingValidator::isDiagonalEmpty(const Coordinates& start, const Coordinates& finish)
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
			if (this->board->getTileByCoordinates(column, row).isOccupied())
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
	
	bool MovingValidator::isReachebleForPawn(const Coordinates& start, const Coordinates& finish, Figure* figure)
	{
		bool result = finish.getColumn() == start.getColumn();
		
		if (result)
		{
			if (std::abs(finish.getRow() - start.getRow()) <= 2)
			{
				if (std::abs(finish.getRow() - start.getRow()) == 2)
				{
					if (!figure->wasMoved())
					{
						result = isVerticalEmpty(start, finish);
					}
					else
					{
						result = false;
					}
				}
			}
			else
			{
				result = false;
			}
		}
		
		return result;
	}
	
	bool MovingValidator::isReachebleForPawnToTake(const Coordinates& start, const Coordinates& finish, FigureColor color)
	{
		bool result = false;
		
		if (color == FigureColor::WHITE)
		{
			result = (finish.getRow() == start.getRow() + 1 && (finish.getColumn() == start.getColumn() - 1 || finish.getColumn() == start.getColumn() + 1));
		}
		else
		{
			result = (finish.getRow() == start.getRow() - 1 && (finish.getColumn() == start.getColumn() - 1 || finish.getColumn() == start.getColumn() + 1));
		}
		
		return result;
	}
	
	bool MovingValidator::isReachebleForKing(const Coordinates& start, const Coordinates& finish, Player& firstPlayer, Player& secondPlayer)
	{
		return (finish.getRow() == start.getRow() + 1 && (finish.getColumn() == start.getColumn() - 1 || finish.getColumn() == start.getColumn() || finish.getColumn() == start.getColumn() + 1)) ||
			   (finish.getRow() == start.getRow() && (finish.getColumn() == start.getColumn() - 1 || finish.getColumn() == start.getColumn() + 1)) ||
			   (finish.getRow() == start.getRow() - 1 && (finish.getColumn() == start.getColumn() - 1 || finish.getColumn() == start.getColumn() || finish.getColumn() == start.getColumn() + 1));
	}
	
//	bool MovingValidator::isPawnMoveValid(Coordinates& startCoordinates, Coordinates& finishCoordinates, Player& otherPlayer)
//	{
//		
//	}
//	
//	bool MovingValidator::isKnightMoveValid(Coordinates& startCoordinates, Coordinates& finishCoordinates, Player& otherPlayer)
//	{
//		
//	}
//	
//	bool MovingValidator::isBishopMoveValid(Coordinates& startCoordinates, Coordinates& finishCoordinates, Player& otherPlayer)
//	{
//		
//	}
//	
//	bool MovingValidator::isRockMoveValid(Coordinates& startCoordinates, Coordinates& finishCoordinates, Player& otherPlayer)
//	{
//		bool result = finishCoordinates.getRow() == startCoordinates.getRow() || finishCoordinates.getColumn() == startCoordinates.getColumn();
//		
//		if (result)
//		{
//			
//		}
//		
//		return result;
//	}
//	
//	bool MovingValidator::isQueenMoveValid(Coordinates& startCoordinates, Coordinates& finishCoordinates, Player& otherPlayer)
//	{
//		
//	}
//	
//	bool MovingValidator::isKingMoveValid(Coordinates& startCoordinates, Coordinates& finishCoordinates, Player& otherPlayer)
//	{
//		
//	}
	
//	char MovingValidator::calcFiguresNumberOnHorizontal(const Coordinates& start, const Coordinates& finish)
//	{
//		
//	}
//	
//	char MovingValidator::calcFiguresNumberOnVertical(const Coordinates& start, const Coordinates& finish)
//	{
//		
//	}
//	
//	char MovingValidator::calcFiguresNumberOnDiagonal(const Coordinates& start, const Coordinates& finish)
//	{
//		
//	}

	
	bool MovingValidator::hasCheck(Coordinates& kingCoordinates, Player& firstPlayer, Player& secondPlayer)
	{
		bool result = false;
		
		for (auto iter = secondPlayer.getAllFigures().begin(); iter != secondPlayer.getAllFigures().end() && !result; iter++)
		{
			if ((*iter)->getType() == FigureType::ROCK || (*iter)->getType() == FigureType::QUEEN || (*iter)->getType() == FigureType::BISHOP)
			{
				result = isLineEmpty((*iter)->getCoordinates(), kingCoordinates);
			}
			
			if ((*iter)->getType() == FigureType::PAWN)
			{
				result = isReachebleForPawnToTake((*iter)->getCoordinates(), kingCoordinates, firstPlayer.getFigureByCoordinates(kingCoordinates)->getColor());
			}
			
			if ((*iter)->getType() == FigureType::KNIGHT)
			{
				result = isReachebleForKnight((*iter)->getCoordinates(), kingCoordinates);
			}
			
		}
		
		return result;
	}
	
	
	
	
//	std::list<Coordinates>* MovingValidator::getPawnPotentialPossibleCoordinates(Coordinates& coordinates)
//	{
//		
//	}
//	
//	std::list<Coordinates>* MovingValidator::getBishopPotentialPossibleCoordinates(Coordinates& coordinates)
//	{
//		
//	}
//	
//	std::list<Coordinates>* MovingValidator::getKnightPotentialPossibleCoordinates(Coordinates& coordinates)
//	{
//		
//	}
//	
//	std::list<Coordinates>* MovingValidator::getRockPotentialPossibleCoordinates(Coordinates& coordinates)
//	{
//		
//	}
//	
//	std::list<Coordinates>* MovingValidator::getQueenPotentialPossibleCoordinates(Coordinates& coordinates)
//	{
//		
//	}
//	
//	std::list<Coordinates>* MovingValidator::getKingPotentialPossibleCoordinates(Coordinates& coordinates)
//	{
//		
//	}
}
