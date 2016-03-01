#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <time.h>

#include "../engine-core/src/graphics/GameManager.h"
#include "../engine-common/src/graphics/Shader.h"
#include "../../../engine-physics/src/Physics.h"
#include "src/input/SnookerInput.h"
#include "src/memory/SnookerMemoryManager.h"
#include "../engine-common/src/graphics/RenderObject.h"
#include "../engine-common/src/graphics/Renderer.h"
#include "../engine-common/src/graphics/Mesh.h"
#include "src/entities/BallEntity.h"

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

#define CUSHION_WIDTH 10

using glm::vec4;

int main()
{
	SnookerInput* input = new SnookerInput();
	SnookerMemoryManager* memory = new SnookerMemoryManager();
	GameManager* g = new GameManager(GameManagerParams{ memory, input });

	Mesh* tableMesh = Mesh::GenerateQuad(SNOOKER_TABLE_WIDTH, SNOOKER_TABLE_HEIGHT, vec4(0.0f, 1.0f, 0.0f, 0.5f));
	Mesh* cueMesh = Mesh::GenerateCircle(BALL_RADIUS, 30, vec4(1.000f, 1.000f, 1.000f, 0.500f)); // cue
	Mesh* blackMesh = Mesh::GenerateCircle(BALL_RADIUS, 30, vec4(0.000f, 0.000f, 0.000f, 0.500f)); // black
	Mesh* pinkMesh = Mesh::GenerateCircle(BALL_RADIUS, 30, vec4(1.000f, 0.412f, 0.706f, 0.500f)); // pink
	Mesh* blueMesh = Mesh::GenerateCircle(BALL_RADIUS, 30, vec4(0.118f, 0.565f, 1.000f, 0.500f)); // blue
	Mesh* yellowMesh = Mesh::GenerateCircle(BALL_RADIUS, 30, vec4(1.000f, 1.000f, 0.000f, 0.500f)); // yellow
	Mesh* brownMesh = Mesh::GenerateCircle(BALL_RADIUS, 30, vec4(0.545f, 0.271f, 0.075f, 0.500f)); // brown
	Mesh* greenMesh = Mesh::GenerateCircle(BALL_RADIUS, 30, vec4(0.596f, 0.984f, 0.596f, 0.500f)); // green
	Mesh* redMesh = Mesh::GenerateCircle(BALL_RADIUS, 30, vec4(1.000f, 0.000f, 0.000f, 0.500f)); // red

	Mesh* cushionHorizontalMesh = Mesh::GenerateQuad(SNOOKER_TABLE_WIDTH, CUSHION_WIDTH, vec4(0, 0, 0, 1));
	Mesh* cushionVerticalMesh = Mesh::GenerateQuad(CUSHION_WIDTH, SNOOKER_TABLE_HEIGHT, vec4(0, 0, 0, 1));

	ShaderParams shaderParams = { "res/shader/BasicVert.glsl", "res/shader/BasicFrag.glsl", "", "", "" };
	Shader* defaultShader = new Shader(shaderParams);

	Entity* table = new Entity(EntityParams{ vec3(0), vec3(0), vec3(0), tableMesh, defaultShader, "table" });

	g->addEntity(table);
	g->addEntity(memory->createBallEntity(BallEntityParams{vec3(15, 0, BALL_RADIUS), vec3(0.001, 0, 0), vec3(0), pinkMesh, defaultShader, "testBall", BALL_RADIUS}));
	Entity* cueBall = memory->createBallEntity(BallEntityParams{ vec3(25, -2.0f, BALL_RADIUS), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), cueMesh, defaultShader, "cueBall", BALL_RADIUS});
	g->addEntity(cueBall);
	input->setCueBall(cueBall->getPhysicsObject());
	input->setAudio(g->getAudio());
	table->addChild(memory->createBallEntity(BallEntityParams{vec3(BLACK_BALL_X, BLACK_BALL_Y, BALL_RADIUS), vec3(0), vec3(0), blackMesh, defaultShader, "blackBall", BALL_RADIUS}));
	table->addChild(memory->createBallEntity(BallEntityParams{vec3(PINK_BALL_X, PINK_BALL_Y, BALL_RADIUS), vec3(0), vec3(0), pinkMesh, defaultShader, "pinkBall", BALL_RADIUS }));
	table->addChild(memory->createBallEntity(BallEntityParams{vec3(BLUE_BALL_X, BLUE_BALL_Y, BALL_RADIUS), vec3(0), vec3(0), blueMesh, defaultShader, "blueBall", BALL_RADIUS }));
	table->addChild(memory->createBallEntity(BallEntityParams{vec3(YELLOW_BALL_X, YELLOW_BALL_Y, BALL_RADIUS), vec3(0), vec3(0), yellowMesh, defaultShader, "yellowBall", BALL_RADIUS }));
	table->addChild(memory->createBallEntity(BallEntityParams{vec3(BROWN_BALL_X, BROWN_BALL_Y, BALL_RADIUS), vec3(0), vec3(0), brownMesh, defaultShader, "brownBall", BALL_RADIUS }));
	table->addChild(memory->createBallEntity(BallEntityParams{vec3(GREEN_BALL_X, GREEN_BALL_Y, BALL_RADIUS), vec3(0), vec3(0), greenMesh, defaultShader, "greenBall", BALL_RADIUS }));
	table->addChild(memory->createBallEntity(BallEntityParams{vec3(RED00_BALL_X, RED00_BALL_Y, BALL_RADIUS), vec3(0), vec3(0), redMesh, defaultShader, "redBall01", BALL_RADIUS}));
	table->addChild(memory->createBallEntity(BallEntityParams{vec3(RED01_BALL_X, RED01_BALL_Y, BALL_RADIUS), vec3(0), vec3(0), redMesh, defaultShader, "redBall02", BALL_RADIUS}));
	table->addChild(memory->createBallEntity(BallEntityParams{vec3(RED02_BALL_X, RED02_BALL_Y, BALL_RADIUS), vec3(0), vec3(0), redMesh, defaultShader, "redBall03", BALL_RADIUS}));
	table->addChild(memory->createBallEntity(BallEntityParams{vec3(RED03_BALL_X, RED03_BALL_Y, BALL_RADIUS), vec3(0), vec3(0), redMesh, defaultShader, "redBall04", BALL_RADIUS}));
	table->addChild(memory->createBallEntity(BallEntityParams{vec3(RED04_BALL_X, RED04_BALL_Y, BALL_RADIUS), vec3(0), vec3(0), redMesh, defaultShader, "redBall05", BALL_RADIUS}));
	table->addChild(memory->createBallEntity(BallEntityParams{vec3(RED05_BALL_X, RED05_BALL_Y, BALL_RADIUS), vec3(0), vec3(0), redMesh, defaultShader, "redBall06", BALL_RADIUS}));
	table->addChild(memory->createBallEntity(BallEntityParams{vec3(RED06_BALL_X, RED06_BALL_Y, BALL_RADIUS), vec3(0), vec3(0), redMesh, defaultShader, "redBall07", BALL_RADIUS}));
	table->addChild(memory->createBallEntity(BallEntityParams{vec3(RED07_BALL_X, RED07_BALL_Y, BALL_RADIUS), vec3(0), vec3(0), redMesh, defaultShader, "redBall08", BALL_RADIUS}));
	table->addChild(memory->createBallEntity(BallEntityParams{vec3(RED08_BALL_X, RED08_BALL_Y, BALL_RADIUS), vec3(0), vec3(0), redMesh, defaultShader, "redBall09", BALL_RADIUS}));
	table->addChild(memory->createBallEntity(BallEntityParams{vec3(RED09_BALL_X, RED09_BALL_Y, BALL_RADIUS), vec3(0), vec3(0), redMesh, defaultShader, "redBall10", BALL_RADIUS}));
	table->addChild(memory->createBallEntity(BallEntityParams{vec3(RED10_BALL_X, RED10_BALL_Y, BALL_RADIUS), vec3(0), vec3(0), redMesh, defaultShader, "redBall11", BALL_RADIUS}));
	table->addChild(memory->createBallEntity(BallEntityParams{vec3(RED11_BALL_X, RED11_BALL_Y, BALL_RADIUS), vec3(0), vec3(0), redMesh, defaultShader, "redBall12", BALL_RADIUS}));
	table->addChild(memory->createBallEntity(BallEntityParams{vec3(RED12_BALL_X, RED12_BALL_Y, BALL_RADIUS), vec3(0), vec3(0), redMesh, defaultShader, "redBall13", BALL_RADIUS}));
	table->addChild(memory->createBallEntity(BallEntityParams{vec3(RED13_BALL_X, RED13_BALL_Y, BALL_RADIUS), vec3(0), vec3(0), redMesh, defaultShader, "redBall14", BALL_RADIUS}));
	table->addChild(memory->createBallEntity(BallEntityParams{vec3(RED14_BALL_X, RED14_BALL_Y, BALL_RADIUS), vec3(0), vec3(0), redMesh, defaultShader, "redBall15", BALL_RADIUS}));

	table->addChild(g->getMemoryManager()->createEntity(EntityParams{vec3(0, SNOOKER_TABLE_HEIGHT / 2, 0), vec3(0), vec3(0), cushionHorizontalMesh, defaultShader, "topCushion" }));
	table->addChild(g->getMemoryManager()->createEntity(EntityParams{vec3(0, -(SNOOKER_TABLE_HEIGHT / 2), 0), vec3(0), vec3(0), cushionHorizontalMesh, defaultShader, "bottomCushion"}));
	table->addChild(g->getMemoryManager()->createEntity(EntityParams{vec3(-(SNOOKER_TABLE_WIDTH / 2), 0, 0), vec3(0), vec3(0), cushionVerticalMesh, defaultShader, "leftCushion"}));
	table->addChild(g->getMemoryManager()->createEntity(EntityParams{vec3((SNOOKER_TABLE_WIDTH / 2), 0, 0), vec3(0), vec3(0), cushionVerticalMesh, defaultShader, "rightCushion"}));

	g->run();

	return 0;
}