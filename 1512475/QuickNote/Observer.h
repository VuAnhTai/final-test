#pragma once
class Observer
{
public:
	virtual void update();

	virtual ~Observer();
protected:
	Observer();
};

