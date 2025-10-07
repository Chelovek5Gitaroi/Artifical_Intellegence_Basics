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

	bool isTargetSituation(AbstractSituation* situation)
	{
//		Situation* chessSituation = reinterpret_cast<Situation*>(situation);
//		
//		return chessSituation->getPotentialMoves()->empty() && ;
	}
	
	bool isDeadlock(AbstractSituation* situation, short depth)
	{
//		Situation* chessSituation = reinterpret_cast<Situation*>(situation);
//		
//		return chessSituation->getPotentialMoves()->empty() && ;
	}

}
