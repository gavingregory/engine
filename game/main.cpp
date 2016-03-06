#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <time.h>

#include "../engine-core/src/graphics/GameManager.h"
#include "../engine-common/src/graphics/Shader.h"
#include "../../../engine-physics/src/Physics.h"
#include "../engine-common/src/graphics/Texture.h"
#include "src/input/SpaceInput.h"
#include "src/memory/SpaceMemoryManager.h"
#include "../engine-common/src/graphics/RenderObject.h"
#include "../engine-common/src/graphics/Renderer.h"
#include "../engine-common/src/graphics/Mesh.h"
#include "src/entities/NodeEntity.h"
#include "../engine-io/src/io/Loader.h"
#include "src/game/SpaceLogic.h"

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

	SpaceInput* input = new SpaceInput();
	SpaceMemoryManager* memory = new SpaceMemoryManager();
	GameLogic* logic = new SpaceLogic();
	Renderer* renderer = new Renderer();
	GameManager* g = new GameManager(GameManagerParams{ memory, input, logic, renderer, gameData.get("title", "Default Title").asString(), gameData.get("width", 800).asInt(), gameData.get("height", 600).asInt() });

	// For each level in JSON
	for (unsigned int level = 0; level < gameData["levels"].size(); level++) {

		// Create a new Level
		Level* lvl = memory->createLevel(LevelParams{renderer});
		g->getLevelStack()->push(lvl); // push this level?
		map<string, Mesh*>* meshes = lvl->getMeshes();
		map<string, Shader*>* shaders = lvl->getShaders();
		map<string, GLuint>* textures = lvl->getTextures();
		map<string, Entity*>* entities = lvl->getEntities();

		// create meshes from game.json
		for (unsigned int i = 0; i < gameData["levels"][level]["meshes"].size(); i++) {
			Json::Value jsonMesh = gameData["levels"][level]["meshes"][i];
			if (jsonMesh["type"] == "QUAD") {
				meshes->insert(pair<string, Mesh*>(jsonMesh["title"].asString(), Mesh::GenerateQuad(jsonMesh["width"].asFloat(), jsonMesh["height"].asFloat(), vec4(jsonMesh["colour"][level].asFloat(), jsonMesh["colour"][1].asFloat(), jsonMesh["colour"][2].asFloat(), jsonMesh["colour"][3].asFloat()))));
			}
			else if (jsonMesh["type"] == "CIRCLE") {
				meshes->insert(pair<string, Mesh*>(jsonMesh["title"].asString(), Mesh::GenerateCircle(jsonMesh["radius"].asFloat(), jsonMesh["tri-count"].asInt(), vec4(jsonMesh["colour"][level].asFloat(), jsonMesh["colour"][1].asFloat(), jsonMesh["colour"][2].asFloat(), jsonMesh["colour"][3].asFloat()))));
			}
			else if (jsonMesh["type"] == "FILE") {
				meshes->insert(pair<string, Mesh*>(jsonMesh["title"].asString(), Mesh::LoadMeshFile(jsonMesh["path"].asString())));
			}
			else {
				exit(1); // mesh could not be loaded
			}
		}

		// create shaders from game.json
		for (unsigned int i = 0; i < gameData["levels"][level]["shaders"].size(); i++) {
			Json::Value jsonShader = gameData["levels"][level]["shaders"][i];
			shaders->insert(pair<string, Shader*>(jsonShader["title"].asString(), memory->createShader(ShaderParams{ jsonShader["vertex"].asString(), jsonShader["fragment"].asString(), jsonShader["geometry"].asString(), jsonShader["tcs"].asString(), jsonShader["tes"].asString() })));
		}
	
		// create textures from game.json
		for (unsigned int i = 0; i < gameData["levels"][level]["textures"].size(); i++) {
			Json::Value jsonTexture = gameData["levels"][level]["textures"][i];
			textures->insert(pair<string, GLuint>(jsonTexture["title"].asString(), Texture::Load(jsonTexture["path"].asString())));
		}

		// create entities from game.json
		for (unsigned int i = 0; i < gameData["levels"][level]["entities"].size(); i++){

			Json::Value jsonEntity = gameData["levels"][level]["entities"][i];
			Mesh* m = meshes->at(jsonEntity["mesh"].asString());
			Shader* s = shaders->at(jsonEntity["shader"].asString());

			// create entity
			Entity* e = nullptr;
			if (jsonEntity["type"].asString() == "entity")
				e = memory->createEntity(EntityParams{ vec3(jsonEntity["position"][0].asFloat(),jsonEntity["position"][1].asFloat(),jsonEntity["position"][2].asFloat()), vec3(jsonEntity["velocity"][0].asFloat(),jsonEntity["velocity"][1].asFloat(),jsonEntity["velocity"][2].asFloat()), vec3(jsonEntity["acceleration"][0].asFloat(),jsonEntity["acceleration"][1].asFloat(),jsonEntity["acceleration"][2].asFloat()), jsonEntity["rotation"].asFloat(), jsonEntity["mass"].asFloat(), m, s, jsonEntity["title"].asString() });
			else if (jsonEntity["type"].asString() == "ball") {
				e = memory->createNodeEntity(
					NodeEntityParams{
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
			} else {
				cout << "Invalid entity detected! Exiting..." << endl;
				return 1;
			};

			// assign textures
			for (unsigned int j = 0; j < gameData["levels"][level]["entities"][i]["textures"].size(); j++) {
				string texture = gameData["levels"][level]["entities"][i]["textures"][j].asString();
				e->getRenderObject()->getTextures()->insert(pair<string, GLuint>(texture, (*textures)[texture]));
			}

			// assign as child or into map if no parent
			Json::Value parent = jsonEntity["parent"].asString();
			entities->insert(pair<string, Entity*>(jsonEntity["title"].asString(), e));
			if (parent != "null") {
				Entity* parent = entities->at(jsonEntity["parent"].asString());
				assert(parent != nullptr);
				parent->addChild(e);
			}
			else entities->insert(pair<string, Entity*>(jsonEntity["title"].asString(), e));
		}
	}

	g->run();

	return 0;
}