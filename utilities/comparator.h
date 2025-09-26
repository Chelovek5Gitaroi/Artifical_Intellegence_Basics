#ifndef COMPARATOR
#define COMPARATOR

namespace chess_solver
{
	template<typename T>
	class Comparator final
	{
	public:
		static bool greaterEqual(T a, T b) { return a >= b;}
		
		static bool greater(T a, T b) { return a > b; }
		
		static bool equal(T a, T b) { return a == b; }
		
		static bool notEqual(T a, T b) { return a != b; }
		
		static bool less(T a, T b) { return a < b; }
		
		static bool lessEqual(T a, T b) { return a <= b; }
	};
}

#endif
