#include "stdafx.h"
#include "TagService.h"
#include <fstream>
#include "DatabaseConfig.h"
using namespace std;

TagService*	TagService::_instance;

TagService* TagService::getInstance() 
{
	if (!_instance) 
	{
		_instance = new TagService();
	}

	return _instance;
}

Tag* TagService::saveOrGetIfExist(Tag* tag) 
{
	ifstream is(DatabaseConfig::FILE_NAME_TAG);
	int nextId = 1;// tao mot id moi
	//Ktra trung ten khong: 1 tra ve tag do, 0 tao tag moi
	//1
	if (is.is_open()) 
	{
		int id = 0;
		string name = "";

		string line;
		while (getline(is, line)) 
		{
			if (line == "") 
			{
				//Ktra co ten do hay khong
				if (tag->getName() == name) 
				{
					Tag* retrievedTag = new Tag();
					retrievedTag->setId(id);
					retrievedTag->setName(name);

					return retrievedTag;
				}
				nextId++;
				id = 0;
				name = "";

				continue;
			}

			if (id == 0) 
			{
				id = stoi(line);
				continue;
			}

			if (name == "") 
			{
				name = line;
				continue;
			}
		}
	}
	is.close();

	//sai tao moi tag
	ofstream os(DatabaseConfig::FILE_NAME_TAG, ios::app | ios::binary);
	if (os.is_open()) 
	{
		os << nextId << endl;
		os << tag->getName() << endl;
		os << endl;
	}
	os.close();

	return findById(nextId);
}

Tag* TagService::findById(int id) 
{
	ifstream is(DatabaseConfig::FILE_NAME_TAG);
	if (is.is_open()) 
	{
		int tmpId = 0;
		string name = "";

		string line;
		while (getline(is, line)) 
		{
			if (line == "") 
			{
				if (id == tmpId) 
				{
					Tag* tag = new Tag();
					tag->setId(id);
					tag->setName(name);

					return tag;
				}

				tmpId = 0;
				name = "";

				continue;
			}

			if (tmpId == 0) 
			{
				tmpId = stoi(line);
				continue;
			}

			if (name == "") 
			{
				name = line;
				continue;
			}
		}
	}
	is.close();
}

vector<Tag*>* TagService::findAll()
{
	vector<Tag*>* tags = new vector<Tag*>();
	ifstream is(DatabaseConfig::FILE_NAME_TAG);
	if (is.is_open()) 
	{
		int id = 0;
		string name = "";

		string line;
		while (getline(is, line)) 
		{
			if (line == "") 
			{
				Tag* tag = new Tag();
				tag->setId(id);
				tag->setName(name);

				tags->push_back(tag);

				id = 0;
				name = "";

				continue;
			}

			if (id == 0) 
			{
				id = stoi(line);
				continue;
			}

			if (name == "") 
			{
				name = line;
				continue;
			}
		}
	}
	is.close();

	return tags;
}

int TagService::count() 
{
	int count = 0;
	ifstream is(DatabaseConfig::FILE_NAME_TAG);
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

	return count;
}

Tag * TagService::findByName(string name)
{
	ifstream is(DatabaseConfig::FILE_NAME_TAG);
	if (is.is_open()) 
	{
		int id = 0;
		string tmpName = "";

		string line;
		while (getline(is, line)) 
		{
			if (line == "") 
			{
				if (tmpName == name) 
				{
					Tag* tag = new Tag();
					tag->setId(id);
					tag->setName(tmpName);

					return tag;
				}
			
				id = 0;
				tmpName = "";

				continue;
			}

			if (id == 0) 
			{
				id = stoi(line);
				continue;
			}

			if (tmpName == "") 
			{
				tmpName = line;
				continue;
			}
		}
	}
	is.close();

	return new Tag();
}

vector<Tag*>* TagService::findByNameLike(string name)
{
	vector<Tag*>* tags = new vector<Tag*>();
	ifstream is(DatabaseConfig::FILE_NAME_TAG);
	if (is.is_open()) 
	{
		int id = 0;
		string tmpName = "";

		string line;
		while (getline(is, line)) 
		{
			if (line == "") 
			{
				if (tmpName.find(name) != string::npos) 
				{
					Tag* tag = new Tag();
					tag->setId(id);
					tag->setName(tmpName);

					tags->push_back(tag);
				}

				id = 0;
				tmpName = "";

				continue;
			}

			if (id == 0) 
			{
				id = stoi(line);
				continue;
			}

			if (tmpName == "") 
			{
				tmpName = line;
				continue;
			}
		}
	}
	is.close();

	return tags;
}

TagService::TagService()
{
}


TagService::~TagService()
{
}
