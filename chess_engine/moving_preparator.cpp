#include "moving_preparator.h"

#include <functional>

#include "../utilities/coordinates_converter.h"
#include "../utilities/comparator.h"

namespace chess_solver
{
	std::list<Coordinates>* MovingPreparator::getPawnPotentialPossibleCoordinates(Coordinates& coordinates, char boardSize, FigureColor figureColor)
	{
		std::list<Coordinates>* result = new std::list<Coordinates>();
		
		if (figureColor == FigureColor::WHITE)
		{
			
		}
		else
		{
			
		}
		
		
		if (1 <= coordinates.getColumn() - 1)
		{
			
		}
		
		if (coordinates.getColumn() + 1 <= CoordinatesConverter::MINIMAL_COLUMN_NAME + boardSize - 1)
		{
			
		}
		
		return result;
	}
	
	std::list<Coordinates>* MovingPreparator::getBishopPotentialPossibleCoordinates(Coordinates& coordinates, char boardSize)
	{
		std::list<Coordinates>* result = new std::list<Coordinates>();
		
		addDiagonalTilesToList(result, coordinates.getColumn() - 1, CoordinatesConverter::MINIMAL_COLUMN_NAME, coordinates.getRow() + 1, boardSize);
		
		addDiagonalTilesToList(result, coordinates.getColumn() + 1, CoordinatesConverter::MINIMAL_COLUMN_NAME + boardSize - 1, coordinates.getRow() + 1, boardSize);
		
		addDiagonalTilesToList(result, coordinates.getColumn() + 1, CoordinatesConverter::MINIMAL_COLUMN_NAME + boardSize - 1, coordinates.getRow() - 1, 1);
		
		addDiagonalTilesToList(result, coordinates.getColumn() - 1, CoordinatesConverter::MINIMAL_COLUMN_NAME, coordinates.getRow() - 1, 1);
		
		return result;
	}
	
	std::list<Coordinates>* MovingPreparator::getKnightPotentialPossibleCoordinates(Coordinates& coordinates, char boardSize)
	{
		
	}
	
	std::list<Coordinates>* MovingPreparator::getRockPotentialPossibleCoordinates(Coordinates& coordinates, char boardSize)
	{
		std::list<Coordinates>* result = new std::list<Coordinates>();
		
		addRowTilesToList(result, coordinates.getColumn() + 1, CoordinatesConverter::MINIMAL_COLUMN_NAME + boardSize - 1, coordinates.getRow());
		
		addRowTilesToList(result, coordinates.getColumn() - 1, CoordinatesConverter::MINIMAL_COLUMN_NAME, coordinates.getRow());
 		
 		addColumnTilesToList(result, coordinates.getColumn(), coordinates.getRow() + 1, boardSize);
 		
		addColumnTilesToList(result, coordinates.getColumn(), coordinates.getRow() - 1, 1);
		
		return result;
	}
	
	std::list<Coordinates>* MovingPreparator::getQueenPotentialPossibleCoordinates(Coordinates& coordinates, char boardSize)
	{
		std::list<Coordinates>* result = new std::list<Coordinates>();
		
		addRowTilesToList(result, coordinates.getColumn() + 1, CoordinatesConverter::MINIMAL_COLUMN_NAME + boardSize - 1, coordinates.getRow());
				
		addRowTilesToList(result, coordinates.getColumn() - 1, CoordinatesConverter::MINIMAL_COLUMN_NAME, coordinates.getRow());
 		
 		addColumnTilesToList(result, coordinates.getColumn(), coordinates.getRow() + 1, boardSize);
 		
		addColumnTilesToList(result, coordinates.getColumn(), coordinates.getRow() - 1, 1);
		
		addDiagonalTilesToList(result, coordinates.getColumn() - 1, CoordinatesConverter::MINIMAL_COLUMN_NAME, coordinates.getRow() + 1, boardSize);
		
		addDiagonalTilesToList(result, coordinates.getColumn() + 1, CoordinatesConverter::MINIMAL_COLUMN_NAME + boardSize - 1, coordinates.getRow() + 1, boardSize);
		
		addDiagonalTilesToList(result, coordinates.getColumn() + 1, CoordinatesConverter::MINIMAL_COLUMN_NAME + boardSize - 1, coordinates.getRow() - 1, 1);
		
		addDiagonalTilesToList(result, coordinates.getColumn() - 1, CoordinatesConverter::MINIMAL_COLUMN_NAME, coordinates.getRow() - 1, 1);
		
		return result;	
	}
	
	std::list<Coordinates>* MovingPreparator::getKingPotentialPossibleCoordinates(Coordinates& coordinates, char boardSize)
	{
		std::list<Coordinates>* result = new std::list<Coordinates>();
		
		if (coordinates.getRow() + 1 <= boardSize)
		{
			result->push_back(Coordinates(coordinates.getColumn(), coordinates.getRow() + 1));
			
			if (CoordinatesConverter::MINIMAL_COLUMN_NAME <= coordinates.getColumn() - 1)
			{
				result->push_back(Coordinates(coordinates.getColumn() - 1, coordinates.getRow() + 1));
			}
			
			if (coordinates.getColumn() + 1 <= CoordinatesConverter::MINIMAL_COLUMN_NAME + boardSize - 1)
			{
				result->push_back(Coordinates(coordinates.getColumn() + 1, coordinates.getRow() + 1));
			}
		}
		
		if (CoordinatesConverter::MINIMAL_COLUMN_NAME <= coordinates.getColumn() - 1)
		{
			result->push_back(Coordinates(coordinates.getColumn() - 1, coordinates.getRow()));
		}
		
		if (coordinates.getColumn() + 1 <= CoordinatesConverter::MINIMAL_COLUMN_NAME + boardSize - 1)
		{
			result->push_back(Coordinates(coordinates.getColumn() + 1, coordinates.getRow()));
		}
		
		if (1 <= coordinates.getRow())
		{
			result->push_back(Coordinates(coordinates.getColumn(), coordinates.getRow() - 1));
			
			if (CoordinatesConverter::MINIMAL_COLUMN_NAME <= coordinates.getColumn() - 1)
			{
				result->push_back(Coordinates(coordinates.getColumn() - 1, coordinates.getRow() - 1));
			}
			
			if (coordinates.getColumn() + 1 <= CoordinatesConverter::MINIMAL_COLUMN_NAME + boardSize - 1)
			{
				result->push_back(Coordinates(coordinates.getColumn() + 1, coordinates.getRow() - 1));
			}
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
			destList->push_back(Coordinates(chessRow, column));
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
		
}
