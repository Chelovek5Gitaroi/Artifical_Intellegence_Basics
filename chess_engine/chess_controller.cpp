#include "chess_controller.h"

namespace chess_solver
{
	
	const std::string ChessController::DEFAULT_FIGURE_DESCRIPTION_NAME = "figures.txt";
	
	const std::string ChessController::MENU_TIILE = "Выберите способ решения:";
	const std::string ChessController::MENU_ITEM_DEEP_SEARCH = "Поиск в глубину";
	const std::string ChessController::MENU_ITEM_EXIT = "Выйти";

	const std::map<ChessController::MenuItem, std::string> ChessController::menu = {{MenuItem::DEEP_SEARCH, MENU_ITEM_DEEP_SEARCH}, {MenuItem::EXIT, MENU_ITEM_EXIT}};
	
	ChessController::ChessController(AbstractSolver* solver, AbstractVisualizer* visualizer, char boardSize) : AbstractController(solver, visualizer), game(boardSize), figureCreator(boardSize)
	{
		init(DEFAULT_FIGURE_DESCRIPTION_NAME);
		
		this->selectedMenuItem = MenuItem::DEEP_SEARCH;
		
		this->isRunning = true;
		
		initSolver();
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
		this->makeMenuStrings(MENU_TIILE);
		this->getVisualizer()->showMenu(this->menuStrings);
		
//		while (isRunning)
//		{
//			
//		}
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
		
//		delete startSituation;
		return solver;
	}
	
	void ChessController::makeMenuStrings(const std::string& title)
	{
		this->menuStrings.push_back(std::pair<std::string, bool>(std::string(title), false));
		
		for (auto iter = menu.begin(); iter != menu.end(); iter++)
		{
			this->menuStrings.push_back(std::pair<std::string, bool>(std::to_string(((int)iter->first)) + ". " + iter->second, this->selectedMenuItem == iter->first));
		}
	}
	
	void ChessController::selectItem(MenuItem item)
	{
		this->selectedMenuItem = item;
		
		for (int i = 0; i < this->menuStrings.size(); i++)
		{
			this->menuStrings[i].second = (int)this->selectedMenuItem == i;
		}
	}
}
