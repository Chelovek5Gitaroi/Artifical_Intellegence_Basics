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
		
		result += "Depth: " + std::to_string(this->depth) + "\n";
		
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
		bool hasChildren = !this->children.empty();
		
		this->children.push_back(child);
		
		if (!hasChildren)
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
		if (this->currentChild == this->children.end())
		{
			return nullptr;
		}
		
		return *currentChild;
	}
	
	std::list<AbstractCommand*>* OptionTree::getCommandSequence()
	{
		std::list<AbstractCommand*>* result = nullptr;
		
		if (this->children.empty())
		{
			std::list<AbstractCommand*>* result = new std::list<AbstractCommand*>();
		}
		else
		{
			result = this->children.front()->getCommandSequence();
		}
		
//		if (this->previousCommand)
//		{
		result->push_front(this->previousCommand);	
//		}
		
		return result;
	}	
}
