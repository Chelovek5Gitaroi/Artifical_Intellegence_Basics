#ifndef COMMAND
#define COMMAND

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
	
	class Command
	{
	public:
		Command(Figure* figure, Coordinates& finishCoordinates, CommandType commandType) : figure(figure), finishCoordinates(finishCoordinates), type(commandType) {}
		
//		Command(Coordinates& startCoordinates, Coordinates& finishCoordinates, CommandType type, FigureType figureType) :
//			startCoordinates(startCoordinates), finishCoordinates(finishCoordinates), type(type) {}
		
//		Coordinates getStartCoordinates() { return this->startCoordinates; }
		Coordinates& getFinishCoordinates() { return this->finishCoordinates; }
		Figure* getFigure() { return figure; }
		CommandType getType() { return this->type; }
//		FigureType getFigureType() { return this->figureType; }
		
	private:
//		Coordinates startCoordinates;
		Coordinates finishCoordinates;
		CommandType type;
		Figure* figure;
//		FigureType figureType;
//		Figure
	};
	
	class CommandTransformation : public Command
	{
	public:
		CommandTransformation(Figure* figure, Coordinates& finishCoordinates, FigureType newFigureType, CommandType commandType = CommandType::TRANSFORMATION) :
			Command(figure, finishCoordinates, commandType), newFigureType(newFigureType) {}
		
//		CommandTransformation(Coordinates& startCoordinates, Coordinates& finishCoordinates, CommandType type, FigureType newFigureType) :
//			Command(startCoordinates, finishCoordinates, type), newFigureType(newFigureType) {}
			
		FigureType getNewFigureType() { return newFigureType; }
		
	private:
		FigureType newFigureType;
	};
}

#endif
