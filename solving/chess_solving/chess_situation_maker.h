#ifndef CHESS_SITUATION_MAKER
#define CHESS_SITUATION_MAKER

#include <map>
#include <list>

#include "../abstract_situation_maker.h"
#include "../../chess_entities/coordinates.h"
#include "../../chess_engine/moving_preparator.h"
#include "../../chess_engine/moving_validator.h"
#include "../../utilities/command.h"
#include "../../utilities/chess_command_executor.h"
#include "situation.h"

namespace chess_solver
{
	class ChessSituationMaker : public AbstractSituationMaker
	{
	public:
//		void prepareStartSituationMoves(Situation* startSituation);
		
		std::list<AbstractCommand*>* getAllSituationMoves(Situation& situation);
		
		AbstractSituation* getNextSituation(AbstractSituation* abstractSituation, AbstractCommand* command) override;
		
	private:
		ChessCommandExecutor executor;
		
		std::list<AbstractCommand*>* getFigurePotentialMoves(Board& board, Figure* figure, const Coordinates& kingCoordinates, std::list<Figure*>* figures, std::list<Figure*>* otherFigures);

		
		
		Figure* getKingFromList(std::list<Figure*>* figures);
		
		Command* createValidCommand(Figure* figure, Board& board, const Coordinates& finishCoordinates, CommandType type,
			const Coordinates& kingCoordinates, std::list<Figure*>* figures, std::list<Figure*>* otherFigures);
		
		bool createValidTransformationCommands(Figure* figure, Board& board, const Coordinates& finishCoordinates, CommandType type,
			const Coordinates& kingCoordinates, std::list<Figure*>* figures, std::list<Figure*>* otherFigures, std::list<AbstractCommand*>* commands);
		
	};
}

#endif
