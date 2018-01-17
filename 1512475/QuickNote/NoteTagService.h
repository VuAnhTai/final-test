#pragma once
#include <vector>
using namespace std;	
class NoteTagService
{
public:
	void save(int noteId, int tagId);
	vector<int>* findNoteIDsByTagId(int tagId);
	int count();
	static NoteTagService* getInstance();
	
	
	~NoteTagService();
private:
	static NoteTagService* _instance;
	NoteTagService();
};

