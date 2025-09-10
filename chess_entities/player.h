#ifndef PLAYER
#define PLAYER

#include "figure.h"

#include <list>

namespace chess_solver
{
	class Player
	{
	public:
		~Player();
		
		void addFigure(Figure* figure);
		
		std::list<Figure*>& getAllFigures() { return figures; }
		
		Figure* getKing();
		Figure* getFigureByCoordinates(const Coordinates& coordinates);//const;
		void removeFigureByCoordinates(const Coordinates& coordinates);
				
		bool hasFigure(Figure& figure);
		
	private:	
		std::list<Figure*> figures;
	
	};
}

#endif
