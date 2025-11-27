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
	//  ласс, описывающий интеллектуальный решатель, наход€щий мат не более чем за два хода
	//
	class Solver : public AbstractSolver
	{
	protected:
		// ѕереопределение порождающей процедуры
		AbstractSituation* getNextSituation(AbstractSituation* abstractSituation, AbstractCommand* command) override;
	
		// ѕереопределение метода, создающего дочерний узел дерева
		OptionTree* createChild(OptionTree* tree) override;
	
		// ѕереопределение функции, провер€ющей, €вл€етс€ ли рассматриваема€ ситуаци€ целевой
		bool isTargetSituation(OptionTree* tree) override;
	
		// ѕереопределение функции, провер€ющей, €вл€етс€ ли рассматриваема€ ситуаци€ тупиковой
		bool isDeadlock(OptionTree* tree, int maximalDepth) override;
	
		// ѕереопределение метода, реализующего поиск в глубину
		OptionTree* deepSearch(OptionTree* tree, short maximalDepth) override;
		
		// ѕереопределение метода, создающего список ходов, возможных в данной ситуации
		std::list<AbstractCommand*>* getAllSituationMoves(AbstractSituation* abstractSituation) override;
	
		// ѕереопределение оценочной функции
		float evaluationFunction(OptionTree* tree) override;
	
	private:
		// ќбъект класса, выполн€ющего команды
		ChessCommandExecutor executor;
		
		// ћетод, возвращающий список возможных ходов дл€ заданной фигуры
		// Board& board - объект, описывающий шахматную доску
		// Figure* figure - указатель на рассматриваемую фигуру
		// const Coordinates& kingCoordinates - координаты корол€ игрока
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
