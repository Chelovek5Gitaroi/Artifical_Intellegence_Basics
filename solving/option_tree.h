#ifndef OPTION_TREE
#define OPTION_TREE

#include <list>

#include "abstract_situation.h"
#include "../utilities/abstract_command.h"

namespace chess_solver
{
	class OptionTree
	{
	public:
		OptionTree(AbstractSituation* situation, AbstractCommand* previousCommand, OptionTree* parent, short depth);
		
		~OptionTree();
		
		AbstractSituation* getSituation() {	return situation; }
		AbstractCommand* getPreviousCommand() { return previousCommand; }
		void setCommand(AbstractCommand* command) { this->previousCommand = command; }
		
		short getDepth() { return this->depth; }
		void increaseDepth() { this->depth++; }
		
		OptionTree* getParent() { return parent; }
		
		OptionTree* getCurrentChild();
		OptionTree* getNextChild();
		
		void insertChild(OptionTree* child) { this->children.push_back(child); }
		
		void removeChild(OptionTree* child) { this->children.remove(child); }
	
		std::list<AbstractCommand*>* getCommandSequence();
		
		void setPotentialMoves(std::list<AbstractCommand*>* commands) { this->potentialMoves = commands; }
		
		std::list<AbstractCommand*>* getCommands() { return this->potentialMoves; }
		
	private:
		short depth;

		std::list<AbstractCommand*>* potentialMoves;

		AbstractSituation* situation;
		AbstractCommand* previousCommand;
		
		OptionTree* parent;

		std::list<OptionTree*>::iterator currentChild;
		
		std::list<OptionTree*> children;
	};
}

#endif
