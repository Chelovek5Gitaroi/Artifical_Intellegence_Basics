#ifndef COMMAND
#define COMMAND

#include "abstract_command.h"
#include "chess_chars.h"
#include "../chess_entities/figure.h"

namespace chess_solver
{
	enum class CommandType
	{
		MOVE,
		BEAT,
		TRANSFORMATION,
		BEAT_TRANSFORMATION	
	};
	
	class Command : public AbstractCommand
	{
	public:
		Command(FigureType figureType, const Coordinates& start, const Coordinates& finish, CommandType commandType) :
			figureType(figureType), startCoordinates(start), finishCoordinates(finish), type(commandType) {}
		
		Command(Command& other) : figureType(other.figureType), startCoordinates(other.startCoordinates), finishCoordinates(other.finishCoordinates), type(other.type) {}
			
		~Command(){}
		
		FigureType getFigureType() { return this->figureType; }
		Coordinates& getStartCoordinates() { return this->startCoordinates; }
		Coordinates& getFinishCoordinates() { return this->finishCoordinates; }
		CommandType getType() { return this->type; }
		
		std::string toString() override
		{
			std::string result;
			
			switch (type)
			{
			case CommandType::MOVE:
				result += "Move ";
				break;
				
			case CommandType::BEAT:
				result += "Beat ";
				break;
				
			case CommandType::TRANSFORMATION:
				result += "Transform ";
				break;
				
			case CommandType::BEAT_TRANSFORMATION:
				result += "Beat transform ";
				break;
			}
			
			result += startCoordinates.toString() + "-" + finishCoordinates.toString();
			
			return result;
		}
		
	private:
		FigureType figureType;
		Coordinates startCoordinates;
		Coordinates finishCoordinates;
		CommandType type;
	};
	
	class CommandTransformation : public Command
	{
	public:
		CommandTransformation(FigureType figureType, const Coordinates& start, const Coordinates& finish, FigureType newFigureType, CommandType commandType = CommandType::TRANSFORMATION) :
			Command(figureType, start, finish, commandType), newFigureType(newFigureType) {}
		
		CommandTransformation(CommandTransformation& other) : Command(other.getFigureType(), other.getStartCoordinates(), other.getFinishCoordinates(), other.getType()), newFigureType(other.newFigureType) {}
		
		FigureType getNewFigureType() { return newFigureType; }
		
		std::string toString() override
		{
			std::string result = Command::toString() + " = ";
			
			switch (newFigureType)
			{
			case FigureType::PAWN:
				result += "pawn";
				break;
				
			case FigureType::KNIGHT:
				result += "knight";
				break;
				
			case FigureType::BISHOP:
				result += "bishop";
				break;
				
			case FigureType::ROCK:
				result += "rock";
				break;
				
			case FigureType::QUEEN:
				result += "queen";
				break;
				
			case FigureType::KING:
				result += "king";
				break;
			}
			
			return result;
		}
		
	private:
		FigureType newFigureType;
	};
}

#endif
