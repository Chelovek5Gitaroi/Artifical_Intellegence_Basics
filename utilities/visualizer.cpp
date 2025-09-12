#include "visualizer.h"


namespace chess_solver
{
	Visualizer::Visualizer(Board* board, Player* firstPlayer, Player* secondPlayer)
	{
		this->board = board;
		this->firstPlayer = firstPlayer;
		this->secondPlayer = secondPlayer;
		
		this->bufferSize.X = this->board->getBoardSize();
		this->bufferSize.Y = this->board->getBoardSize();
				
		this->buffer = new CHAR_INFO[this->bufferSize.X * this->bufferSize.Y];
		this->clearBoardBuffer = new CHAR_INFO[this->bufferSize.X * this->bufferSize.Y];
		
		this->topLeftBufferPoint.X = 0;
		this->topLeftBufferPoint.Y = 0;
		
		this->consoleScreenArea.Left = Visualizer::LEFT_BOARD_IDENT;
		this->consoleScreenArea.Top = Visualizer::TOP_BOARD_IDENT;
		this->consoleScreenArea.Bottom = this->consoleScreenArea.Top + this->bufferSize.Y - 1;
		this->consoleScreenArea.Right = this->consoleScreenArea.Right + this->bufferSize.X - 1;	
		
			
	}
	
	Visualizer::~Visualizer()
	{
		delete[] this->buffer;
		delete[] this->clearBoardBuffer;
	}
	
	void Visualizer::writeMove(std::string& moveDescription)
	{
		
	}
	
	void Visualizer::prepareClearBoardBuffer()
	{
		for (short row = 0; row < this->bufferSize.Y; row++)
		{
			for (short column = 0; column < this->bufferSize.X; column++)
			{
				this->clearBoardBuffer[getBufferCellIndexFromCoordinates(row, column)];
				
							
			}
		}
	}
	
	short Visualizer::getBufferCellIndexFromCoordinates(short row, short column)
	{
		return row * this->bufferSize.X + column;
	}
}
