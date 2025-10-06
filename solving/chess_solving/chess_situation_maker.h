#ifndef CHESS_SITUATION_MAKER
#define CHESS_SITUATION_MAKER

#include <map>
#include <list>

#include "../abstract_situation_maker.h"
#include "../../chess_entities/coordinates.h"
#include "../../chess_engine/moving_preparator.h"
#include "../../chess_engine/moving_validator.h"
#include "../../utilities/command.h"
#include "situation.h"

namespace chess_solver
{
	class ChessSituationMaker : public AbstractSituationMaker
	{
	public:
		~ChessSituationMaker();
		
		AbstractSituation* getNextSituation(AbstractSituation* abstractSituation);
		
	private:
		void makeMove(Situation& situation, Command* command);
		
		std::list<Command*>* getFigurePotentialMoves(Board& board, Figure* figure);

		void addAllTransformationCommandsToList(Figure* figure, Coordinates& finish, std::list<Command*>& commands);
		
		std::list<Command*>* getAllSituationMoves(Situation& situation);
		
		void makeMove(Figure* figure, const Coordinates& finishCoordinates, Board& board);
		void makeTaking(Figure* figure, const Coordinates& finishCoordinates, Figure* figureToTake, Board& board, std::list<Figure*>* secondPlayerFigures);
		void makeTransformation(Figure* figure, const Coordinates& finishCoordinates, Board& board, FigureType newFigureType, std::list<Figure*>* figures);
		void makeBeatTransformation(Figure* figure, const Coordinates& finishCoordinates, Figure* figureToTake, Board& board, FigureType newFigureType,
			std::list<Figure*>* figures, std::list<Figure*>* secondPlayerFigures);
		
		Figure* getFigureFromList(const Coordinates& coordinates, std::list<Figure*>* figures);
	};
}

#endif
