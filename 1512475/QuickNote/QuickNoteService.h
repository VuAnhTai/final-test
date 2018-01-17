#pragma once
#include <string>
#include <vector>
#include "Note.h"
#include "NoteRepository.h"
#include "Observable.h"
#include "NoteTagService.h"

using namespace std;
class QuickNoteService
{
public:
	vector<Note*>* findAll();
	vector<Note*>* findByTagName(string tagName);
	void createNote(string content, string commaDelimitedTagNames);
	void registerObservable(Observable* o);
	int getSumOfNotesForEachTag();

	static class QuickNoteService* getInstance();
	~QuickNoteService();
private:
	NoteRepository* _noteRepository;
	vector<Observable*> *_observables;
	NoteTagService* _noteTagService;

	int _cachedSumNotes;

	static QuickNoteService* _instance;
	QuickNoteService();
};

