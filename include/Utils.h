#pragma once
#include <string>

namespace oriongl::utils
{
	std::string readFile(std::string path);
	void writeFile(std::string path, auto content);
	void logger(std::string log);
};

