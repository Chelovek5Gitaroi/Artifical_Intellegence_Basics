#include <iostream>
#include <string>
#include <list>

#include "solving/chess_solving/solver.h"
#include "chess_engine/chess_controller.h"
#include "abstract_controller.h"
#include "visualizing/chess_visualizing/visualizer.h"

using namespace chess_solver;

int main(int argc, char** argv)
{
	system("chcp 1251");
//	system("cls");
	
	AbstractController* controller = new ChessController(new Solver(), new Visualizer(ChessController::BOARD_SIZE), ChessController::BOARD_SIZE);
	
	controller->control();
	
	delete controller;
	
//	system("pause");
	
	return 0;
}
