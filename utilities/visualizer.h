#ifndef VISUALIZER
#define VISUALIZER

#include <windows.h>
#include <wincon.h>

#include <string>

#include "..\\chess_entities\\board.h"
#include "..\\chess_entities\\player.h"

namespace chess_solver
{
	class Visualizer
	{
	public:
		Visualizer(Board* board, Player* firstPlayer, Player* secondPlayer);
		~Visualizer();
		
		static const std::string DEFAULT_FILE;// = "CONOUT$";
//		void writeMove(std::string& moveDescription);
		
		void render();
				
	private:
		HANDLE consoleFile;
		
		COORD bufferSize;
		COORD topLeftBufferPoint;

		SMALL_RECT consoleScreenArea;

		CHAR_INFO* buffer;
		CHAR_INFO* emptyBoardBuffer;
		
		static const short LEFT_BOARD_IDENT = 2;
		static const short TOP_BOARD_IDENT = 5;
		
		static const short LEFT_COMMAND_IDENT = 15;
		
		static const char FIGURE_CHAR_KING = 'K';
		static const char FIGURE_CHAR_QUEEN = 'Q';
		static const char FIGURE_CHAR_KNIGHT = 'N';
		static const char FIGURE_CHAR_BISHOP = 'B';
		static const char FIGURE_CHAR_ROCK = 'R';
		static const char FIGURE_CHAR_PAWN = 'p';

		static const char TILE_CHAR = ' ';

		static const unsigned short FIGURE_COLOR_BLACK = 0x0008;
		static const unsigned short FIGURE_COLOR_WHITE = 0x0001 | 0x0002 | 0x0004 | 0x0008;
	
		static const unsigned short TILE_COLOR_WHITE =  0x0010 | 0x0020 | 0x0040 | 0x0080;
		//static const unsigned short TILE_COLOR_BLACK = 0x0000;
		
		Board* board;
		
		Player* firstPlayer;
		Player* secondPlayer;
		
		void prepareClearBoardBuffer();
		
		void copyBoardBufferToOutBuffer();
		
		
		short getBufferCellIndexFromCoordinates(short rowIndex, short columnIndex);
		Coordinates makeChessCoordinatesFromIndexes(short rowIndex, short columnIndex);
		
	};
}


#endif
