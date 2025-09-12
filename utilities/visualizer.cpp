#include "visualizer.h"


namespace chess_solver
{
	const std::string Visualizer::DEFAULT_FILE = "CONOUT$";
	
	void Visualizer::render()
	{
		
	}
	
	Visualizer::Visualizer(Board* board, Player* firstPlayer, Player* secondPlayer)
	{
		this->board = board;
		this->firstPlayer = firstPlayer;
		this->secondPlayer = secondPlayer;
		
		this->bufferSize.X = this->board->getBoardSize();
		this->bufferSize.Y = this->board->getBoardSize();
				
		this->buffer = new CHAR_INFO[this->bufferSize.X * this->bufferSize.Y];
		this->emptyBoardBuffer = new CHAR_INFO[this->bufferSize.X * this->bufferSize.Y];
		
		this->consoleFile = CreateFileA(Visualizer::DEFAULT_FILE.c_str(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr);
		
		this->topLeftBufferPoint.X = 0;
		this->topLeftBufferPoint.Y = 0;
		
		this->consoleScreenArea.Left = Visualizer::LEFT_BOARD_IDENT;
		this->consoleScreenArea.Top = Visualizer::TOP_BOARD_IDENT;
		this->consoleScreenArea.Bottom = this->consoleScreenArea.Top + this->bufferSize.Y - 1;
		this->consoleScreenArea.Right = this->consoleScreenArea.Right + this->bufferSize.X - 1;	
		
		prepareClearBoardBuffer();
		
	}
	
	Visualizer::~Visualizer()
	{
		delete[] this->buffer;
		delete[] this->emptyBoardBuffer;
	}
	
//	void Visualizer::writeMove(std::string& moveDescription)
//	{
//		
//	}
	
	void Visualizer::prepareClearBoardBuffer()
	{
		for (short row = 0; row < this->bufferSize.Y; row++)
		{
			for (short column = 0; column < this->bufferSize.X; column++)
			{
				this->emptyBoardBuffer[getBufferCellIndexFromCoordinates(row, column)].Char.AsciiChar = TILE_CHAR;

				Tile* tile = &this->board->getTileByCoordinates(makeChessCoordinatesFromIndexes(row, column));
				
				if (tile->getColor() == TileColor::WHITE)
				{
					this->emptyBoardBuffer[getBufferCellIndexFromCoordinates(row, column)].Attributes |= Visualizer::TILE_COLOR_WHITE;
				}
				else
				{
					this->emptyBoardBuffer[getBufferCellIndexFromCoordinates(row, column)].Attributes &= ~Visualizer::TILE_COLOR_WHITE;
				}
			}
		}
	}
	
	void Visualizer::copyBoardBufferToOutBuffer()
	{
		for (char row = 0; row < this->board->getBoardSize(); row++)
		{
			for (char column = 0; column < this->board->getBoardSize(); column++)
			{
				this->buffer[getBufferCellIndexFromCoordinates(row, column)].Char.AsciiChar = this->emptyBoardBuffer[getBufferCellIndexFromCoordinates(row, column)].Char.AsciiChar;
				this->buffer[getBufferCellIndexFromCoordinates(row, column)].Attributes = this->emptyBoardBuffer[getBufferCellIndexFromCoordinates(row, column)].Attributes;
			}
		}
	}
	
	Coordinates Visualizer::makeChessCoordinatesFromIndexes(short rowIndex, short columnIndex)
	{
		char row = this->board->getBoardSize() - static_cast<char>(rowIndex);
		char column = static_cast<char>(columnIndex) + Board::MINIMAL_COLUMN_NAME;
		
		return Coordinates(column, row);
	}
	
	short Visualizer::getBufferCellIndexFromCoordinates(short rowIndex, short columnIndex)
	{
		return rowIndex * this->bufferSize.X + columnIndex;
	}
}
