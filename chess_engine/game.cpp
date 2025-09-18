#include "game.h"

namespace chess_solver
{
	Game::Game(char boardSize, FigureColor firstPlayer) : board(boardSize), currentPlayer(firstPlayer), validator(&this->board)
	{
	}
	
	
}
