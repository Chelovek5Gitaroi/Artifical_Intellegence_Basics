#ifndef FIGURE_CREATOR
#define FIGURE_CREATOR

#include <list>
#include <string>

#include "..\\chess_entities\\figure.h"
#include "coordinates_converter.h"
#include "chess_chars.h"

#include "..\\exceptions\\invalid_figure_description_exception.h"

namespace chess_solver
{
	class FigureCreator
	{
	public:
		static const char DESCRIPTION_PARTS_SEPARATOR = ' ';
		
		FigureCreator(char boardSize) : boardSize(boardSize){}
		
		std::list<Figure*>* makeFigureList(std::list<std::string*>& figureDescriptions, FigureColor figureColor);
		
		static FigureType getFigureTypeFromString(char ch);
	private:
		
		Figure* createFigure(std::string& figureDescription, FigureColor color);
		
		char getColumnFromString(std::string& str);
		char getRowFromString(std::string& str);
		
		char boardSize;
		
	};
}


#endif
