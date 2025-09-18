#include "invalid_command_exception.h"

namespace exceptions
{
	const std::string InvalidCommandException::ERROR_MESSAGE_INVALID_COORDINATES = "Invalid coordinates!";
	const std::string InvalidCommandException::ERROR_MESSAGE_INVALID_COORDINATES_SEPARATOR = "Invalid coordinates separator!";
	
	const char* InvalidCommandException::what() const noexcept
	{
		return this->errorMessage.c_str();
	}
}
