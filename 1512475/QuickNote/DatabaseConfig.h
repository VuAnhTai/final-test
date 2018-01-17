#pragma once
#include <string>
using namespace std;

class DatabaseConfig
{
public:
	static const string FILE_NAME_NOTE;
	static const string FILE_NAME_TAG;
	static const string FILE_NAME_NOTETAG;


	DatabaseConfig();
	~DatabaseConfig();
};

