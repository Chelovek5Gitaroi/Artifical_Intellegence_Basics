#ifndef COMMAND
#define COMMAND

#include "../chess_entities/figure.h"

namespace chess_solver
{
	enum class CommandType
	{
		MOVE,
		BEAT,
		TRANSFORMATION	
	};
	
	class Command
	{
	public:
		Command(Coordinates& startCoordinates, Coordinates& finishCoordinates, CommandType type) :
			startCoordinates(startCoordinates), finishCoordinates(finishCoordinates), type(type) {}
		
		Coordinates getStartCoordinates() { return this->startCoordinates; }
		Coordinates getFinishCoordinates() { return this->finishCoordinates; }
		CommandType getType(){ return this->type; }
		
	private:
		Coordinates startCoordinates;
		Coordinates finishCoordinates;
		CommandType type;
	};
	
	class CommandTransformation : public Command
	{
	public:
		CommandTransformation(Coordinates& startCoordinates, Coordinates& finishCoordinates, CommandType type, FigureType newFigureType) :
			Command(startCoordinates, finishCoordinates, type), newFigureType(newFigureType) {}
			
		FigureType getNewFigureType() { return newFigureType; }
		
	private:
		FigureType newFigureType;
	};
}

#endif
