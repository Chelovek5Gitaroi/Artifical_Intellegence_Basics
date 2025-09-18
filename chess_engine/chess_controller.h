#ifndef CHESS_CONTROLLER
#define CHESS_CONTROLLER

#include "game.h"
#include "..\\utilities/visualizer.h"
#include "..\\utilities/file_reader.h"
#include "..\\utilities/figure_creator.h"
#include "../utilities/command_parser.h"

namespace chess_solver
{
	class ChessController
	{
	public:
		static const std::string DEFAULT_FIGURE_DESCRIPTION_NAME;
		
		ChessController(char boardSize, FigureColor firstPlayer);
		
		void init(std::string& figureDescriptionFileName);
		
		void show();
		
		void startGame();
		
	private:
		
		Game game;
		
		FileReader reader;
		
		FigureCreator figureCreator;
		
		Visualizer visualizer;
		
	};
}

#endif
