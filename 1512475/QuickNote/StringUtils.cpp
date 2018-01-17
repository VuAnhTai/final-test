#include "stdafx.h"
#include "StringUtils.h"
#include <sstream>

//Phan tach chuoi thang vector bang delimited
vector<string> StringUtils::delimitedStringToVector(string str, char delimited)
{
	vector<string> strings;

	string each;
	for (string::const_iterator it = str.begin(); it != str.end(); it++)
	{
		if (*it == delimited)
		{
			if (!each.empty())
			{
				strings.push_back(each);
				each.clear();
			}

			continue;
		}

		each += *it;
	}

	if (!each.empty())
	{
		strings.push_back(each);
	}

	return strings;
}
//chuyen Wchar thanh string
string StringUtils::toString(WCHAR * wchar)
{
	wstring ws(wchar);
	string str(ws.begin(), ws.end());
	return str;
}

WCHAR * StringUtils::toWCHAR(string str)
{

	wstring wideStr = wstring(str.begin(), str.end());
	WCHAR* w = (WCHAR*)wideStr.c_str();
	
	int length = str.length() + 1;
	WCHAR* wchar = new WCHAR[length];
	wcscpy_s(wchar, length, w);
	return wchar;
}

StringUtils::StringUtils()
{
}


StringUtils::~StringUtils()
{
}
