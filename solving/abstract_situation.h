#ifndef ABSTRACT_SITUATION
#define ABSTRACT_SITUATION

#include <string>

namespace chess_solver
{
	//
	// Класс, описывающий абстрактную ситуацию
	//
	class AbstractSituation
	{
	public:
		// Виртуальный деструктор
		virtual ~AbstractSituation() = 0;
		
		virtual AbstractSituation* copy() = 0;
		
		// Абстрактный метод, возвращающий строковое представление объекта
		virtual std::string toString() = 0;
	};
}

#endif
