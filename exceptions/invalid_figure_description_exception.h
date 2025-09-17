#ifndef INVALID_FIGURE_DESCRIPTION_EXCEPTION
#define INVALID_FIGURE_DESCRIPTION_EXCEPTION

#include <exception>
#include <string>
//#include "exception.h"

namespace exceptions
{
	class InvalidFigureDescriptionException : public std::exception
	{
	public:
		static const std::string ERROR_MESSAGE_INVALID_FIGURE_TYPE;
		static const std::string ERROR_MESSAGE_INVALID_COLUMN_NAME;
		static const std::string ERROR_MESSAGE_INVALID_ROW_NUMBER;
		static const std::string ERROR_MESSAGE_INVALID_FIGURE_DESCRIPTION_SINTACSIS;
		
		const char* what() const noexcept override;
		
		InvalidFigureDescriptionException(const std::string& errorMessage);
	private:
		std::string errorMessage;
	};
}

#endif
