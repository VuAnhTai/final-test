#pragma once

#include "Note.h"
#include "NoteService.h"
#include "TagService.h"
#include "NoteTagService.h"

class NoteRepository
{
public:
	void save(Note* note);
	vector<Note*>* findAll();
	vector<Note*>* findByTagName(string tagName);

	static NoteRepository* getInstance();
	~NoteRepository();

private:
	NoteService* _NoteService;
	TagService* _TagService;
	NoteTagService* _noteTagService;
	

	static NoteRepository* _instance;
	NoteRepository();
};

