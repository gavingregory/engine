
#include <vector>
#include <GL/glew.h>
#include "RenderObject.h"

class Renderer {
public:
	Renderer();
	~Renderer();
	virtual void	RenderScene();
	virtual void	Render(RenderObject &o);
	virtual void	UpdateScene(float msec);
	void	AddRenderObject(RenderObject &r) {
		renderObjects.push_back(&r);
	}
protected:
	std::vector<RenderObject*> renderObjects;
	//added code
	RenderObject renderObject;
	Mesh* mesh;
	Shader* shader;
};