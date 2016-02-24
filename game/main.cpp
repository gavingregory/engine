#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <time.h>

#include "../engine-core/src/graphics/Shader.h"
#include "../engine-core/src/physics/Physics.h"
#include "../engine-core/src/graphics/RenderObject.h"
#include "../engine-core/src/graphics/Renderer.h"
#include "../engine-core/src/graphics/GameManager.h"
#include "../engine-core/src/graphics/Mesh.h"

#define WIDTH 800
#define HEIGHT 600

#define SNOOKER_TABLE_WIDTH 356.87f
#define SNOOKER_TABLE_HEIGHT 177.8f
#define BLUE_BALL_X SNOOKER_TABLE_WIDTH / 2.0f
#define BLUE_BALL_Y SNOOKER_TABLE_HEIGHT / 2.0f
#define BLACK_BALL_X SNOOKER_TABLE_WIDTH - 31.75f
#define BLACK_BALL_Y SNOOKER_TABLE_HEIGHT / 2.0f


int main()
{
	using namespace engine;
	using namespace graphics;
	using namespace utils;
	using namespace glm;

	GameManager* g = new GameManager();

	Mesh* tableMesh = Mesh::GenerateQuad(SNOOKER_TABLE_WIDTH, SNOOKER_TABLE_HEIGHT, vec4(0.0f, 1.0f, 0.0f, 1.0f));
	Mesh* cueMesh = Mesh::GenerateCircle(2.625f, 30, vec4(1.000f, 1.000f, 1.000f, 1.000f)); // cue
	Mesh* blackMesh = Mesh::GenerateCircle(2.625f, 30, vec4(0.000f, 0.000f, 0.000f, 1.000f)); // black
	Mesh* pinkMesh = Mesh::GenerateCircle(2.625f, 30, vec4(1.000f, 0.412f, 0.706f, 1.000f)); // pink
	Mesh* blueMesh = Mesh::GenerateCircle(2.625f, 30, vec4(0.118f, 0.565f, 1.000f, 1.000f)); // blue
	Mesh* yellowMesh = Mesh::GenerateCircle(2.625f, 30, vec4(1.000f, 1.000f, 0.000f, 1.000f)); // yellow
	Mesh* brownMesh = Mesh::GenerateCircle(2.625f, 30, vec4(0.545f, 0.271f, 0.075f, 1.000f)); // brown
	Mesh* greenMesh = Mesh::GenerateCircle(2.625f, 30, vec4(0.596f, 0.984f, 0.596f, 1.000f)); // green
	Mesh* redMesh = Mesh::GenerateCircle(2.625f, 30, vec4(1.000f, 0.000f, 0.000f, 1.000f)); // red

	Shader* defaultShader = new Shader("res/shader/BasicVert.glsl", "res/shader/BasicFrag.glsl");

	RenderObject tableObject(tableMesh, defaultShader);
	
	g->addRenderObject(&tableObject);

	tableObject.AddChild(new RenderObject(   cueMesh, defaultShader, vec3(1, 1, 1))); // cue
	tableObject.AddChild(new RenderObject( blackMesh, defaultShader, vec3(1, 1, 1))); // black
	tableObject.AddChild(new RenderObject(  pinkMesh, defaultShader, vec3(1, 1, 1))); // pink
	tableObject.AddChild(new RenderObject(  blueMesh, defaultShader, vec3(1, 1, 1))); // blue
	tableObject.AddChild(new RenderObject(yellowMesh, defaultShader, vec3(1, 1, 1))); // yellow
	tableObject.AddChild(new RenderObject( brownMesh, defaultShader, vec3(1, 1, 1))); // brown
	tableObject.AddChild(new RenderObject (greenMesh, defaultShader, vec3(1, 1, 1))); // green
	tableObject.AddChild(new RenderObject(   redMesh, defaultShader, vec3(1, 1, 1))); // red00
	tableObject.AddChild(new RenderObject(   redMesh, defaultShader, vec3(1, 1, 1))); // red01
	tableObject.AddChild(new RenderObject(   redMesh, defaultShader, vec3(1, 1, 1))); // red02
	tableObject.AddChild(new RenderObject(   redMesh, defaultShader, vec3(1, 1, 1))); // red03
	tableObject.AddChild(new RenderObject(   redMesh, defaultShader, vec3(1, 1, 1))); // red04
	tableObject.AddChild(new RenderObject(   redMesh, defaultShader, vec3(1, 1, 1))); // red05
	tableObject.AddChild(new RenderObject(   redMesh, defaultShader, vec3(1, 1, 1))); // red06
	tableObject.AddChild(new RenderObject(   redMesh, defaultShader, vec3(1, 1, 1))); // red07
	tableObject.AddChild(new RenderObject(   redMesh, defaultShader, vec3(1, 1, 1))); // red08
	tableObject.AddChild(new RenderObject(   redMesh, defaultShader, vec3(1, 1, 1))); // red09
	tableObject.AddChild(new RenderObject(   redMesh, defaultShader, vec3(1, 1, 1))); // red10
	tableObject.AddChild(new RenderObject(   redMesh, defaultShader, vec3(1, 1, 1))); // red11
	tableObject.AddChild(new RenderObject(   redMesh, defaultShader, vec3(1, 1, 1))); // red12
	tableObject.AddChild(new RenderObject(   redMesh, defaultShader, vec3(1, 1, 1))); // red13
	tableObject.AddChild(new RenderObject(   redMesh, defaultShader, vec3(1, 1, 1))); // red14

	//tableObject.AddChild(RenderObject(ballMesh, defaultShader, vec3(1, 5, -30)));
	//tableObject.AddChild(RenderObject(ballMesh, defaultShader, vec3(1, 5, -30)));
	//tableObject.AddChild(RenderObject(ballMesh, defaultShader, vec3(1, 5, -30)));
	//tableObject.AddChild(RenderObject(ballMesh, defaultShader, vec3(1, 5, -30)));
	//tableObject.AddChild(RenderObject(ballMesh, defaultShader, vec3(1, 5, -30)));
	//tableObject.AddChild(RenderObject(ballMesh, defaultShader, vec3(1, 5, -30)));
	//tableObject.AddChild(RenderObject(ballMesh, defaultShader, vec3(1, 5, -30)));
	//tableObject.AddChild(RenderObject(ballMesh, defaultShader, vec3(1, 5, -30)));
	//tableObject.AddChild(RenderObject(ballMesh, defaultShader, vec3(1, 5, -30)));
	//tableObject.AddChild(RenderObject(ballMesh, defaultShader, vec3(1, 5, -30)));
	//tableObject.AddChild(RenderObject(ballMesh, defaultShader, vec3(1, 5, -30)));
	//tableObject.AddChild(RenderObject(ballMesh, defaultShader, vec3(1, 5, -30)));
	//tableObject.AddChild(RenderObject(ballMesh, defaultShader, vec3(1, 5, -30)));
	//tableObject.AddChild(RenderObject(ballMesh, defaultShader, vec3(1, 5, -30)));
	//tableObject.AddChild(RenderObject(ballMesh, defaultShader, vec3(1, 5, -30)));
	//tableObject.AddChild(RenderObject(ballMesh, defaultShader, vec3(1, 5, -30)));
	//tableObject.AddChild(RenderObject(ballMesh, defaultShader, vec3(1, 5, -30)));
	//tableObject.AddChild(RenderObject(ballMesh, defaultShader, vec3(1, 5, -30)));
	//tableObject.AddChild(RenderObject(ballMesh, defaultShader, vec3(1, 5, -30)));
	//tableObject.AddChild(RenderObject(ballMesh, defaultShader, vec3(1, 5, -30)));
	//tableObject.AddChild(RenderObject(ballMesh, defaultShader, vec3(1, 5, -30)));

	g->run();

	return 0;
}