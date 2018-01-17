#include "stdafx.h"
#include "Tag.h"

int Tag::getId() 
{
	return _id;
}

void Tag::setId(int id) 
{
	_id = id;
}

string Tag::getName() 
{
	return _name;
}

void Tag::setName(string name) 
{
	_name = name;
}

vector<Note*>* Tag::getNotes() 
{
	return _notes;
}

void Tag::setNotes(vector<Note*> *notes) 
{
	_notes = notes;
}

Tag::Tag()
{
}

Tag::Tag(string name) 
{
	_name = name;
}

Tag::~Tag()
{
	for (int i = 0; i < _notes->size(); i++) 
	{
		delete _notes->at(i);
	}
	_notes->clear();
}

