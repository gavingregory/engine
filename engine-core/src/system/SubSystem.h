#pragma once

class SubSystem {
public:
	virtual bool Init() = 0;
	virtual bool Destroy() = 0;
	virtual bool Update(float msec) = 0;
};