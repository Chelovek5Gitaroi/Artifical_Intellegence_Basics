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
		const Coordinates& kingCoordinates, std::list<Figure*>* figures, std::list<Figure*>* otherFigures)
	{
//		std::cout << "*Debug* creating valid command...\n";
		
		Command* result = new Command(figure, finishCoordinates, type);
		
		bool isValid = MovingValidator::isMoveValid(result, *otherFigures, board);
		
		if (isValid)
		{
			isValid = !MovingValidator::hasCheck(result, board, kingCoordinates, *otherFigures);
			
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
		
//		std::cout << "*Debug* end valid command creating... ";
//		
//		if (result)
//		{
//			std::cout << "valid command...\n";
//		}
//		else
//		{
//			std::cout << "no command...\n";
//		}
		
		return result;
	}
	
	bool Solver::createValidTransformationCommands(Figure* figure, Board& board, const Coordinates& finishCoordinates, CommandType type,
		const Coordinates& kingCoordinates, std::list<Figure*>* figures, std::list<Figure*>* otherFigures, std::list<AbstractCommand*>* commands)
	{
//		std::cout << "*Debug* creating valid transformation commands...\n";
		
		Command* command = new CommandTransformation(figure, finishCoordinates, FigureType::BISHOP, type);
		
		bool isValid = MovingValidator::isMoveValid(command, *otherFigures, board);
		
		if (isValid)
		{
			isValid = !MovingValidator::hasCheck(command, board, kingCoordinates, *otherFigures);
			
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
		
//		std::cout << "end creating valid trans commands... ";
//		
//		if (isValid)
//		{
//			std::cout << "valid\n";
//		}
//		else
//		{
//			std::cout << "non valid\n";
//		}
		
		return isValid;
	}
	
	std::list<AbstractCommand*>* Solver::getFigurePotentialMoves(Board& board, Figure* figure, const Coordinates& kingCoordinates, std::list<Figure*>* figures, std::list<Figure*>* otherFigures)
	{
//		std::cout << "*Debug* preparing figure moves figure type: " << (int)figure->getType() << "\n";
		
		std::list<AbstractCommand*>* result = new std::list<AbstractCommand*>();
		
		Coordinates startCoordinates = figure->getCoordinates();
		
		std::list<Coordinates>* coordinates = MovingPreparator::getPotentialPossibleCoordinates(startCoordinates, figure->getType(), figure->getColor(), board.getBoardSize());
		
		Command* command = nullptr;
		
		bool wasCreated = false;
		
		for (auto iter = coordinates->begin(); iter != coordinates->end(); iter++)
		{
			command = createValidCommand(figure, board, *iter, CommandType::MOVE, kingCoordinates, figures, otherFigures);
			
			if (command)
			{
				result->push_back(command);
			}
			else
			{
				command = createValidCommand(figure, board, *iter, CommandType::BEAT, kingCoordinates, figures, otherFigures);
				
				if (command)
				{
					result->push_back(command);
				}
				else if (figure->getType() == FigureType::PAWN)
				{
					wasCreated = createValidTransformationCommands(figure, board, *iter, CommandType::TRANSFORMATION, kingCoordinates, figures, otherFigures, result);
					
					if (!wasCreated)
					{
						createValidTransformationCommands(figure, board, *iter, CommandType::BEAT_TRANSFORMATION, kingCoordinates, figures, otherFigures, result);
					}
				}
			}
		}
		
//		std::cout << "*Debug* figure moves prepared...\n";
		
		return result;
	}
	
	std::list<AbstractCommand*>* Solver::getAllSituationMoves(Situation& situation)
	{
//		std::cout << "*Debug* making situation moves\n";
		
		std::list<AbstractCommand*>* result = new std::list<AbstractCommand*>();
		
		std::list<Figure*>* figures = &situation.getWhiteFigures();
		std::list<Figure*>* otherFigures = &situation.getBlackFigures();
		
		if (situation.getCurrentPlayer() == FigureColor::BLACK)
		{
			figures = &situation.getBlackFigures();
			otherFigures = &situation.getWhiteFigures();
		}
		
//		std::cout << "*Debug* getting king coordinates...\n";
		
		const Coordinates& kingCoordinates = getKingFromList(figures)->getCoordinates();
		
//		std::cout << "*Debug* preparing figures moves\n";
		
		for (auto iter = figures->begin(); iter != figures->end(); iter++)
		{
			std::list<AbstractCommand*>* moves = getFigurePotentialMoves(situation.getBoard(), *iter, kingCoordinates, figures, otherFigures);
			
			for (auto cmdIter = moves->begin(); cmdIter != moves->end(); cmdIter++)
			{
				result->push_back(*cmdIter);
			}
			
			delete moves;
		}
		
//		std::cout << "*Debug* situation moves prepared...\n";
		
		return result;
	}

	Figure* Solver::getKingFromList(std::list<Figure*>* figures)
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
		
		this->getOptionTreeRoot()->setPotentialMoves(getAllSituationMoves(*situation));
		
		return deepSearch(getOptionTreeRoot(), maximalDepth);
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

	bool Solver::isTargetSituation(OptionTree* tree)
	{
		return isTargetSituation(reinterpret_cast<Situation*>(tree->getSituation()), tree->getCommands());
	}
	
	bool Solver::isDeadlock(OptionTree* tree, int maximalDepth)
	{
		return isDeadlock(reinterpret_cast<Situation*>(tree->getSituation()), tree->getCommands(), maximalDepth, tree->getDepth());
	}

	bool Solver::isTargetSituation(Situation* situation, std::list<AbstractCommand*>* potentialMoves)
	{
		std::list<Figure*>* figures = &situation->getWhiteFigures();
		std::list<Figure*>* secondPlayerFigures = &situation->getBlackFigures();
		
		if (situation->getCurrentPlayer() == FigureColor::BLACK)
		{
			std::swap(figures, secondPlayerFigures);
		}
		
		Coordinates* kingCoordinates;
		
		return situation->getCurrentPlayer() != situation->getTargetPlayer() &&
			MovingValidator::hasCheck(situation->getBoard(), *kingCoordinates, *secondPlayerFigures);
	}
		
	bool Solver::isDeadlock(Situation* situation, std::list<AbstractCommand*>* potentialMoves, short maximalDepth, short currentDepth)
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

	bool Solver::deepSearch(OptionTree* tree, short maximalDepth)
	{
		bool result = false;
		
		if (isDeadlock(tree, maximalDepth))
		{
			result = false;
		}
		else if (isTargetSituation(tree))
		{
			result = true;
		}
		else
		{
			bool areAllChildrenTarget = true;
			
			OptionTree* child = nullptr;
			
			std::list<AbstractCommand*>* moves = tree->getCommands();
			
			while (areAllChildrenTarget && !moves->empty())
			{
				child = createChild(tree);
				moves->pop_front();
				child->setPotentialMoves(getAllSituationMoves(*reinterpret_cast<Situation*>(child->getSituation())));
				
				areAllChildrenTarget = deepSearch(child, maximalDepth);
				
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
