#pragma once
#include <string>

namespace engine {
	namespace utils {

		class File {
		public:
			static std::string ReadTextFile(const char* filePath);
		private:
			File(); // no constructor for this class :)
		};

	}
}