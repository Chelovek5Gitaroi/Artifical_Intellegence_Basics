#ifndef ABSTRACT_SOLVER
#define ABSTRACT_SOLVER

#include "option_tree.h"

#include <fstream>
#include <queue>

namespace chess_solver
{
	//
	// Класс, описывающий абстрактный интеллектуальный решатель
	//
	class AbstractSolver
	{
	public:
		// Конструктор
		AbstractSolver();
		
		// Виртуальный деструктор
		virtual ~AbstractSolver() = 0;
		
		// Метод, применяющий обход в глубину к инициализированному дереву
		// short maximalDepth - максимальная глубина поиска
		// Возвращается узел с целевой ситуацией, если такой узел существует, иначе возвращается nullptr
		virtual OptionTree* useDeepSearch(short maximalDepth);
		
		// Метод, применяющий обход в ширину к инициализированному дереву
		// short maximalDepth - максимальная глубина поиска
		// Возвращается узел с целевой ситуацией, если такой узел существует, иначе возвращается nullptr
		virtual OptionTree* useWideSearch(short maximalDepth);
		
		// Метод, выполняющий инициализацию дерева вариантов
		// AbstractSituation* startSituation - начальная ситуация
		virtual void initTree(AbstractSituation* startSituation);
	
		// Метод, возвращающий указатель на корень дерева вариантов
		OptionTree* getTree() const { return tree; }
	
		// Метод, выполняющий очистку дерева
		void clearTree();
		
	protected:
		// Метод, реализующий поиск в глубину
		// OptionTree* tree - рассматриваемый узел дерева
		// short maximalDepth - максимально допустимая глубина поиска
		virtual OptionTree* deepSearch(OptionTree* tree, short maximalDepth);

		// Метод, создающий все узлы дерева, находящиеся на следующем уровне
		// std::queue<OptionTree*>* treeLevel - указатель на очередь, содержащую узлы дерева, находящиеся на одном уровне
		std::queue<OptionTree*>* generateNextTreeLevel(std::queue<OptionTree*>* treeLevel, short maximalDepth);

		// Метод, реализующий поиск в ширину
		// std::queue<OptionTree*>* treeLevel - указатель на очередь, содержащую узлы дерева, находящиеся на рассматриваемом уровне
		// short maximalDepth - максимальная глубина поиска
		virtual OptionTree* wideSearch(std::queue<OptionTree*>* treeLevel, short maximalDepth);
		
		// Абстрактная порождающая процедура
		// AbstractSituation* abstractSituation - указатель на рассматриваемую ситуацию
		// AbstractCommand* command - указатель на объект, описывающий действие, которое необходимо выполнить для создания новой ситуации
		virtual AbstractSituation* getNextSituation(AbstractSituation* abstractSituation, AbstractCommand* command) = 0;
		
		// Виртуальный метод, создающий дочерний узел дерева вариантов
		// OptionTree* tree - указатель на рассматриваемый узел дерева
		virtual OptionTree* createChild(OptionTree* tree);
		
		// Метод, создающий список всех возможных ходов в рассматриваемой ситуации
		// AbstractSituation* abstractSituation - рассматриваемая ситуация
		virtual std::list<AbstractCommand*>* getAllSituationMoves(AbstractSituation* abstractSituation) = 0;
		
		// Абстрактный метод, проверяющий, является ли ситуация в рассматриваемом узле дерева целевой
		// OptionTree* tree - указатель на рассматриваемый узел дерева вариантов
		virtual bool isTargetSituation(OptionTree* tree) = 0;
		
		// Абстрактный метод, проверяющий, является ли ситуация в рассматриваемом узле дерева тупиковой
		// OptionTree* tree - указатель на рассматриваемый узел дерева вариантов
		virtual bool isDeadlock(OptionTree* tree, int maximalDepth) = 0;
	private:
		// Указатель на корневой узел дерева вариантов
		OptionTree* tree;
		
		// Метод, создающий дочерние узлы для заданного, и помещающий их в заданную очередь
		// OptionTree* tree - указатель на узел, потомков которого необходимо создать
		// std::queue<OptionTree*>* children - указатель на очередь, в которую нужно помещать создаваемые узлы
		void createTreeChildren(OptionTree* tree, std::queue<OptionTree*>* children);
	};
}

#endif
