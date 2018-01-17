#pragma once
#include "Observer.h"
#include "TagRepository.h"
class TagListController : public Observer
{
public:
	void update();
	TagListController(HWND*);
	~TagListController();

private:
	HWND* _hwnd;
	TagRepository* _tagRepository;
};

