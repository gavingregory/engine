#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <time.h>

#include "../engine-core/src/graphics/Shader.h"
#include "../engine-core/src/physics/Physics.h"
#include "../engine-core/src/graphics/RenderObject.h"
#include "../engine-core/src/graphics/Renderer.h"
#include "../engine-core/src/graphics/GameManager.h"
#include "../engine-core/src/graphics/Mesh.h"
#include "src/input/SnookerInput.h"

#define WIDTH 800
#define HEIGHT 600

#define SNOOKER_TABLE_WIDTH 356.87f
#define SNOOKER_TABLE_HEIGHT 177.8f
#define BALL_RADIUS 2.625f
#define BAULK_LINE 283.21f
#define SEMI_CIRCLE_RADIUS 29.21f
#define   BLUE_BALL_X 0
#define   BLUE_BALL_Y 0
#define  BLACK_BALL_X (SNOOKER_TABLE_WIDTH/2) - 31.75f
#define  BLACK_BALL_Y 0
#define   PINK_BALL_X (SNOOKER_TABLE_WIDTH/2) - 88.9f
#define   PINK_BALL_Y 0
#define  GREEN_BALL_X (SNOOKER_TABLE_WIDTH/2) - BAULK_LINE
#define  GREEN_BALL_Y SEMI_CIRCLE_RADIUS
#define YELLOW_BALL_X (SNOOKER_TABLE_WIDTH/2) - BAULK_LINE
#define YELLOW_BALL_Y -SEMI_CIRCLE_RADIUS
#define  BROWN_BALL_X (SNOOKER_TABLE_WIDTH/2) - BAULK_LINE
#define  BROWN_BALL_Y 0
#define RED_BALL_OFFSET 4.546633369868303f
#define RED00_BALL_X PINK_BALL_X + (BALL_RADIUS*2)
#define RED00_BALL_Y 0
#define RED01_BALL_X RED00_BALL_X + RED_BALL_OFFSET
#define RED01_BALL_Y BALL_RADIUS
#define RED02_BALL_X RED01_BALL_X
#define RED02_BALL_Y RED01_BALL_Y - (BALL_RADIUS*2)
#define RED03_BALL_X RED01_BALL_X + RED_BALL_OFFSET
#define RED03_BALL_Y RED01_BALL_Y + BALL_RADIUS
#define RED04_BALL_X RED03_BALL_X
#define RED04_BALL_Y RED03_BALL_Y - (BALL_RADIUS*2)
#define RED05_BALL_X RED03_BALL_X
#define RED05_BALL_Y RED04_BALL_Y - (BALL_RADIUS*2)
#define RED06_BALL_X RED03_BALL_X + RED_BALL_OFFSET
#define RED06_BALL_Y RED03_BALL_Y + BALL_RADIUS
#define RED07_BALL_X RED06_BALL_X
#define RED07_BALL_Y RED06_BALL_Y - (BALL_RADIUS*2)
#define RED08_BALL_X RED07_BALL_X
#define RED08_BALL_Y RED07_BALL_Y - (BALL_RADIUS*2)
#define RED09_BALL_X RED08_BALL_X
#define RED09_BALL_Y RED08_BALL_Y - (BALL_RADIUS*2)
#define RED10_BALL_X RED06_BALL_X + RED_BALL_OFFSET
#define RED10_BALL_Y RED06_BALL_Y + BALL_RADIUS
#define RED11_BALL_X RED10_BALL_X
#define RED11_BALL_Y RED10_BALL_Y - (BALL_RADIUS*2)
#define RED12_BALL_X RED11_BALL_X
#define RED12_BALL_Y RED11_BALL_Y - (BALL_RADIUS*2)
#define RED13_BALL_X RED12_BALL_X
#define RED13_BALL_Y RED12_BALL_Y - (BALL_RADIUS*2)
#define RED14_BALL_X RED13_BALL_X
#define RED14_BALL_Y RED13_BALL_Y - (BALL_RADIUS*2)




int main()
{
	using namespace engine;
	using namespace graphics;
	using namespace utils;
	using namespace glm;

	GameManager* g = new GameManager();
	g->setInputHandler(new SnookerInput());

	Mesh* tableMesh  = Mesh::GenerateQuad(SNOOKER_TABLE_WIDTH, SNOOKER_TABLE_HEIGHT, vec4(0.0f, 1.0f, 0.0f, 0.5f));
	Mesh* cueMesh    = Mesh::GenerateCircle(BALL_RADIUS, 30, vec4(1.000f, 1.000f, 1.000f, 0.500f)); // cue
	Mesh* blackMesh  = Mesh::GenerateCircle(BALL_RADIUS, 30, vec4(0.000f, 0.000f, 0.000f, 0.500f)); // black
	Mesh* pinkMesh   = Mesh::GenerateCircle(BALL_RADIUS, 30, vec4(1.000f, 0.412f, 0.706f, 0.500f)); // pink
	Mesh* blueMesh   = Mesh::GenerateCircle(BALL_RADIUS, 30, vec4(0.118f, 0.565f, 1.000f, 0.500f)); // blue
	Mesh* yellowMesh = Mesh::GenerateCircle(BALL_RADIUS, 30, vec4(1.000f, 1.000f, 0.000f, 0.500f)); // yellow
	Mesh* brownMesh  = Mesh::GenerateCircle(BALL_RADIUS, 30, vec4(0.545f, 0.271f, 0.075f, 0.500f)); // brown
	Mesh* greenMesh  = Mesh::GenerateCircle(BALL_RADIUS, 30, vec4(0.596f, 0.984f, 0.596f, 0.500f)); // green
	Mesh* redMesh    = Mesh::GenerateCircle(BALL_RADIUS, 30, vec4(1.000f, 0.000f, 0.000f, 0.500f)); // red

	Shader* defaultShader = new Shader("res/shader/BasicVert.glsl", "res/shader/BasicFrag.glsl");

	RenderObject tableObject(tableMesh, defaultShader);
	
	Entity* table = new Entity(vec3(0), vec3(0), vec3(0), tableMesh, defaultShader, "table");

	g->addEntity(table);

	table->addChild(new Entity(vec3(0), vec3(0), vec3(0), cueMesh, defaultShader, "cueBall"));
	table->addChild(new Entity(vec3( BLACK_BALL_X,  BLACK_BALL_Y, BALL_RADIUS), vec3(0), vec3(0),  blackMesh, defaultShader, "blackBall"));
	table->addChild(new Entity(vec3(  PINK_BALL_X,   PINK_BALL_Y, BALL_RADIUS), vec3(0), vec3(0),   pinkMesh, defaultShader, "pinkBall"));
	table->addChild(new Entity(vec3(  BLUE_BALL_X,   BLUE_BALL_Y, BALL_RADIUS), vec3(0), vec3(0),   blueMesh, defaultShader, "blueBall"));
	table->addChild(new Entity(vec3(YELLOW_BALL_X, YELLOW_BALL_Y, BALL_RADIUS), vec3(0), vec3(0), yellowMesh, defaultShader, "yellowBall"));
	table->addChild(new Entity(vec3( BROWN_BALL_X,  BROWN_BALL_Y, BALL_RADIUS), vec3(0), vec3(0),  brownMesh, defaultShader, "brownBall"));
	table->addChild(new Entity(vec3( GREEN_BALL_X,  GREEN_BALL_Y, BALL_RADIUS), vec3(0), vec3(0),  greenMesh, defaultShader, "greenBall"));
	table->addChild(new Entity(vec3( RED00_BALL_X,  RED00_BALL_Y, BALL_RADIUS), vec3(0), vec3(0),    redMesh, defaultShader, "redBall01"));
	table->addChild(new Entity(vec3( RED01_BALL_X,  RED01_BALL_Y, BALL_RADIUS), vec3(0), vec3(0),    redMesh, defaultShader, "redBall02"));
	table->addChild(new Entity(vec3( RED02_BALL_X,  RED02_BALL_Y, BALL_RADIUS), vec3(0), vec3(0),    redMesh, defaultShader, "redBall03"));
	table->addChild(new Entity(vec3( RED03_BALL_X,  RED03_BALL_Y, BALL_RADIUS), vec3(0), vec3(0),    redMesh, defaultShader, "redBall04"));
	table->addChild(new Entity(vec3( RED04_BALL_X,  RED04_BALL_Y, BALL_RADIUS), vec3(0), vec3(0),    redMesh, defaultShader, "redBall05"));
	table->addChild(new Entity(vec3( RED05_BALL_X,  RED05_BALL_Y, BALL_RADIUS), vec3(0), vec3(0),    redMesh, defaultShader, "redBall06"));
	table->addChild(new Entity(vec3( RED06_BALL_X,  RED06_BALL_Y, BALL_RADIUS), vec3(0), vec3(0),    redMesh, defaultShader, "redBall07"));
	table->addChild(new Entity(vec3( RED07_BALL_X,  RED07_BALL_Y, BALL_RADIUS), vec3(0), vec3(0),    redMesh, defaultShader, "redBall08"));
	table->addChild(new Entity(vec3( RED08_BALL_X,  RED08_BALL_Y, BALL_RADIUS), vec3(0), vec3(0),    redMesh, defaultShader, "redBall09"));
	table->addChild(new Entity(vec3( RED09_BALL_X,  RED09_BALL_Y, BALL_RADIUS), vec3(0), vec3(0),    redMesh, defaultShader, "redBall10"));
	table->addChild(new Entity(vec3( RED10_BALL_X,  RED10_BALL_Y, BALL_RADIUS), vec3(0), vec3(0),    redMesh, defaultShader, "redBall11"));
	table->addChild(new Entity(vec3( RED11_BALL_X,  RED11_BALL_Y, BALL_RADIUS), vec3(0), vec3(0),    redMesh, defaultShader, "redBall12"));
	table->addChild(new Entity(vec3( RED12_BALL_X,  RED12_BALL_Y, BALL_RADIUS), vec3(0), vec3(0),    redMesh, defaultShader, "redBall13"));
	table->addChild(new Entity(vec3( RED13_BALL_X,  RED13_BALL_Y, BALL_RADIUS), vec3(0), vec3(0),    redMesh, defaultShader, "redBall14"));
	table->addChild(new Entity(vec3( RED14_BALL_X,  RED14_BALL_Y, BALL_RADIUS), vec3(0), vec3(0),    redMesh, defaultShader, "redBall15"));

	g->run();

	return 0;
}