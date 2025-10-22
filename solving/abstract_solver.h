#ifndef ABSTRACT_SOLVER
#define ABSTRACT_SOLVER

#include "option_tree.h"

#include <fstream>

//#include "abstract_situation_maker.h"

namespace chess_solver
{
	class AbstractSolver
	{
	public:
//		AbstractSolver(AbstractSituationMaker* situationMaker);
		AbstractSolver();
		
		virtual ~AbstractSolver() = 0;
		
		virtual bool useDeepSearch(short maximalDepth) = 0;
	
		virtual void initTree(AbstractSituation* startSituation);
	
		OptionTree* getTree() const { return tree; }
	
		void clearTree();
		
	protected:
		OptionTree* getOptionTreeRoot() { return tree; }
		
		virtual AbstractSituation* getNextSituation(AbstractSituation* abstractSituation, AbstractCommand* command) = 0;
		
		virtual OptionTree* createChild(OptionTree* tree, std::ofstream& fout);
		
		virtual bool isTargetSituation(OptionTree* tree, std::ofstream& fout) = 0;
		
		virtual bool isDeadlock(OptionTree* tree, int maximalDepth, std::ofstream& fout) = 0;
		
//		AbstractSituationMaker* getSituationMaker() { return situationMaker; }
		
	private:
		OptionTree* tree;
		
//		AbstractSituationMaker* situationMaker;
	};
}

#endif
