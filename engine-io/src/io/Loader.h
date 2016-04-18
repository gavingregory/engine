/******************************************************************************
Class:Loader
Author:Gavin Gregory
Description:Contains static methods related to JSON file input.
*//////////////////////////////////////////////////////////////////////////////

#pragma once

#include <json/json.h>
#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;

class Loader
{
private:
	Loader(); // private, don't instantiate
public:
	static Json::Value LoadJson(string path);
	virtual ~Loader();
};