#ifndef ABSTRACT_SITUATION_MAKER
#define ABSTRACT_SITUATION_MAKER

#include <list>

#include "../utilities/abstract_command.h"
#include "abstract_situation.h"

namespace chess_solver
{
	class AbstractSituationMaker
	{
	public:
		virtual ~AbstractSituationMaker(){ /*std::cout << "*Debug* abs sit maker d-tor...\n";*/ }
		
		virtual AbstractSituation* getNextSituation(AbstractSituation* abstractSituation, AbstractCommand* command) = 0;
	};
}

#endif
