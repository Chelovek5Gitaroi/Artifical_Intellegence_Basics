#ifndef OPTION_TREE
#define OPTION_TREE

#include <list>
#include <string>

#include <fstream>

#include "abstract_situation.h"
#include "../utilities/abstract_command.h"

namespace chess_solver
{
	// 
	// Класс, описывающий узел дерева вариантов
	//
	class OptionTree
	{
	public:
		//
		// Конструктор
		// 
		// AbstractSituation* situation - указатель, на рассматриваемую ситуацию
		// AbstractCommand* previousCommand - указатель на объект, описывающий ход, после которого возникла рассматриваемая ситуация
		// OptionTree* parent - узел дерева вариантов, потомком которого является создаваемый узел
		// short depth - глубина создаваемого узла
		OptionTree(AbstractSituation* situation, AbstractCommand* previousCommand, OptionTree* parent, short depth);
		
		OptionTree(OptionTree* other);
		
		// Деструктор
		~OptionTree();
		
		// Метод, возвращающий указатель на текущую ситуацию
		AbstractSituation* getSituation() {	return situation; }
		
		// Метод, возвращающий указатель на объект, описывающий ход, после которого возникла рассматриваемая ситуация
		AbstractCommand* getPreviousCommand() { return previousCommand; }
		
		// Метод, возвращающий количество потомков данного узла
		std::size_t getChildrenNumber() { return this->children.size(); }
		
		// Метод, возвращающий глубину данного узла
		short getDepth() { return this->depth; }
		
		// Метод, увеличивающий глубину данного узла на 1
		void increaseDepth() { this->depth++; }
		
		// Метод, возвращающий указатель на родительский узел
		OptionTree* getParent() { return parent; }
		
		// Метод, возвращающий указатель на рассматриваемого потомка
		OptionTree* getCurrentChild();
		
		// Метод, возвращающий указатель на следующего потомка
		OptionTree* getNextChild();
		
		// Метод, возвращающий указатель на первого потомка
		OptionTree* getFirstChild();
		
		// Метод, добавляющий нового потомка
		// OptionTree* child - указатель на добавляемый дочерний узел
		void insertChild(OptionTree* child);
		
		// Метод, удаляющий указатель на дочерний узел
		// OptionTree* child - указатель на удаляемый узел
		void removeChild(OptionTree* child);
	
		// Метод, возвращающий список объектов, описывающих действия, выполнение которых привело к возникновению рассматриваемой ситуации
		std::list<AbstractCommand*>* getCommandSequence();
		
		// Метод, записывающий указатель на список возможных ходов
		// std::list<AbstractCommand*>* commands - список объектов, описывающих возможные действия
		void setPotentialMoves(std::list<AbstractCommand*>* commands) { this->potentialMoves = commands; }
		
		// Метод, возвращающий указатель на список объектов, описывающих возможные действия
		std::list<AbstractCommand*>* getCommands() { return this->potentialMoves; }
		
		// Метод, возвращающий строковое представление объекта
		std::string toString();
		
				
	private:
		// Глубина узла в дереве
		short depth;

		// Список объектов, описывающих возможные действия
		std::list<AbstractCommand*>* potentialMoves;

		// Рассматриваемая ситуация
		AbstractSituation* situation;
		
		// Объект, описывающий действие, выполнение которого привело к возникновению рассматриваемой ситуации
		AbstractCommand* previousCommand;
		
		// Указатель на родительский узел дерева
		OptionTree* parent;

		// Итератор, указывающий на рассматриваемый дочерний узел
		std::list<OptionTree*>::iterator currentChild;
		
		// Список дочерних узлов
		std::list<OptionTree*> children;
	};
}

#endif
