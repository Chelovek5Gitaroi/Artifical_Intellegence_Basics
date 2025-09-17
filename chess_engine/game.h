#ifndef GAME
#define GAME

#include "..\\chess_entities\\player.h"
#include "..\\chess_entities\\board.h"

namespace chess_solver
{
	class Game
	{
	public:
		static const char BOARD_SIZE = 8;
		
		Game(char boardSize);
		
		Board* getBoard(){ return &board; }
		Player* getFirstPlayer(){ return &firstPlayer; }
		Player* getSecondPlayer() {	return &secondPlayer; }

	private:
		Board board;
		
		//FigureColor currentPlayer;
		
		Player firstPlayer;
		Player secondPlayer;
	};
}

#endif
