#include "stdafx.h"
#include "NoteService.h"
#include <fstream>
#include "DatabaseConfig.h"
#include "StringUtils.h"

NoteService* NoteService::_instance;

//Khoi tao gia tri
NoteService* NoteService::getInstance() 
{
	if (!_instance) 
	{
		_instance = new NoteService();
	}

	return _instance;
}
//lưu note vô file text
int NoteService::save(Note* note) 
{
	int count = 0;
	//Mo file Note.txt
	ifstream is(DatabaseConfig::FILE_NAME_NOTE);
	//Dem so note da co trong file
	if (is.is_open()) 
	{
		string line;
		while (getline(is, line)) 
		{
			if (line == "") 
			{
				count++;
			}
		}
	}
	is.close();
	//Khoi tao 1 id moi
	int nextId = count + 1;
	//mo lai file note.txt
	ofstream os(DatabaseConfig::FILE_NAME_NOTE, ios::app | ios::binary);
	//ghi noi dung note can luu vao file
	if (os.is_open()) 
	{
		os << nextId << endl;
		os << note->getContent() << endl;
		os << endl;
	}

	os.close();

	return nextId;
}

vector<Note*>* NoteService::findAll()
{
	vector<Note*>* notes = new vector<Note*>();
	ifstream is(DatabaseConfig::FILE_NAME_NOTE);
	//Mo file de lay thong tin
	if (is.is_open()) 
	{
		int id = 0;
		string content = "";

		string line;
		while (getline(is, line)) 
		{
			//ktra file rong
			if (line == "") 
			{
				Note* note = new Note();
				note->setId(id);
				note->setContent(content);
				
				notes->push_back(note);

				id = 0;
				content = "";

				continue;
			}
			
			if (id == 0) 
			{
				id = stoi(line);
				continue;
			}

			if (content == "") 
			{
				content = line;
				continue;
			}
		}
	}
	is.close();

	return notes;
}

Note * NoteService::findById(int id)
{
	ifstream is(DatabaseConfig::FILE_NAME_NOTE);
	if (is.is_open()) {
		int tmpId = 0;
		string content = "";

		string line;
		while (getline(is, line)) {
			if (line == "") {
				if (tmpId == id) {
					Note* note = new Note();
					note->setId(tmpId);
					note->setContent(content);

					return note;
				}

				tmpId = 0;
				content = "";

				continue;
			}

			if (tmpId == 0) {
				tmpId = stoi(line);
				continue;
			}

			if (content == "") {
				content = line;
				continue;
			}
		}
	}
	is.close();
}

NoteService::NoteService()
{
}


NoteService::~NoteService()
{
}
