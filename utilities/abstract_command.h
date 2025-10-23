#ifndef ABSTRACT_COMMAND
#define ABSTRACT_COMMAND

#include <string>

namespace chess_solver
{
	class AbstractCommand
	{
	public:
		virtual ~AbstractCommand() = 0;
		
		virtual std::string toString() = 0;
	};
}

#endif
