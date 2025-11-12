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
		
		fout << std::boolalpha;
		
		return deepSearch(this->tree, maximalDepth, fout);
	}
	
	bool AbstractSolver::deepSearch(OptionTree* tree, short maximalDepth, std::ofstream& fout)
	{
		fout << "Using base deep search\n";
		fout.flush();
		
		fout << tree->toString();
		fout.flush();
		
		bool result = false;
		
		if (isDeadlock(tree, maximalDepth, fout))
		{
			fout << "Deadlock!\n";
			fout.flush();
			
			result = false;
		}
		else if (isTargetSituation(tree, fout))
		{
			fout << "Target!\n";
			fout.flush();
			
			result = true;
		}
		else
		{
			result = false;
			
			OptionTree* child = nullptr;
		
			while (!result && !tree->getCommands()->empty())
			{
				child = createChild(tree, fout);
				
				if (child)
				{
					result = deepSearch(child, maximalDepth, fout);
				
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
			
			if (tree->getCommands()->empty())
			{
				fout << "Base no more children!";
				fout.flush();
			}
		}
		
		fout << "Base returning " << result << ". depth = " << tree->getDepth() << "\n";
		fout.flush();
		
		return result;
	}
	
	
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
			
			result = new OptionTree(nextSituation, commands->front(), tree, tree->getDepth());
			
			commands->pop_front();
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
