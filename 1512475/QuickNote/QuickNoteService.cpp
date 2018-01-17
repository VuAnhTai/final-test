#include "stdafx.h"
#include "QuickNoteService.h"
#include "StringUtils.h"
#include "NoteRepository.h"
#include "TagRepository.h"

QuickNoteService* QuickNoteService::_instance;
QuickNoteService* QuickNoteService::getInstance()
{
	if (!_instance) 
	{
		_instance = new QuickNoteService();
	}

	return _instance;
}

vector<Note*>* QuickNoteService::findAll()
{
	return _noteRepository->findAll();
}

vector<Note*>* QuickNoteService::findByTagName(string tagName)
{
	if (tagName == "") 
	{
		return findAll();
	}
	return _noteRepository->findByTagName(tagName);
}

void QuickNoteService::createNote(string content, string tagName)
{
	Note* note = new Note();
	note->setContent(content);

	Tag *tag = new Tag(tagName);
	
	note->setTag(tag);

	_noteRepository->save(note);

	// notify all registered observables
	if (_observables != NULL) {
		for (int i = 0; i < _observables->size(); i++) 
		{
			_observables->at(i)->notify();
		}
	}

	// update cached
	_cachedSumNotes = _noteTagService->count();
}

void QuickNoteService::registerObservable(Observable * o)
{
	_observables->push_back(o);
}

int QuickNoteService::getSumOfNotesForEachTag()
{
	return _cachedSumNotes;
}

QuickNoteService::QuickNoteService()
{
	_noteRepository = NoteRepository::getInstance();
	_observables = new vector<Observable*>();
	_noteTagService = NoteTagService::getInstance();
	_cachedSumNotes = _noteTagService->count();
}


QuickNoteService::~QuickNoteService()
{
	for (int i = 0; i < _observables->size(); i++) {
		delete _observables->at(i);
	}
	_observables->clear();
}
