//split.hpp

#pragma once

#include <sstream> // Used for istringstream
#include <string> // Used for string
#include <vector>  // Used for vector

// A helper function to split a string by a delimiter
static std::vector<std::string> split(const std::string& s, char delim)
{
	std::vector<std::string> result;
	std::string token;
	std::istringstream iss(s);
	while (std::getline(iss, token, delim))
	{
		result.push_back(token);
	}
	return result;
}