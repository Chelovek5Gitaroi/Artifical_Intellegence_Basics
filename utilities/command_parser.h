#ifndef COMMAND_PARSER
#define COMMAND_PARSER

#include <set>
#include <string>


#include "chess_chars.h"
#include "..\\chess_entities\\board.h"
#include "figure_creator.h"
#include "../exceptions/invalid_command_exception.h"

#include "command.h"

namespace chess_solver
{
	class CommandParser
	{
	public:
		
		static Command* parseCommand(std::string& command);
		
		static std::string makeStringCommand(Command* command);
		
		CommandParser() = delete;
		~CommandParser() = delete;
	private:
		static Coordinates getCoordinates(std::string::iterator& iter, std::string& command);
		
		static CommandType getCommandType(std::string::iterator& iter, std::string& command);
		
		static bool checkTransformationCommand(std::string::iterator& iter, std::string& command);
		static FigureType getTransormedFigureType(std::string::iterator& iter, std::string& command);
		
		static bool isColumnNameChar(char ch) { return ChessChars::FIRST_ENGLISH_LETTER <= ch && ch <= ChessChars::LAST_ENGLISH_LETTER; }

		static char getFigureChar(FigureType figureType);
		
		template<typename T>
		static bool hasItemInSet(const std::set<T>& items, T& item)
		{
			for (auto iter = items.begin(); iter != items.end(); iter++)
			{
				if (*iter == item)
				{
					return true;
				}
			}
			
			return false;
		} 
		
	};
}

#endif
