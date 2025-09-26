#include "coordinates_converter.h"

namespace chess_solver
{
	char CoordinatesConverter::getRowIndexFromCoordinate(char row, char boardSize)
	{
		return boardSize - row;
	}
	
	char CoordinatesConverter::getColumnIndexFromCoordinate(char column)
	{
		return column - MINIMAL_COLUMN_NAME;
	}
}
