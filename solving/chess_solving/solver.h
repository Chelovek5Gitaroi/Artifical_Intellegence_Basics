#ifndef SOLVER
#define SOLVER

#include "../abstract_solver.h"
#include "chess_situation_maker.h"

namespace chess_solver
{
	class Solver : public AbstractSolver
	{
	public:
		Solver(AbstractSituationMaker* situationMaker);
				
//		void UseDeepSearch(AbstractSituation* startSituation, short maximalDepth, short currentDepth) override;
	
	protected:
		void initTree(AbstractSituation* startSituation) override;
	
		bool isTargetSituation(AbstractSituation* situation) override;
	
		bool isDeadlock(AbstractSituation* situation, short depth) override;
	
	private:
		
	};
}

#endif
