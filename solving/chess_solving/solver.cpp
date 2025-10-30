#include "solver.h"

namespace chess_solver
{
	AbstractSituation* Solver::getNextSituation(AbstractSituation* abstractSituation, AbstractCommand* command)
	{
		Situation* result = new Situation(*reinterpret_cast<Situation*>(abstractSituation));
		
		std::list<Figure*>* figures = &result->getWhiteFigures();
		std::list<Figure*>* otherFigures = &result->getBlackFigures();
		
		FigureColor currentColor = FigureColor::BLACK;
		
		if (result->getCurrentPlayer() == FigureColor::BLACK)
		{
			figures = &result->getBlackFigures();
			otherFigures = &result->getWhiteFigures();
			currentColor = FigureColor::WHITE;
		}

		executor.executeCommand(reinterpret_cast<Command*>(command), result->getBoard(), figures, otherFigures);
			
		result->setCurrentPlayer(currentColor);

		return result;
	}
	
	Command* Solver::createValidCommand(Figure* figure, Board& board, const Coordinates& finishCoordinates, CommandType type,
		const Coordinates& kingCoordinates, std::list<Figure*>* figures, std::list<Figure*>* otherFigures, std::ofstream& fout)
	{
//		fout << "Start creating valid command ";
//		fout.flush();
		
		Command* result = new Command(figure->getType(), figure->getCoordinates(), finishCoordinates, type);
		
		bool isValid = MovingValidator::isMoveValid(result, *figures, *otherFigures, board, fout);
		
		if (isValid)
		{
			isValid = !MovingValidator::hasCheck(result, board, kingCoordinates, *figures, *otherFigures, fout);
			
			if (!isValid)
			{
				delete result;
				result = nullptr;
			}
		}
		else
		{
			delete result;
			result = nullptr;
		}
		
//		if (result)
//		{
//			fout << "valid command...\n";
//		}
//		else
//		{
//			fout << "no command...\n";
//		}
//		
//		fout.flush();
		
		return result;
	}
	
	bool Solver::createValidTransformationCommands(Figure* figure, Board& board, const Coordinates& finishCoordinates, CommandType type,
		const Coordinates& kingCoordinates, std::list<Figure*>* figures, std::list<Figure*>* otherFigures, std::list<AbstractCommand*>* commands, std::ofstream& fout)
	{
//		fout << "Start creating valid transformation commands\nFigure: " << figure->toString() << ", finish: " << finishCoordinates.toString() << "\n";
		
		Command* command = new CommandTransformation(figure->getType(), figure->getCoordinates(), finishCoordinates, FigureType::BISHOP, type);
		
		bool isValid = MovingValidator::isMoveValid(command, *figures, *otherFigures, board, fout);
		
		if (isValid)
		{
			isValid = !MovingValidator::hasCheck(command, board, kingCoordinates, *figures, *otherFigures, fout);
			
			if (isValid)
			{
				commands->push_back(command);
				commands->push_back(new CommandTransformation(figure->getType(), figure->getCoordinates(), finishCoordinates, FigureType::KNIGHT, type));
				commands->push_back(new CommandTransformation(figure->getType(), figure->getCoordinates(), finishCoordinates, FigureType::ROCK, type));
				commands->push_back(new CommandTransformation(figure->getType(), figure->getCoordinates(), finishCoordinates, FigureType::QUEEN, type));
			}
			else
			{
				delete command;
			}
		}
		else
		{
			delete command;
		}
		
//		if (isValid)
//		{
//			fout << "valid transformation commands\n";
//		}
//		else
//		{
//			fout << "non valid transformation commands\n";
//		}
//		fout.flush();
		
		return isValid;
	}
	
	std::list<AbstractCommand*>* Solver::getFigurePotentialMoves(Board& board, Figure* figure, const Coordinates& kingCoordinates, std::list<Figure*>* figures, std::list<Figure*>* otherFigures, std::ofstream& fout)
	{
//		fout << "*Debug* preparing moves " << figure->toString() << "\n";
//		fout.flush();
		
		std::list<AbstractCommand*>* result = new std::list<AbstractCommand*>();
		
		Coordinates startCoordinates = figure->getCoordinates();
		
		std::list<Coordinates>* coordinates = MovingPreparator::getPotentialPossibleCoordinates(startCoordinates, figure->getType(), figure->getColor(), board.getBoardSize());
		
//		fout << "potential coordinates created\n";
//		fout.flush();
		
		Command* command = nullptr;
		
		bool wasCreated = false;
		
		for (auto iter = coordinates->begin(); iter != coordinates->end(); iter++)
		{
			command = createValidCommand(figure, board, *iter, CommandType::MOVE, kingCoordinates, figures, otherFigures, fout);
			
			if (command)
			{
				result->push_back(command);
			}
			else
			{
				command = createValidCommand(figure, board, *iter, CommandType::BEAT, kingCoordinates, figures, otherFigures, fout);
				
				if (command)
				{
					result->push_back(command);
				}
				else if (figure->getType() == FigureType::PAWN)
				{
					wasCreated = createValidTransformationCommands(figure, board, *iter, CommandType::TRANSFORMATION, kingCoordinates, figures, otherFigures, result, fout);
					
					if (!wasCreated)
					{
						createValidTransformationCommands(figure, board, *iter, CommandType::BEAT_TRANSFORMATION, kingCoordinates, figures, otherFigures, result, fout);
					}
				}
			}
		}
		
//		fout << "*Debug* figure moves prepared...\n";
//		fout.flush();
		return result;
	}
	
	std::list<AbstractCommand*>* Solver::getAllSituationMoves(Situation& situation, std::ofstream& fout)
	{
//		fout << "Making situation moves\n";
//		fout.flush();
		std::list<AbstractCommand*>* result = new std::list<AbstractCommand*>();
		
		std::list<Figure*>* figures = &situation.getWhiteFigures();
		std::list<Figure*>* otherFigures = &situation.getBlackFigures();
		
		if (situation.getCurrentPlayer() == FigureColor::BLACK)
		{
//			fout << "curr color - black\n";
			
			figures = &situation.getBlackFigures();
			otherFigures = &situation.getWhiteFigures();
		}
		
//		fout << "Getting king coordinates...\n";
//		fout.flush();
		const Coordinates& kingCoordinates = getKingFromList(figures, fout)->getCoordinates();
		
//		fout << "Preparing figures moves\n";
//		fout.flush();
		for (auto iter = figures->begin(); iter != figures->end(); iter++)
		{
			std::list<AbstractCommand*>* moves = getFigurePotentialMoves(situation.getBoard(), *iter, kingCoordinates, figures, otherFigures, fout);
			
			for (auto cmdIter = moves->begin(); cmdIter != moves->end(); cmdIter++)
			{
				result->push_back(*cmdIter);
			}
			
			delete moves;
		}
		
//		fout << "Situation moves prepared\n";
//		fout.flush();
		
		return result;
	}

	Figure* Solver::getKingFromList(std::list<Figure*>* figures, std::ofstream& fout)
	{
		for (auto iter = figures->begin(); iter != figures->end(); iter++)
		{
//			fout << (*iter)->toString() << "\n";
//			fout.flush();
			
			if ((*iter)->getType() == FigureType::KING)
			{
//				fout << "found!\n";
//				fout.flush();
				return *iter;
			}
		}
		
		return nullptr;
	}
	
	void Solver::initTree(AbstractSituation* startSituation)
	{
//		std::cout << "*Debug* init tree...\n";
		
		AbstractSolver::initTree(startSituation);
		
		std::ofstream fout("log.txt", std::ios::app);
		
		this->getTree()->setPotentialMoves(getAllSituationMoves(*reinterpret_cast<Situation*>(this->getTree()->getSituation()), fout));
		
		fout.close();
		
//		std::cout << "*Debug* tree inited...\n";
	}

	OptionTree* Solver::createChild(OptionTree* tree, std::ofstream& fout)
	{
		fout << "Derived child creating parent: " << (long long)tree << "\n";
		
		OptionTree* result = AbstractSolver::createChild(tree, fout);
		
		if (result)
		{
			Situation* situation = reinterpret_cast<Situation*>(result->getSituation());
		
			result->setPotentialMoves(getAllSituationMoves(*situation, fout));
			
			if (situation->getCurrentPlayer() == situation->getTargetPlayer())
			{
				result->increaseDepth();
			}
			
			fout << "Derived child created\n";
		}
		
		fout.flush();
		
		return result;
	}

	bool Solver::isTargetSituation(OptionTree* tree, std::ofstream& fout)
	{
		fout << "Derived override target situation check\n";
		fout.flush();
		return isTargetSituation(reinterpret_cast<Situation*>(tree->getSituation()), tree->getCommands(), fout);
	}
	
	bool Solver::isDeadlock(OptionTree* tree, int maximalDepth, std::ofstream& fout)
	{
		fout << "Derived override deadlock check\n";
		fout.flush();
		return isDeadlock(reinterpret_cast<Situation*>(tree->getSituation()), tree->getCommands(), maximalDepth, tree->getDepth(), fout);
	}

	bool Solver::isTargetSituation(Situation* situation, std::list<AbstractCommand*>* potentialMoves, std::ofstream& fout)
	{
		fout << "cpecific target check\n";
		fout.flush();
		
		std::list<Figure*>* figures = &situation->getWhiteFigures();
		std::list<Figure*>* secondPlayerFigures = &situation->getBlackFigures();
		
		if (situation->getCurrentPlayer() == FigureColor::BLACK)
		{
			std::swap(figures, secondPlayerFigures);
		}
		
		Coordinates* kingCoordinates = &getKingFromList(figures, fout)->getCoordinates();
		
		fout << "cpecific target check returning\n";
		
		return situation->getCurrentPlayer() != situation->getTargetPlayer() && potentialMoves->empty() &&
			MovingValidator::hasCheck(situation->getBoard(), *kingCoordinates, *figures, *secondPlayerFigures, fout);
	}
		
	bool Solver::isDeadlock(Situation* situation, std::list<AbstractCommand*>* potentialMoves, short maximalDepth, short currentDepth, std::ofstream& fout)
	{
		fout << "cpecific deadlock check\n";
		fout.flush();
		
		bool result = false;
		
		if (situation->getTargetPlayer() == situation->getCurrentPlayer())
		{
			result = potentialMoves->empty();
		}
		else
		{
			result = !potentialMoves->empty() && maximalDepth == currentDepth;
		}
		
		fout << "cpecific deadlock check returning\n";
		
		return result;
	}

	bool Solver::deepSearch(OptionTree* tree, short maximalDepth, std::ofstream& fout)
	{
		fout << "derived deep search\n";
		fout.flush();
		
		Situation* situation = reinterpret_cast<Situation*>(tree->getSituation());
		
		bool result = false;
		
		if (situation->getTargetPlayer() == situation->getCurrentPlayer())
		{
			fout << "Target player moves\n";
			fout.flush();
			result = AbstractSolver::deepSearch(tree, maximalDepth, fout);
		}
		else
		{
			if (tree->getDepth() < maximalDepth)
			{
				result = true;
				
				fout << "Not maximal depth\n";
				fout.flush();
				
				while (result && !tree->getCommands()->empty())
				{
					OptionTree* nextChild = createChild(tree, fout);
					
					fout << "derived check next child\n";
					fout.flush();
					
					if (nextChild)
					{
						fout << "has next child\n";
						fout.flush();
				
						result = AbstractSolver::deepSearch(nextChild, maximalDepth, fout);
				
						if (!result)
						{
							fout << "no solve\n";
							fout.flush();
							delete nextChild;
							nextChild = nullptr;
						}
						else
						{
							tree->insertChild(nextChild);
						}
					}
					else
					{
						fout << "No more children\n";
						fout.flush();
					}
					
//					fout << "All children target: " << areAllChildrenTarget << "\n";
//					fout.flush();
				}
				
				if (tree->getCommands()->empty())
				{	
					fout << "Derived no more children!";
					fout.flush();
				}
			}
			else
			{
				fout << "Maximal depth\n";
				fout.flush();
				
				result = AbstractSolver::deepSearch(tree, maximalDepth, fout);
			}
		}

		fout << "Derived returning " << result << ". Depth = " << tree->getDepth() << "\n";
		fout.flush();

		return result;
	}
}
