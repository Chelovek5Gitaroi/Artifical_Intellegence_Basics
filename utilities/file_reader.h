#ifndef FILE_READER
#define FILE_READER

#include <list>
#include <string>
#include <fstream>

#include "..\\chess_entities\\board.h"
#include "..\\chess_entities\\figure.h"
#include "..\\chess_entities\\player.h"

namespace chess_solver
{
	class FileReader
	{
	public:
		~FileReader();
		
		static const std::string COLOR_BLACK;
		static const std::string COLOR_WHITE;
		
		static const std::string PLAYER_SEPARATOR;

		void readFigureFile(std::string& fileName);

		char getMovingPlayerColor() { return movingPlayerColor; }
		
		std::list<std::string*>& getWhiteFigures() { return whiteFigures; }
		std::list<std::string*>& getBlackFigures() { return blackFigures; }
		
		
	private:
		char movingPlayerColor;
		
		std::list<std::string*> whiteFigures;
		std::list<std::string*> blackFigures;
		
		bool isStringFirstPlayerColor(std::string& str);
				
	};
}

#endif
