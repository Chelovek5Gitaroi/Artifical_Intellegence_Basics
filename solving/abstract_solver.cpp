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
	
	OptionTree* AbstractSolver::useWideSearch(short maximalDepth, std::ofstream& fout)
	{
		std::queue<OptionTree*>* rootQueue = new std::queue<OptionTree*>();
		
		rootQueue->push(this->tree);
		
		OptionTree* result = wideSearch(rootQueue, maximalDepth, fout);
		
		delete rootQueue;
		
		return result;
	}
	
	OptionTree* AbstractSolver::wideSearch(std::queue<OptionTree*>* treeLevel, short maximalDepth, std::ofstream& fout)
	{
		OptionTree* result = nullptr;
		
		fout << "using wide search..." << std::endl << "source level nodes numbers: " << treeLevel->size() << std::endl;
		
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
		
		fout << "not deadlock number: " << processedNodes->size() << std::endl;
		
		if (!result && !processedNodes->empty())
		{
			std::queue<OptionTree*>* nextTreeLevel = generateNextTreeLevel(processedNodes, maximalDepth, fout);
			
			result = wideSearch(nextTreeLevel, maximalDepth, fout);
			delete nextTreeLevel;
		}
		
		delete processedNodes;
		
		return result;
	}
	
	
	std::queue<OptionTree*>* AbstractSolver::generateNextTreeLevel(std::queue<OptionTree*>* treeLevel, short maximalDepth, std::ofstream& fout)
	{
		std::queue<OptionTree*>* result = new std::queue<OptionTree*>();
		
		fout << "Generating next level. tree level size: " << treeLevel->size() << std::endl;
		
		while (!treeLevel->empty())
		{
			createTreeChildren(treeLevel->front(), result, fout);
			
			fout << "next level size: " << result->size() << std::endl;
			
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
	
	void AbstractSolver::createTreeChildren(OptionTree* tree, std::queue<OptionTree*>* children, std::ofstream& fout)
	{
		fout << "creating tree children" << std::endl;
		
		while (!tree->getCommands()->empty())
		{
			OptionTree* child = createChild(tree);
			
			tree->insertChild(child);
			children->push(child);
		}
	}
	
	
}
