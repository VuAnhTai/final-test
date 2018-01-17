#pragma once
#include "Observer.h"
#include <vector>
using namespace std;

class Observable
{
public:
	virtual ~Observable();

	virtual void attach(Observer*);
	virtual void detach(Observer*);
	virtual void notify();
protected:
	Observable();
	
private:
	vector<Observer*> *_observers;
};

