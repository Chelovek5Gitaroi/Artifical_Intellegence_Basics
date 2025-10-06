#ifndef COORDINATES_CONVERTER
#define COORDINATES_CONVERTER

#include "../chess_entities/coordinates.h"

namespace chess_solver
{
	class CoordinatesConverter
	{
	public:
		static const char MINIMAL_COLUMN_NAME = 'a';
		
		// ћетод, возвращающий индекс горизонтали в массиве
		// row - обозначение горизонтали в шахматной нотации
		static char getRowIndexFromCoordinate(char row, char boardSize) { return boardSize - row; }
		
		// ћетод, возвращающий индекс вертикали в массиве
		// column - обозначение вертикали в шахматной нотации
		static char getColumnIndexFromCoordinate(char column) {	return column - MINIMAL_COLUMN_NAME; };
		
		static Coordinates makeChessCoordinatesFromIndexes(char rowIndex, char columnIndex, char boardSize)
		{
			return Coordinates(getChessColumnFromColumnIndex(columnIndex), getChessRowFromRowIndex(rowIndex, boardSize));
		}
		
	private:
		static char getChessColumnFromColumnIndex(char columnIndex) { return MINIMAL_COLUMN_NAME + columnIndex; }
		static char getChessRowFromRowIndex(char rowIndex, char boardSize) { return boardSize - rowIndex; }
		
	};
}

#endif
