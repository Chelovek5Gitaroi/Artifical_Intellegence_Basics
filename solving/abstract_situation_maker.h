#ifndef ABSTRACT_SITUATION_MAKER
#define ABSTRACT_SITUATION_MAKER

//#include <iostream>

#include "abstract_situation.h"

namespace chess_solver
{
	class AbstractSituationMaker
	{
	public:
		virtual ~AbstractSituationMaker(){ /*std::cout << "*Debug* abs sit maker d-tor...\n";*/ }
		
		virtual AbstractSituation* getNextSituation(AbstractSituation* abstractSituation) = 0;
	};
}

#endif
