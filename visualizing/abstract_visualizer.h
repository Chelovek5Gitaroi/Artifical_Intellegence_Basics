#ifndef ABSTRACT_VISUALIZER
#define ABSTRACT_VISUALIZER

#include <vector>
#include <string>

#include "../solving/abstract_situation.h"
#include "../utilities/abstract_command.h"

namespace chess_solver
{
	class AbstractVisualizer
	{
	public:
		virtual void showSituation(AbstractSituation* abstractSituation) = 0;
		
		virtual void showCommand(AbstractCommand* abstractCommand) = 0;
		
	private:
	};
}

#endif
