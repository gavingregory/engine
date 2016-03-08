#pragma once
class State
{
public:
	State();
	virtual ~State();
	virtual void update(float msec) =0;
};

