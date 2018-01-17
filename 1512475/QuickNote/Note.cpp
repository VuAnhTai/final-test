#include "stdafx.h"
#include "Note.h"


Note::Note()
{
}


Note::~Note()
{
	delete _tag;
}

int Note::getId() 
{
	return _id;
}

void Note::setId(int id) 
{
	_id = id;
}

string Note::getContent() 
{
	return _content;
}

void Note::setContent(string content) 
{
	_content = content;
}

Tag* Note::getTag() 
{
	return _tag;
}

void Note::setTag(Tag*tag) 
{
	_tag = tag;
}
