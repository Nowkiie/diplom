#pragma once
#include <stdexcept>

class inv_input_error : public std::invalid_argument
{
public:
	explicit inv_input_error(std::string const& message)
		: std::invalid_argument(message)
	{}
	explicit inv_input_error(const char* message)
		: std::invalid_argument(message)
	{}
};