#ifndef ABSTRACT_SOLVER
#define ABSTRACT_SOLVER

#include "option_tree.h"

#include <fstream>
#include <list>
#include <vector>
#include <chrono>
#include <algorithm>

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
		
		// Метод, применяющий поиск по градиенту к инициализированному дереву
		// short maximalDepth - максимальная глубина поиска
		// Возвращается узел с целевой ситуацией, если такой узел существует, иначе возвращается nullptr
		virtual OptionTree* useGradientSearch(short maximalDepth);
		
		virtual OptionTree* useBestParticalWaySearch(short maximalDepth, int newLevelsCount);
		
		// Метод, выполняющий инициализацию дерева вариантов
		// AbstractSituation* startSituation - начальная ситуация
		virtual void initTree(AbstractSituation* startSituation);
	
		// Метод, возвращающий указатель на корень дерева вариантов
		OptionTree* getTree() const { return tree; }
	
		// Метод, выполняющий очистку дерева
		void clearTree();
		
		virtual void evaluateAllMethods(AbstractSituation* startSituation, int maximalDepth);
	protected:
		const static std::string EVALUATION_FILE_NAME;
		
		static const std::string EVALUATION_WORKING_TIME;
		
		static const std::string EVALUATION_ROW_MAX_SEARCH_DEPTH;
		static const std::string EVALUATION_SOLVE_LENGTH;
		static const std::string EVALUATION_TOTAL_NODES_COUNT;
		static const std::string EVALUATION_BRANCHING;
		static const std::string EVALUATION_TIME;
		
		static const std::string METHOD_DEEP_SEARCH;
		static const std::string METHOD_WIDE_SEARCH;
		static const std::string METHOD_GRADIENT_SEARCH;
		static const std::string METHOD_BEST_PARTICLE_WAY;
		
		static const int ROW_NAME_LENGTH = 40;
		static const int CELL_WIDTH = 10;
		
		// Метод, реализующий поиск в глубину
		// OptionTree* tree - рассматриваемый узел дерева
		// short maximalDepth - максимально допустимая глубина поиска
		virtual OptionTree* deepSearch(OptionTree* tree, short maximalDepth);

		// Метод, создающий все узлы дерева, находящиеся на следующем уровне
		// std::queue<OptionTree*>* treeLevel - указатель на очередь, содержащую узлы дерева, находящиеся на одном уровне
		std::list<OptionTree*>* generateNextTreeLevel(std::list<OptionTree*>* treeLevel, short maximalDepth);

		// Метод, реализующий поиск в ширину
		// std::list<OptionTree*>* treeLevel - указатель на очередь, содержащую узлы дерева, находящиеся на рассматриваемом уровне
		// short maximalDepth - максимальная глубина поиска
		virtual OptionTree* wideSearch(std::list<OptionTree*>* treeLevel, short maximalDepth);
		
		// Метод, реализующий поиск по градиенту
		// OptionTree* - узел дерева с рассматриваемой ситуацией
		// short maximalDepth - максимальная глубина поиска
		virtual OptionTree* gradientSearch(OptionTree* tree, short maximalDepth);
				
		
		virtual OptionTree* bestParticleWaySearch(OptionTree* tree, int maximalDepth, int newLevelsCount);
		
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
		
		// Абстрактная оценочная функция
		// OptionTree* - узел дерева с рассматриваемой ситуацией
		virtual float evaluationFunction(OptionTree* tree) = 0;
		
		// Функция, сортирующая узлы дерева по возрастанию оценочной функции
		// std::list<OptionTree*>* nodes - список сортируемых узлов
		void sortNodesByTargetFunction(std::list<OptionTree*>* nodes);
	private:
		// Указатель на корневой узел дерева вариантов
		OptionTree* tree;
		
		// Метод, создающий дочерние узлы для заданного, и помещающий их в заданную очередь
		// OptionTree* tree - указатель на узел, потомков которого необходимо создать
		// std::queue<OptionTree*>* children - указатель на очередь, в которую нужно помещать создаваемые узлы
		void createTreeChildren(OptionTree* tree, std::list<OptionTree*>* children);
		
		short calcMaximalOptionTreeDepth(OptionTree* node, short currentMax);
		
		size_t calcOptionTreeSize(OptionTree* node);
		
		int getHours(int totalSeconds);
		
		int getMinutes(int totalSeconds);
		
		int getRemainingSeconds(int totalSeconds);
		
		std::string buildTableRow(std::string& rowName, int rowNameLength, int cellWidth, int l, int d, int n, int r, int seconds);
		
		std::string makeCellText(int cellWidth, int value);
		std::string makeCellText(int cellWidth, std::string value);
		
		std::string makeTableSepRow(int rowNameLen, int cellsCount, int cellWidth);
	};
}

#endif
