#ifndef SOLVER
#define SOLVER

//#include <iostream>

#include "../abstract_solver.h"
#include "chess_situation_maker.h"

namespace chess_solver
{
	class Solver : public AbstractSolver
	{
	public:
		Solver(AbstractSituationMaker* situationMaker);
//		~Solver(){ std::cout << "*Debug* solver d-tor\n"; }
				
		bool useDeepSearch(short maximalDepth) override;
	
		void initTree(AbstractSituation* startSituation) override;
	
	protected:
	
		OptionTree* createChild(OptionTree* tree) override;
	
		bool isTargetSituation(OptionTree* tree) override;
	
		bool isDeadlock(OptionTree* tree, int maximalDepth) override;
	
//		void addNewChild(OptionTree* tree);
	
	
	private:
		
		bool isTargetSituation(Situation* situation, std::list<AbstractCommand*>* potentialMoves);
		
		bool isDeadlock(Situation* situation, std::list<AbstractCommand*>* potentialMoves, short maximalDepth, short currentDepth);
		
		bool deepSearch(OptionTree* tree, short maximalDepth);
		
	};
}

#endif
