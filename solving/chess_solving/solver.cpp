#include "solver.h"

namespace chess_solver
{

	
	
//	void Solver::UseDeepSearch(AbstractSituation* startSituation, short maximalDepth, short currentDepth)
//	{
//		
//	}

	Solver::Solver(AbstractSituationMaker* situationMaker) : AbstractSolver(situationMaker)
	{
	}

	void Solver::addNewChild(OptionTree* tree)
	{
		
	}

	void Solver::initTree(AbstractSituation* startSituation)
	{
		AbstractSolver::initTree(startSituation);
		
		Situation* situation = reinterpret_cast<Situation*>(startSituation);
		
		ChessSituationMaker* situationMaker = reinterpret_cast<ChessSituationMaker*>(getSituationMaker());
		
		situationMaker->prepareStartSituationMoves(situation);
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
		return situation->getCurrentPlayer() != situation->getTargetPlayer() && situation->getPotentialMoves()->empty();
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


}
