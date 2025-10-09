#include "abstract_solver.h"

namespace chess_solver
{
	AbstractSolver::~AbstractSolver()
	{
		delete this->tree;
		delete this->situationMaker;
	}
	
	AbstractSolver::AbstractSolver(AbstractSituationMaker* situationMaker)
	{
		this->situationMaker = situationMaker;
	}
	
	void AbstractSolver::clearTree()
	{
		delete this->tree;
		this->tree = nullptr;
	}
	
	void AbstractSolver::initTree(AbstractSituation* startSituation)
	{
		if (tree)
		{
			clearTree();
		}
		
		this->tree = new OptionTree(startSituation, nullptr, nullptr, 0);
	}
	
	OptionTree* AbstractSolver::createChild(OptionTree* tree)
	{
		AbstractSituation* situation = tree->getSituation();
		
		AbstractSituation* nextSituation = situationMaker->getNextSituation(situation);
		
		return new OptionTree(nextSituation, nullptr, tree, tree->getDepth());
	}
}
