#ifndef CHESS_CONTROLLER
#define CHESS_CONTROLLER

#include <Windows.h>
#include <WinUser.h>

#include <thread>
#include <chrono>

#include "../abstract_controller.h"

#include <map>
#include <vector>

#include "game.h"
#include "..\\utilities/file_reader.h"
#include "..\\utilities/figure_creator.h"
#include "../utilities/command_parser.h"
#include "../solving/chess_solving/solver.h"
#include "../visualizing/chess_visualizing/visualizer.h"

namespace chess_solver
{
	//
	// Класс, управляющий работой приложения
	//
	class ChessController : public AbstractController
	{
	public:
		// Размер стороны шахматной доски
		static const char BOARD_SIZE = 8;
		
		// Название файла, из которого загружается описание начальной ситуации
		static const std::string DEFAULT_FIGURE_DESCRIPTION_NAME;
		
		// Конструктор
		// AbstractSolver* solver - решатель
		// AbstractVisualizer* visualizer - визуализатор
		// char boardSize - длина стороны шахматной доски
		ChessController(AbstractSolver* solver, AbstractVisualizer* visualizer, char boardSize);
		
		// Метод, выполняющий инициализацию контоллера
		void init(const std::string& figureDescriptionFileName);
		
		// Метод, содержащий вызовы методов решения
		void control() override;
		
	private:
		enum class MenuItem
		{
			DEEP_SEARCH = 1,
			WIDE_SEARCH,
			GRADIENT_SEARCH,
			BEST_PARTICLE_WAY_SEARCH,
			SELECT_SITUATION,
			EXIT
		};
		
		// Приветственное сообщение
		static const std::string GREETING_MESSAGE;
		
		// Заголовок меню
		static const std::string MENU_TIILE;
		
		// Пункт меню, вызывающий обход в глубину
		static const std::string MENU_ITEM_DEEP_SEARCH;
		
		// Пункт меню, вызывающий обход в ширину
		static const std::string MENU_ITEM_WIDE_SEARCH;
		
		//Пункт меню, вызывающий поиск по градиенту
		static const std::string MENU_ITEM_GRADIENT_SEARCH;

		static const std::string MENU_ITEM_BEST_PARTICLE_WAY_SEARCH;

		// Пункт меню, вызывающий переход к просмотру ситуаций
		static const std::string MENU_ITEM_SELECT_SITUATION;
		
		// Пункт меню, вызывающий завершение работы приложения
		static const std::string MENU_ITEM_EXIT;
		
		// Сообщение об отсутствии решения
		static const std::string MESSAGE_NO_SOLVE;
		
		// Сообщение о найденном решении
		static const std::string MESSAGE_SOLVE;

		// Значение флага работы приложения
		static const unsigned short CONTROLLER_STATE_RUNNING = 1 << 7;
		
		// Значение флага выбора действия
		static const unsigned short CONTROLLER_STATE_MENU_SELECT_SOLVING_METHOD = 1 << 6;
		
		// Значение флага выбора ситуации
		static const unsigned short CONTROLLER_STATE_SELECTING_SITUATION = 1 << 5;

		// Пункты меню с их индексами
		static const std::map<MenuItem, std::string> menu;
		
		// Набор флагов состояния приложения
		unsigned short controllerState;
		
		Game game;
		
		// Класс, загружающий из файла описание начальной ситуации
		FileReader reader;
		
		// Класс, создающий шахматные фигуры по их описанию
		FigureCreator figureCreator;
		
		// Метод, формирующий начальную ситуацию
		Situation* makeStartSituation();
		
		// Метод, выполняющий инициализацию решателя
		Solver* initSolver();
		
		// Узел дерева, хранящий отображаемую ситуацию
		OptionTree* currentTreeNode;
		
		// Узел дерева, хранящий целевую ситуацию
		OptionTree* solve;
		
		// Узел дерева, хранящий начальную ситуацию
		OptionTree* solveRoot;
		
		// Выбранный пункт меню
		MenuItem selectedMenuItem;
		
		// Метод, запускающий действие, соответствующее выбранному пункту меню
		void enterSelectedItem();
		
		// Названия пунктов меню и отметки о выборе
		std::vector<std::pair<std::string, bool>> menuStrings;
		
		// Метод, создающий список имён пунктов меню и отметок о их выборе
		void makeMenuStrings(const std::string& title);
		
		// Список описаний ходов и отметок о их выборе
		std::vector<std::pair<std::string, bool>> solvingMenu;
		
		
		void selectItem(MenuItem item);
		
		void selectNextMenuItem();
		
		void selectPreviousItem();
		
		void selectNextItem();
		
		void processKeyEnter();
		
		void processKeyUp();
		
		void processKeyDown();
		
		void processKeyEscape();
		
		void selectSituation(OptionTree* tree);
		
		void makeSolvingMenu(std::list<AbstractCommand*>* commandList);
		
		OptionTree* copySolveTree(OptionTree* node);
		
		OptionTree* getSolveRoot(OptionTree* targetNode);
		
		void prepareToUseSolvingMethod();
		
		void showSolvingResult(OptionTree* target);
		
	};
}

#endif
