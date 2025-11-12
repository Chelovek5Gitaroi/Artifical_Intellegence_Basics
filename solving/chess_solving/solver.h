#ifndef SOLVER
#define SOLVER

//#include <iostream>

#include "../abstract_solver.h"
#include "../../utilities/chess_command_executor.h"
#include "situation.h"
#include "../../chess_engine/moving_preparator.h"
#include "../../chess_engine/moving_validator.h"

#include <exception>

namespace chess_solver
{
	class Solver : public AbstractSolver
	{
	public:
		
		void initTree(AbstractSituation* startSituation) override;
	
	protected:
	
		AbstractSituation* getNextSituation(AbstractSituation* abstractSituation, AbstractCommand* command) override;
	
		OptionTree* createChild(OptionTree* tree) override;
	
		bool isTargetSituation(OptionTree* tree) override;
	
		bool isDeadlock(OptionTree* tree, int maximalDepth) override;
	
		OptionTree* deepSearch(OptionTree* tree, short maximalDepth) override;
	
	private:
		std::list<AbstractCommand*>* getAllSituationMoves(Situation& situation);
		
		ChessCommandExecutor executor;
		
		std::list<AbstractCommand*>* getFigurePotentialMoves(Board& board, Figure* figure, const Coordinates& kingCoordinates, std::list<Figure*>* figures, std::list<Figure*>* otherFigures);
		
		Figure* getKingFromList(std::list<Figure*>* figures);
		
		Command* createValidCommand(Figure* figure, Board& board, const Coordinates& finishCoordinates, CommandType type,
			const Coordinates& kingCoordinates, std::list<Figure*>* figures, std::list<Figure*>* otherFigures);
		
		bool createValidTransformationCommands(Figure* figure, Board& board, const Coordinates& finishCoordinates, CommandType type,
			const Coordinates& kingCoordinates, std::list<Figure*>* figures, std::list<Figure*>* otherFigures, std::list<AbstractCommand*>* commands);
		
		
		bool isTargetSituation(Situation* situation, std::list<AbstractCommand*>* potentialMoves);
		
		bool isDeadlock(Situation* situation, std::list<AbstractCommand*>* potentialMoves, short maximalDepth, short currentDepth);
	};
}

#endif
