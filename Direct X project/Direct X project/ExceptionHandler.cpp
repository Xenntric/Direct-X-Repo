
#include "ExceptionHandler.h"
#include <sstream>

ExceptionHandler::ExceptionHandler(int line, const char* file) noexcept
	:
	line(line),
	file(file)
{}

const char* ExceptionHandler::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();

}

const char* ExceptionHandler::GetType() const noexcept
{
	return "Exception Handler";
}

int ExceptionHandler::Getline() const noexcept
{
	return line;
}

std::string ExceptionHandler::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[FILE] " << file << std::endl
		<< "[LINE] " << line;
	return oss.str();
}