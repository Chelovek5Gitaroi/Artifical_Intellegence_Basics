#include "chess_controller.h"

namespace chess_solver
{
	const std::string ChessController::GREETING_MESSAGE = "Поиск мата не более, чем за два хода";
	
	const std::string ChessController::DEFAULT_FIGURE_DESCRIPTION_NAME = "figures.txt";
	
	const std::string ChessController::MENU_TIILE = "Выберите действие:";
	const std::string ChessController::MENU_ITEM_DEEP_SEARCH = "Поиск в глубину";
	const std::string ChessController::MENU_ITEM_SELECT_SITUATION = "Просматривать ситуации";
	const std::string ChessController::MENU_ITEM_EXIT = "Выйти";

	const std::string ChessController::MESSAGE_NO_SOLVE = "Решение не найдено!";
	const std::string ChessController::MESSAGE_SOLVE = "Найденное решение: ";

	const std::map<ChessController::MenuItem, std::string> ChessController::menu = {{ MenuItem::DEEP_SEARCH, MENU_ITEM_DEEP_SEARCH },
																					{ MenuItem::SELECT_SITUATION, MENU_ITEM_SELECT_SITUATION },
																					{ MenuItem::EXIT, MENU_ITEM_EXIT }};
	
	ChessController::ChessController(AbstractSolver* solver, AbstractVisualizer* visualizer, char boardSize) : AbstractController(solver, visualizer), game(boardSize), figureCreator(boardSize)
	{
		init(DEFAULT_FIGURE_DESCRIPTION_NAME);
		
		this->selectedMenuItem = MenuItem::DEEP_SEARCH;
		
		this->controllerState |= CONTROLLER_STATE_RUNNING;
		
		initSolver();
		
		this->currentTreeNode = nullptr;
	}
	
	void ChessController::init(const std::string& figureDescriptionFileName)
	{
//		cfout.open("controller_log.txt", std::ios::app);
		
		this->reader.readFigureFile(figureDescriptionFileName);
		
		this->game.setCurrentPlayer(this->reader.getMovingPlayerColor());
		
		std::list<Figure*>* blackFigures = this->figureCreator.makeFigureList(this->reader.getBlackFigures(), FigureColor::BLACK);
		std::list<Figure*>* whiteFigures = this->figureCreator.makeFigureList(this->reader.getWhiteFigures(), FigureColor::WHITE);
		
		for (Figure* figure : *whiteFigures)
		{
			this->game.getFirstPlayer()->addFigure(figure);
			
			this->game.getBoard()->setOccupancyByCoordinates(figure->getCoordinates(), true);
		}
		
		delete whiteFigures;
		
		for (Figure* figure : *blackFigures)
		{
			this->game.getSecondPlayer()->addFigure(figure);
			this->game.getBoard()->setOccupancyByCoordinates(figure->getCoordinates(), true);
		}
		
		delete blackFigures;
	}
	
	void ChessController::control()
	{
		this->makeMenuStrings(MENU_TIILE);
		system("cls");
		
		this->controllerState |= CONTROLLER_STATE_MENU_SELECT_SOLVING_METHOD;
		
		this->getVisualizer()->showSituation(this->getSolver()->getTree()->getSituation());
		
		Visualizer* visualizer = reinterpret_cast<Visualizer*>(this->getVisualizer());
			
		visualizer->showMessage(GREETING_MESSAGE, visualizer->getGreetingTop());
			
		visualizer->showMenu(this->menuStrings, visualizer->getMenuTop());
		
		visualizer->showMenu(this->menuStrings, reinterpret_cast<Visualizer*>(this->getVisualizer())->getMenuTop());
		
		bool wasPressed = false;
		
		this->setMaximalDepth(2);
		
		while (this->controllerState & CONTROLLER_STATE_RUNNING)
		{
			if (wasPressed)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(120));
				wasPressed = false;
			}
			
			if (GetKeyState(VK_RETURN) & 0x8000)
			{
				processKeyEnter();
				wasPressed = true;
			}
			
			if (GetKeyState(VK_UP) & 0x8000)
			{
				processKeyUp();
				wasPressed = true;
			}
			
			if (GetKeyState(VK_DOWN) & 0x8000)
			{
				processKeyDown();
				wasPressed = true;
			}
			
			if (GetKeyState(VK_ESCAPE) & 0x8000)
			{
				processKeyEscape();
				wasPressed = true;
			}
		}
	}
	
	Solver* ChessController::initSolver()
	{
		Solver* solver = reinterpret_cast<Solver*>(this->getSolver());
		
		solver->clearTree();
		
		this->currentTreeNode = nullptr;
		
		Situation* startSituation = new Situation(this->game.getFirstPlayer()->getAllFigures(), this->game.getSecondPlayer()->getAllFigures(), *this->game.getBoard(), this->game.getCurrentPlayer(), this->game.getCurrentPlayer());
		
		solver->initTree(startSituation);
		
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
			this->menuStrings[i].second = static_cast<short>(this->selectedMenuItem) == i;
		}
	}
	
	void ChessController::selectPreviousItem()
	{
		short selected = static_cast<short>(selectedMenuItem);
		
		if (selected > static_cast<short>(MenuItem::DEEP_SEARCH))
		{
			selected -= 1;
		}
		
		selectItem(static_cast<MenuItem>(selected));
	}
		
	void ChessController::selectNextItem()
	{
		short selected = static_cast<short>(selectedMenuItem);
		
		if (selected < static_cast<short>(MenuItem::EXIT))
		{
			selected += 1;
		}
		
		selectItem(static_cast<MenuItem>(selected));
	}
	
	void ChessController::processKeyEnter()
	{
//		cfout << "Enter pressed\n";
//		c
		
		Visualizer* visualizer = reinterpret_cast<Visualizer*>(this->getVisualizer());
		
		if (controllerState & CONTROLLER_STATE_MENU_SELECT_SOLVING_METHOD)
		{
			bool isSolved = false;

//			cfout << "Entering menu item\n";
			
			switch (this->selectedMenuItem)
			{
			case MenuItem::DEEP_SEARCH:
				this->initSolver();
				this->solvingMenu.clear();
				visualizer->clearMenu(this->solvingMenu, visualizer->getCommandsTop());
			
				visualizer->showMessage(std::string(MESSAGE_NO_SOLVE.size(), ' '), visualizer->getCommandsTop());

				isSolved = this->getSolver()->useDeepSearch(this->getMaximalDepth());

				if (isSolved)
				{
					COORD messageTop = visualizer->getCommandsTop();
					messageTop.Y -= 1;
					
					visualizer->showMessage(MESSAGE_SOLVE, messageTop);
					
					this->currentTreeNode = this->getSolver()->getTree();
					makeSolvingMenu(this->getSolver()->getTree()->getCommandSequence());
					visualizer->showMenu(this->solvingMenu, visualizer->getCommandsTop());
				}
				else
				{
					visualizer->showMessage(MESSAGE_NO_SOLVE, visualizer->getCommandsTop());
				}
				break;
			
			case MenuItem::SELECT_SITUATION:
				if (this->currentTreeNode)
				{
					this->controllerState &= ~CONTROLLER_STATE_MENU_SELECT_SOLVING_METHOD;
					this->controllerState |= CONTROLLER_STATE_SELECTING_SITUATION;
				}
				break;
				
			case MenuItem::EXIT:
				this->controllerState &= ~CONTROLLER_STATE_RUNNING;
				break;
			}
		}
		else if (this->controllerState & CONTROLLER_STATE_SELECTING_SITUATION)
		{
			if (this->currentTreeNode)
			{
				visualizer->showSituation(this->currentTreeNode->getSituation());
			}
		}
	}
	
	void ChessController::processKeyUp()
	{
		Visualizer* visualizer = reinterpret_cast<Visualizer*>(this->getVisualizer());
		
		if (controllerState & CONTROLLER_STATE_MENU_SELECT_SOLVING_METHOD)
		{
			selectPreviousItem();
			
			visualizer->showMenu(this->menuStrings, visualizer->getMenuTop());
		}
		else if (controllerState & CONTROLLER_STATE_SELECTING_SITUATION)
		{
			if (this->currentTreeNode->getParent())
			{
				this->currentTreeNode = this->currentTreeNode->getParent();
			
				selectSituation(this->currentTreeNode);
				
				visualizer->showMenu(this->solvingMenu, visualizer->getCommandsTop());
			}
		}
	}
		
	void ChessController::processKeyDown()
	{
		Visualizer* visualizer = reinterpret_cast<Visualizer*>(this->getVisualizer());
		
		if (controllerState & CONTROLLER_STATE_MENU_SELECT_SOLVING_METHOD)
		{
			selectNextItem();
			
			visualizer->showMenu(this->menuStrings, visualizer->getMenuTop());
		}
		else if (controllerState & CONTROLLER_STATE_SELECTING_SITUATION)
		{
			if (this->currentTreeNode->getCurrentChild())
			{
				this->currentTreeNode = this->currentTreeNode->getFirstChild();
				
				selectSituation(this->currentTreeNode);
				visualizer->showMenu(this->solvingMenu, visualizer->getCommandsTop());
			}
		}
	}

	void ChessController::processKeyEscape()
	{
		if (this->controllerState & CONTROLLER_STATE_SELECTING_SITUATION)
		{
			this->controllerState &= ~CONTROLLER_STATE_SELECTING_SITUATION;
			
			this->controllerState |= CONTROLLER_STATE_MENU_SELECT_SOLVING_METHOD;
		}
		
	}
	
	void ChessController::selectSituation(OptionTree* tree)
	{
		Figure* figure = nullptr;
		
		Command* command = reinterpret_cast<Command*>(tree->getPreviousCommand());
		
		std::string cmd = CommandParser::makeStringCommand(command);
		
		for (auto iter = this->solvingMenu.begin(); iter != this->solvingMenu.end(); iter++)
		{
			if (iter->first == cmd)
			{
				iter->second = true;
			}
			else
			{
				iter->second = false;
			}
		}
	}

	void ChessController::makeSolvingMenu(std::list<AbstractCommand*>* commandList)
	{
		solvingMenu.clear();
		
		std::list<AbstractCommand*>* commands = this->getSolver()->getTree()->getCommandSequence();
		
		this->currentTreeNode = this->getSolver()->getTree();
		
		for (AbstractCommand* command : *commandList)
		{
			
			bool selected = false;
			
			if (command == currentTreeNode->getPreviousCommand())
			{
				selected = true;
			}
			
			this->solvingMenu.push_back(std::pair<std::string, bool>(CommandParser::makeStringCommand(reinterpret_cast<Command*>(command)), selected));
		}
	}
	
	
}
