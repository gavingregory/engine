#ifndef COLLISION_SHAPE_H
#define COLLISION_SHAPE_H

#include <glm/glm.hpp>

//
// Shape Class
// Represents a shape. This is a pure abstract base class!
//

class Shape {
public:
    Shape(glm::vec3* position);
    virtual ~Shape();
	inline glm::vec3* getPositionPtr() { return m_Position; }
	inline glm::vec3 getPosition() { return *m_Position; }
protected:
	glm::vec3* m_Position;
};


#endif //COLLISION_SHAPE_H
