#ifndef ABSTRACT_SOLVER
#define ABSTRACT_SOLVER

#include "option_tree.h"

#include <fstream>
#include <queue>

namespace chess_solver
{
	//
	//  ласс, описывающий абстрактный интеллектуальный решатель
	//
	class AbstractSolver
	{
	public:
		//  онструктор
		AbstractSolver();
		
		// ¬иртуальный деструктор
		virtual ~AbstractSolver() = 0;
		
		// ћетод, примен€ющий обход в глубину к инициализированному дереву
		// ¬озвращаетс€ наличие решени€ дл€ заданной начальной ситуации
		virtual OptionTree* useDeepSearch(short maximalDepth);
		
		virtual OptionTree* useWideSearch(short maximalDepth, std::ofstream& fout);
		
		// ћетод, выполн€ющий инициализацию дерева вариантов
		// AbstractSituation* startSituation - начальна€ ситуаци€
		virtual void initTree(AbstractSituation* startSituation);
	
		// ћетод, возвращающий указатель на корень дерева вариантов
		OptionTree* getTree() const { return tree; }
	
		// ћетод, выполн€ющий очистку дерева
		void clearTree();
		
	protected:
		// ћетод, реализующий поиск в глубину
		// OptionTree* tree - рассматриваемый узел дерева
		// short maximalDepth - максимально допустима€ глубина поиска
		virtual OptionTree* deepSearch(OptionTree* tree, short maximalDepth);
		
		std::queue<OptionTree*>* generateNextTreeLevel(std::queue<OptionTree*>* treeLevel, short maximalDepth, std::ofstream& fout);
		
		virtual OptionTree* wideSearch(std::queue<OptionTree*>* treeLevel, short maximalDepth, std::ofstream& fout);
		
		// јбстрактна€ порождающа€ процедура
		// AbstractSituation* abstractSituation - указатель на рассматриваемую ситуацию
		// AbstractCommand* command - указатель на объект, описывающий действие, которое необходимо выполнить дл€ создани€ новой ситуации
		virtual AbstractSituation* getNextSituation(AbstractSituation* abstractSituation, AbstractCommand* command) = 0;
		
		// ¬иртуальный метод, создающий дочерний узел дерева вариантов
		// OptionTree* tree - указатель на рассматриваемый узел дерева
		virtual OptionTree* createChild(OptionTree* tree);
		
		// јбстрактный метод, провер€ющий, €вл€етс€ ли ситуаци€ в рассматриваемом узле дерева целевой
		// OptionTree* tree - указатель на рассматриваемый узел дерева вариантов
		virtual bool isTargetSituation(OptionTree* tree) = 0;
		
		// јбстрактный метод, провер€ющий, €вл€етс€ ли ситуаци€ в рассматриваемом узле дерева тупиковой
		// OptionTree* tree - указатель на рассматриваемый узел дерева вариантов
		virtual bool isDeadlock(OptionTree* tree, int maximalDepth) = 0;
	private:
		// ”казатель на корневой узел дерева вариантов
		OptionTree* tree;
		
		void createTreeChildren(OptionTree* tree, std::queue<OptionTree*>* children, std::ofstream& fout);
	};
}

#endif
