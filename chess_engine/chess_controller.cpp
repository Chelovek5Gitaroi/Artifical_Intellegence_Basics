#include "chess_controller.h"

namespace chess_solver
{
	
	const std::string ChessController::DEFAULT_FIGURE_DESCRIPTION_NAME = "figures.txt";
	
	ChessController::ChessController(AbstractSolver* solver, AbstractVisualizer* visualizer, int maximalDepth, char boardSize) : AbstractController(solver, visualizer, maximalDepth), game(boardSize), figureCreator(boardSize)
	{
		init(DEFAULT_FIGURE_DESCRIPTION_NAME);
		
		this->selectedMenuItem = MenuItem::DEEP_SEARCH;
	}
	
	void ChessController::init(const std::string& figureDescriptionFileName)
	{
		this->reader.readFigureFile(figureDescriptionFileName);
		
		this->game.setCurrentPlayer(this->reader.getMovingPlayerColor());
		
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
	
	void ChessController::control()
	{
		init(DEFAULT_FIGURE_DESCRIPTION_NAME);
		
		
		
		
		
	}
	
	void ChessController::enterSelectedItem()
	{
		switch (selectedMenuItem)
		{
		case MenuItem::DEEP_SEARCH:
			this->initSolver()->useDeepSearch(this->getMaximalDepth());
			break;
		default:
			break;
		}
	}
	
	Solver* ChessController::initSolver()
	{
		Solver* solver = reinterpret_cast<Solver*>(this->getSolver());
		
		solver->clearTree();
		
		Situation* startSituation = new Situation(this->game.getFirstPlayer()->getAllFigures(), this->game.getSecondPlayer()->getAllFigures(), *this->game.getBoard(), this->game.getCurrentPlayer(), this->game.getCurrentPlayer());
		
		solver->initTree(startSituation);
		
		delete startSituation;
		return solver;
	}
}
