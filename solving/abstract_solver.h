#ifndef ABSTRACT_SOLVER
#define ABSTRACT_SOLVER

#include "option_tree.h"

//#include "abstract_situation_maker.h"

namespace chess_solver
{
	class AbstractSolver
	{
	public:
//		AbstractSolver(AbstractSituationMaker* situationMaker);
		AbstractSolver();
		
		virtual ~AbstractSolver();
		
		virtual bool useDeepSearch(short maximalDepth) = 0;
	
		virtual void initTree(AbstractSituation* startSituation);
	
		OptionTree* getTree() const { return tree; }
	
		void clearTree();
		
	protected:
		OptionTree* getOptionTreeRoot() { return tree; }
		
		virtual AbstractSituation* getNextSituation(AbstractSituation* abstractSituation, AbstractCommand* command) = 0;
		
		virtual OptionTree* createChild(OptionTree* tree);
		
		virtual bool isTargetSituation(OptionTree* tree) = 0;
		
		virtual bool isDeadlock(OptionTree* tree, int maximalDepth) = 0;
		
//		AbstractSituationMaker* getSituationMaker() { return situationMaker; }
		
	private:
		OptionTree* tree;
		
//		AbstractSituationMaker* situationMaker;
	};
}

#endif
