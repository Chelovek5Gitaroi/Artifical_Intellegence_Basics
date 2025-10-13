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
				
		bool useDeepSearch(short maximalDepth) override;
	
		void initTree(AbstractSituation* startSituation) override;
	
	protected:
	
		OptionTree* createChild(OptionTree* tree) override;
	
		bool isTargetSituation(OptionTree* tree) override;
	
		bool isDeadlock(OptionTree* tree, int maximalDepth) override;
	
//		void addNewChild(OptionTree* tree);
	
	
	private:
		
		bool isTargetSituation(Situation* situation);
		
		bool isDeadlock(Situation* situation, short maximalDepth, short currentDepth);
		
		bool deepSearch(OptionTree* tree, short maximalDepth);
		
	};
}

#endif
