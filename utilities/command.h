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
		Command(Coordinates& startCoordinates, Coordinates& finishCoordinates, CommandType type, FigureType newFigureType) :
			startCoordinates(startCoordinates), finishCoordinates(finishCoordinates), type(type), newFigureType(newFigureType) {}
		
		Coordinates getStartCoordinates() { return this->startCoordinates; }
		Coordinates getFinishCoordinates() { return this->finishCoordinates; }
		CommandType getType(){ return this->type; }
		
	private:
		Coordinates startCoordinates;
		Coordinates finishCoordinates;
		CommandType type;
		FigureType newFigureType;
	};
}

#endif
