#include "option_tree.h"

namespace chess_solver
{
	OptionTree::OptionTree(AbstractSituation* situation, Command* previousCommand, OptionTree* parent, short depth)
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
		
		this->parent->removeChild(this);
		
		delete this->previousCommand;
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
	
//	void OptionTree::removeChild(OptionTree* child)
//	{
//		auto iter = children.begin();
//		
//		bool wasRemoved = false;
//
//		for (iter; iter != children.end() && !wasRemoved; iter++)
//		{
//			if (*iter == child)
//			{
//				wasRemoved = true;
//				
//				children.remove()
//			}
//		}
//	}
	
}
