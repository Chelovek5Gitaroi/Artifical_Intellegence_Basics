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
		std::list<OptionTree*>* rootList = new std::list<OptionTree*>();
		
		rootList->push_back(this->tree);
		
		OptionTree* result = wideSearch(rootList, maximalDepth, fout);
		
		delete rootList;
		
		return result;
	}
	
	OptionTree* AbstractSolver::wideSearch(std::list<OptionTree*>* treeLevel, short maximalDepth, std::ofstream& fout)
	{
		OptionTree* result = nullptr;
		
		fout << "using wide search..." << std::endl << "source level nodes numbers: " << treeLevel->size() << std::endl;
		
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
		
		fout << "not deadlock number: " << processedNodes->size() << std::endl;
		
		if (!result && !processedNodes->empty())
		{
			std::list<OptionTree*>* nextTreeLevel = generateNextTreeLevel(processedNodes, maximalDepth, fout);
			
			result = wideSearch(nextTreeLevel, maximalDepth, fout);
			delete nextTreeLevel;
		}
		
		delete processedNodes;
		
		return result;
	}
	
	
	std::list<OptionTree*>* AbstractSolver::generateNextTreeLevel(std::list<OptionTree*>* treeLevel, short maximalDepth, std::ofstream& fout)
	{
		std::list<OptionTree*>* result = new std::list<OptionTree*>();
		
		fout << "Generating next level. tree level size: " << treeLevel->size() << std::endl;
		
		while (!treeLevel->empty())
		{
			createTreeChildren(treeLevel->front(), result, fout);
			
			fout << "next level size: " << result->size() << std::endl;
			
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
	
	void AbstractSolver::createTreeChildren(OptionTree* tree, std::list<OptionTree*>* children, std::ofstream& fout)
	{
		fout << "creating tree children" << std::endl;
		
		while (!tree->getCommands()->empty())
		{
			OptionTree* child = createChild(tree);
			
			tree->insertChild(child);
			children->push_back(child);
		}
	}
	
	
}
