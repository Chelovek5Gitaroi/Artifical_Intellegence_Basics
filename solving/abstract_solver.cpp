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
		
		this->tree->setPotentialMoves(getAllSituationMoves(startSituation));
	}
	
	OptionTree* AbstractSolver::useDeepSearch(short maximalDepth)
	{
		return deepSearch(this->tree, maximalDepth);
	}
	
	OptionTree* AbstractSolver::deepSearch(OptionTree* tree, short maximalDepth)
	{
		OptionTree* result = nullptr;
		
		if (isTargetSituation(tree))
		{
			result = tree;
		}
		else if (!isDeadlock(tree, maximalDepth))
		{
			result = nullptr;
			
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
	
	OptionTree* AbstractSolver::useWideSearch(short maximalDepth)
	{
		std::queue<OptionTree*>* rootQueue = new std::queue<OptionTree*>();
		
		rootQueue->push(this->tree);
		
		OptionTree* result = wideSearch(rootQueue, maximalDepth);
		
		delete rootQueue;
		
		return result;
	}
	
	OptionTree* AbstractSolver::wideSearch(std::queue<OptionTree*>* treeLevel, short maximalDepth)
	{
		OptionTree* result = nullptr;
		
		std::queue<OptionTree*>* processedNodes = new std::queue<OptionTree*>();

		while (!result && !treeLevel->empty())
		{
			OptionTree* tree = treeLevel->front();
			
			treeLevel->pop();
			
			if (isTargetSituation(tree))
			{
				result = tree;
			}
			else if (!isDeadlock(tree, maximalDepth))
			{
				processedNodes->push(tree);
			}
		}
		
		if (!result && !processedNodes->empty())
		{
			std::queue<OptionTree*>* nextTreeLevel = generateNextTreeLevel(processedNodes, maximalDepth);
			
			result = wideSearch(nextTreeLevel, maximalDepth);
			delete nextTreeLevel;
		}
		
		delete processedNodes;
		
		return result;
	}
	
	
	std::queue<OptionTree*>* AbstractSolver::generateNextTreeLevel(std::queue<OptionTree*>* treeLevel, short maximalDepth)
	{
		std::queue<OptionTree*>* result = new std::queue<OptionTree*>();
		
		while (!treeLevel->empty())
		{
			createTreeChildren(treeLevel->front(), result);
			
			treeLevel->pop();
		}
		
		return result;
	}
	
	OptionTree* AbstractSolver::createChild(OptionTree* tree)
	{
		std::list<AbstractCommand*>* commands = tree->getCommands();
		
		OptionTree* result = nullptr;
		
		if (!commands->empty())
		{
			AbstractSituation* nextSituation = getNextSituation(tree->getSituation(), commands->front());
			
			result = new OptionTree(nextSituation, commands->front(), tree, tree->getDepth());
			
			result->setPotentialMoves(getAllSituationMoves(nextSituation));
			
			commands->pop_front();
		}
		
		return result;
	}
	
	void AbstractSolver::createTreeChildren(OptionTree* tree, std::queue<OptionTree*>* children)
	{
		while (!tree->getCommands()->empty())
		{
			OptionTree* child = createChild(tree);
			
			tree->insertChild(child);
			children->push(child);
		}
	}
	
	
}
