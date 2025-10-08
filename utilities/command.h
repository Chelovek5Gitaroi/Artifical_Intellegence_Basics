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
		Command(Figure* figure, Coordinates& finishCoordinates, CommandType commandType) : figure(figure), finishCoordinates(finishCoordinates), type(commandType) {}
		~Command(){}
		
		Coordinates& getFinishCoordinates() { return this->finishCoordinates; }
		Figure* getFigure() { return figure; }
		CommandType getType() { return this->type; }
		
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
		CommandTransformation(Figure* figure, Coordinates& finishCoordinates, FigureType newFigureType, CommandType commandType = CommandType::TRANSFORMATION) :
			Command(figure, finishCoordinates, commandType), newFigureType(newFigureType) {}
		
		FigureType getNewFigureType() { return newFigureType; }
		
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
