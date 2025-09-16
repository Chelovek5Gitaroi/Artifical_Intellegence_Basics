#include "file_reader.h"

namespace chess_solver
{
	const std::string FileReader::PLAYER_SEPARATOR = "...";
	
	const std::string FileReader::COLOR_BLACK = "black";
	const std::string FileReader::COLOR_WHITE = "white";
	
	FileReader::~FileReader()
	{
		for (std::string* str: this->blackFigures)
		{
			delete str;
		}
		
		this->blackFigures.clear();
		
		for (std::string* str: this->whiteFigures)
		{
			delete str;
		}
		
		this->whiteFigures.clear();
	}
	
	void FileReader::readFigureFile(std::string& fileName)
	{
		std::ifstream fin(fileName);
		
		if (fin.is_open())
		{
			std::string* stBuf = nullptr;
			
			FigureColor playerColor = FigureColor::WHITE;
			
			while (!fin.eof())
			{
				stBuf = new std::string();
				
				std::getline(fin, *stBuf);
				
				if (*stBuf == COLOR_BLACK)
				{
					playerColor = FigureColor::BLACK;
				}
				else if (*stBuf == COLOR_WHITE)
				{
					playerColor = FigureColor::WHITE;
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
			}
			
			fin.close();
		}
	}
	
	
}
