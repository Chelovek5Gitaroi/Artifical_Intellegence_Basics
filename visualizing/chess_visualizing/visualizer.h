#ifndef VISUALIZER
#define VISUALIZER

#include <windows.h>
#include <wincon.h>

#include "../abstract_visualizer.h"
#include "../../solving/chess_solving/situation.h"
#include "../../utilities/chess_chars.h"
#include "../../utilities/command.h"

namespace chess_solver
{
	class Visualizer : public AbstractVisualizer
	{
	public:
		Visualizer(char boardSize);
		
		~Visualizer();
		
		static const std::string DEFAULT_FILE;
		
		void showSituation(AbstractSituation* abstractSituation) override;
		
		void showCommand(AbstractCommand* abstractCommand) override;
		
		void showMenu(std::vector<std::pair<std::string, bool>>& menuStrings, COORD top);
			
		COORD getMenuTop() { return this->menuTop; }
		COORD getCommandsTop() { return this->commandTop; }
		
		void clearMenu(std::vector<std::pair<std::string, bool>>& menu, COORD top);
		
		void showMessage(const std::string& message, COORD top);
		
	private:
		HANDLE consoleFile;
		
		COORD bufferSize;
		COORD topLeftBufferPoint;
		
		COORD currentCursorPosition;

		COORD menuTop;

		COORD screenSize;
		
		SMALL_RECT windowPosition;

		SMALL_RECT consoleScreenArea;

		COORD commandTop;
		
		COORD commandCurrentCursorPosition;

		CHAR_INFO* buffer;
		CHAR_INFO* emptyBoardBuffer;
		
		char boardSize;
		
		static const short LEFT_BOARD_IDENT = 4;
		static const short TOP_BOARD_IDENT = 3;
		static const short SIDE_COMMANDS_IDENT = 3;
		static const short TOP_COMMAND_IDENT = 4;
		
		static const short MENU_LEFT_IDENT = 3;
		static const short MENU_TOP_IDENT = 2;
		
		static const short LEFT_COMMAND_IDENT = 15;
		
		static const char TILE_WIDTH = 3;
		
		static const char BOARD_FRAME_ANGLE_CHAR = '+';
		static const char BOARD_FRAME_HORIZONTAL = '-';
		static const char BOARD_FRAME_VERTICAL = '|';

		static const std::string SELECTED_ITEM_MARKER;

		static const unsigned short FIGURE_COLOR_WHITE = 0x0001 | 0x0002 | 0x0004 | 0x0008;
	
		static const unsigned short BACKGROUND_COLOR_INTENSIFIED = 0X0080;
	
		static const unsigned short FIGURE_COLOR_BACKGROUND = 0x0080;
	
		static const unsigned short TILE_COLOR_WHITE =  0x0010 | 0x0020 | 0x0040 | 0x0080;
		
		void prepareClearBoardBuffer();
		
		void copyBoardBufferToOutBuffer();
		
		void renderFigures(std::list<Figure*>& figures);
		
		char getFigureChar(Figure& figure);
		char getFigureChar(FigureType figureType);
		
		short getBufferCellIndexFromCoordinates(short rowIndex, short columnIndex);
		
		short getBufferCellIndexFromCoordinates(short bufferCellIndex, short rowShift, short columnShift);
		
		short getBufferCellIndexFromChessCoordinates(const Coordinates& coordinates);
		void drawBoardFrame();
		
		void drawRowMarks();
		void drawColumnMarks();
	};
}


#endif
