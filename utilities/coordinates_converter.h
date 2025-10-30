#ifndef COORDINATES_CONVERTER
#define COORDINATES_CONVERTER

#include "../chess_entities/coordinates.h"
#include "chess_chars.h"

namespace chess_solver
{
	class CoordinatesConverter
	{
	public:
		// ћетод, возвращающий индекс горизонтали в массиве
		// row - обозначение горизонтали в шахматной нотации
		static char getRowIndexFromCoordinate(char row, char boardSize) { return boardSize - row; }
		
		// ћетод, возвращающий индекс вертикали в массиве
		// column - обозначение вертикали в шахматной нотации
		static char getColumnIndexFromCoordinate(char column) {	return column - ChessChars::FIRST_ENGLISH_LETTER; };
		
		static Coordinates makeChessCoordinatesFromIndexes(char rowIndex, char columnIndex, char boardSize)
		{
			return Coordinates(getChessColumnFromColumnIndex(columnIndex), getChessRowFromRowIndex(rowIndex, boardSize));
		}
		
	private:
		static char getChessColumnFromColumnIndex(char columnIndex) { return ChessChars::FIRST_ENGLISH_LETTER + columnIndex; }
		static char getChessRowFromRowIndex(char rowIndex, char boardSize) { return boardSize - rowIndex; }
		
	};
}

#endif
