#include "command_parser.h"


namespace chess_solver
{
	Command* CommandParser::parseCommand(std::string& command)
	{
//		std::string::iterator iter = command.begin();
//		
//		Coordinates start = getCoordinates(iter, command);
//		
//		CommandType commandType = getCommandType(iter, command);
//		
//		Coordinates finish = getCoordinates(iter, command);
//	
		Command* result = nullptr;	
//
//		if (iter != command.end())
//		{
//			if (checkTransformationCommand(iter, command))
//			{
//				commandType = CommandType::TRANSFORMATION;
//				
//				FigureType newFigureType = getTransormedFigureType(iter, command);
//				
//				result = new CommandTransformation(start, finish, newFigureType, commandType);
//			}
//		}
//		else
//		{
//			result = new Command(start, finish, commandType);
//		}
		
		return result;
	}
	
	Coordinates CommandParser::getCoordinates(std::string::iterator& iter, std::string& command)
	{
		std::string columnString = "";
		
		for (iter; iter != command.end() && isColumnNameChar(std::tolower(*iter)); iter++)
		{
			columnString += *iter;
		}
		
		if (columnString.size() != 1)
		{
			throw exceptions::InvalidCommandException(exceptions::InvalidCommandException::ERROR_MESSAGE_INVALID_COORDINATES);
		}
		
		std::string rowString = "";
		
		for (iter; iter != command.end() && std::isdigit(*iter); iter++)
		{
			rowString += *iter;
		}
		
		if (rowString.size() == 0)
		{
			throw exceptions::InvalidCommandException(exceptions::InvalidCommandException::ERROR_MESSAGE_INVALID_COORDINATES);
		}	
			
		return Coordinates(columnString[0], static_cast<char>(std::stoi(rowString)));
	}

		
	CommandType CommandParser::getCommandType(std::string::iterator& iter, std::string& command)
	{
		if (hasItemInSet(ChessChars::COMMAND_POSITION_MOVE_SEPARATORS, *iter))
		{
			iter++;
			return CommandType::MOVE;			
		}
		
		if (hasItemInSet(ChessChars::COMMAND_POSITION_BEAT_SEPARATORS, *iter))
		{
			iter++;
			return CommandType::BEAT;
		}
		
		throw exceptions::InvalidCommandException(exceptions::InvalidCommandException::ERROR_MESSAGE_INVALID_COORDINATES_SEPARATOR);
	}
		
	bool CommandParser::checkTransformationCommand(std::string::iterator& iter, std::string& command)
	{
		if (*iter == ChessChars::COMMAND_TRANSFORMATION_CHAR)
		{
			iter++;
			return true;
		}
		else
		{
			return false;
		}
	}
	
	FigureType CommandParser::getTransormedFigureType(std::string::iterator& iter, std::string& command)
	{
		return FigureCreator::getFigureTypeFromString(*iter);
	}
	
	char CommandParser::getFigureChar(FigureType figureType)
	{
		char result = ChessChars::TILE_CHAR;
		
		switch (figureType)
		{
		case FigureType::PAWN:
			result = ChessChars::FIGURE_CHAR_PAWN;
			break;
			
		case FigureType::BISHOP:
			result = ChessChars::FIGURE_CHAR_BISHOP;
			break;
			
		case FigureType::KNIGHT:
			result = ChessChars::FIGURE_CHAR_KNIGHT;
			break;
		
		case FigureType::ROCK:
			result = ChessChars::FIGURE_CHAR_ROCK;
			break;
			
		case FigureType::QUEEN:
			result = ChessChars::FIGURE_CHAR_QUEEN;
			break;
			
		case FigureType::KING:
			result = ChessChars::FIGURE_CHAR_KING;
			break;
		}
		
		return result;
	}
	
	std::string CommandParser::makeStringCommand(Command* command)
	{
		std::string result;
		
		if (command)
		{
			result += getFigureChar(command->getFigure()->getType());
		
			result += command->getFigure()->getCoordinates().toString();
		
			CommandType commandType = command->getType();
		
			if (commandType == CommandType::MOVE || commandType == CommandType::TRANSFORMATION)
			{
				result += *ChessChars::COMMAND_POSITION_MOVE_SEPARATORS.begin();
			}
			else if (commandType == CommandType::BEAT || commandType == CommandType::BEAT_TRANSFORMATION)
			{
				result += *ChessChars::COMMAND_POSITION_BEAT_SEPARATORS.begin();
			}
		
			result += command->getFinishCoordinates().toString();
		
			if (commandType == CommandType::TRANSFORMATION || commandType == CommandType::BEAT_TRANSFORMATION)
			{
				CommandTransformation* transCommand = reinterpret_cast<CommandTransformation*>(command);
			
				result += ChessChars::COMMAND_TRANSFORMATION_CHAR;
			
				result += getFigureChar(transCommand->getNewFigureType());
			}
		}
		
		return result;
	}
	
}
