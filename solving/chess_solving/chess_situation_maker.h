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
//		class SituationMoves
//		{
//		public:
//			SituationMoves(Situation& situation, std::list<Command*>* moves) : situation(situation), moves(moves){}
//			
//			~SituationMoves();
//			
//			Situation& situation;
//			std::list<Command*>* moves;
//		};
		
//		std::list<SituationMoves> allPotentialMoves;
		
		
		void makeMove(Situation& situation, Command* command);
		
		std::list<Command*>* getFigurePotentialMoves(Board& board, Figure* figure);

		void addAllTransformationCommandsToList(Figure* figure, Coordinates& finish, std::list<Command*>& commands);
		
		std::list<Command*>* getAllSituationMoves(Situation& situation);
		
//		bool hasSituation(Situation& situation);
		
//		std::list<Command*>* getSituationMoves(Situation& situation, std::list<SituationMoves>& situationMoves);
		
	};
}

#endif
