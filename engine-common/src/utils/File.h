#pragma once
#include <string>
#include <fstream>
#include <iostream>

namespace engine {
	namespace utils {

		class File {
		public:
			static bool ReadTextFile(const char* filePath, std::string& into);
		private:
			File(); // no constructor for this class :)
		};

	}
}