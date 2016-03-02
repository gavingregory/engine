#pragma once

#include <glm/glm.hpp>

//
// Shape Class
// Represents a shape. This is a pure abstract base class!
//

class CollisionShape {
public:
	CollisionShape(glm::vec3* position);
    virtual ~CollisionShape();
	inline glm::vec3* getPositionPtr() { return m_Position; }
	inline glm::vec3 getPosition() { return *m_Position; }
protected:
	glm::vec3* m_Position;
};
