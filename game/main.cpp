#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <time.h>

#include "../engine-core/src/graphics/Shader.h"
#include "../engine-core/src/physics/Physics.h"
#include "../engine-core/src/graphics/RenderObject.h"
#include "../engine-core/src/graphics/Renderer.h"
#include "../engine-core/src/graphics/GameManager.h"
#include "../engine-core/src/graphics/Entity.h"
#include "../engine-core/src/graphics/Mesh.h"
#include "src/entities/BallEntity.h"
#include "src/entities/TableEntity.h"

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
	Mesh* triMesh = Mesh::GenerateTriangle(); //Mesh::GenerateCircle(5, 10, glm::vec4(1,1,1,1));
	Mesh* ballMesh = Mesh::GenerateCircle(2.625f, 30, vec4(1, 1, 1, 1));
	Shader* defaultShader = new Shader("res/shader/BasicVert.glsl", "res/shader/BasicFrag.glsl");
	Shader* ballShader = new Shader("res/shader/ball.vert", "res/shader/ball.frag");
	RenderObject triObject(triMesh, defaultShader);
	g->addEntity(new Entity(vec3(1, 10, -30), vec3(0.001f, 0, 0), vec3(-0.0001f, 0, 0), triObject, "triangle"));

	RenderObject ballObject(ballMesh, ballShader);
	g->addEntity((Entity*)new BallEntity(vec3(1, 5, -30), vec3(0.001f, 0, 0), vec3(-0.0001f, 0, 0), ballObject, "cueball", vec4(1.0f,1.0f,1.0f,1.0f)));
	g->addEntity((Entity*)new BallEntity(vec3(BLACK_BALL_X, BLACK_BALL_Y, -30), vec3(0.001f, 0, 0), vec3(-0.0001f, 0, 0), ballObject, "blackball", vec4(0.0f, 0.0f, 0.0f, 1.0f)));
	g->addEntity((Entity*)new BallEntity(vec3(1, 5, -30), vec3(0.001f, 0, 0), vec3(-0.0001f, 0, 0), ballObject, "pinkball", vec4(1.0f, 0.412f, 0.706f, 1.0f)));
	g->addEntity((Entity*)new BallEntity(vec3(BLUE_BALL_X, BLUE_BALL_Y, -30), vec3(0.001f, 0, 0), vec3(-0.0001f, 0, 0), ballObject, "blueball", vec4(0, 0, 0.804f, 1.0f)));
	g->addEntity((Entity*)new BallEntity(vec3(1, 5, -30), vec3(0.001f, 0, 0), vec3(-0.0001f, 0, 0), ballObject, "greenball", vec4(0.0f, 0.392f, 0.0f, 1.0f)));
	g->addEntity((Entity*)new BallEntity(vec3(1, 5, -30), vec3(0.001f, 0, 0), vec3(-0.0001f, 0, 0), ballObject, "brownball", vec4(0.647f, 0.165f, 0.165f, 1.0f)));
	g->addEntity((Entity*)new BallEntity(vec3(1, 5, -30), vec3(0.001f, 0, 0), vec3(-0.0001f, 0, 0), ballObject, "yellowball", vec4(1.0f, 1.0f, 0.0f, 1.0f)));
	g->addEntity((Entity*)new BallEntity(vec3(1, 5, -30), vec3(0.001f, 0, 0), vec3(-0.0001f, 0, 0), ballObject, "redball00", vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	g->addEntity((Entity*)new BallEntity(vec3(1, 5, -30), vec3(0.001f, 0, 0), vec3(-0.0001f, 0, 0), ballObject, "redball01", vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	g->addEntity((Entity*)new BallEntity(vec3(1, 5, -30), vec3(0.001f, 0, 0), vec3(-0.0001f, 0, 0), ballObject, "redball02", vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	g->addEntity((Entity*)new BallEntity(vec3(1, 5, -30), vec3(0.001f, 0, 0), vec3(-0.0001f, 0, 0), ballObject, "redball03", vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	g->addEntity((Entity*)new BallEntity(vec3(1, 5, -30), vec3(0.001f, 0, 0), vec3(-0.0001f, 0, 0), ballObject, "redball04", vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	g->addEntity((Entity*)new BallEntity(vec3(1, 5, -30), vec3(0.001f, 0, 0), vec3(-0.0001f, 0, 0), ballObject, "redball05", vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	g->addEntity((Entity*)new BallEntity(vec3(1, 5, -30), vec3(0.001f, 0, 0), vec3(-0.0001f, 0, 0), ballObject, "redball06", vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	g->addEntity((Entity*)new BallEntity(vec3(1, 5, -30), vec3(0.001f, 0, 0), vec3(-0.0001f, 0, 0), ballObject, "redball07", vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	g->addEntity((Entity*)new BallEntity(vec3(1, 5, -30), vec3(0.001f, 0, 0), vec3(-0.0001f, 0, 0), ballObject, "redball08", vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	g->addEntity((Entity*)new BallEntity(vec3(1, 5, -30), vec3(0.001f, 0, 0), vec3(-0.0001f, 0, 0), ballObject, "redball09", vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	g->addEntity((Entity*)new BallEntity(vec3(1, 5, -30), vec3(0.001f, 0, 0), vec3(-0.0001f, 0, 0), ballObject, "redball10", vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	g->addEntity((Entity*)new BallEntity(vec3(1, 5, -30), vec3(0.001f, 0, 0), vec3(-0.0001f, 0, 0), ballObject, "redball11", vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	g->addEntity((Entity*)new BallEntity(vec3(1, 5, -30), vec3(0.001f, 0, 0), vec3(-0.0001f, 0, 0), ballObject, "redball12", vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	g->addEntity((Entity*)new BallEntity(vec3(1, 5, -30), vec3(0.001f, 0, 0), vec3(-0.0001f, 0, 0), ballObject, "redball13", vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	g->addEntity((Entity*)new BallEntity(vec3(1, 5, -30), vec3(0.001f, 0, 0), vec3(-0.0001f, 0, 0), ballObject, "redball14", vec4(1.0f, 0.0f, 0.0f, 1.0f)));

	Mesh* tableMesh = Mesh::GenerateQuad(SNOOKER_TABLE_WIDTH, SNOOKER_TABLE_HEIGHT, vec4(0.0f, 1.0f, 0.0f, 1.0f));
	RenderObject tableObject(tableMesh, defaultShader);
	g->addEntity((Entity*)new TableEntity(vec3(5, 5, -30), vec3(0), vec3(0), tableObject, "table"));

	g->run();

	return 0;
}