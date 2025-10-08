#ifndef GAME
#define GAME

#include "..\\chess_entities\\player.h"
#include "..\\chess_entities\\board.h"

#include "../chess_engine/moving_validator.h"

namespace chess_solver
{
	class Game
	{
	public:
		static const char BOARD_SIZE = 8;
		
		Game(char boardSize, FigureColor firstPlayer);
		
		Board* getBoard(){ return &board; }
		Player* getFirstPlayer(){ return &firstPlayer; }
		Player* getSecondPlayer() {	return &secondPlayer; }
		FigureColor getCurrentPlayer() { return currentPlayer; }
		

	private:
		Board board;
		
//		MovingValidator validator;
		
		FigureColor currentPlayer;
		
		Player firstPlayer;
		Player secondPlayer;
	};
}

#endif
