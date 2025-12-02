#include "Utils.h"
#include <fstream>
#include <sstream>
#include <format>
#include <ctime>

namespace Utils {
	std::string readFile(const char shaderName[]) {
		try {
			std::ifstream file(shaderName);

			file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

			std::stringstream buffer;

			buffer << file.rdbuf();

			return buffer.str();
		}
		catch(const std::ifstream::failure& e) {

			throw std::runtime_error(e.what());

		}
	}

	void writeFile(const char* path, auto content) {
		try {
			std::ofstream file(path);

			file.exceptions(file.failbit | file.badbit);

			file << content << std::endl;

			file.close();
		}
		catch(const std::ofstream::failure& e) {

			throw std::runtime_error(e.what());

		}
	}

	void logger(const char* log) {
		time_t timestamp = time(NULL);
		tm datetime{};

		#ifdef _WIN32
				localtime_s(&datetime, &timestamp);
		#else
				localtime_r(&timestamp, &datetime);
		#endif

		char* ascDateTime = std::asctime(&datetime);

		std::string formattedStr = std::format("Date: {} - {}", ascDateTime, log);

		writeFile("log.txt", formattedStr);
	}
}