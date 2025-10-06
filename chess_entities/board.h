#ifndef BOARD
#define BOARD

#include "../utilities/coordinates_converter.h"

namespace chess_solver
{	
	/*
	 * Класс, описывающий игровую доску
	 */
	class Board
	{
	public:
		// Конструктор
		//
		// boardSize - количество горизонталей и вертикалей доски
		Board(char boardSize);
		
		// Конструктор копирования
		Board(const Board& other);
		
		//Деструктор 
		~Board();
		
		// Геттер для поля boardSize
		char getBoardSize() const { return this->boardSize; };
		
		// Метод, возвращающий занятость клетки по её координатам, записанным в шахматной нотации
		bool getTileOccupancyByCoordinates(const Coordinates& coordinates) const;
		
		// Метод, возвращающий занятость клетки по её индексам в массиве
		bool getTileOccupancyByCoordinates(char column, char row) const;
		
		// Метод, устанавливающий занятость клетки по координатам, записанным в шахматной нотации
		void setOccupancyByCoordinates(const Coordinates& coordinates, bool occupancy);
		
		// Перегрузка оператора ==
		bool operator==(const Board& other) const;
			
	private:
		// Длина стороны доски в клетках
		char boardSize;
		
		// Двумерный массив указателей на клетки
		bool** tilesOccupancy;
		
		// Метод, создающий клетки в массиве при инициализации
		void createEmptyTileOccupancyArray();
	};
}

#endif
