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
		
		this->tree = new OptionTree(startSituation, nullptr, nullptr, 1);
	}
	
	bool AbstractSolver::useDeepSearch(short maximalDepth)
	{
		std::ofstream fout("log.txt", std::ios::app);
		
		return deepSearch(this->tree, maximalDepth, fout);
	}
	
	bool AbstractSolver::deepSearch(OptionTree* tree, short maximalDepth, std::ofstream& fout)
	{
		fout << "Using base deep search\n";
		fout.flush();
		
		fout << tree->toString();
		fout.flush();
		
		if (isDeadlock(tree, maximalDepth, fout))
		{
			return false;
		}
		else if (isTargetSituation(tree, fout))
		{
			return true;
		}
		else
		{
			bool result = false;
			
			OptionTree* child = nullptr;
		
			while (!result && !tree->getCommands()->empty())
			{
				child = createChild(tree, fout);
				
				result = deepSearch(child, maximalDepth, fout);
				
				if (!result)
				{
//					tree->removeChild(child);
					delete child;
					child = nullptr;
				}
				else
				{
					tree->insertChild(child);
				}
			}
			
			return result;
		}
	}
	
	OptionTree* AbstractSolver::createChild(OptionTree* tree, std::ofstream& fout)
	{
		fout << "Base creating child\n";
		fout.flush();
		
		std::list<AbstractCommand*>* commands = tree->getCommands();
		
		OptionTree* result = nullptr;
		
		if (!commands->empty())
		{
			fout << "Creating next situation\n";
			fout.flush();
			
			AbstractSituation* nextSituation = getNextSituation(tree->getSituation(), commands->front());
			
			commands->pop_front();
			
			result = new OptionTree(nextSituation, nullptr, tree, tree->getDepth());
		}
		
		if (result)
		{
			fout << "Base child created\n";
		}
		else
		{
			fout << "Failed to base create child\n";
		}
		
		fout.flush();
		
		return result;
	}
}
