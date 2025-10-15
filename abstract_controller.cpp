#include "abstract_controller.h"

namespace chess_solver
{
	AbstractController::AbstractController(AbstractSolver* solver, AbstractVisualizer* visualizer, int maximalSearchDepth)
	{
		this->maximalDepth = maximalSearchDepth;
	}
	
	AbstractController::~AbstractController()
	{
		delete this->solver;
	}
	
	bool AbstractController::useDeepSearching(short maximalDepth)
	{
		return solver->useDeepSearch(maximalDepth);
	}
}
