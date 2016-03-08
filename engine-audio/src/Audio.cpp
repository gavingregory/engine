#include "Audio.h"

Audio::Audio() { }


Audio::~Audio() { }

bool Audio::init() {
	m_SoundEngine = createIrrKlangDevice();
	m_SoundEngine->play2D("res/audio/breakout.mp3", true);
	return 1;
}

bool Audio::destroy() {
	return 1;
}

void Audio::update(float msec) {
			
}

void Audio::play() {
	
}
		
void Audio::stop() {

}