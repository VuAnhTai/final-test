#include "stdafx.h"
#include "NoteRepository.h"

NoteRepository*	NoteRepository::_instance;

void NoteRepository::save(Note* note) 
{
	int noteId = _NoteService->save(note);

	Tag *tag = note->getTag();
	Tag* retrievedTag = _TagService->saveOrGetIfExist( tag );
	_noteTagService->save(noteId, retrievedTag->getId());
}

vector<Note*>* NoteRepository::findAll()
{
	return _NoteService->findAll();
}

vector<Note*>* NoteRepository::findByTagName(string tagName)
{
	Tag* tag = _TagService->findByName(tagName);
	vector<int>* noteIDs = _noteTagService->findNoteIDsByTagId(tag->getId());
	vector<Note*>* notes = new vector<Note*>();
	for (int i = 0; i < noteIDs->size(); i++) 
	{
		notes->push_back( _NoteService->findById(noteIDs->at(i)) );
	}
	return notes;
}

NoteRepository* NoteRepository::getInstance() 
{
	if (!_instance) 
	{
		_instance = new NoteRepository();
	}

	return _instance;
}

NoteRepository::NoteRepository()
{
	_NoteService = NoteService::getInstance();
	_TagService = TagService::getInstance();
	_noteTagService = NoteTagService::getInstance();
}


NoteRepository::~NoteRepository()
{
}
