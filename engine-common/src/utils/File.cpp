#include "File.h"

namespace engine {
	namespace utils {

		bool File::ReadTextFile(const char* filePath, std::string& into) {
			std::ifstream f(filePath);
			std::string line;
			std::string s;
			if (f.is_open()) {
				while (getline(f, line))
					s.append(line + '\n');
				f.close();
				return true;
			}
			else {
				f.close();
				return false;
			}
		}
	}
}