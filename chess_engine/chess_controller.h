#ifndef CHESS_CONTROLLER
#define CHESS_CONTROLLER

//#include <map>

#include "game.h"
#include "..\\utilities/visualizer.h"
#include "..\\utilities/file_reader.h"
#include "..\\utilities/figure_creator.h"

namespace chess_solver
{
	class ChessController
	{
	public:
		static const std::string DEFAULT_FIGURE_DESCRIPTION_NAME;
		
//		static const std::map<FigureType, char> START_FIGURES_NUMBERS;
		
		ChessController(char boardSize);
		
		void init(std::string& figureDescriptionFileName);
		
		void show();
		
		
	private:
		
		Game game;
		
		FileReader reader;
		
		FigureCreator figureCreator;
		
		Visualizer visualizer;
	};
}

#endif
