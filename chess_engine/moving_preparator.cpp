#include "moving_preparator.h"

#include <functional>

#include "../utilities/coordinates_converter.h"
#include "../utilities/comparator.h"

namespace chess_solver
{
	std::list<Coordinates>* MovingPreparator::getPotentialPossibleCoordinates(const Coordinates& coordinates, FigureType type, FigureColor color, char boardSize)
	{
		std::list<Coordinates>* result = nullptr;
		
		switch (type)
		{
		case FigureType::PAWN:
			result = getPawnPotentialPossibleCoordinates(coordinates, boardSize, color);
			break;
			
		case FigureType::KNIGHT:
			result = getKnightPotentialPossibleCoordinates(coordinates, boardSize);
			break;
			
		case FigureType::BISHOP:
			result = getBishopPotentialPossibleCoordinates(coordinates, boardSize);
			break;
			
		case FigureType::ROCK:
			result = getRockPotentialPossibleCoordinates(coordinates, boardSize);
			break;
			
		case FigureType::QUEEN:
			result = getQueenPotentialPossibleCoordinates(coordinates, boardSize);
			break;
			
		case FigureType::KING:
			result = getKingPotentialPossibleCoordinates(coordinates, boardSize);
			break;
		}
		
		return result;
	}
	
	std::list<Coordinates>* MovingPreparator::getPawnPotentialPossibleCoordinates(const Coordinates& coordinates, char boardSize, FigureColor figureColor)
	{
		std::list<Coordinates>* result = new std::list<Coordinates>();
		
		if (figureColor == FigureColor::WHITE)
		{
			if (coordinates.getRow() + 1 <= boardSize)
			{
				addNextTilesInRowToList(result, coordinates.getColumn(), coordinates.getRow() + 1, boardSize);
			}
		}
		else
		{
			if (coordinates.getRow() - 1 >= 1)
			{
				addNextTilesInRowToList(result, coordinates.getColumn(), coordinates.getRow() - 1, boardSize);
			}
		}
		
		return result;
	}
	
	std::list<Coordinates>* MovingPreparator::getBishopPotentialPossibleCoordinates(const Coordinates& coordinates, char boardSize)
	{
		std::list<Coordinates>* result = new std::list<Coordinates>();
		
		if (1 < coordinates.getRow())
		{
			if (ChessChars::FIRST_ENGLISH_LETTER < coordinates.getColumn())
			{
				addDiagonalTilesToList(result, coordinates.getColumn() - 1, ChessChars::FIRST_ENGLISH_LETTER, coordinates.getRow() - 1, 1);
			}
			
			if (coordinates.getColumn() < ChessChars::FIRST_ENGLISH_LETTER + boardSize - 1)
			{
				addDiagonalTilesToList(result, coordinates.getColumn() + 1, ChessChars::FIRST_ENGLISH_LETTER + boardSize - 1, coordinates.getRow() - 1, 1);
			}
		}
		
		if (coordinates.getRow() < boardSize)
		{
			if (ChessChars::FIRST_ENGLISH_LETTER < coordinates.getColumn())
			{
				addDiagonalTilesToList(result, coordinates.getColumn() - 1, ChessChars::FIRST_ENGLISH_LETTER, coordinates.getRow() + 1, boardSize);
			}
			
			if (coordinates.getColumn() < ChessChars::FIRST_ENGLISH_LETTER + boardSize - 1)
			{
				addDiagonalTilesToList(result, coordinates.getColumn() + 1, ChessChars::FIRST_ENGLISH_LETTER + boardSize - 1, coordinates.getRow() + 1, boardSize);
			}
		}
		
		return result;
	}
	
	std::list<Coordinates>* MovingPreparator::getKnightPotentialPossibleCoordinates(const Coordinates& coordinates, char boardSize)
	{
		std::list<Coordinates>* result = new std::list<Coordinates>();
		
		if (1 <= coordinates.getRow() - 2)
		{
			if (ChessChars::FIRST_ENGLISH_LETTER <= coordinates.getColumn() - 1)
			{
				result->push_back(Coordinates(coordinates.getColumn() - 1, coordinates.getRow() - 2));
			}
			
			if (coordinates.getColumn() + 1 <= ChessChars::FIRST_ENGLISH_LETTER + boardSize - 1)
			{
				result->push_back(Coordinates(coordinates.getColumn() + 1, coordinates.getRow() - 2));
			}
		}
		
		if (1 <= coordinates.getRow() - 1)
		{
			if (ChessChars::FIRST_ENGLISH_LETTER <= coordinates.getColumn() - 2)
			{
				result->push_back(Coordinates(coordinates.getColumn() - 2, coordinates.getRow() - 1));
			}
			
			if (coordinates.getColumn() + 2 <= ChessChars::FIRST_ENGLISH_LETTER + boardSize - 1)
			{
				result->push_back(Coordinates(coordinates.getColumn() + 2, coordinates.getRow() - 1));
			}
		}
		
		if (coordinates.getRow() + 1 <= boardSize)
		{
			if (ChessChars::FIRST_ENGLISH_LETTER <= coordinates.getColumn() - 2)
			{
				result->push_back(Coordinates(coordinates.getColumn() - 2, coordinates.getRow() + 1));
			}
			
			if (coordinates.getColumn() + 2 <= ChessChars::FIRST_ENGLISH_LETTER + boardSize - 1)
			{
				result->push_back(Coordinates(coordinates.getColumn() + 2, coordinates.getRow() + 1));
			}
		}
		
		if (coordinates.getRow() + 2 <= boardSize)
		{
			if (ChessChars::FIRST_ENGLISH_LETTER <= coordinates.getColumn() - 1)
			{
				result->push_back(Coordinates(coordinates.getColumn() - 1, coordinates.getRow() + 2));
			}
			
			if (coordinates.getColumn() + 1 <= ChessChars::FIRST_ENGLISH_LETTER + boardSize - 1)
			{
				result->push_back(Coordinates(coordinates.getColumn() + 1, coordinates.getRow() + 2));
			}
		}
				
		return result;
	}
	
	std::list<Coordinates>* MovingPreparator::getRockPotentialPossibleCoordinates(const Coordinates& coordinates, char boardSize)
	{
		std::list<Coordinates>* result = new std::list<Coordinates>();
	
		if (ChessChars::FIRST_ENGLISH_LETTER < coordinates.getColumn())
		{
			addRowTilesToList(result, coordinates.getColumn() - 1, ChessChars::FIRST_ENGLISH_LETTER, coordinates.getRow());
		}
		
		if (coordinates.getColumn() < ChessChars::FIRST_ENGLISH_LETTER + boardSize - 1)
		{
			addRowTilesToList(result, coordinates.getColumn() + 1, ChessChars::FIRST_ENGLISH_LETTER + boardSize - 1, coordinates.getRow());
		}
		
		if (1 < coordinates.getRow())
		{
			addColumnTilesToList(result, coordinates.getColumn(), coordinates.getRow() - 1, 1);
		}
		
		if (coordinates.getRow() < ChessChars::FIRST_ENGLISH_LETTER + boardSize - 1)
		{
			addColumnTilesToList(result, coordinates.getColumn(), coordinates.getRow() + 1, boardSize);
		}
		
		return result;
	}
	
	std::list<Coordinates>* MovingPreparator::getQueenPotentialPossibleCoordinates(const Coordinates& coordinates, char boardSize)
	{
		std::list<Coordinates>* result = new std::list<Coordinates>();
		
		if (ChessChars::FIRST_ENGLISH_LETTER < coordinates.getColumn())
		{
			if (1 < coordinates.getRow())
			{
				addDiagonalTilesToList(result, coordinates.getColumn() - 1, ChessChars::FIRST_ENGLISH_LETTER, coordinates.getRow() - 1, 1);
			}
			
			addRowTilesToList(result, coordinates.getColumn() - 1, ChessChars::FIRST_ENGLISH_LETTER, coordinates.getRow());
			
			if (coordinates.getRow() < boardSize)
			{
				addDiagonalTilesToList(result, coordinates.getColumn() - 1, ChessChars::FIRST_ENGLISH_LETTER, coordinates.getRow() + 1, boardSize);
			}
		}
		
		if (1 < coordinates.getRow())
		{
			addColumnTilesToList(result, coordinates.getColumn(), coordinates.getRow() - 1, 1);	
		}
			
		if (coordinates.getRow() < boardSize)
		{
			addColumnTilesToList(result, coordinates.getColumn(), coordinates.getRow() + 1, boardSize);
		}
		
		if (coordinates.getColumn() < ChessChars::FIRST_ENGLISH_LETTER + boardSize - 1)
		{
			if (1 < coordinates.getRow())
			{
				addDiagonalTilesToList(result, coordinates.getColumn() + 1, ChessChars::FIRST_ENGLISH_LETTER + boardSize - 1, coordinates.getRow() - 1, 1);
			}
			
			addRowTilesToList(result, coordinates.getColumn() + 1, ChessChars::FIRST_ENGLISH_LETTER + boardSize - 1, coordinates.getRow());
			
			if (coordinates.getRow() < boardSize)
			{
				addDiagonalTilesToList(result, coordinates.getColumn() + 1, ChessChars::FIRST_ENGLISH_LETTER + boardSize - 1, coordinates.getRow() + 1, boardSize);
			}
		}

		return result;	
	}
	
	std::list<Coordinates>* MovingPreparator::getKingPotentialPossibleCoordinates(const Coordinates& coordinates, char boardSize)
	{
		std::list<Coordinates>* result = new std::list<Coordinates>();
		
		if (coordinates.getRow() + 1 <= boardSize)
		{
			addNextTilesInRowToList(result, coordinates.getColumn(), coordinates.getRow() + 1, boardSize);
		}
		
		if (ChessChars::FIRST_ENGLISH_LETTER <= coordinates.getColumn() - 1)
		{
			result->push_back(Coordinates(coordinates.getColumn() - 1, coordinates.getRow()));
		}
		
		if (coordinates.getColumn() + 1 <= ChessChars::FIRST_ENGLISH_LETTER + boardSize - 1)
		{
			result->push_back(Coordinates(coordinates.getColumn() + 1, coordinates.getRow()));
		}
		
		if (1 <= coordinates.getRow() - 1)
		{
			addNextTilesInRowToList(result, coordinates.getColumn(), coordinates.getRow() - 1, boardSize);
		}
		
		return result;
	}
	
	void MovingPreparator::addRowTilesToList(std::list<Coordinates>* destList, char chessColumnFirst, char chessColumnLast, char chessRow)
	{
		std::function<bool(char, char)> continueCondition = Comparator<char>::lessEqual;
		
		char step = 1;		
		
		if (chessColumnFirst > chessColumnLast)
		{
			continueCondition = Comparator<char>::greaterEqual;
			step *= -1;
		}
		
		for (char column = chessColumnFirst; continueCondition(column, chessColumnLast); column += step)
		{
			destList->push_back(Coordinates(column, chessRow));
		}
	}
	
	void MovingPreparator::addColumnTilesToList(std::list<Coordinates>* destList, char chessColumn, char chessRowFirst, char chessRowLast)
	{
		std::function<bool(char, char)> continueCondition = Comparator<char>::lessEqual;
		
		char step = 1;
		
		if (chessRowFirst > chessRowLast)
		{
			continueCondition = Comparator<char>::greaterEqual;
			step *= -1;
		}
		
		for (char row = chessRowFirst; continueCondition(row, chessRowLast); row += step)
		{
			destList->push_back(Coordinates(chessColumn, row));
		}
	}
	
	void MovingPreparator::addDiagonalTilesToList(std::list<Coordinates>* destList, char chessColumnFirst, char chessColumnLast, char chessRowFirst, char chessRowLast)
	{
		std::function<bool(char, char)> continueConditionRow = Comparator<char>::lessEqual;
		
		char stepRow = 1;
		
		if (chessRowFirst > chessRowLast)
		{
			continueConditionRow = Comparator<char>::greaterEqual;
			stepRow *= -1;
		}
		
		std::function<bool(char, char)> continueConditionColumn = Comparator<char>::lessEqual;
		
		char stepColumn = 1;
		
		if (chessColumnFirst > chessColumnLast)
		{
			continueConditionColumn = Comparator<char>::greaterEqual;
			stepColumn *= -1;
		}
		
		for (char row = chessRowFirst, column = chessColumnFirst; continueConditionRow(row, chessRowLast) &&
			continueConditionColumn(column, chessColumnLast); row += stepRow, column += stepColumn)
		{
			destList->push_back(Coordinates(column, row));
		}
	}
	
	void MovingPreparator::addNextTilesInRowToList(std::list<Coordinates>* destList, char chessColumn, char chessRow, char boardSize)
	{
		if (ChessChars::FIRST_ENGLISH_LETTER <= chessColumn - 1)
		{	
			destList->push_back(Coordinates(chessColumn - 1, chessRow));
		}
		
		destList->push_back(Coordinates(chessColumn, chessRow));
		
		if (chessColumn + 1 <= ChessChars::FIRST_ENGLISH_LETTER + boardSize - 1)
		{
			destList->push_back(Coordinates(chessColumn + 1, chessRow));
		}
	}
	
}
