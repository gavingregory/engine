#pragma once

#include <vector>

using std::pair;

// Callback Function Types for Events

// a collision event signature -> gets called from the physics subsystem when a collision is detected
typedef void(*CollisionEventCallback)(pair<void*, void*> entities);

/**
 * Input event callback function pointer.
 * isKey: if true this is a keyboard input, if false this is a mouse input.
 * isPressed: if true, this is an intial press, if false this is a release.
 * id: the ID of the keyboard/mouse button.
 */
typedef void(*InputEventCallback)(bool isKey, bool isPressed, int id);