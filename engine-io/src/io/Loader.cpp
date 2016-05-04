#include "Loader.h"

Loader::~Loader() {}

Json::Value Loader::LoadJson(string path) {
	Json::Value root;
	Json::Reader reader;
	ifstream fs(path);
	if (!fs) throw "Failed to read from path.";
	if (!reader.parse(fs, root)) throw "Failed to parse.";
	return root;
}