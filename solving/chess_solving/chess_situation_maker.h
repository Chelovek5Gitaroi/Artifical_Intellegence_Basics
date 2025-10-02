#ifndef CHESS_SITUATION_MAKER
#define CHESS_SITUATION_MAKER

#include <map>
#include <list>

#include "../abstract_situation_maker.h"
#include "../../chess_entities/coordinates.h"

namespace chess_solver
{
	class ChessSituationMaker : public AbstractSituationMaker
	{
	public:
		~ChessSituationMaker();
		
		AbstractSituation* getNextSituation(AbstractSituation* situation);
		
	private:
//		std::map<Situation, std::list<Coordinates>> potential
	};
}

#endif
