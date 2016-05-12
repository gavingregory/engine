/******************************************************************************
Class:Audio
Author:Gavin Gregory
Description:The audio class provides functionality for playing audio files.
*//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "../../engine-common/src/system/SubSystem.h"
#include <irrKlang.h>
#include <iostream>
#include <string>
#include <assert.h>

using std::cout;
using std::endl;
using std::string;
using namespace irrklang;

class Audio : public SubSystem
{
public:
	Audio();
	~Audio();
	virtual bool init();
	virtual bool destroy();
	virtual void update(float msec);
	ISound* play(string path, bool loop);
	ISound* play(string path, bool loop, float volume);
	ISound* play(ISoundSource* source);
	ISoundSource* createSoundSource(string path);
	void stop(ISound* sound);
	static Audio* Instance;
private:
	ISoundEngine* m_SoundEngine;
};