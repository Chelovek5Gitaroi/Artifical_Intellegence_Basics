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
		const Coordinates& kingCoordinates, std::list<Figure*>* figures, std::list<Figure*>* otherFigures)
	{
		Command* result = new Command(figure->getType(), figure->getCoordinates(), finishCoordinates, type);
		
		bool isValid = MovingValidator::isMoveValid(result, *figures, *otherFigures, board);
		
		if (isValid)
		{
			isValid = !MovingValidator::hasCheck(result, board, kingCoordinates, *figures, *otherFigures);
			
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
		
		return result;
	}
	
	bool Solver::createValidTransformationCommands(Figure* figure, Board& board, const Coordinates& finishCoordinates, CommandType type,
		const Coordinates& kingCoordinates, std::list<Figure*>* figures, std::list<Figure*>* otherFigures, std::list<AbstractCommand*>* commands)
	{
		Command* command = new CommandTransformation(figure->getType(), figure->getCoordinates(), finishCoordinates, FigureType::BISHOP, type);
		
		bool isValid = MovingValidator::isMoveValid(command, *figures, *otherFigures, board);
		
		if (isValid)
		{
			isValid = !MovingValidator::hasCheck(command, board, kingCoordinates, *figures, *otherFigures);
			
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
		
		return isValid;
	}
	
	std::list<AbstractCommand*>* Solver::getFigurePotentialMoves(Board& board, Figure* figure, const Coordinates& kingCoordinates, std::list<Figure*>* figures, std::list<Figure*>* otherFigures)
	{
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

		return result;
	}
	
	std::list<AbstractCommand*>* Solver::getAllSituationMoves(AbstractSituation* abstractSituation)
	{
		std::list<AbstractCommand*>* result = new std::list<AbstractCommand*>();
		
		Situation* situation = reinterpret_cast<Situation*>(abstractSituation);
		
		std::list<Figure*>* figures = &situation->getWhiteFigures();
		std::list<Figure*>* otherFigures = &situation->getBlackFigures();
		
		if (situation->getCurrentPlayer() == FigureColor::BLACK)
		{
			figures = &situation->getBlackFigures();
			otherFigures = &situation->getWhiteFigures();
		}
		
		const Coordinates& kingCoordinates = getKingFromList(figures)->getCoordinates();
		
		for (auto iter = figures->begin(); iter != figures->end(); iter++)
		{
			std::list<AbstractCommand*>* moves = getFigurePotentialMoves(situation->getBoard(), *iter, kingCoordinates, figures, otherFigures);
			
			for (auto cmdIter = moves->begin(); cmdIter != moves->end(); cmdIter++)
			{
				result->push_back(*cmdIter);
			}
			
			delete moves;
		}
		
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
	
	OptionTree* Solver::createChild(OptionTree* tree)
	{
		OptionTree* result = AbstractSolver::createChild(tree);
		
		if (result)
		{
			Situation* situation = reinterpret_cast<Situation*>(result->getSituation());
		
			if (situation->getCurrentPlayer() == situation->getTargetPlayer())
			{
				result->increaseDepth();
			}
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
		
		Coordinates* kingCoordinates = &getKingFromList(figures)->getCoordinates();
		
		return situation->getCurrentPlayer() != situation->getTargetPlayer() && potentialMoves->empty() &&
			MovingValidator::hasCheck(situation->getBoard(), *kingCoordinates, *figures, *secondPlayerFigures);
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

	OptionTree* Solver::deepSearch(OptionTree* tree, short maximalDepth)
	{
		Situation* situation = reinterpret_cast<Situation*>(tree->getSituation());
		
		OptionTree* result = nullptr;
		
		if (situation->getTargetPlayer() == situation->getCurrentPlayer())
		{
			result = AbstractSolver::deepSearch(tree, maximalDepth);
		}
		else
		{
			if (tree->getDepth() < maximalDepth)
			{
				result = tree;
				
				while (result && !tree->getCommands()->empty())
				{
					OptionTree* nextChild = createChild(tree);
					
					if (nextChild)
					{
						result = AbstractSolver::deepSearch(nextChild, maximalDepth);
				
						if (!result)
						{
							delete nextChild;
							nextChild = nullptr;
						}
						else
						{
							tree->insertChild(nextChild);
						}
					}
				}
			}
			else
			{
				result = AbstractSolver::deepSearch(tree, maximalDepth);
			}
		}

		return result;
	}
	
	bool Solver::areAllSiblingsTarget(OptionTree* node)
	{
		OptionTree* parent = node->getParent();
		
		bool result = true;
		
		if (parent)
		{
			OptionTree* child = parent->getFirstChild();
			
			while (child && !result)
			{
				result = isTargetSituation(child);
				child = parent->getNextChild();
			}
		}
		
		return result;
	}
}
