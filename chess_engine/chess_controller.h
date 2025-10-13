#ifndef CHESS_CONTROLLER
#define CHESS_CONTROLLER

#include "../abstract_controller.h"

#include "game.h"
#include "..\\utilities/file_reader.h"
#include "..\\utilities/figure_creator.h"
#include "../utilities/command_parser.h"

namespace chess_solver
{
	class ChessController : public AbstractController
	{
	public:
		static const std::string DEFAULT_FIGURE_DESCRIPTION_NAME;
		
		ChessController(char boardSize);
		
		void init(const std::string& figureDescriptionFileName);
		
		void show();
		
		void startGame();
		
		void control() override;		
		
	private:
		
		Game game;
		
		FileReader reader;
		
		FigureCreator figureCreator;
		
		Situation* makeStartSituation();
		
//		Visualizer visualizer;
		
	};
}

#endif
