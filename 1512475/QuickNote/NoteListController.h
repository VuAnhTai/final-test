#pragma once
#include "QuickNoteService.h"
class NoteListController : public Observer
{
public:
	void update();
	void setSelectedTagName(string name);
	NoteListController(HWND*);
	~NoteListController();
private:
	HWND* _hwnd;
	QuickNoteService* _QuicknoteService;
	string _selectedTagName;
};

