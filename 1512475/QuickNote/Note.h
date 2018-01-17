#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Tag.h"
using namespace std;
class Tag;
class Note
{
public:
	int getId();
	void setId(int id);

	string getContent();
	void setContent(string content);

	Tag* getTag();
	void setTag(Tag *tags);

	Note();
	~Note();
private:
	int _id;
	string _content;
	Tag* _tag;
};

