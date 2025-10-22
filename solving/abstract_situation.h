#ifndef ABSTRACT_SITUATION
#define ABSTRACT_SITUATION

#include <string>

namespace chess_solver
{
	class AbstractSituation
	{
	public:
		virtual ~AbstractSituation() = 0;
		
		virtual std::string toString() = 0;
	};
}

#endif
