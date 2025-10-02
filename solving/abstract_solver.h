#ifndef SOLVER
#define SOLVER

#include "option_tree.h"

namespace chess_solver
{
	class AbstractSolver
	{
	public:
		virtual ~AbstractSolver() = 0;
	private:
		OptionTree tree;
		
	};
}

#endif
