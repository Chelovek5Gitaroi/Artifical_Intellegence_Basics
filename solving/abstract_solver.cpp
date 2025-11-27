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
		std::list<OptionTree*>* rootList = new std::list<OptionTree*>();
		
		rootList->push_back(this->tree);
		
		OptionTree* result = wideSearch(rootList, maximalDepth);
		
		delete rootList;
		
		return result;
	}
	
	OptionTree* AbstractSolver::useGradientSearch(short maximalDepth)
	{
		return gradientSearch(this->tree, maximalDepth);
	}
	
	OptionTree* AbstractSolver::wideSearch(std::list<OptionTree*>* treeLevel, short maximalDepth)
	{
		OptionTree* result = nullptr;
		
		std::list<OptionTree*>* processedNodes = new std::list<OptionTree*>();

		while (!result && !treeLevel->empty())
		{
			OptionTree* tree = treeLevel->front();
			
			treeLevel->pop_front();
			
			if (isTargetSituation(tree))
			{
				result = tree;
			}
			else if (!isDeadlock(tree, maximalDepth))
			{
				processedNodes->push_back(tree);
			}
		}
		
		if (!result && !processedNodes->empty())
		{
			std::list<OptionTree*>* nextTreeLevel = generateNextTreeLevel(processedNodes, maximalDepth);
			
			result = wideSearch(nextTreeLevel, maximalDepth);
			delete nextTreeLevel;
		}
		
		delete processedNodes;
		
		return result;
	}
	
	OptionTree* AbstractSolver::gradientSearch(OptionTree* tree, short maximalDepth)
	{
		OptionTree* result = nullptr;
		
		if (isTargetSituation(tree))
		{
			result = tree;
		}
		else if (!isDeadlock(tree, maximalDepth))
		{
			std::list<OptionTree*>* children = new std::list<OptionTree*>();
			
			createTreeChildren(tree, children);
			
			sortNodesByTargetFunction(children);
			
			while (!result && !children->empty())
			{
				result = gradientSearch(children->front(), maximalDepth);
				
				if (!result)
				{
					tree->removeChild(children->front());
					delete children->front();
					children->pop_front();
				}
			}
			
			delete children;
		}
		
		return result;
	}
	
	void AbstractSolver::sortNodesByTargetFunction(std::list<OptionTree*>* nodes)
	{
		std::vector<std::pair<float, OptionTree*>> sorted(nodes->size());
		
		sorted[0] = std::pair<float, OptionTree*>(evaluationFunction(nodes->front()), nodes->front());
		
		size_t currentSize = 1;
		
		auto iter = nodes->begin();
		iter++;
		
		for (iter; iter != nodes->end(); iter++)
		{
			int ind = 0;
			
			float funcValue = evaluationFunction(*iter);
			
			while (funcValue > sorted[ind].first && ind < currentSize)
			{
				ind++;
			}
			
			for (int i = currentSize - 1; i >= ind; i--)
			{
				sorted[i + 1] = sorted[i];
			}
			
			sorted[ind] = std::pair<float, OptionTree*>(funcValue, *iter);
			currentSize++;
		}
		
		nodes->clear();
		
		for (std::pair<float, OptionTree*> el : sorted)
		{
			nodes->push_back(el.second);
		}
	}
	
	std::list<OptionTree*>* AbstractSolver::generateNextTreeLevel(std::list<OptionTree*>* treeLevel, short maximalDepth)
	{
		std::list<OptionTree*>* result = new std::list<OptionTree*>();
		
		while (!treeLevel->empty())
		{
			createTreeChildren(treeLevel->front(), result);
			
			treeLevel->pop_front();
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
	
	void AbstractSolver::createTreeChildren(OptionTree* tree, std::list<OptionTree*>* children)
	{
		while (!tree->getCommands()->empty())
		{
			OptionTree* child = createChild(tree);
			
			tree->insertChild(child);
			children->push_back(child);
		}
	}
	
	
}
