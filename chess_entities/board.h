#ifndef BOARD
#define BOARD

#include "coordinates.h"
#include "tile.h"


namespace chess_solver
{	
	/*
	 * Класс, описывающий игровую доску
	 */
	class Board
	{
	public:
		//Обозначение крайней левой вертикали доски
		static const char MINIMAL_COLUMN_NAME = 'a';	
		
		// Конструктор
		//
		// boardSize - количество горизонталей и вертикалей доски
		Board(char boardSize);
		
		
		Board(Board& other);
		
		//Деструктор
		~Board();
		
		// Геттер для поля boardSize
		char getBoardSize() const { return this->boardSize; };
		
		// Метод возвращающий ссылку на клетку доски
		// coordinates - координаты клетки в шахматной нотации
		Tile& getTileByCoordinates(const Coordinates& coordinates);
		
		// Метод возвращающий ссылку на клетку доски
		// column - вертикаль в шахматной нотации
		// row - горизонталь в шахматной нотации
		Tile& getTileByCoordinates(char column, char row);
		
	private:
		// Длина стороны доски в клетках
		char boardSize;
		
		// Двумерный массив указателей на клетки
		Tile*** tiles;
		
		// Метод, создающий клетки в массиве при инициализации
		void createTiles();
		
		// Метод, возвращающий индекс горизонтали в массиве
		// row - обозначение горизонтали в шахматной нотации
		char getRowIndexFromCoordinate(const char row) const;
		
		// Метод, возвращающий индекс вертикали в массиве
		// column - обозначение вертикали в шахматной нотации
		char getColumnIndexFromCoordinate(const char column) const;
		
		void prepareEmptyTilesArray();
	};
}

#endif
