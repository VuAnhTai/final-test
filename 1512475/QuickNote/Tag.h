#pragma once

#include "Note.h"
#include <vector>
#include <string>
using namespace std;
class Note;
class Tag
{
public:
	int getId();
	void setId(int id);

	string getName();
	void setName(string name);

	vector<Note*>* getNotes();
	void setNotes(vector<Note*> *notes);

	Tag();
	Tag(string name);
	~Tag();

private:
	int _id;
	string _name;
	vector<Note*> *_notes;
};



