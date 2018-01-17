// QuickNote.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "QuickNote.h"


#define MAX_LOADSTRING 100

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void OnPaint(HWND hwnd);
void OnDestroy(HWND hwnd);
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
LRESULT OnNotify(HWND hwnd, int idFrom, NMHDR *pnm);

//My function
#include "NoteService.h"
#include "StringUtils.h"

WCHAR* getEnteredTextAsBuffer(HWND textboxHwnd, WCHAR* textboxName, bool emptyCheck);
WCHAR* concat(WCHAR* source, WCHAR* dest);
void init();
void updateSuggestedTags(string tagName);

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_QUICKNOTE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_QUICKNOTE));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_QUICKNOTE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_BTNFACE + 1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_QUICKNOTE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable
   //WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 1000, 500, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hWnd, WM_NOTIFY, OnNotify);

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}



#include "CreatingNoteObservable.h"
#include "TagListController.h"
#include "NoteListController.h"

HWND txtNote;
HWND txtTag;
HWND lstNote;
HWND lstTag;


HFONT hFont;
BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	INITCOMMONCONTROLSEX icc;
	icc.dwSize = sizeof(icc);
	icc.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icc);

	// Lấy font hệ thống
	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	hFont = CreateFont(lf.lfHeight, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);

	// Note
	HWND hwnd = CreateWindowEx(0, L"STATIC", L"Note", WS_CHILD | WS_VISIBLE | SS_LEFT, 220, 10, 100, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	txtNote = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_MULTILINE, 250, 10, 300, 100, hWnd, NULL, hInst, NULL);
	SendMessage(txtNote, WM_SETFONT, WPARAM(hFont), TRUE);

	SendMessage(txtNote, EM_LIMITTEXT, (WPARAM)0, 0);
	
	// Tag
	hwnd = CreateWindowEx(0, L"STATIC", L"Tags", WS_CHILD | WS_VISIBLE | SS_LEFT, 220, 120, 100, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	txtTag = CreateWindowEx(0, WC_COMBOBOX, L"", CBS_DROPDOWN | CBS_HASSTRINGS | WS_VISIBLE | WS_CHILD | WS_BORDER, 250, 120, 300, 20, hWnd, NULL, hInst, NULL);
	SendMessage(txtTag, WM_SETFONT, WPARAM(hFont), TRUE);

	SendMessage(txtTag, EM_LIMITTEXT, 0, 0);

	// List of tags
	lstTag = CreateWindowEx(0, WC_TREEVIEW, _T("Tree View"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_SIZEBOX | WS_VSCROLL | WS_TABSTOP | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS,
		10, 10, 200, 300,
		hWnd,
		(HMENU)IDC_LIST_TAG, hInst, NULL);

	// Init
	TV_INSERTSTRUCT tvDrive;
	tvDrive.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	tvDrive.hParent = NULL;
	tvDrive.item.iImage = NULL;
	tvDrive.item.iSelectedImage = NULL;
	tvDrive.item.pszText = L"HAHAHA";
	HTREEITEM hDrive = TreeView_InsertItem(lstTag, &tvDrive);

	TreeView_InsertItem(lstTag, &tvDrive);

	// List of note
	lstNote = CreateWindowEx(WS_EX_CLIENTEDGE, WC_LISTVIEW, _T("List View"),
		WS_CHILD | LVS_REPORT | WS_VISIBLE | WS_VSCROLL | WS_TABSTOP | LVS_ICON | LVS_EDITLABELS | LVS_SHOWSELALWAYS,
		250, 150, 300, 100,
		hWnd, (HMENU)IDC_LIST_NOTE, hInst, NULL);
	SendMessage(lstNote, WM_SETFONT, WPARAM(hFont), TRUE);

	// Init columns
	LVCOLUMN lvCol;

	lvCol.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvCol.fmt = LVCFMT_LEFT;

	lvCol.cx = 200;
	lvCol.pszText = _T("Notes");
	ListView_InsertColumn(lstNote, 0, &lvCol);

	// save button
	hwnd = CreateWindowEx(0, L"BUTTON", L"Save", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 250, 270, 60, 40, hWnd, (HMENU)IDC_BUTTON_SAVE, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);


	init();

	return true;
}

CreatingNoteObservable* observable = new CreatingNoteObservable();
TagListController* tagList = new TagListController(&lstTag);
NoteListController* noteList = new NoteListController(&lstNote);
void init() 
{
	observable->attach(tagList);
	observable->attach(noteList);
	QuickNoteService::getInstance()->registerObservable(observable);

	tagList->update();
	noteList->update();

	updateSuggestedTags("");

	int totalNotes = 0;
	vector<Tag*>* tags = TagRepository::getInstance()->findAll();
	for (int i = 0; i < tags->size(); i++) 
	{
		totalNotes += TagRepository::getInstance()->countNoteByTag(tags->at(i)->getId());
	}
}
vector<Tag*>* globalTags = TagRepository::getInstance()->findAll();
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	WCHAR* bufferNote = NULL;
	WCHAR* bufferTag = NULL;
	switch (id) {
		case IDC_BUTTON_SAVE: 
		{
		
			bufferNote = getEnteredTextAsBuffer(txtNote, L"note", true);
			if (bufferNote == NULL) 
			{
				return;
			}

			bufferTag = getEnteredTextAsBuffer(txtTag, L"tag", false);
			if (bufferTag == NULL) 
			{
				return;
			}

			QuickNoteService::getInstance()->createNote(StringUtils::toString(bufferNote),
												   StringUtils::toString(bufferTag));
			globalTags = TagRepository::getInstance()->findAll();

			InvalidateRect(hwnd, NULL, TRUE);

			break;
		}
		case IDM_EXIT:
			DestroyWindow(hwnd);
			break;
	}

	switch (codeNotify) {
		case CBN_EDITCHANGE: {
			int count = ComboBox_GetCount(txtTag);
			for (int i = count - 1; i >= 0; i--) 
			{
				int result = ComboBox_DeleteString(txtTag, i);
			}

			wchar_t buffer[256];
			ComboBox_GetText(txtTag, buffer, 256);
			updateSuggestedTags(StringUtils::toString(buffer));
		}
	}

	if (!bufferNote) 
	{
		delete[] bufferNote;
	}

	if (!bufferTag) 
	{
		delete[] bufferTag;
	}
}

void updateSuggestedTags(string tagName) 
{
	vector<Tag*>* suggestedTags =
		TagRepository::getInstance()->findTagByNameLikeAndSortByFrequency(tagName);

	// add suggested tag item
	for (int i = 0; i < suggestedTags->size(); i++) 
	{
		SendMessage(txtTag,
			CB_ADDSTRING, 0,
			(LPARAM)StringUtils::toWCHAR(suggestedTags->at(i)->getName()));
	}
}

WCHAR* getEnteredTextAsBuffer(HWND textboxHwnd, WCHAR* textboxName, bool emptyCheck) 
{
	int textLength = GetWindowTextLength(textboxHwnd);
	if (emptyCheck && textLength == 0) 
	{
		MessageBox(textboxHwnd, concat(L"Please enter ", textboxName), L"Error", MB_OK);
		return NULL;
	}
	WCHAR* buffer = new WCHAR[textLength + 1];
	GetWindowText(textboxHwnd, buffer, textLength + 1);

	return buffer;
}

WCHAR* concat(WCHAR* source, WCHAR* dest) 
{
	int bufferSize = wcsnlen_s(source, INT_MAX) + wcsnlen_s(dest, INT_MAX) + 1;
	WCHAR* result = new WCHAR[bufferSize];
	wcscpy_s(result, bufferSize, source);
	wcscat_s(result, bufferSize, dest);

	return result;
}

LRESULT OnNotify(HWND hwnd, int idFrom, NMHDR *pnm)
{
	switch (pnm->code) 
	{
		case TVN_SELCHANGED: 
		{
			LPNMTREEVIEW lpnmTree = (LPNMTREEVIEW)pnm;

			HTREEITEM currentSelectedItem = lpnmTree->itemNew.hItem;
			TVITEMEX currentItem;
			currentItem.mask = TVIF_PARAM;
			currentItem.hItem = currentSelectedItem;
			TreeView_GetItem(lstTag, &currentItem);

			string selectedTagName = StringUtils::toString((WCHAR*)currentItem.lParam);
			noteList->setSelectedTagName(selectedTagName);
			noteList->update();

			break;
		}
		case NM_DBLCLK: 
		{
			int pos = ListView_GetNextItem(lstNote, -1, LVNI_SELECTED);
			if (pos == -1) 
			{
				break;
			}

			wchar_t buffer[256];
			ListView_GetItemText(lstNote, pos, 0, buffer, 256);
			MessageBox(hwnd, buffer, L"Note", MB_OK);
			break;
		}
							 
	}

	return 0;
}

struct TagRGB 
{
	int r, g, b;

	TagRGB() {}
	TagRGB(int a, int b, int c) 
	{
		r = a;
		g = b;
		b = c;
	}
};

TagRGB toRGB(string hex) 
{
	hex = hex.erase(0, 1);

	TagRGB tagRGB;
	sscanf_s(hex.c_str(), "%02x%02x%02x", &tagRGB.r, &tagRGB.g, &tagRGB.b);

	return tagRGB;
}

string colors[];

void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc;
	hdc = BeginPaint(hWnd, &ps);

	int startY = 10;
	int height = 400;

	int startYDesc = 10;
	int endYDesc = 30;
	int noteCountLevel = 0;

	TextOut(hdc,
		710,
		startY - 5,
		L"0",
		wcslen(L"0"));

	for (int i = 0; i < globalTags->size(); i++) 
	{
		int numberOfNotes = TagRepository::getInstance()->countNoteByTag(globalTags->at(i)->getId());

		TagRGB rgb = toRGB(colors[i]);

		int h = (height * numberOfNotes) / QuickNoteService::getInstance()->getSumOfNotesForEachTag();
		HRGN hRegion = CreateRectRgn(600, startY, 700, startY + h) ;
		HBRUSH hBrush = CreateSolidBrush(RGB(rgb.r, rgb.g, rgb.b));
		FillRgn(hdc, hRegion, hBrush);

		startY += h;

		WCHAR* buffer = StringUtils::toWCHAR(to_string(noteCountLevel + numberOfNotes));
		TextOut(hdc, 
			710, 
			startY - 5, 
			buffer,
			wcslen(buffer));

		noteCountLevel += numberOfNotes;

		FillRgn(
			hdc,
			CreateRectRgn(800, startYDesc, 830, endYDesc),
			CreateSolidBrush(RGB(rgb.r, rgb.g, rgb.b))
		);

		WCHAR* bufferTagName = StringUtils::toWCHAR(globalTags->at(i)->getName());
		TextOut(hdc,
			850,
			startYDesc + 2,
			bufferTagName,
			wcslen(bufferTagName));

		startYDesc = endYDesc + 10;
		endYDesc += 30;
	}

	EndPaint(hWnd, &ps);
}

void OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
}

int GetTextSize(LPSTR a0)
{
	for (int iLoopCounter = 0; ; iLoopCounter++)
	{
		if (a0[iLoopCounter] == '\0')
			return iLoopCounter;
	}
}
void SetSystemFont(HWND hwnd)
{
	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);

	HFONT hFont = CreateFont(16, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);

	SetWindowFont(hwnd, hFont, TRUE);
}

string colors[] = {
	"#9966ff", "#ff66cc", "#ffffcc", "#9999ff", "#80ff80", "#df9fbf", "#d6d6c2", "#80d4ff", 
	"#e6b3b3", "#ffbf80", "#ff66d9", "#df9fbf", "#ff471a", "#805500", "#0066cc", "#ff99bb"
};