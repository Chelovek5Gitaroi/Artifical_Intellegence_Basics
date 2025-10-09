#ifndef ABSTRACT_SOLVER
#define ABSTRACT_SOLVER

#include "option_tree.h"

#include "abstract_situation_maker.h"

namespace chess_solver
{
	class AbstractSolver
	{
	public:
		AbstractSolver(AbstractSituationMaker* situationMaker);
		
		virtual ~AbstractSolver() = 0;
		
		virtual bool useDeepSearch(AbstractSituation* startSituation, short maximalDepth) = 0;
	
	protected:
		OptionTree* getOptionTreeRoot() { return tree; }
		void clearTree();
		
		virtual OptionTree* createChild(OptionTree* tree);
		
		virtual void initTree(AbstractSituation* startSituation);
		
		virtual bool isTargetSituation(OptionTree* tree) = 0;
		
		virtual bool isDeadlock(OptionTree* tree, int maximalDepth) = 0;
		
		
		
		AbstractSituationMaker* getSituationMaker() { return situationMaker; }
		
	private:
		OptionTree* tree;
		
		AbstractSituationMaker* situationMaker;
	};
}

#endif
