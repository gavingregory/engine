#pragma once
#include "../../../engine-common/src/graphics/PhysicsObject.h"
#include "../../../engine-common/src/input/InputHandler.h"
#include "../../../engine-common/src/graphics/Window.h"
#include "../../../engine-common/src/graphics/Camera.h"
#include "../../../engine-audio/src/Audio.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#define MAX_KEYS 1024

using namespace engine;
using namespace graphics;
using namespace audio;

class SnookerInput : public InputHandler
{
public:
	SnookerInput();
	virtual ~SnookerInput();
	void handleInput(float msec) override;
	inline void setCueBall(PhysicsObject* cueBall) { m_CueBall = cueBall; }
	inline void setAudio(Audio* audio) { m_Audio = audio; }
private:
	bool m_KeysHeld[MAX_KEYS];
	PhysicsObject* m_CueBall;
	Audio* m_Audio;
};

