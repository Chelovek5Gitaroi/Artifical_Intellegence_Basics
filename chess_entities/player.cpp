#include "player.h"


namespace chess_solver
{
	Player::~Player()
	{
		for (Figure* figure: this->figures)
		{
			delete figure;
		}
		
		figures.clear();
	}
	
	bool Player::hasFigure(Figure& figure)
	{
		for (Figure* elFigure: this->figures)
		{
			if (*elFigure == figure)
			{
				return true;
			}	
		}
		
		return false;
	}
	
	void Player::addFigure(Figure* figure)
	{
		this->figures.push_back(figure);
	}
		
	Figure* Player::getFigureByCoordinates(Coordinates& coordinates) //const
	{
		Figure* result = nullptr;
		
		for (auto iter = this->figures.begin(); iter != this->figures.end() && !result; iter++)
		{
			if ((*iter)->getCoordinates() == coordinates)
			{
				result = *iter;
			}
		}
		
		return result;
	}
	
	Figure* Player::getKing()
	{
		for (Figure* elFigure: this->figures)
		{
			if (elFigure->getType() == FigureType::KING)
			{
				return elFigure;
			}
		}
		
		return nullptr;
	}
	
	void Player::removeFigureByCoordinates(Coordinates& coordinates)
	{
		this->figures.remove(getFigureByCoordinates(coordinates));
	}
}
