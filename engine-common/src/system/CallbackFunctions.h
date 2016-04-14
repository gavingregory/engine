#pragma once

#include <vector>

using std::pair;

// Callback Function Types for Events

// a collision event signature -> gets called from the physics subsystem when a collision is detected
typedef void(*CollisionEventCallback)(pair<void*, void*> entities);

// an input event signature -> gets called from the input subsystem when a new input is detected
typedef void(*InputEventCallback)(bool key, bool mouse, int id);