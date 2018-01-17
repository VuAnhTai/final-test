#pragma once
#include "Note.h"
#include <vector>

class NoteService
{
public:
	int save(Note* note);
	vector<Note*>* findAll();
	Note* findById(int id);

	static NoteService* getInstance();

	NoteService();
	~NoteService();
private:

	static NoteService* _instance;
};

