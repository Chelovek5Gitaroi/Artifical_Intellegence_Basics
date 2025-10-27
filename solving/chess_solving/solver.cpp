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

//		if (!commands->empty())
//		{
		executor.executeCommand(reinterpret_cast<Command*>(command), result->getBoard(), figures, otherFigures);
			
//			commands->pop_front();
			
		result->setCurrentPlayer(currentColor);
//		}
//		else
//		{
//			delete result;
//			result = nullptr;
//		}

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
	
//	bool Solver::useDeepSearch(short maximalDepth)
//	{
//		Situation* situation = reinterpret_cast<Situation*>(this->getOptionTreeRoot()->getSituation());
//		
//		std::ofstream fout("log.txt", std::ios::app);
//		
//		this->getOptionTreeRoot()->setPotentialMoves(getAllSituationMoves(*situation, fout));
//		
//		bool result = deepSearch(getOptionTreeRoot(), maximalDepth, fout);
//		
//		fout.close();
//		
//		return result;
//	}

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
		fout << "Derived child creating\n";
		
		OptionTree* result = AbstractSolver::createChild(tree, fout);
		
		Situation* situation = reinterpret_cast<Situation*>(result->getSituation());
//		Situation* previousSituation = reinterpret_cast<Situation*>(tree->getParent()->getSituation());
		
		result->setPotentialMoves(getAllSituationMoves(*situation, fout));
		
//		if (situation)
//		{
			if (situation->getCurrentPlayer() == situation->getTargetPlayer())
			{
				result->increaseDepth();
			}
			
			fout << "Derived child created\n";
//		}
//		else
//		{
//			delete result;
//			result = nullptr;
//			
//			fout << "Failed to derived create child\n";
//		}
//		
		fout.flush();
		
		return result;
	}

	bool Solver::isTargetSituation(OptionTree* tree, std::ofstream& fout)
	{
		fout << "Derived override target situation check\n";
		fout.flush();
		return isTargetSituation(reinterpret_cast<Situation*>(tree->getSituation()), tree->getCommands(), fout);
//		if (tree->getChildrenNumber() == 0)
//		{
//			return isTargetSituation(reinterpret_cast<Situation*>(tree->getSituation()), tree->getCommands(), fout);
//		}
//		else
//		{
//			bool areAllChildrenTarget = true;
//			
//			OptionTree* currentChild = tree->getCurrentChild();
//			
//			while (currentChild && areAllChildrenTarget)
//			{
//				areAllChildrenTarget = isTargetSituation(currentChild, fout);
//				
//				currentChild = tree->getNextChild();
//			}
//		}
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
		
		bool result = AbstractSolver::deepSearch(tree, maximalDepth, fout);

		Situation* situation = reinterpret_cast<Situation*>(tree->getSituation());

		if (result)
		{
			if (situation->getCurrentPlayer() != situation->getTargetPlayer() && tree->getDepth() < maximalDepth)
			{
				fout << "derived check next child\n";
				fout.flush();
			
				OptionTree* nextChild = createChild(tree, fout);
			
				if (nextChild)
				{
					fout << "has next child\n";
					fout.flush();
				
//				tree->insertChild(nextChild);
			
					result = AbstractSolver::deepSearch(nextChild, maximalDepth, fout);
				
					if (!result)
					{
						fout << "no solve\n";
//					tree->removeChild(child);
						delete nextChild;
						nextChild = nullptr;
					}
					else
					{
						fout << "maybe solve\n";
						tree->insertChild(nextChild);
					}
					fout.flush();
				}
				else
				{
					fout << "No more children\n";
					fout.flush();
				}
			}
			
			
		}

//		Situation* sit = reinterpret_cast<Situation*>(tree->getSituation()) ;
//		
//		fout << "Depth: " << tree->getDepth() << "\n" << sit->toString() << "\n";
//		
//		fout.flush();
//		
//		if (isDeadlock(tree, maximalDepth, fout))
//		{
//			fout << "Deadlock!\n";
//			fout.flush();
//			result = false;
//		}
//		else if (isTargetSituation(tree, fout))
//		{
//			fout << "Target!\n";
//			fout.flush();
//			result = true;
//		}
//		else
//		{
//			bool areAllChildrenTarget = true;
//		
//			OptionTree* child = nullptr;
//			
//			std::list<AbstractCommand*>* moves = tree->getCommands();
//		
////			fout << "Moves:\n";
////			
////			for (auto iter = moves->begin(); iter != moves->end(); iter++)
////			{
////				Command* cmd = reinterpret_cast<Command*>(*iter);
////				
////				fout << cmd->toString() << "\n";
////			}
////		
////			fout << "\n";
////			fout.flush();
//			
//			while (areAllChildrenTarget && !moves->empty())
//			{
//				child = createChild(tree, fout);
//				
//				moves->pop_front();
//
//				fout << " ";
//				fout.flush();
//				
////				if (!child)
////				{
////					fout << "Child not found!\n";
////				}
////				else
////				{
////					fout << "Child\n";
////				}
////
////				fout << "getting moves...\n";
////				fout.flush();
//				
////				AbstractSituation* sit = child->getSituation();
//				
////				fout << "*****\n";
////				fout.flush();
////				
////				if (sit)
////				{
////					fout << "situation\n";
////				}
////				else
////				{
////					fout << "non valid situation\n";
////				}
//				
//				fout.flush();
//				
//				std::list<AbstractCommand*>* cmds = getAllSituationMoves(*reinterpret_cast<Situation*>(child->getSituation()), fout);
//				
//				if (cmds)
//				{
//					fout << "moves list\n";
//				}
//				else
//				{
//					fout << "invalid moves list\n";
//				}
//				
//				fout.flush();
//				
//				child->setPotentialMoves(cmds);
//				
//				areAllChildrenTarget = deepSearch(child, maximalDepth, fout);
//				
//				if (areAllChildrenTarget)
//				{
//					tree->insertChild(child);
//				}
//				else
//				{
//					delete child;
//				}
//			}
//			
//			result = areAllChildrenTarget;
//		}
//		
//		if (!result)
//		{
//			delete tree;
//			
//			tree = nullptr;
//		}
		
		return result;
	}
}
