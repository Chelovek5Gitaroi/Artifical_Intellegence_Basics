#include "solver.h"

namespace chess_solver
{

	
	
	bool Solver::useDeepSearch(short maximalDepth)
	{
		return deepSearch(getOptionTreeRoot(), maximalDepth);
	}

	Solver::Solver(AbstractSituationMaker* situationMaker) : AbstractSolver(situationMaker)
	{
	}

	void Solver::initTree(AbstractSituation* startSituation)
	{
//		std::cout << "*Debug* init tree...\n";
		
		AbstractSolver::initTree(startSituation);
		
		Situation* situation = reinterpret_cast<Situation*>(startSituation);
		
		ChessSituationMaker* situationMaker = reinterpret_cast<ChessSituationMaker*>(getSituationMaker());
		
		situationMaker->prepareStartSituationMoves(situation);
		
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
			
			result->setCommand(previousSituation->getPotentialMoves()->front());
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
		return isTargetSituation(reinterpret_cast<Situation*>(tree->getSituation()));
	}
	
	bool Solver::isDeadlock(OptionTree* tree, int maximalDepth)
	{
		return isDeadlock(reinterpret_cast<Situation*>(tree->getSituation()), maximalDepth, tree->getDepth());
	}

	bool Solver::isTargetSituation(Situation* situation)
	{
		
//		return situation->getCurrentPlayer() != situation->getTargetPlayer() && situation->getPotentialMoves()->empty() && MovingValidator::hasCheck(situation->getBoard(), );
	}
		
	bool Solver::isDeadlock(Situation* situation, short maximalDepth, short currentDepth)
	{
		bool result = false;
		
		if (situation->getTargetPlayer() == situation->getCurrentPlayer())
		{
			result = situation->getPotentialMoves()->empty();
		}
		else
		{
			result = !situation->getPotentialMoves()->empty() && maximalDepth == currentDepth;
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
			
			std::list<Command*>* moves = reinterpret_cast<Situation*>(tree->getSituation())->getPotentialMoves();
			
			while (areAllChildrenTarget && !moves->empty())
			{
				child = createChild(tree);
				
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
		
		return result;
	}

}
