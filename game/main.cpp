#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <time.h>

#include "../engine-core/src/graphics/GameManager.h"
#include "../engine-common/src/graphics/Shader.h"
#include "../../../engine-physics/src/Physics.h"
#include "../engine-common/src/graphics/Texture.h"
#include "src/input/SnookerInput.h"
#include "src/memory/SnookerMemoryManager.h"
#include "../engine-common/src/graphics/RenderObject.h"
#include "../engine-common/src/graphics/Renderer.h"
#include "../engine-common/src/graphics/Mesh.h"
#include "src/entities/BallEntity.h"
#include "../engine-io/src/io/Loader.h"
#include "src/game/SnookerLogic.h"

#define WIDTH 800
#define HEIGHT 600


using glm::vec4;

int main()
{
	Json::Value gameData;
	try {
		gameData = Loader::LoadJson("res/json/game.json");
	}
	catch (const char* msg) { cout << msg << endl; }

	SnookerInput* input = new SnookerInput();
	SnookerMemoryManager* memory = new SnookerMemoryManager();
	GameLogic* logic = new SnookerLogic();
	GameManager* g = new GameManager(GameManagerParams{ memory, input, logic, gameData.get("title", "Default Title").asString(), gameData.get("width", 800).asInt(), gameData.get("height", 600).asInt() });

	Json::Value levelData = gameData["levels"];
	Json::Value levelOneData = levelData[0];

	// create meshes from game.json
	map<string, Mesh*> meshes;
	for (unsigned int i = 0; i < gameData["levels"][0]["meshes"].size(); i++) {
		Json::Value jsonMesh = gameData["levels"][0]["meshes"][i];
		if (jsonMesh["type"] == "QUAD") {
			meshes.insert(pair<string, Mesh*>(jsonMesh["title"].asString(), Mesh::GenerateQuad(jsonMesh["width"].asFloat(), jsonMesh["height"].asFloat(), vec4(jsonMesh["colour"][0].asFloat(), jsonMesh["colour"][1].asFloat(), jsonMesh["colour"][2].asFloat(), jsonMesh["colour"][3].asFloat()))));
		}
		else if (jsonMesh["type"] == "CIRCLE") {
			meshes.insert(pair<string, Mesh*>(jsonMesh["title"].asString(), Mesh::GenerateCircle(jsonMesh["radius"].asFloat(), jsonMesh["tri-count"].asInt(), vec4(jsonMesh["colour"][0].asFloat(), jsonMesh["colour"][1].asFloat(), jsonMesh["colour"][2].asFloat(), jsonMesh["colour"][3].asFloat()))));
		}
		else if (jsonMesh["type"] == "FILE") {
			meshes.insert(pair<string, Mesh*>(jsonMesh["title"].asString(), Mesh::LoadMeshFile(jsonMesh["path"].asString())));
		}
		else {
			exit(1); // mesh could not be loaded
		}
	}

	// create shaders from game.json
	map<string, Shader*> shaders;
	for (unsigned int i = 0; i < gameData["levels"][0]["shaders"].size(); i++) {
		Json::Value jsonShader = gameData["levels"][0]["shaders"][i];
		shaders.insert(pair<string, Shader*>(jsonShader["title"].asString(), memory->createShader(ShaderParams{ jsonShader["vertex"].asString(), jsonShader["fragment"].asString(), jsonShader["geometry"].asString(), jsonShader["tcs"].asString(), jsonShader["tes"].asString() })));
	}
	
	// create textures from game.json
	map<string, GLuint> textures;
	for (unsigned int i = 0; i < gameData["levels"][0]["textures"].size(); i++) {
		Json::Value jsonTexture = gameData["levels"][0]["textures"][i];
		textures.insert(pair<string, GLuint>(jsonTexture["title"].asString(), Texture::Load(jsonTexture["path"].asString())));
	}

	// create entities from game.json
	map<string, Entity*> entities;
	for (unsigned int i = 0; i < gameData["levels"][0]["entities"].size(); i++){
		Json::Value jsonEntity = gameData["levels"][0]["entities"][i];
		Mesh* m = meshes.at(jsonEntity["mesh"].asString());
		Shader* s = shaders.at(jsonEntity["shader"].asString());

		// create entity
		Entity* e = nullptr;
		if (jsonEntity["type"].asString() == "entity")
			e = memory->createEntity(EntityParams{ vec3(jsonEntity["position"][0].asFloat(),jsonEntity["position"][1].asFloat(),jsonEntity["position"][2].asFloat()), vec3(jsonEntity["velocity"][0].asFloat(),jsonEntity["velocity"][1].asFloat(),jsonEntity["velocity"][2].asFloat()), vec3(jsonEntity["acceleration"][0].asFloat(),jsonEntity["acceleration"][1].asFloat(),jsonEntity["acceleration"][2].asFloat()), jsonEntity["rotation"].asFloat(), jsonEntity["mass"].asFloat(), m, s, jsonEntity["title"].asString() });
		else if (jsonEntity["type"].asString() == "ball") {
			e = memory->createBallEntity(
				BallEntityParams{
					vec3(jsonEntity["position"][0].asFloat(),jsonEntity["position"][1].asFloat(),jsonEntity["position"][2].asFloat()),
					vec3(jsonEntity["velocity"][0].asFloat(),jsonEntity["velocity"][1].asFloat(),jsonEntity["velocity"][2].asFloat()),
					vec3(jsonEntity["acceleration"][0].asFloat(),jsonEntity["acceleration"][1].asFloat(),jsonEntity["acceleration"][2].asFloat()),
					jsonEntity["rotation"].asFloat(),
					jsonEntity["mass"].asFloat(),
					m,
					s,
					jsonEntity["title"].asString(),
					jsonEntity["radius"].asFloat()
			});
		}
		else if (jsonEntity["type"].asString() == "cushion") {
			e = memory->createCushionEntity(
				CushionEntityParams{
					vec3(jsonEntity["position"][0].asFloat(),jsonEntity["position"][1].asFloat(),jsonEntity["position"][2].asFloat()),
					vec3(jsonEntity["velocity"][0].asFloat(),jsonEntity["velocity"][1].asFloat(),jsonEntity["velocity"][2].asFloat()),
					vec3(jsonEntity["acceleration"][0].asFloat(),jsonEntity["acceleration"][1].asFloat(),jsonEntity["acceleration"][2].asFloat()),
					jsonEntity["rotation"].asFloat(),
					jsonEntity["mass"].asFloat(),
					m,
					s,
					jsonEntity["title"].asString(),
					vec3(jsonEntity["normal"][0].asFloat(),jsonEntity["normal"][1].asFloat(),jsonEntity["normal"][2].asFloat()),
					vec3(jsonEntity["distance"][0].asFloat(),jsonEntity["distance"][1].asFloat(),jsonEntity["distance"][2].asFloat())
			});
		}
		else if (jsonEntity["type"].asString() == "pocket") {
			e = memory->createPocketEntity(
				PocketEntityParams{
				vec3(jsonEntity["position"][0].asFloat(),jsonEntity["position"][1].asFloat(),jsonEntity["position"][2].asFloat()),
				vec3(jsonEntity["velocity"][0].asFloat(),jsonEntity["velocity"][1].asFloat(),jsonEntity["velocity"][2].asFloat()),
				vec3(jsonEntity["acceleration"][0].asFloat(),jsonEntity["acceleration"][1].asFloat(),jsonEntity["acceleration"][2].asFloat()),
				jsonEntity["rotation"].asFloat(),
				jsonEntity["mass"].asFloat(),
				m,
				s,
				jsonEntity["title"].asString(),
				vec3(jsonEntity["normal"][0].asFloat(),jsonEntity["normal"][1].asFloat(),jsonEntity["normal"][2].asFloat()),
				vec3(jsonEntity["distance"][0].asFloat(),jsonEntity["distance"][1].asFloat(),jsonEntity["distance"][2].asFloat())
			});
		} else {
			cout << "Invalid entity detected! Exiting..." << endl;
			return 1;
		};

		// assign textures
		for (unsigned int j = 0; j < gameData["levels"][0]["entities"][i]["textures"].size(); j++) {
			string texture = gameData["levels"][0]["entities"][i]["textures"][j].asString();
			e->getRenderObject()->getTextures()->insert(pair<string, GLuint>(texture, textures[texture]));
		}

		// assign as child or into map if no parent
		Json::Value parent = jsonEntity["parent"].asString();
		entities.insert(pair<string, Entity*>(jsonEntity["title"].asString(), e));
		if (parent != "null") {
			Entity* parent = entities.at(jsonEntity["parent"].asString());
			assert(parent != nullptr);
			parent->addChild(e);
		}
		else g->addEntity(e);
	}
	Entity* cueBall = entities["cueBall"];
	input->setCueBall(cueBall->getPhysicsObject());
	input->setAudio(g->getAudio());
	input->setCamera(g->getCamera());
	
	Mesh* snookerCueMesh = g->getMemoryManager()->createMesh("res/mesh/cue.json");
	Entity* cue = g->getMemoryManager()->createEntity(EntityParams{ vec3(0,0,0.1f) , vec3(0,0,0) , vec3(0,0,0), 0.0f, 1.0f, snookerCueMesh, shaders.at("default"), "cue" });
	cueBall->addChild(cue);
	input->setCue(cue->getPhysicsObject());
	
	Mesh* triangle = Mesh::GenerateTriangle();



	g->run();

	return 0;
}