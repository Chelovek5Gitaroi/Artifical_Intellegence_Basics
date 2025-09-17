#include "visualizer.h"


namespace chess_solver
{
	const std::string Visualizer::DEFAULT_FILE = "CONOUT$";
	
	void Visualizer::render()
	{
		copyBoardBufferToOutBuffer();
		
//		if (firstPlayer)
//		{
//			renderPlayerFigures(firstPlayer);
//		}
//		
//		if (secondPlayer)
//		{
//			renderPlayerFigures(secondPlayer);
//		}
		
		drawColumnMarks();
		drawRowMarks();
		
		drawBoardFrame();
		
		WriteConsoleOutput(this->consoleFile, this->buffer, this->bufferSize, this->topLeftBufferPoint, &this->consoleScreenArea);
	}
	
	void Visualizer::renderPlayerFigures(Player* player)
	{
		for (Figure* figure: player->getAllFigures())
		{
			short bufferCellIndex = getBufferCellIndexFromChessCoordinates(figure->getCoordinates());
			
			this->buffer[bufferCellIndex].Char.AsciiChar = getFigureChar(*figure);
			
			this->buffer[bufferCellIndex].Attributes &= ~FIGURE_COLOR_WHITE;
			this->buffer[bufferCellIndex].Attributes &= ~FIGURE_COLOR_BLACK;
			
			if (figure->getColor() == FigureColor::WHITE)
			{
				this->buffer[bufferCellIndex].Attributes |= FIGURE_COLOR_WHITE;
			}		
			else
			{
				this->buffer[bufferCellIndex].Attributes |= FIGURE_COLOR_BLACK;
			}
		}
	}
	
	Visualizer::Visualizer(Board* board, Player* firstPlayer, Player* secondPlayer)
	{
		this->board = board;
		this->firstPlayer = firstPlayer;
		this->secondPlayer = secondPlayer;
		
		this->bufferSize.X = this->board->getBoardSize() * TILE_WIDTH;
		this->bufferSize.Y = this->board->getBoardSize() * TILE_WIDTH;
				
		this->buffer = new CHAR_INFO[this->bufferSize.X * this->bufferSize.Y];
		this->emptyBoardBuffer = new CHAR_INFO[this->bufferSize.X * this->bufferSize.Y];
		
		this->consoleFile = CreateFileA(Visualizer::DEFAULT_FILE.c_str(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr);
		
		this->topLeftBufferPoint.X = 0;
		this->topLeftBufferPoint.Y = 0;
		
		this->consoleScreenArea.Left = Visualizer::LEFT_BOARD_IDENT;
		this->consoleScreenArea.Top = Visualizer::TOP_BOARD_IDENT;
		this->consoleScreenArea.Bottom = Visualizer::TOP_BOARD_IDENT + this->bufferSize.Y - 1;
		this->consoleScreenArea.Right = Visualizer::LEFT_BOARD_IDENT + this->bufferSize.X - 1;	
		
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
	
	char Visualizer::getFigureChar(Figure& figure)
	{
		char figureChar = Visualizer::TILE_CHAR;
			
		switch (figure.getType())
		{
		case FigureType::PAWN:
			figureChar = FigureCreator::FIGURE_CHAR_PAWN;
			break;
			
		case FigureType::KNIGHT:
			figureChar = FigureCreator::FIGURE_CHAR_KNIGHT;
			break;
				
		case FigureType::BISHOP:
			figureChar = FigureCreator::FIGURE_CHAR_BISHOP;
			break;
				
		case FigureType::ROCK:
			figureChar = FigureCreator::FIGURE_CHAR_ROCK;
			break;
				
		case FigureType::QUEEN:
			figureChar = FigureCreator::FIGURE_CHAR_QUEEN;
			break;
				
		case FigureType::KING:
			figureChar = FigureCreator::FIGURE_CHAR_KING;
			break;
		}
			
		return figureChar;
	}
	
	void Visualizer::prepareClearBoardBuffer()
	{
		for (short row = 0; row < this->board->getBoardSize(); row++)
		{
			for (short column = 0; column < this->board->getBoardSize(); column++)
			{
				short cellIndex = getBufferCellIndexFromCoordinates(row, column);
				
				TileColor tileColor = this->board->getTileByCoordinates(makeChessCoordinatesFromIndexes(row, column)).getColor();

				for (char rowShift = 0; rowShift < TILE_WIDTH; rowShift++)
				{
					for (char columnShift = 0; columnShift < TILE_WIDTH; columnShift++)
					{
						short cellShiftIndex = getBufferCellIndexFromCoordinates(cellIndex, rowShift, columnShift);
						
						this->emptyBoardBuffer[cellShiftIndex].Char.AsciiChar = TILE_CHAR;
						
						if (tileColor == TileColor::WHITE)
						{
							this->emptyBoardBuffer[cellShiftIndex].Attributes |= Visualizer::TILE_COLOR_WHITE;
						}
						else
						{
							this->emptyBoardBuffer[cellShiftIndex].Attributes &= ~Visualizer::TILE_COLOR_WHITE;
						}
					}
				}
			}
		}
		
		
//		for (short row = 0; row < this->bufferSize.Y; row++)
//		{
//			for (short column = 0; column < this->bufferSize.X; column++)
//			{
//				this->emptyBoardBuffer[getBufferCellIndexFromCoordinates(row, column)].Char.AsciiChar = TILE_CHAR;
//
//				Tile& tile = this->board->getTileByCoordinates(makeChessCoordinatesFromIndexes(row, column));
//				
//				if (tile.getColor() == TileColor::WHITE)
//				{
//					this->emptyBoardBuffer[getBufferCellIndexFromCoordinates(row, column)].Attributes |= Visualizer::TILE_COLOR_WHITE;
//				}
//				else
//				{
//					this->emptyBoardBuffer[getBufferCellIndexFromCoordinates(row, column)].Attributes &= ~Visualizer::TILE_COLOR_WHITE;
//				}
//			}
//		}
	}
	
	void Visualizer::copyBoardBufferToOutBuffer()
	{
		for (char row = 0; row < this->bufferSize.Y; row++)
		{
			for (char column = 0; column < this->bufferSize.X; column++)
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
	
	short Visualizer::getBufferCellIndexFromChessCoordinates(const Coordinates& coordinates)
	{
		short rowIndex = static_cast<short>(this->board->getBoardSize() - coordinates.getRow());
		short columnIndex = static_cast<short>(coordinates.getColumn() - Board::MINIMAL_COLUMN_NAME);
		
		return getBufferCellIndexFromCoordinates(rowIndex, columnIndex);
	}
	
	short Visualizer::getBufferCellIndexFromCoordinates(short rowIndex, short columnIndex)
	{
		return rowIndex * this->bufferSize.X + columnIndex;
	}
	
	short Visualizer::getBufferCellIndexFromCoordinates(short bufferCellIndex, short rowShift, short columnShift)
	{
		return bufferCellIndex + rowShift * this->bufferSize.X + columnShift;
	}
	
	void Visualizer::drawBoardFrame()
	{
		short column = static_cast<short>(this->consoleScreenArea.Left - 1);
		short row = static_cast<short>(this->consoleScreenArea.Top - 1);
		
		COORD cursorPosition{ column, row };
		
		SetConsoleCursorPosition(this->consoleFile, cursorPosition);
		
		std::cout << BOARD_FRAME_ANGLE_CHAR;
		
		for (char i = 0; i < this->board->getBoardSize(); i++)
		{
			std::cout << BOARD_FRAME_HORIZONTAL;
		}
		
		std::cout << BOARD_FRAME_ANGLE_CHAR;
		
		for (char i = 1; i <= this->board->getBoardSize(); i++)
		{
			cursorPosition.X = column;
			cursorPosition.Y = row + i;
			
			SetConsoleCursorPosition(this->consoleFile, cursorPosition);
			
			std::cout << BOARD_FRAME_VERTICAL;
			
			cursorPosition.X = column + this->board->getBoardSize() + 1;
			SetConsoleCursorPosition(this->consoleFile, cursorPosition);
			
			std::cout << BOARD_FRAME_VERTICAL;
		}
		
		cursorPosition.X = column;
		cursorPosition.Y += 1;
		
		SetConsoleCursorPosition(this->consoleFile, cursorPosition);
		
		std::cout << BOARD_FRAME_ANGLE_CHAR;
		
		for (char i = 0; i < this->board->getBoardSize(); i++)
		{
			std::cout << BOARD_FRAME_HORIZONTAL;
		}
		
		std::cout << BOARD_FRAME_ANGLE_CHAR << '\n';
	}
	
	void Visualizer::drawColumnMarks()
	{
		short column = static_cast<short>(this->consoleScreenArea.Left);
		short row = static_cast<short>(this->consoleScreenArea.Top - 2);
		
		SetConsoleCursorPosition(consoleFile, { column, row });
		
		std::string marksStr = "";
		
		marksStr.insert(marksStr.begin(), this->board->getBoardSize() * TILE_WIDTH, TILE_CHAR);
		
		for (char i = 0; i < this->board->getBoardSize(); i++)
		{
			marksStr[i * TILE_WIDTH + TILE_WIDTH / 2] = Board::MINIMAL_COLUMN_NAME + i;
		}
		
		std::cout << marksStr;
	}
	
	void Visualizer::drawRowMarks()
	{
		short column = static_cast<short>(this->consoleScreenArea.Left - 2);
		short row = static_cast<short>(this->consoleScreenArea.Top);
		
		COORD cursorPosition{ column, row };
		
		for (short i = this->board->getBoardSize(); i >= 1; i--)
		{
			SetConsoleCursorPosition(consoleFile, cursorPosition);
			std::cout << i;
			
			cursorPosition.Y += 1;
		}
		
	}
	
}
