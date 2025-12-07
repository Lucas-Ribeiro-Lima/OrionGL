#pragma once
#include <string>

namespace oriongl::utils
{
	std::string readFile(const char path[]);
	void writeFile(const char* path, auto content);
	void logger(const char* log);
};

