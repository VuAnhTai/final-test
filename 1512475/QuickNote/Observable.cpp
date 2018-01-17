#include "stdafx.h"
#include "Observable.h"




void Observable::attach(Observer *o)
{
	_observers->push_back(o);
}

void Observable::detach(Observer *o)
{
	// not implement
}

void Observable::notify()
{
	for (int i = 0; i < _observers->size(); i++) {
		_observers->at(i)->update();
	}
}

Observable::Observable()
{
	_observers = new vector<Observer*>();
}

Observable::~Observable()
{
	for (int i = 0; i < _observers->size(); i++) {
		delete _observers->at(i);
	}
	_observers->clear();
}

