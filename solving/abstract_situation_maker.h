#ifndef ABSTRACT_SITUATION_MAKER
#define ABSTRACT_SITUATION_MAKER

#include "abstract_situation.h"



namespace chess_solver
{
	class AbstractSituationMaker
	{
	public:
		virtual AbstractSituation* getNextSituation(AbstractSituation* abstractSituation) = 0;
	};
}

#endif
