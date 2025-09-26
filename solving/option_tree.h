#ifndef OPTION_TREE
#define OPTION_TREE

#include <list>

#include "situation.h"
#include "../utilities/command.h"

namespace chess_solver
{
//	class OptionTreeTop
//	{
//	public:
//		OptionTreeTop(Situation& situation, Command* previousCommand) : sitaution(situation) {}
//		
//		Situation& getSituation() {	return this->situation; }
//		Command* getPreviousCommand() { return this->previousCommand; }
//		
//	private:
//		Situation situation;
//		Command* previousCommand;
//		
//		OptionTreeTop
//		
//		std::list<OptionTreeTop*> 
//	};
	
	class OptionTree
	{
	public:
		OptionTree(Situation& situation, Command* previousCommand, OptionTree* parent, short depth);
		
		Situation& getSituation() {	return situation; }
		Command* getPreviousCommand() { return previousCommand; }
		
		short getDepth() { return this->depth; }
		
		OptionTree* getParent() { return parent; }
		
		OptionTree* getCurrentChild();
		OptionTree* getNextChild();
		
		void insertChild(OptionTree* child) { this->children.push_back(child); }
		
		void removeChild(OptionTree* child) { this->children.remove(child); }
		
	private:
		short depth;

		Situation situation;
		Command* previousCommand;
		
		OptionTree* parent;

		std::list<OptionTree*>::iterator currentChild;
		
		std::list<OptionTree*> children;
	};
}

#endif
