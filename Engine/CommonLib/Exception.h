#pragma once

#include <string>

struct Exception : std::exception {
	std::string Message;

	Exception(std::string message) :
		Message(message)
	{}
	virtual ~Exception() {}
	const char* what() { return "Generic Exception"; }
};