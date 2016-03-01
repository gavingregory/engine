#pragma once
#include "../../lib/portaudio/include/portaudio.h"
#include "../../engine-common/src/system/SubSystem.h"
#include <iostream>

class Audio : public SubSystem
{
public:
	Audio();
	~Audio();
	virtual bool init();
	virtual bool destroy();
	virtual void update(float msec);
	void play();
	void stop();
private:
	PaStream *m_Stream;
};