#include "invalid_figure_description_exception.h"


namespace exceptions
{
	const std::string InvalidFigureDescriptionException::ERROR_MESSAGE_INVALID_FIGURE_TYPE = "Invalid figure type!";
	const std::string InvalidFigureDescriptionException::ERROR_MESSAGE_INVALID_COLUMN_NAME = "Invalid column name!";
	const std::string InvalidFigureDescriptionException::ERROR_MESSAGE_INVALID_ROW_NUMBER = "Invalid row number!";
	const std::string InvalidFigureDescriptionException::ERROR_MESSAGE_INVALID_FIGURE_DESCRIPTION_SINTACSIS = "Invalid figure description sintacsis!";
		
	
	InvalidFigureDescriptionException::InvalidFigureDescriptionException(const std::string& errorMessage) : errorMessage(errorMessage)//: Exception(errorMessage)
	{
	}

	const char* InvalidFigureDescriptionException::what() const noexcept
	{
		return this->errorMessage.c_str();
	}
	
}
