#ifndef OPTION_TREE
#define OPTION_TREE

#include <list>

#include "abstract_situation.h"
#include "../utilities/command.h"

namespace chess_solver
{
	class OptionTree
	{
	public:
		OptionTree(AbstractSituation* situation, Command* previousCommand, OptionTree* parent, short depth);
		
		~OptionTree();
		
		AbstractSituation* getSituation() {	return situation; }
		Command* getPreviousCommand() { return previousCommand; }
		
		short getDepth() { return this->depth; }
		
		OptionTree* getParent() { return parent; }
		
		OptionTree* getCurrentChild();
		OptionTree* getNextChild();
		
		void insertChild(OptionTree* child) { this->children.push_back(child); }
		
		void removeChild(OptionTree* child) { this->children.remove(child); }
		
	private:
		short depth;

		AbstractSituation* situation;
		Command* previousCommand;
		
		OptionTree* parent;

		std::list<OptionTree*>::iterator currentChild;
		
		std::list<OptionTree*> children;
	};
}

#endif
