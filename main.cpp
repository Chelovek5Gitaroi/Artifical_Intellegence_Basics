// В данной программе реализуется абстрактный интеллектуальный решатель.
// Работа решателя проверяется на примере поиска мата в два хода.
//
// Программист - студент группы 543М Рязанского государственного радиотехнического университета имени В.Ф.Уткина
// Шестопалов Леонид Алексеевич
//
// *****************
//
// 30.10.2025 протестирована работа обхода в глубину
//
// *****************
// 
// Перед запуском программы необходимо заполнить файл figures.txt
// Файл figures.txt должен находиться в одном каталоге с запускаемым файлом
// 
// Структура файла figures.txt:
// Первая строка - игрок, который должен ходить в начальной ситуации (black или white)
// Список белых фигур
// Разделитель - ... (три точки)
// Список чёрных фигур
// 
// Описание каждой новой фигуры должно начинаться с новой строки
// Строка с описанием фигуры содержит:
// * Символ фигуры в шахматной нотации (p - пешка, B - слон, N - конь, R - ладья, Q - ферзь, K - король)
// * Пробел
// * Координаты в шахматной нотации (буква столбца и цифра строки, не разделённые пробелом)


#include <iostream>
#include <string>
#include <list>

#include "solving/chess_solving/solver.h"
#include "chess_engine/chess_controller.h"
#include "abstract_controller.h"
#include "visualizing/chess_visualizing/visualizer.h"

using namespace chess_solver;

int main(int argc, char** argv)
{
	system("chcp 1251");
	
	AbstractController* controller = new ChessController(new Solver(), new Visualizer(ChessController::BOARD_SIZE), ChessController::BOARD_SIZE);
	
	controller->control();
	
	delete controller;
	
	return 0;
}
