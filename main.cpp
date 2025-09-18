#include <iostream>

#include <string>


#include <list>

#include "chess_engine/chess_controller.h"

int main(int argc, char** argv)
{
//	std::string str;
//	
//	str.insert(str.begin(), 4, 'd');
//	
//	std::cout << str;
//	
	
	chess_solver::ChessController controller(chess_solver::Game::BOARD_SIZE, chess_solver::FigureColor::WHITE);
	
	std::string fileName(chess_solver::ChessController::DEFAULT_FIGURE_DESCRIPTION_NAME);
	
	controller.init(fileName);
	
	controller.show();

	
	system("pause");
	
	return 0;
}
