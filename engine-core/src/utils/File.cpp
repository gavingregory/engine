#include "File.h"
#include <fstream>
#include <iostream>

namespace engine {
	namespace utils {

		std::string File::ReadTextFile(const char* filePath) {
			//TODO: throw error if file doesn't exist
			std::ifstream f(filePath);
			std::string line;
			std::string s;
			if (f.is_open())
				while (getline(f, line))
					s.append(line + '\n');
			f.close();
			return s;
		}
	}
}