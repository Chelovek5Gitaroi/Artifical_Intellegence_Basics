#include "file_reader.h"

namespace chess_solver
{
	const std::string FileReader::PLAYER_SEPARATOR = "...";
	
	const std::string FileReader::COLOR_BLACK = "black";
	const std::string FileReader::COLOR_WHITE = "white";
	
	FileReader::~FileReader()
	{
		clearFigureList(whiteFigures);
		clearFigureList(blackFigures);
	}
	
	void FileReader::readFigureFile(const std::string& fileName)
	{
		std::ifstream fin(fileName);
		
		if (fin.is_open())
		{
			clearFigureList(whiteFigures);
			clearFigureList(blackFigures);
			
			std::string* stBuf = nullptr;
			
			FigureColor playerColor = FigureColor::WHITE;
			
			while (!fin.eof())
			{
				stBuf = new std::string();
				
				std::getline(fin, *stBuf);
				
				if (*stBuf == COLOR_BLACK)
				{
					movingPlayerColor = FigureColor::BLACK;
					delete stBuf;
				}
				else if (*stBuf == COLOR_WHITE)
				{
					movingPlayerColor = FigureColor::WHITE;
					delete stBuf;
				}
				else if (*stBuf != PLAYER_SEPARATOR)
				{
					if (playerColor == FigureColor::WHITE)
					{
						this->whiteFigures.push_back(stBuf);
					}
					else
					{
						this->blackFigures.push_back(stBuf);
					}
				}
				else 
				{
					playerColor = FigureColor::BLACK;	
					delete stBuf;
				}
			}
			
			fin.close();
		}
	}
	
	void FileReader::clearFigureList(std::list<std::string*>& figureList)
	{
		for (std::string* str : figureList)
		{
			delete str;
		}
		
		figureList.clear();
	}
	
}
