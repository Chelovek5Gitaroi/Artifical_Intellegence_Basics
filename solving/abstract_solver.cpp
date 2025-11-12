#include "abstract_solver.h"

namespace chess_solver
{
	AbstractSolver::~AbstractSolver()
	{
		delete this->tree;
	}
	
	AbstractSolver::AbstractSolver()
	{
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
		if (tree)
		{
			clearTree();
		}
		
		this->tree = new OptionTree(startSituation, nullptr, nullptr, 1);
	}
	
	bool AbstractSolver::useDeepSearch(short maximalDepth)
	{
		return deepSearch(this->tree, maximalDepth);
	}
	
	bool AbstractSolver::deepSearch(OptionTree* tree, short maximalDepth)
	{
		bool result = false;
		
		if (isDeadlock(tree, maximalDepth))
		{
			result = false;
		}
		else if (isTargetSituation(tree))
		{
			result = true;
		}
		else
		{
			result = false;
			
			OptionTree* child = nullptr;
		
			while (!result && !tree->getCommands()->empty())
			{
				child = createChild(tree);
				
				if (child)
				{
					result = deepSearch(child, maximalDepth);
				
					if (!result)
					{
						delete child;
						child = nullptr;
					}
					else
					{
						tree->insertChild(child);
					}
				}
			}
		}
		
		return result;
	}
	
//<<<<<<< HEAD
//	OptionTree* AbstractSolver::createChild(OptionTree* tree)
//=======
	
	bool AbstractSolver::wideSearch(std::queue<OptionTree*>* treeLevel, short maximalDepth, std::ofstream& fout)
	{
		bool result = false;
		
		std::queue<OptionTree*>* processedNodes = new std::queue<OptionTree*>();

		while (!result && !treeLevel->empty())
		{
			OptionTree* tree = treeLevel->front();
			
			processedNodes->push(tree);
			
			if (isTargetSituation(tree, fout))
			{
				result = true;
			}
		}
		
		if (!result)
		{
//			result = 
		}
		
		return result;
	}
	
	
	std::queue<OptionTree*>* AbstractSolver::generateNextTreeLevel(std::queue<OptionTree*>* treeLevel, short maximalDepth, std::ofstream& fout)
	{
		std::queue<OptionTree*>* result = new std::queue<OptionTree*>();
		
		while (!treeLevel->empty())
		{
			if (!isDeadlock(treeLevel->front(), maximalDepth, fout))
			{
				createTreeChildren(treeLevel->front(), result, fout);
			}
			
			treeLevel->pop();
		}
		
		return result;
	}
	
	OptionTree* AbstractSolver::createChild(OptionTree* tree, std::ofstream& fout)
//>>>>>>> aeb6af2a0c8779fa6b6573067eb71cb27eae1378
	{
		std::list<AbstractCommand*>* commands = tree->getCommands();
		
		OptionTree* result = nullptr;
		
		if (!commands->empty())
		{
			AbstractSituation* nextSituation = getNextSituation(tree->getSituation(), commands->front());
			
			result = new OptionTree(nextSituation, commands->front(), tree, tree->getDepth());
			
			commands->pop_front();
		}
		
		return result;
	}
	
	void AbstractSolver::createTreeChildren(OptionTree* tree, std::queue<OptionTree*>* children, std::ofstream& fout)
	{
		while (!tree->getCommands())
		{
			OptionTree* child = createChild(tree, fout);
			
			tree->insertChild(child);
			children->push(child);
		}
	}
	
//	void AbstractSolver::insertFirstQueueIntoSecond(std::queue<OptionTree*>* first, std::queue<OptionTree*>* second)
//	{
//		while (!first->empty())
//		{
//			second->push(first->front());
//			first->pop();
//		}
//	}
}
