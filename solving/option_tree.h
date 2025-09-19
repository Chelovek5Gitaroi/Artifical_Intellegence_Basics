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
		OptionTree(Situation& situation, Command* previousCommand, OptionTree* parent);
		
		Situation& getSituation() {	return situation; }
		Command* getPreviousCommand() { return previousCommand; }
		
		OptionTree* getParent() { return parent; }
		
	private:
		Situation situation;
		Command* previousCommand;
		
		OptionTree* parent;

		OptionTree* currentChild;
				
		std::list<OptionTree*> children;
	};
}

#endif
