#ifndef ABSTRACT_CONTROLLER
#define ABSTRACT_CONTROLLER

#include "solving/abstract_solver.h"
#include "visualizing/abstract_visualizer.h"

namespace chess_solver
{
	class AbstractController
	{
	public:
		
		AbstractController(AbstractSolver* solver, AbstractVisualizer* visualizer);
		
		virtual ~AbstractController() = 0;
		
		bool useDeepSearching(short maximalDepth);
		
		
		virtual void control() = 0;
	
	protected:
		int getMaximalDepth() { return maximalDepth; }
		void setMaximalDepth(int maximalDepth) { this->maximalDepth = maximalDepth; }
		
		AbstractSolver* getSolver() { return this->solver; }
		AbstractVisualizer* getVisualizer() { return this->visualizer; }
		
	private:
		int maximalDepth;
		
		AbstractSolver* solver;
		AbstractVisualizer* visualizer;
		
	};
}

#endif
