#include "visualizer.h"


namespace chess_solver
{
	const std::string Visualizer::DEFAULT_FILE = "CONOUT$";
	
	const std::string Visualizer::SELECTED_ITEM_MARKER = " <-";
	
	void Visualizer::showSituation(AbstractSituation* abstractSituation)
	{
		Situation* situation = reinterpret_cast<Situation*>(abstractSituation);
		
		copyBoardBufferToOutBuffer();
		
		renderFigures(situation->getWhiteFigures());
		renderFigures(situation->getBlackFigures());
		
		drawColumnMarks();
		drawRowMarks();
		
		drawBoardFrame();
		
		WriteConsoleOutput(this->consoleFile, this->buffer, this->bufferSize, this->topLeftBufferPoint, &this->consoleScreenArea);
	}
	
	void Visualizer::renderFigures(std::list<Figure*>& figures)
	{
		for (Figure* figure: figures)
		{
			short bufferCellIndex = getBufferCellIndexFromChessCoordinates(figure->getCoordinates());
			
			short bufferCellIndexShifted = getBufferCellIndexFromCoordinates(bufferCellIndex, TILE_WIDTH / 2, TILE_WIDTH / 2);
			
			this->buffer[bufferCellIndexShifted].Char.AsciiChar = getFigureChar(*figure);
			
			this->buffer[bufferCellIndexShifted].Attributes &= ~TILE_COLOR_WHITE;
			
			this->buffer[bufferCellIndexShifted].Attributes |= FIGURE_COLOR_BACKGROUND;
			
			if (figure->getColor() == FigureColor::WHITE)
			{
				this->buffer[bufferCellIndexShifted].Attributes |= FIGURE_COLOR_WHITE;
			}		
			else
			{
				this->buffer[bufferCellIndexShifted].Attributes &= ~FIGURE_COLOR_WHITE;
			}
		}
	}
	
	Visualizer::Visualizer(char boardSize)
	{
		this->boardSize = boardSize;
		
		this->bufferSize.X = this->boardSize * TILE_WIDTH;
		this->bufferSize.Y = this->boardSize * TILE_WIDTH;
		
		this->buffer = new CHAR_INFO[this->bufferSize.X * this->bufferSize.Y];
		this->emptyBoardBuffer = new CHAR_INFO[this->bufferSize.X * this->bufferSize.Y];
		
		this->consoleFile = GetStdHandle(STD_OUTPUT_HANDLE);
		
		this->topLeftBufferPoint.X = 0;
		this->topLeftBufferPoint.Y = 0;
		
		this->consoleScreenArea.Left = Visualizer::LEFT_BOARD_IDENT;
		this->consoleScreenArea.Top = Visualizer::TOP_BOARD_IDENT;
		this->consoleScreenArea.Bottom = Visualizer::TOP_BOARD_IDENT + this->bufferSize.Y - 1;
		this->consoleScreenArea.Right = Visualizer::LEFT_BOARD_IDENT + this->bufferSize.X - 1;
		
		this->commandTop.X = this->consoleScreenArea.Right + SIDE_COMMANDS_IDENT;
		this->commandTop.Y = TOP_COMMAND_IDENT;
		
		prepareClearBoardBuffer();
		
		this->menuTop.X = this->MENU_LEFT_IDENT;
		this->menuTop.Y = this->consoleScreenArea.Bottom + MENU_TOP_IDENT;
		
		this->currentCursorPosition.X = 0;
		this->currentCursorPosition.Y = 0;
		
		this->screenSize.X = 100;
		this->screenSize.Y = 35;
		
		this->windowPosition.Left = 10;
		this->windowPosition.Top = 10;
		this->windowPosition.Right = this->windowPosition.Left + screenSize.X - 1;
		this->windowPosition.Bottom = this->windowPosition.Top + screenSize.Y - 1;
		
		SetConsoleScreenBufferSize(this->consoleFile, screenSize);
		SetConsoleWindowInfo(this->consoleFile, TRUE, &windowPosition);
		
	}
	
	Visualizer::~Visualizer()
	{
		delete[] this->buffer;
		delete[] this->emptyBoardBuffer;
	}
	
	void Visualizer::showCommand(AbstractCommand* abstractCommand)
	{
		SetConsoleCursorPosition(this->consoleFile, this->commandCurrentCursorPosition);
		Command* command = reinterpret_cast<Command*>(abstractCommand);
		
		std::cout << getFigureChar(command->getFigureType()) << command->getStartCoordinates();
		
//		std::cout << getFigureChar(*command->getFigure()) << command->getFigure()->getCoordinates();
		
		CommandType type = command->getType();
		
		if (type == CommandType::BEAT || type == CommandType::BEAT_TRANSFORMATION)
		{
			std::cout << *ChessChars::COMMAND_POSITION_BEAT_SEPARATORS.begin();
		}
		else
		{
			std::cout << *ChessChars::COMMAND_POSITION_MOVE_SEPARATORS.begin();
		}
		
		std::cout << command->getFinishCoordinates();
		
		if (type == CommandType::TRANSFORMATION || type == CommandType::BEAT_TRANSFORMATION)
		{
			std::cout << ChessChars::COMMAND_TRANSFORMATION_CHAR << getFigureChar(reinterpret_cast<CommandTransformation*>(command)->getNewFigureType());
		}
		
		this->commandCurrentCursorPosition.Y++;
	}
	
	void Visualizer::showMenu(std::vector<std::pair<std::string, bool>>& menuStrings, COORD top)
	{
		this->currentCursorPosition.X = top.X;
		this->currentCursorPosition.Y = top.Y;
		
		for (auto iter = menuStrings.begin(); iter != menuStrings.end(); iter++)
		{
			SetConsoleCursorPosition(this->consoleFile, this->currentCursorPosition);
			
			std::cout << std::string(iter->first.size() + 4, ' ');
			
			SetConsoleCursorPosition(this->consoleFile, this->currentCursorPosition);
			
			std::cout << iter->first;
			
			if (iter->second)
			{
				std::cout << SELECTED_ITEM_MARKER;
			}
			
			this->currentCursorPosition.Y += 1;
		}
	}
	
	char Visualizer::getFigureChar(Figure& figure)
	{
		return getFigureChar(figure.getType());
	}
	
	char Visualizer::getFigureChar(FigureType figureType)
	{
		char figureChar = ChessChars::TILE_CHAR;
			
		switch (figureType)
		{
		case FigureType::PAWN:
			figureChar = ChessChars::FIGURE_CHAR_PAWN;
			break;
			
		case FigureType::KNIGHT:
			figureChar = ChessChars::FIGURE_CHAR_KNIGHT;
			break;
				
		case FigureType::BISHOP:
			figureChar = ChessChars::FIGURE_CHAR_BISHOP;
			break;
				
		case FigureType::ROCK:
			figureChar = ChessChars::FIGURE_CHAR_ROCK;
			break;
				
		case FigureType::QUEEN:
			figureChar = ChessChars::FIGURE_CHAR_QUEEN;
			break;
				
		case FigureType::KING:
			figureChar = ChessChars::FIGURE_CHAR_KING;
			break;
		}
			
		return figureChar;
	}
	
	void Visualizer::prepareClearBoardBuffer()
	{
		for (short row = 0; row < this->boardSize; row++)
		{
			for (short column = 0; column < this->boardSize; column++)
			{
				short cellIndex = getBufferCellIndexFromCoordinates(row, column);
				
				for (char rowShift = 0; rowShift < TILE_WIDTH; rowShift++)
				{
					for (char columnShift = 0; columnShift < TILE_WIDTH; columnShift++)
					{
						short cellShiftIndex = getBufferCellIndexFromCoordinates(cellIndex, rowShift, columnShift);
						
						this->emptyBoardBuffer[cellShiftIndex].Char.AsciiChar = ChessChars::TILE_CHAR;
						
						if ((row % 2 == 0 && column % 2 == 0) || (row % 2 != 0 && column % 2 != 0))						
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
	}
	
	void Visualizer::copyBoardBufferToOutBuffer()
	{
		for (char row = 0; row < this->boardSize; row++)
		{
			for (char column = 0; column < this->boardSize; column++)
			{
				short cellIndex = getBufferCellIndexFromCoordinates(row, column);
				
				for (short rowShift = 0; rowShift < TILE_WIDTH; rowShift++)
				{
					for (short columnShift = 0; columnShift < TILE_WIDTH; columnShift++)
					{
						short cellShiftIndex = getBufferCellIndexFromCoordinates(cellIndex, rowShift, columnShift);
						
						this->buffer[cellShiftIndex].Char.AsciiChar = this->emptyBoardBuffer[cellShiftIndex].Char.AsciiChar;
						this->buffer[cellShiftIndex].Attributes = this->emptyBoardBuffer[cellShiftIndex].Attributes;
					}
				}
			}
		}
	}
	
	short Visualizer::getBufferCellIndexFromChessCoordinates(const Coordinates& coordinates)
	{
		short rowIndex = static_cast<short>(CoordinatesConverter::getRowIndexFromCoordinate(coordinates.getRow(), this->boardSize));
		short columnIndex = static_cast<short>(CoordinatesConverter::getColumnIndexFromCoordinate(coordinates.getColumn()));

		return getBufferCellIndexFromCoordinates(rowIndex, columnIndex);
	}
	
	short Visualizer::getBufferCellIndexFromCoordinates(short rowIndex, short columnIndex)
	{
		return (rowIndex * this->bufferSize.X + columnIndex) * TILE_WIDTH;
	}
	
	short Visualizer::getBufferCellIndexFromCoordinates(short bufferCellIndex, short rowShift, short columnShift)
	{
		return bufferCellIndex + rowShift * this->bufferSize.X + columnShift;
	}
	
	void Visualizer::drawBoardFrame()
	{
		short cursorColumn = static_cast<short>(this->consoleScreenArea.Left - 1);
		short cursorRow = static_cast<short>(this->consoleScreenArea.Top - 1);
		
		COORD cursorPosition{ cursorColumn, cursorRow };
		
		std::string frameRow = "";
		
		frameRow += BOARD_FRAME_ANGLE_CHAR;
		frameRow.insert(frameRow.end(), this->boardSize * TILE_WIDTH, BOARD_FRAME_HORIZONTAL);
		frameRow += BOARD_FRAME_ANGLE_CHAR;
		
		SetConsoleCursorPosition(this->consoleFile, cursorPosition);
		
		std::cout << frameRow;
		
		for (char row = 0; row < this->boardSize; row++)
		{
			for (char rowShift = 0; rowShift < TILE_WIDTH; rowShift++)
			{
				cursorPosition.X = cursorColumn;
				cursorPosition.Y = cursorRow + row * TILE_WIDTH + rowShift + 1;
				
				SetConsoleCursorPosition(this->consoleFile, cursorPosition);
				
				std::cout << BOARD_FRAME_VERTICAL;
				
				cursorPosition.X += this->bufferSize.X + 1;
				
				SetConsoleCursorPosition(this->consoleFile, cursorPosition);
				
				std::cout << BOARD_FRAME_VERTICAL;
			}
		}
		
		cursorPosition.X = cursorColumn;
		cursorPosition.Y += 1;
		
		SetConsoleCursorPosition(this->consoleFile, cursorPosition);
		
		std::cout << frameRow;
	}
	
	void Visualizer::drawColumnMarks()
	{
		short column = static_cast<short>(this->consoleScreenArea.Left);
		short row = static_cast<short>(this->consoleScreenArea.Top - 2);
		
		SetConsoleCursorPosition(consoleFile, { column, row });
		
		std::string marksStr = "";
		
		marksStr.insert(marksStr.begin(), this->boardSize * TILE_WIDTH, ChessChars::TILE_CHAR);
		
		for (char i = 0; i < this->boardSize; i++)
		{
			marksStr[i * TILE_WIDTH + TILE_WIDTH / 2] = ChessChars::FIRST_ENGLISH_LETTER + i;
		}
		
		std::cout << marksStr;
	}
	
	void Visualizer::drawRowMarks()
	{
		short cursorColumn = static_cast<short>(this->consoleScreenArea.Left - 2);
		short cursorRow = static_cast<short>(this->consoleScreenArea.Top);
		
		COORD cursorPosition{ cursorColumn, cursorRow };
		
		for (short row = 0; row < this->boardSize; row++)
		{
			cursorPosition.Y = cursorRow + row * TILE_WIDTH + TILE_WIDTH / 2;
			
			SetConsoleCursorPosition(consoleFile, cursorPosition);
			std::cout << (this->boardSize - row);
		}
	}
	
}
