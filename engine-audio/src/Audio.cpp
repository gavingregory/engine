#include "Audio.h"

Audio::Audio() { }

Audio::~Audio() { }

Audio* Audio::Instance;

bool Audio::init() {
	m_SoundEngine = createIrrKlangDevice();
	return (m_SoundEngine != nullptr);
}

bool Audio::destroy() {
	return 1;
}

void Audio::update(float msec) {
	// do nothing
}

ISound* Audio::play(string path, bool loop) {
	ISound* s = m_SoundEngine->play2D(path.c_str(), loop, false, true);
	assert(s != nullptr);
	return s;
}

ISound* Audio::play(string path, bool loop, float volume) {
	ISound* s = m_SoundEngine->play2D(path.c_str(), loop, false, true);
	s->setVolume(volume);
	assert(s != nullptr);
	return s;
}

ISound* Audio::play(ISoundSource* source) {
	return m_SoundEngine->play2D(source);
}

ISoundSource* Audio::createSoundSource(string path) {
	return m_SoundEngine->addSoundSourceFromFile(path.c_str(), ESM_AUTO_DETECT, true);
}

void Audio::stop(ISound* sound) {
	sound->stop();
}