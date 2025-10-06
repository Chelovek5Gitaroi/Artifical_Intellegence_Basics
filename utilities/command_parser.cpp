#include "command_parser.h"


namespace chess_solver
{
	const std::set<char> CommandParser::COMMAND_POSITION_MOVE_SEPARATORS = {' ', '-'};
	const std::set<char> CommandParser::COMMAND_POSITION_BEAT_SEPARATORS = {'x', ':'};
		
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
		if (hasItemInSet(COMMAND_POSITION_MOVE_SEPARATORS, *iter))
		{
			iter++;
			return CommandType::MOVE;			
		}
		
		if (hasItemInSet(COMMAND_POSITION_BEAT_SEPARATORS, *iter))
		{
			iter++;
			return CommandType::BEAT;
		}
		
		throw exceptions::InvalidCommandException(exceptions::InvalidCommandException::ERROR_MESSAGE_INVALID_COORDINATES_SEPARATOR);
	}
		
	bool CommandParser::checkTransformationCommand(std::string::iterator& iter, std::string& command)
	{
		if (*iter == COMMAND_TRANSFORMATION_CHAR)
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
}
