#include "abstract_solver.h"

namespace chess_solver
{
	AbstractSolver::~AbstractSolver()
	{
//		std::cout << "*Debug* abstract solver d-tor...\n";
		
		delete this->tree;
//		delete this->situationMaker;
	}
	
	AbstractSolver::AbstractSolver()
//	AbstractSolver::AbstractSolver(AbstractSituationMaker* situationMaker)
	{
//		this->situationMaker = situationMaker;
		this->tree = nullptr;
	}
	
	void AbstractSolver::clearTree()
	{
		if (this->tree)
		{
			delete this->tree;
		}
		
		this->tree = nullptr;
	}
	
	void AbstractSolver::initTree(AbstractSituation* startSituation)
	{
//		std::cout << "*Debug* base init tree...\n";
		
		if (tree)
		{
			clearTree();
		}
		
		this->tree = new OptionTree(startSituation, nullptr, nullptr, 0);
	}
	
	OptionTree* AbstractSolver::createChild(OptionTree* tree)
	{
		std::list<AbstractCommand*>* commands = tree->getCommands();
		
		OptionTree* result = nullptr;
		
		if (!commands->empty())
		{
			AbstractSituation* nextSituation = getNextSituation(tree->getSituation(), commands->front());
			
			result = new OptionTree(nextSituation, nullptr, tree, tree->getDepth());
		}
		
		return result;
	}
}
