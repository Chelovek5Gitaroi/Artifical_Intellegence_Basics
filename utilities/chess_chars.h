#ifndef CHESS_CHARS
#define CHESS_CHARS

#include <set>

namespace chess_solver
{
	class ChessChars
	{
	public:
		static const char TILE_CHAR = ' ';
		
		static const char FIGURE_CHAR_KING = 'K';
		static const char FIGURE_CHAR_QUEEN = 'Q';
		static const char FIGURE_CHAR_KNIGHT = 'N';
		static const char FIGURE_CHAR_BISHOP = 'B';
		static const char FIGURE_CHAR_ROCK = 'R';
		static const char FIGURE_CHAR_PAWN = 'P';
		
		static const char FIRST_ENGLISH_LETTER = 'a';
		static const char LAST_ENGLISH_LETTER = 'z';
		
		static const std::set<char> COMMAND_POSITION_MOVE_SEPARATORS;
		static const std::set<char> COMMAND_POSITION_BEAT_SEPARATORS;
		
		static const char COMMAND_TRANSFORMATION_CHAR = '=';
	};
}

#endif
