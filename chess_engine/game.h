#ifndef GAME
#define GAME

#include "..\\chess_entities\\player.h"
#include "..\\chess_entities\\board.h"

namespace chess_solver
{
	class Game
	{
	public:
		Game(unsigned char boardSize);

		
		

	private:
		Board board;
		
		Player firstPlayer;
		Player secondPlayers;
	};
}

#endif
