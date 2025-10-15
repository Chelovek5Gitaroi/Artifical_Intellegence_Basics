#include "abstract_controller.h"

namespace chess_solver
{
	AbstractController::AbstractController(AbstractSolver* solver, AbstractVisualizer* visualizer)
	{
		this->solver = solver;
		this->visualizer = visualizer;
	}
	
	AbstractController::~AbstractController()
	{
		delete this->solver;
		delete this->visualizer;
	}
	
	bool AbstractController::useDeepSearching(short maximalDepth)
	{
		return solver->useDeepSearch(maximalDepth);
	}
}
