#pragma once
#include "Tag.h"
class TagService
{
public:
	Tag* saveOrGetIfExist(Tag* tag);
	int count();
	Tag* findById(int id);
	Tag* findByName(string name);
	vector<Tag*>* findByNameLike(string name);
	vector<Tag*>* findAll();

	static TagService* getInstance();
	
	~TagService();
private:
	static TagService* _instance;
	TagService();
};

