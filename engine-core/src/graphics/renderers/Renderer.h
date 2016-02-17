
#include <vector>
#include <GL/glew.h>
#include "RenderObject.h"

class Renderer {
public:
	Renderer();
	~Renderer();
	virtual void RenderScene();
	virtual void Render(RenderObject &o);
	virtual void UpdateScene(float msec);
	void AddRenderObject(RenderObject &r);
protected:
	std::vector<RenderObject*> renderObjects;
	void UpdateShaderMatrices(GLuint program);
};