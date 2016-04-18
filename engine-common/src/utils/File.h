/******************************************************************************
Class:File
Author:Gavin Gregory
Description:Provides static functions related to file IO.
*//////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>
#include <fstream>
#include <iostream>

class File {
public:
	static bool ReadTextFile(const char* filePath, std::string& into);
private:
	File(); // no constructor for this class :)
};