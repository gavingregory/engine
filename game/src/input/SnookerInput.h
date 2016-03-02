#pragma once
#include "../../../engine-common/src/graphics/PhysicsObject.h"
#include "../../../engine-common/src/input/InputHandler.h"
#include "../../../engine-common/src/graphics/Window.h"
#include "../../../engine-common/src/graphics/Camera.h"
#include "../../../engine-audio/src/Audio.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#define MAX_KEYS 1024
#define MAX_BUTTONS 10

class SnookerInput : public InputHandler
{
public:
	SnookerInput();
	virtual ~SnookerInput();
	void handleInput(float msec) override;
	inline void setCueBall(PhysicsObject* cueBall) { m_CueBall = cueBall; }
	inline void setCamera(Camera* camera) { m_Camera = camera; }
	inline void setAudio(Audio* audio) { m_Audio = audio; }
	virtual bool init();
	virtual bool destroy();
	virtual void update(float msec);
private:
	bool m_KeysHeld[MAX_KEYS];
	bool m_MouseButtonsHeld[MAX_BUTTONS];
	PhysicsObject* m_CueBall;
	Camera* m_Camera;
	Audio* m_Audio;
};

