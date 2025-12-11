#ifndef SITUATION
#define SITUATION

#include <list>

#include "../abstract_situation.h"

#include "../../chess_entities/figure.h"
#include "../../chess_entities/board.h"
#include "../../utilities/command.h"


namespace chess_solver
{
	//
	// Класс, описывающий ситуацию на шахматной доске
	//
	class Situation : public AbstractSituation
	{
	public:
		// Конструктор
		// std::list<Figure*>& whiteFigures - список указателей на белые фигуры
		// std::list<Figure*>& blackFigures - список указателей на черные фигуры
		// Board& board - объект, описывающий шахматную доску
		// FigureColor currentPlayer - цвет фигур игрока, который должен делать ход
		// FigureColor targetPlayer - цвет фигур игрока, который должен победить
		Situation(std::list<Figure*>& whiteFigures, std::list<Figure*>& blackFigures, Board& board, FigureColor currentPlayer, FigureColor targetPlayer);
		
		// Конструктор копирования
		// Situation& other - ситуация, копия которой делается
		Situation(Situation& other);
		
		// Деструктор
		~Situation();
		
		// Метод, возвращающий список белых фигур
		std::list<Figure*>& getWhiteFigures() { return whiteFigures; }
		
		// Метод, возвращающий список чёрных фигур
		std::list<Figure*>& getBlackFigures() { return blackFigures; }
		
		// Метод, возвращающий цвет фигур игрока, который должен победить
		FigureColor getTargetPlayer() { return targetPlayer; }
		
		// Метод, возвращающий цвет фигур игрока, который должен делать ход
		FigureColor getCurrentPlayer() { return currentPlayer; }
		
		// Метод, возвращающий объект, описывающий щахматную доску
		Board& getBoard() { return board; }
		
		// Оператор, сравнивающий данный объект с другой ситуацией
		// Situation& other - другая ситуация
		bool operator==(const Situation& other) const;
		
		// Метод, устанавливающий цвет фигур игрока, который должен делать ход
		void setCurrentPlayer(FigureColor currentPlayer) { this->currentPlayer = currentPlayer; }
		
		// Метод, возвращающий указатель на фигуру по её координатам на доске
		// Coordinates& coordinates - координаты фигуры в шахматой нотации
		Figure* getFigure(const Coordinates& coordinates);
		
		AbstractSituation* copy() override;
		
		// Метод, возвращающий строковое представление объекта
		std::string toString() override;
		
	private:
		// Список указателей на белые фигуры
		std::list<Figure*> whiteFigures;
		
		// Список указателей на черные фигуры
		std::list<Figure*> blackFigures;
		
		// Цвет фигур игрока, который должен победить
		FigureColor targetPlayer;
		
		// Цвет фигур игрока, который должен делать ход
		FigureColor currentPlayer;
		
		// Объект, описывающий шахматную доску
		Board board;
		
		// Метод, копирующий объекты фигур из первого списка во второй
		void insertListItemsToOtherList(std::list<Figure*>& sourceList, std::list<Figure*>& destList);
		
		// Метод, возвращающий указатель на шахматную фигуру из списка по её координатам
		Figure* getFigureFormList(const Coordinates& coordinates, std::list<Figure*>& figures);
	};	
}

#endif
