#include "option_tree.h"

//#include <iostream>`

namespace chess_solver
{
	OptionTree::OptionTree(AbstractSituation* situation, AbstractCommand* previousCommand, OptionTree* parent, short depth)
	{
		this->situation = situation;
		
		this->previousCommand = previousCommand;
		this->parent = parent;
		
		this->depth = depth;
		
		this->currentChild = this->children.begin();
	}
	
	OptionTree::~OptionTree()
	{
		for (auto iter = this->children.begin(); iter != children.end(); iter++)
		{
			delete *iter;
		}
		
//		if (this->parent)
//		{
//			this->parent->removeChild(this);
//		}
		
		if (this->previousCommand)
		{
			delete this->previousCommand;
		}
		
		delete this->situation;
	}
	
	std::string OptionTree::toString()
	{
		std::string result;

		result += "Depth: " + std::to_string(this->depth) + "\nCommand: ";

		if (this->previousCommand)
		{
			result += previousCommand->toString();
		}
		
		result += "\n";
		
		if (this->situation)
		{
			result += this->situation->toString();
		}
		
		result += "Moves:\n";
		
		if (this->potentialMoves)
		{
			for (AbstractCommand* cmd : *this->potentialMoves)
			{
				result += cmd->toString() + "\n";
			}
			
			result += "\n";
		}
		
		return result;
	}
	
	void OptionTree::insertChild(OptionTree* child)
	{
//		bool hasChildren = !;
		
		this->children.push_back(child);
		
		if (this->children.empty())
		{
			this->currentChild = this->children.begin();
		}
	}
	
	OptionTree* OptionTree::OptionTree::getNextChild()
	{
		if (this->currentChild == this->children.end())
		{
			return nullptr;
		}
		
		this->currentChild++;
		
		return *this->currentChild;
	}
	
	OptionTree* OptionTree::getCurrentChild()
	{
		if (this->children.empty())
		{
			return nullptr;
		}
		
		if (this->currentChild == this->children.end())
		{
			return children.back();
		}

		return *currentChild;
	}
	
	OptionTree* OptionTree::getFirstChild()
	{
		if (this->children.empty())
		{
			return nullptr;
		}
		
		this->currentChild = children.begin();
		
		return *currentChild;
	}
	
	void OptionTree::removeChild(OptionTree* child)
	{
		this->currentChild = children.begin();
		
		this->children.remove(child);
	}
	
	std::list<AbstractCommand*>* OptionTree::getCommandSequence()
	{
		std::list<AbstractCommand*>* result = nullptr;
		
		std::ofstream fout("tree_log.txt", std::ios::app);
		
		fout << this->toString();
		
		if (this->children.empty())
		{
			fout << "creating empty list\n";
			fout.flush();
			fout.close();
			
			result = new std::list<AbstractCommand*>();
		}
		else
		{
			fout << "getting child command\n";
			fout.flush();
			fout.close();
			
			result = this->children.front()->getCommandSequence();
		}
		
		fout.open("tree_log.txt", std::ios::app);
		
		if (result)
		{
			fout << "pushing command\n";
			result->push_front(this->previousCommand);
		}
		else
		{
			fout << "no list!\n";
		}
		
		fout.flush();
		fout.close();
		
//		if (this->previousCommand)
//		{
			
//		}
		
		return result;
	}	
}
