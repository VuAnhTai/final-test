#pragma once
#include <string>
#include <vector>
using namespace std;

class StringUtils
{
public:
	static vector<string> delimitedStringToVector(string str, char delimited);
	static string toString(WCHAR* wchar);
	static WCHAR* toWCHAR(string str);

	StringUtils();
	~StringUtils();
};

