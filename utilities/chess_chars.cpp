#include "chess_chars.h"

namespace chess_solver
{
	const std::set<char> ChessChars::COMMAND_POSITION_MOVE_SEPARATORS = {'-'};
	const std::set<char> ChessChars::COMMAND_POSITION_BEAT_SEPARATORS = {'x', ':'};
}
