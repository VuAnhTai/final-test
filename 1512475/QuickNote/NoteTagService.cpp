#include "stdafx.h"
#include "NoteTagService.h"
#include <fstream>
#include "DatabaseConfig.h"
#include "StringUtils.h"
using namespace std;

NoteTagService*	NoteTagService::_instance;

void NoteTagService::save(int noteId, int tagId) 
{
	ofstream os(DatabaseConfig::FILE_NAME_NOTETAG, ios::app);
	if (os.is_open()) 
	{
		os << noteId << " " << tagId << endl;
	}
	os.close();
}

vector<int>* NoteTagService::findNoteIDsByTagId(int tagId)
{
	vector<int>* IDs = new vector<int>();

	ifstream is(DatabaseConfig::FILE_NAME_NOTETAG);
	string line;
	if (is.is_open()) 
	{
		while (getline(is, line)) 
		{
			vector<string> noteIdAndTagId = StringUtils::delimitedStringToVector(line, ' ');
			if ( tagId == stoi(noteIdAndTagId.at(1)) ) 
			{
				IDs->push_back( stoi(noteIdAndTagId.at(0)) );
			}
		}
	}
	is.close();

	return IDs;
}

int NoteTagService::count()
{
	int count = 0;
	ifstream is(DatabaseConfig::FILE_NAME_NOTETAG);
	string line;
	if (is.is_open()) 
	{
		while (getline(is, line)) 
		{
			count++;
		}
	}
	is.close();

	return count;
}

NoteTagService* NoteTagService::getInstance() 
{
	if (!_instance) 
	{
		_instance = new NoteTagService();
	}

	return _instance;
}

NoteTagService::NoteTagService()
{
}


NoteTagService::~NoteTagService()
{
}
