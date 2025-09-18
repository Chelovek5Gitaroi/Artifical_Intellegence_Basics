#ifndef INVALID_COMMAND_EXCEPTION
#define INVALID_COMMAND_EXCEPTION

#include <string>
#include <exception>

namespace exceptions
{
	class InvalidCommandException : public std::exception
	{
	public:
		static const std::string ERROR_MESSAGE_INVALID_COORDINATES;
		static const std::string ERROR_MESSAGE_INVALID_COORDINATES_SEPARATOR;
		
		InvalidCommandException(const std::string& errorMessage) : errorMessage(errorMessage){}
		
		const char* what() const noexcept override;
				
	private:
		std::string errorMessage;
	};
}

#endif
