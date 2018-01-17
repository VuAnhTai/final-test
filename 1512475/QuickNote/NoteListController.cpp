#include "stdafx.h"
#include "NoteListController.h"
#include <commctrl.h>
#include <windowsX.h>
#include <winuser.h>
#include "StringUtils.h"

void NoteListController::update()
{
	ListView_DeleteAllItems(*_hwnd);

	vector<Note*>* notes = _QuicknoteService->findByTagName(_selectedTagName);
	
	for (int i = 0; i < notes->size(); i++)  
	{
		LV_ITEM lv;
		lv.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
		lv.iItem = 0;
		lv.iSubItem = 0;
		lv.pszText = StringUtils::toWCHAR(notes->at(i)->getContent());
		lv.lParam = (LPARAM)StringUtils::toWCHAR(notes->at(i)->getContent());
		ListView_InsertItem(*_hwnd, &lv);
	}

	if (!notes) 
	{
		for (int i = 0; i < notes->size(); i++) 
		{
			delete notes->at(i);
		}
		notes->clear();
	}
}

void NoteListController::setSelectedTagName(string name)
{
	_selectedTagName = name;
}

NoteListController::NoteListController(HWND* hwnd)
{
	_hwnd = hwnd;
	_QuicknoteService = QuickNoteService::getInstance();
	_selectedTagName = "";
}


NoteListController::~NoteListController()
{
}
