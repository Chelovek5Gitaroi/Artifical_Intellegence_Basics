#ifndef CHESS_CONTROLLER
#define CHESS_CONTROLLER

#include <Windows.h>
#include <WinUser.h>

#include "../abstract_controller.h"

#include <map>
#include <vector>

#include "game.h"
#include "..\\utilities/file_reader.h"
#include "..\\utilities/figure_creator.h"
#include "../utilities/command_parser.h"
#include "../solving/chess_solving/solver.h"

namespace chess_solver
{
	class ChessController : public AbstractController
	{
	public:
		static const char BOARD_SIZE = 8;
		
		static const std::string DEFAULT_FIGURE_DESCRIPTION_NAME;
		
		ChessController(AbstractSolver* solver, AbstractVisualizer* visualizer, char boardSize);
		
		void init(const std::string& figureDescriptionFileName);
		
		void show();
		
		void startGame();
		
		void control() override;
		
	private:
		enum class MenuItem
		{
			DEEP_SEARCH = 1,
			EXIT
		};
		
		static const std::string MENU_TIILE;
		static const std::string MENU_ITEM_DEEP_SEARCH;
		static const std::string MENU_ITEM_EXIT;

		static const unsigned short CONTROLLER_STATE_RUNNING = 1 << 7;
		static const unsigned short CONTROLLER_STATE_MENU_SELECT_SOLVING_METHOD = 1 << 6;
		static const unsigned short CONTROLLER_STATE_SELECTING_SITUATION = 1 << 5;

		static const std::map<MenuItem, std::string> menu;
		
		unsigned short controllerState;
		
		Game game;
		
		FileReader reader;
		
		FigureCreator figureCreator;
		
		Situation* makeStartSituation();
		
		Solver* initSolver();
		
		MenuItem selectedMenuItem;
		
		void enterSelectedItem();
		
		std::vector<std::pair<std::string, bool>> menuStrings;
		
		void makeMenuStrings(const std::string& title);
		
		void selectItem(MenuItem item);
		
		void selectNextMenuItem();
		
		void selectPreviousItem();
		
		void selectNextItem();
		
		void processKeyEnter();
		
		void processKeyUp();
		
		void processKeyDown();
	};
}

#endif
