#ifndef COMMAND
#define COMMAND

#include "abstract_command.h"
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
		Command(Figure* figure, const Coordinates& finishCoordinates, CommandType commandType) : figure(figure), finishCoordinates(finishCoordinates), type(commandType) {}
		~Command(){}
		
		Coordinates& getFinishCoordinates() { return this->finishCoordinates; }
		Figure* getFigure() { return figure; }
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
			
			result += figure->toString() + "-" + finishCoordinates.toString();
			
			return result;
		}
		
	private:
		Coordinates finishCoordinates;
		CommandType type;
		Figure* figure;
	};
	
//	class CommandBeat : public Command
//	{
//	public:
//		CommandBeat(Figure* figure, Figure* figureToTake) : Command(figure, figureToTake->getCoordinates(), CommandType::BEAT), figureToTake(figureToTake) {}
//		
//		Figure* getFigureToTake() { return figureToTake; }
//	private:
//		Figure* figureToTake;
//	};
	
	class CommandTransformation : public Command
	{
	public:
		CommandTransformation(Figure* figure, const Coordinates& finishCoordinates, FigureType newFigureType, CommandType commandType = CommandType::TRANSFORMATION) :
			Command(figure, finishCoordinates, commandType), newFigureType(newFigureType) {}
		
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
	
//	class CommandBeatTransformation : public CommandTransformation
//	{
//	public:
//		CommandBeatTransformation(Figure* figure, Figure* figureToTake, FigureType newFigureType) :
//			Command(figure, figure->getCoordinates(), CommandType::BEAT_TRANSFORMATION), figureToTake(figureToTake) {}
//		
//		Figure* getFigureToTake() { return figureToTake; }
//	private:
//		Figure* figureToTake;	
//	};
}

#endif
