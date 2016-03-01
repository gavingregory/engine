#pragma once

class SubSystem {
public:
	virtual bool init() = 0;
	virtual bool destroy() = 0;
	virtual void update(float msec) = 0;
};