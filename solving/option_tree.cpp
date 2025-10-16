#include "option_tree.h"

#include <iostream>

namespace chess_solver
{
	OptionTree::OptionTree(AbstractSituation* situation, AbstractCommand* previousCommand, OptionTree* parent, short depth)
	{
//		std::cout << "*Debug* option tree ñ-tor...\n";
		
		this->situation = situation;
		
		this->previousCommand = previousCommand;
		this->parent = parent;
		
		this->depth = depth;
		
		this->currentChild = this->children.begin();
		
//		std::cout << "*Debug* option tree ñ-tor end...\n";
	}
	
	OptionTree::~OptionTree()
	{
//		std::cout << "*Debug* option tree d-tor...\n children: " << this->children.size() << "\n";
		
		for (auto iter = this->children.begin(); iter != children.end(); iter++)
		{
			delete *iter;
		}
		
		if (this->parent)
		{
			this->parent->removeChild(this);
		}
		
		if (this->previousCommand)
		{
			delete this->previousCommand;
		}
		
		delete this->situation;
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
		
}
