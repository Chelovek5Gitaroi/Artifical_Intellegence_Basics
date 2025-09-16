#ifndef FIGURE_CREATOR
#define FIGURE_CREATOR

#include <list>
#include <string>

#include "..\\chess_entities\\figure.h"
#include "..\\chess_entities\\board.h"

//#include "..\\exceptions\\invalid_figure_type_exception.h"
#include "..\\exceptions\\invalid_figure_description_exception.h"

namespace chess_solver
{
	class FigureCreator
	{
	public:
		static const char FIGURE_CHAR_KING = 'K';
		static const char FIGURE_CHAR_QUEEN = 'Q';
		static const char FIGURE_CHAR_KNIGHT = 'N';
		static const char FIGURE_CHAR_BISHOP = 'B';
		static const char FIGURE_CHAR_ROCK = 'R';
		static const char FIGURE_CHAR_PAWN = 'p';
		
		static const char DESCRIPTION_PARTS_SEPARATOR = ' ';
		
		static const char FIRST_ENGLISH_LETTER = 'a';
		static const char LAST_ENGLISH_LETTER = 'z';
		
		FigureCreator(char boardSize) : boardSize(boardSize){}
		
		std::list<Figure*>* makeFigureList(std::list<std::string*>& figureDescriptions, FigureColor figureColor);
		
	private:
		FigureType getFigureTypeFromString(std::string& str);
		
		Figure* createFigure(std::string& figureDescription);
		
		char getColumnFromString(std::string& str);
		char getRowFromString(std::string& str);
		
		char boardSize;
		
	};
}


#endif
