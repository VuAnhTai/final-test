#pragma once

#include "Tag.h"
#include "TagService.h"
#include "NoteTagService.h"

class TagRepository
{
public:
	vector<Tag*>* findAll();
	vector<Tag*>* findTagByNameLikeAndSortByFrequency(string name);
	int countNoteByTag(int tagId);
	static TagRepository* getInstance();

	~TagRepository();
private:
	TagService* _TagService;
	NoteTagService* _noteTagService;

	bool compareMethod(Tag* tag1, Tag* tag2);

	static TagRepository* _instance;
	TagRepository();
};

