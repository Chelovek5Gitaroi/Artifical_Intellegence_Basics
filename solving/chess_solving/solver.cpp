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
//		fout << "Start creating valid command\n";
		
		Command* result = new Command(figure, finishCoordinates, type);
		
		bool isValid = MovingValidator::isMoveValid(result, *otherFigures, board, fout);
		
		if (isValid)
		{
			isValid = !MovingValidator::hasCheck(result, board, kingCoordinates, *otherFigures, fout);
			
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
		
		return result;
	}
	
	bool Solver::createValidTransformationCommands(Figure* figure, Board& board, const Coordinates& finishCoordinates, CommandType type,
		const Coordinates& kingCoordinates, std::list<Figure*>* figures, std::list<Figure*>* otherFigures, std::list<AbstractCommand*>* commands, std::ofstream& fout)
	{
//		fout << "Start creating valid transformation commands\nFigure: " << figure->toString() << ", finish: " << finishCoordinates.toString() << "\n";
		
		Command* command = new CommandTransformation(figure, finishCoordinates, FigureType::BISHOP, type);
		
		bool isValid = MovingValidator::isMoveValid(command, *otherFigures, board, fout);
		
		if (isValid)
		{
			isValid = !MovingValidator::hasCheck(command, board, kingCoordinates, *otherFigures, fout);
			
			if (isValid)
			{
				commands->push_back(command);
				commands->push_back(new CommandTransformation(figure, finishCoordinates, FigureType::KNIGHT, type));
				commands->push_back(new CommandTransformation(figure, finishCoordinates, FigureType::ROCK, type));
				commands->push_back(new CommandTransformation(figure, finishCoordinates, FigureType::QUEEN, type));
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
		
		return isValid;
	}
	
	std::list<AbstractCommand*>* Solver::getFigurePotentialMoves(Board& board, Figure* figure, const Coordinates& kingCoordinates, std::list<Figure*>* figures, std::list<Figure*>* otherFigures, std::ofstream& fout)
	{
//		fout << "*Debug* preparing figure moves figure type: " << (int)figure->getType() << "\n";
		
		std::list<AbstractCommand*>* result = new std::list<AbstractCommand*>();
		
		Coordinates startCoordinates = figure->getCoordinates();
		
		std::list<Coordinates>* coordinates = MovingPreparator::getPotentialPossibleCoordinates(startCoordinates, figure->getType(), figure->getColor(), board.getBoardSize());
		
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
		
		return result;
	}
	
	std::list<AbstractCommand*>* Solver::getAllSituationMoves(Situation& situation, std::ofstream& fout)
	{
//		fout << "Making situation moves\n";
		
		std::list<AbstractCommand*>* result = new std::list<AbstractCommand*>();
		
		std::list<Figure*>* figures = &situation.getWhiteFigures();
		std::list<Figure*>* otherFigures = &situation.getBlackFigures();
		
		if (situation.getCurrentPlayer() == FigureColor::BLACK)
		{
			figures = &situation.getBlackFigures();
			otherFigures = &situation.getWhiteFigures();
		}
		
//		fout << "Getting king coordinates...\n";
		
		const Coordinates& kingCoordinates = getKingFromList(figures, fout)->getCoordinates();
		
//		fout << "Preparing figures moves\n";
		
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
		
		return result;
	}

	Figure* Solver::getKingFromList(std::list<Figure*>* figures, std::ofstream& fout)
	{
		for (auto iter = figures->begin(); iter != figures->end(); iter++)
		{
			if ((*iter)->getType() == FigureType::KING)
			{
				return *iter;
			}
		}
		
		return nullptr;
	}
	
	bool Solver::useDeepSearch(short maximalDepth)
	{
		Situation* situation = reinterpret_cast<Situation*>(this->getOptionTreeRoot()->getSituation());
		
		std::ofstream fout("log.txt");
		
		this->getOptionTreeRoot()->setPotentialMoves(getAllSituationMoves(*situation, fout));
		
		bool result = deepSearch(getOptionTreeRoot(), maximalDepth, fout);
		
		fout.close();
		
		return result;
	}

	void Solver::initTree(AbstractSituation* startSituation)
	{
//		std::cout << "*Debug* init tree...\n";
		
		AbstractSolver::initTree(startSituation);
		
//		std::cout << "*Debug* tree inited...\n";
	}

	OptionTree* Solver::createChild(OptionTree* tree)
	{
		OptionTree* result = AbstractSolver::createChild(tree);
		
		Situation* situation = reinterpret_cast<Situation*>(result->getSituation());
		Situation* previousSituation = reinterpret_cast<Situation*>(tree->getParent()->getSituation());
		
		if (situation)
		{
			if (situation->getCurrentPlayer() == situation->getTargetPlayer())
			{
				result->increaseDepth();
			}
		}
		else
		{
			delete result;
			result = nullptr;
		}
		
		return result;
	}

	bool Solver::isTargetSituation(OptionTree* tree, std::ofstream& fout)
	{
		return isTargetSituation(reinterpret_cast<Situation*>(tree->getSituation()), tree->getCommands(), fout);
	}
	
	bool Solver::isDeadlock(OptionTree* tree, int maximalDepth, std::ofstream& fout)
	{
		return isDeadlock(reinterpret_cast<Situation*>(tree->getSituation()), tree->getCommands(), maximalDepth, tree->getDepth(), fout);
	}

	bool Solver::isTargetSituation(Situation* situation, std::list<AbstractCommand*>* potentialMoves, std::ofstream& fout)
	{
		std::list<Figure*>* figures = &situation->getWhiteFigures();
		std::list<Figure*>* secondPlayerFigures = &situation->getBlackFigures();
		
		if (situation->getCurrentPlayer() == FigureColor::BLACK)
		{
			std::swap(figures, secondPlayerFigures);
		}
		
		Coordinates* kingCoordinates;
		
		return situation->getCurrentPlayer() != situation->getTargetPlayer() &&
			MovingValidator::hasCheck(situation->getBoard(), *kingCoordinates, *secondPlayerFigures, fout);
	}
		
	bool Solver::isDeadlock(Situation* situation, std::list<AbstractCommand*>* potentialMoves, short maximalDepth, short currentDepth, std::ofstream& fout)
	{
		bool result = false;
		
		if (situation->getTargetPlayer() == situation->getCurrentPlayer())
		{
			result = potentialMoves->empty();
		}
		else
		{
			result = !potentialMoves->empty() && maximalDepth == currentDepth;
		}
		
		return result;
	}

	bool Solver::deepSearch(OptionTree* tree, short maximalDepth, std::ofstream& fout)
	{
		bool result = false;
		
		Situation* sit = reinterpret_cast<Situation*>(tree->getSituation()) ;
		
		fout << "Depth: " << tree->getDepth() << "\n" << sit->toString() << "\n";
		
//		fout.close();
		
		if (isDeadlock(tree, maximalDepth, fout))
		{
			fout << "Deadlock!\n";
//			fout.close();
			result = false;
		}
		else if (isTargetSituation(tree, fout))
		{
			fout << "Target!\n";
//			fout.close();
			result = true;
		}
		else
		{
			bool areAllChildrenTarget = true;
		
			OptionTree* child = nullptr;
			
			std::list<AbstractCommand*>* moves = tree->getCommands();
		
//			fout.open("log.txt");
		
			fout << "Moves:\n";
			
			for (auto iter = moves->begin(); iter != moves->end(); iter++)
			{
				Command* cmd = reinterpret_cast<Command*>(*iter);
				
				fout << cmd->toString() << "\n";
			}
		
			fout << "\n";
//			fout.close();
			
			while (areAllChildrenTarget && !moves->empty())
			{
				child = createChild(tree);
				
//				fout.open("log.txt");
				fout << " ";
				
				moves->pop_front();
				child->setPotentialMoves(getAllSituationMoves(*reinterpret_cast<Situation*>(child->getSituation()), fout));
				
//				fout.close();
				
//				fout.open("log.txt");
				
				areAllChildrenTarget = deepSearch(child, maximalDepth, fout);
				
				if (areAllChildrenTarget)
				{
					tree->insertChild(child);
				}
				else
				{
					delete child;
				}
			}
			
			result = areAllChildrenTarget;
		}
		
		if (!result)
		{
			delete tree;
			
			tree = nullptr;
		}
		
		return result;
	}
}
