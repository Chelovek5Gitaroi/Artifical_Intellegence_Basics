#include "chess_controller.h"

namespace chess_solver
{
//	const std::map<FigureType, char> START_FIGURES_NUMBERS =
//		{{FigureType::KING, 1},
//		 {FigureType::QUEEN, 1},
//		 {FigureType::ROCK, 2},
//		 {FigureType::BISHOP, 2},
//		 {FigureType::KNIGHT, 2},
//		 {FigureType::PAWN, 8}};
	
	const std::string ChessController::DEFAULT_FIGURE_DESCRIPTION_NAME = "figures.txt";
	
	ChessController::ChessController(char boardSize) : game(boardSize), figureCreator(boardSize), visualizer(this->game.getBoard(), this->game.getFirstPlayer(), this->game.getSecondPlayer())
	{
	}
	
	void ChessController::show()
	{
		visualizer.render();
	}
	
	void ChessController::init(std::string& figureDescriptionFileName)
	{
		this->reader.readFigureFile(figureDescriptionFileName);
		
		std::list<Figure*>* blackFigures = this->figureCreator.makeFigureList(this->reader.getBlackFigures(), FigureColor::BLACK);
		std::list<Figure*>* whiteFigures = this->figureCreator.makeFigureList(this->reader.getWhiteFigures(), FigureColor::WHITE);
		
		for (Figure* figure : *whiteFigures)
		{
			this->game.getFirstPlayer()->addFigure(figure);
		}
		
		delete whiteFigures;
		
		for (Figure* figure : *blackFigures)
		{
			this->game.getSecondPlayer()->addFigure(figure);
		}
		
		delete blackFigures;
		
	}
}
