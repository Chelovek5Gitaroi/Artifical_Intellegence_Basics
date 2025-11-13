#ifndef SOLVER
#define SOLVER

//#include <iostream>

#include "../abstract_solver.h"
#include "../../utilities/chess_command_executor.h"
#include "situation.h"
#include "../../chess_engine/moving_preparator.h"
#include "../../chess_engine/moving_validator.h"

#include <exception>

namespace chess_solver
{
	//
	// Класс, описывающий интеллектуальный решатель, находящий мат не более чем за два хода
	//
	class Solver : public AbstractSolver
	{
	protected:
		// Переопределение порождающей процедуры
		AbstractSituation* getNextSituation(AbstractSituation* abstractSituation, AbstractCommand* command) override;
	
		// Переопределение метода, создающего дочерний узел дерева
		OptionTree* createChild(OptionTree* tree) override;
	
		// Переопределение функции, проверяющей, является ли рассматриваемая ситуация целевой
		bool isTargetSituation(OptionTree* tree) override;
	
		// Переопределение функции, проверяющей, является ли рассматриваемая ситуация тупиковой
		bool isDeadlock(OptionTree* tree, int maximalDepth) override;
	
		// Переопределение метода, реализующего поиск в глубину
		OptionTree* deepSearch(OptionTree* tree, short maximalDepth) override;
		
//		OptionTree* wideSearch(std::queue<OptionTree*>* treeLevel, short maximalDepth) override;
		
		// Переопределение метода, создающего список ходов, возможных в данной ситуации
		std::list<AbstractCommand*>* getAllSituationMoves(AbstractSituation* abstractSituation) override;
	
	private:
		ChessCommandExecutor executor;
		
		// Метод, возвращающий список возможных ходов для заданной фигуры
		// Board& board - объект, описывающий шахматную доску
		// Figure* figure - указатель на рассматриваемую фигуру
		// const Coordinates& kingCoordinates - координаты короля игрока
		// std::list<Figure*>* figures - список фигур игрока
		// std::list<Figure*>* otherFigures - список фигур соперника
		std::list<AbstractCommand*>* getFigurePotentialMoves(Board& board, Figure* figure, const Coordinates& kingCoordinates, std::list<Figure*>* figures, std::list<Figure*>* otherFigures);
		
		Figure* getKingFromList(std::list<Figure*>* figures);
		
		Command* createValidCommand(Figure* figure, Board& board, const Coordinates& finishCoordinates, CommandType type,
			const Coordinates& kingCoordinates, std::list<Figure*>* figures, std::list<Figure*>* otherFigures);
		
		bool createValidTransformationCommands(Figure* figure, Board& board, const Coordinates& finishCoordinates, CommandType type,
			const Coordinates& kingCoordinates, std::list<Figure*>* figures, std::list<Figure*>* otherFigures, std::list<AbstractCommand*>* commands);
		
		bool isTargetSituation(Situation* situation, std::list<AbstractCommand*>* potentialMoves);
		
		bool isDeadlock(Situation* situation, std::list<AbstractCommand*>* potentialMoves, short maximalDepth, short currentDepth);
		
		bool areAllSiblingsTarget(OptionTree* node);
	};
}

#endif
