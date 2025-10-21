#ifndef SOLVER
#define SOLVER

//#include <iostream>

#include "../abstract_solver.h"
#include "../../utilities/chess_command_executor.h"
#include "situation.h"
#include "../../chess_engine/moving_preparator.h"
#include "../../chess_engine/moving_validator.h"

#include <fstream>
#include <exception>

//#include "chess_situation_maker.h"

namespace chess_solver
{
	class Solver : public AbstractSolver
	{
	public:
		
//		Solver(AbstractSituationMaker* situationMaker);
//		~Solver(){ std::cout << "*Debug* solver d-tor\n"; }
				
		bool useDeepSearch(short maximalDepth) override;
	
		void initTree(AbstractSituation* startSituation) override;
	
	protected:
	
		AbstractSituation* getNextSituation(AbstractSituation* abstractSituation, AbstractCommand* command) override;
	
		OptionTree* createChild(OptionTree* tree) override;
	
		bool isTargetSituation(OptionTree* tree, std::ofstream& fout) override;
	
		bool isDeadlock(OptionTree* tree, int maximalDepth, std::ofstream& fout) override;
	
//		void addNewChild(OptionTree* tree);
	
	private:
		std::list<AbstractCommand*>* getAllSituationMoves(Situation& situation, std::ofstream& fout);
		
		ChessCommandExecutor executor;
		
		std::list<AbstractCommand*>* getFigurePotentialMoves(Board& board, Figure* figure, const Coordinates& kingCoordinates, std::list<Figure*>* figures, std::list<Figure*>* otherFigures, std::ofstream& fout);
		
		Figure* getKingFromList(std::list<Figure*>* figures, std::ofstream& fout);
		
		Command* createValidCommand(Figure* figure, Board& board, const Coordinates& finishCoordinates, CommandType type,
			const Coordinates& kingCoordinates, std::list<Figure*>* figures, std::list<Figure*>* otherFigures, std::ofstream& fout);
		
		bool createValidTransformationCommands(Figure* figure, Board& board, const Coordinates& finishCoordinates, CommandType type,
			const Coordinates& kingCoordinates, std::list<Figure*>* figures, std::list<Figure*>* otherFigures, std::list<AbstractCommand*>* commands, std::ofstream& fout);
		
		
		bool isTargetSituation(Situation* situation, std::list<AbstractCommand*>* potentialMoves, std::ofstream& fout);
		
		bool isDeadlock(Situation* situation, std::list<AbstractCommand*>* potentialMoves, short maximalDepth, short currentDepth, std::ofstream& fout);
		
		bool deepSearch(OptionTree* tree, short maximalDepth, std::ofstream& fout);
		
	};
}

#endif
