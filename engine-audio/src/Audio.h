#pragma once
#include "../../engine-common/src/system/SubSystem.h"
#include <irrKlang.h>
#include <iostream>
#include <iostream>

using std::cout;
using std::endl;
using namespace irrklang;

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
	ISoundEngine* m_SoundEngine;
};