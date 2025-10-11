#include "figure_creator.h"

namespace chess_solver
{
	std::list<Figure*>* FigureCreator::makeFigureList(std::list<std::string*>& figureDescriptions, FigureColor figureColor)
	{
		std::list<Figure*>* result = new std::list<Figure*>();
		
		for (std::string* str: figureDescriptions)
		{
			if (str->size() > 0)
			{
				try
				{
					result->push_back(createFigure(*str, figureColor));	
				}
				catch(exceptions::InvalidFigureDescriptionException& ex)
				{
					std::cerr << ex.what();
				}
			}
		}
		
		return result;
	}
	
	FigureType FigureCreator::getFigureTypeFromString(char ch)
	{
		FigureType figureType;
		
		switch (ch)
		{
		case ChessChars::FIGURE_CHAR_PAWN:
			figureType = FigureType::PAWN;
			break;
			
		case ChessChars::FIGURE_CHAR_BISHOP:
			figureType = FigureType::BISHOP;
			break;
			
		case ChessChars::FIGURE_CHAR_KNIGHT:
			figureType = FigureType::KNIGHT;
			break;
			
		case ChessChars::FIGURE_CHAR_ROCK:
			figureType = FigureType::ROCK;
			break;
			
		case ChessChars::FIGURE_CHAR_QUEEN:
			figureType = FigureType::QUEEN;
			break;
			
		case ChessChars::FIGURE_CHAR_KING:
			figureType = FigureType::KING;
			break;
		
		default:
			throw exceptions::InvalidFigureDescriptionException(exceptions::InvalidFigureDescriptionException::ERROR_MESSAGE_INVALID_FIGURE_TYPE/*, ch*/);
			break;
		}		
		
		return figureType;
	}
	
	Figure* FigureCreator::createFigure(std::string& figureDescription, FigureColor color)
	{
		FigureType type = getFigureTypeFromString(figureDescription[0]);
		
		char column = getColumnFromString(figureDescription);
		
		char row = getRowFromString(figureDescription);
		
		if (row == 0 || row > this->boardSize)
			throw exceptions::InvalidFigureDescriptionException(exceptions::InvalidFigureDescriptionException::ERROR_MESSAGE_INVALID_ROW_NUMBER);
			
		if (column < ChessChars::FIRST_ENGLISH_LETTER || column >= ChessChars::FIRST_ENGLISH_LETTER + this->boardSize)
			throw exceptions::InvalidFigureDescriptionException(exceptions::InvalidFigureDescriptionException::ERROR_MESSAGE_INVALID_COLUMN_NAME);
		
		return new Figure(type, color, column, row);
	}
	
	char FigureCreator::getColumnFromString(std::string& str)
	{
		size_t index = 0;
		
		while (str[index] != DESCRIPTION_PARTS_SEPARATOR && index < str.size())
		{
			index++;
		}
		
		index++;
		
		if (index >= str.size())
		{
			throw exceptions::InvalidFigureDescriptionException(exceptions::InvalidFigureDescriptionException::ERROR_MESSAGE_INVALID_FIGURE_DESCRIPTION_SINTACSIS);
		}

		std::string columnString = "";
		
		while (ChessChars::FIRST_ENGLISH_LETTER <= std::tolower(str[index]) && std::tolower(str[index]) <= ChessChars::LAST_ENGLISH_LETTER && index < str.size())
		{
			columnString += str[index];
			index++;
		}
		
		if (columnString.size() != 1)
		{
			throw exceptions::InvalidFigureDescriptionException(exceptions::InvalidFigureDescriptionException::ERROR_MESSAGE_INVALID_COLUMN_NAME);
		}
				
		return static_cast<char>(columnString[0]);
	}
	
	char FigureCreator::getRowFromString(std::string& str)
	{
		size_t i = 0;
		
		while (!std::isdigit(str[i]) && i < str.size())
		{
			i++;
		}
	
		if (i == str.size())
		{
			throw exceptions::InvalidFigureDescriptionException(exceptions::InvalidFigureDescriptionException::ERROR_MESSAGE_INVALID_ROW_NUMBER);
		}
		
		std::string rowStr = "";
		
		while (std::isdigit(str[i]) && i < str.size())
		{
			rowStr += str[i];
			i++;
		}
				
		return static_cast<char>(std::stoi(rowStr));
	}
}
