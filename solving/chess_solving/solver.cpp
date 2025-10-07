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

	void Solver::initTree(AbstractSituation* startSituation)
	{
		AbstractSolver::initTree(startSituation);
		
		Situation* situation = reinterpret_cast<Situation*>(startSituation);
		
		ChessSituationMaker* situationMaker = reinterpret_cast<ChessSituationMaker*>(getSituationMaker());
		
		situationMaker->prepareStartSituationMoves(situation);
	}

	bool Solver::isTargetSituation(OptionTree* tree)
	{
	}
	
	bool Solver::isDeadlock(OptionTree* tree, int maximalDepth)
	{
	}

	bool Solver::isTargetSituation(Situation* situation)
	{
		
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
