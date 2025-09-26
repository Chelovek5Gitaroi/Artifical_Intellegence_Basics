#ifndef VISUALIZER
#define VISUALIZER

#include <windows.h>
#include <wincon.h>

#include <string>


#include "coordinates_converter.h"
#include "..\\chess_entities\\board.h"
#include "..\\chess_entities\\player.h"
#include "figure_creator.h"

namespace chess_solver
{
	class Visualizer
	{
	public:
		
		Visualizer(Board* board, Player* firstPlayer, Player* secondPlayer);
		~Visualizer();
		
		static const std::string DEFAULT_FILE;// = "CONOUT$";
		
//		void writeMove(std::string& moveDescription);
		
		void showSituation();
				
	private:
		HANDLE consoleFile;
		
		COORD bufferSize;
		COORD topLeftBufferPoint;

		SMALL_RECT consoleScreenArea;

		CHAR_INFO* buffer;
		CHAR_INFO* emptyBoardBuffer;
		
		static const short LEFT_BOARD_IDENT = 4;
		static const short TOP_BOARD_IDENT = 3;
		
		static const short LEFT_COMMAND_IDENT = 15;
		
		static const char TILE_CHAR = ' ';
		
		static const char TILE_WIDTH = 3;
		
		static const char BOARD_FRAME_ANGLE_CHAR = '+';
		static const char BOARD_FRAME_HORIZONTAL = '-';
		static const char BOARD_FRAME_VERTICAL = '|';
		

		static const unsigned short FIGURE_COLOR_WHITE = 0x0001 | 0x0002 | 0x0004 | 0x0008;
	
		static const unsigned short FIGURE_COLOR_BACKGROUND = 0x0010 | 0x0020 | 0x0040;
	
		static const unsigned short TILE_COLOR_WHITE =  0x0010 | 0x0020 | 0x0040 | 0x0080;
		
		static const unsigned short BACKGROUND_COLOR_INTENSIFIED = 0X0800;
		
		Board* board;
		
		Player* firstPlayer;
		Player* secondPlayer;
		
		void prepareClearBoardBuffer();
		
		void copyBoardBufferToOutBuffer();
		
		void renderPlayerFigures(Player* player);
		
		char getFigureChar(Figure& figure);
		
		short getBufferCellIndexFromCoordinates(short rowIndex, short columnIndex);
		
		short getBufferCellIndexFromCoordinates(short bufferCellIndex, short rowShift, short columnShift);
		
		short getBufferCellIndexFromChessCoordinates(const Coordinates& coordinates);
//		Coordinates makeChessCoordinatesFromIndexes(short rowIndex, short columnIndex);
		void drawBoardFrame();
		
		void drawRowMarks();
		void drawColumnMarks();
	};
}


#endif
