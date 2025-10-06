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
		
		static bool areListsEqual(const std::list<T*>& firstList, const std::list<T*>& secondList)
		{
			bool result = true;
			
			if (firstList.size() == secondList.size())
			{
				for (auto iterFirst = firstList.begin(), iterSecond = secondList.begin(); result && iterFirst != firstList.end() && iterSecond != secondList.end(); iterFirst++, iterSecond++)
				{
					result = **iterFirst == **iterSecond;
				}
			}
			else
			{
				result = false;
			}
			
			return result;
		}
	};
}

#endif
