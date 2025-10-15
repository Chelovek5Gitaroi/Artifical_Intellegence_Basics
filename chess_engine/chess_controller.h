#ifndef CHESS_CONTROLLER
#define CHESS_CONTROLLER

#include "../abstract_controller.h"

#include "game.h"
#include "..\\utilities/file_reader.h"
#include "..\\utilities/figure_creator.h"
#include "../utilities/command_parser.h"
#include "../solving/chess_solving/solver.h"

namespace chess_solver
{
	enum class MenuItem
	{
		DEEP_SEARCH
	};
	
	class ChessController : public AbstractController
	{
	public:
		static const std::string DEFAULT_FIGURE_DESCRIPTION_NAME;
		
		ChessController(AbstractSolver* solver, AbstractVisualizer* visualizer, int maximalDepth, char boardSize);
		
		void init(const std::string& figureDescriptionFileName);
		
		void show();
		
		void startGame();
		
		void control() override;
		
		MenuItem getSelectedItem() { return selectedMenuItem; }
		
	private:
		
		Game game;
		
		FileReader reader;
		
		FigureCreator figureCreator;
		
		Situation* makeStartSituation();
		
		Solver* initSolver();
		
		MenuItem selectedMenuItem;
		
		void enterSelectedItem();
		
	};
}

#endif
