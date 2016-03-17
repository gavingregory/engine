#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <time.h>
#include <Box2D/Box2D.h>
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

	Audio* audio = new Audio();
	SpaceMemoryManager* memory = new SpaceMemoryManager();
	GameLogic* logic = new SpaceLogic(memory);
	SpaceInput* input = new SpaceInput(audio, (SpaceLogic*)logic);
	Renderer* renderer = new Renderer();
	GameManager* g = new GameManager(GameManagerParams{ memory, input, logic, audio, renderer, gameData.get("title", "Default Title").asString(), gameData.get("width", 800).asInt(), gameData.get("height", 600).asInt() });

	// For each level in JSON
	for (unsigned int level = 0; level < gameData["levels"].size(); level++) {

		// Create a new Level
		b2World world(b2Vec2(0.0f, -10.0f));
		Level* lvl = memory->createLevel(LevelParams{renderer, vec2(0.0f, -10.0f)});
		Level::currentLevel = lvl; // level contains a pointer to the current level - FOR NOW
		g->getLevelStack()->push(lvl); // push this level?
		map<string, Mesh*>* meshes = lvl->getMeshes();
		map<string, Shader*>* shaders = lvl->getShaders();
		map<string, GLuint>* textures = lvl->getTextures();
		map<string, Entity*>* entities = lvl->getEntities();
		map<string, ISoundSource*>* sounds = lvl->getSounds();

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

		// load audio files from game.json
		for (unsigned int i = 0; i < gameData["levels"][level]["sounds"].size(); ++i) {
			Json::Value jsonAudio = gameData["levels"][level]["sounds"][i];
			sounds->insert(pair<string, ISoundSource*>(jsonAudio["title"].asString(), g->getAudioManager()->createSoundSource(jsonAudio["path"].asString())));
		}

		// create entities from game.json
		for (unsigned int i = 0; i < gameData["levels"][level]["entities"].size(); i++){

			Json::Value jsonEntity = gameData["levels"][level]["entities"][i];
			Mesh* m = meshes->at(jsonEntity["mesh"].asString());
			Shader* s = shaders->at(jsonEntity["shader"].asString());

			// create entity
			Entity* e = nullptr;

			// box2d
			b2BodyDef def;
			if (jsonEntity["dynamic"].asBool()) def.type = b2_dynamicBody; // otherwise static
			def.position.Set(jsonEntity["position"][0].asFloat(), jsonEntity["position"][1].asFloat());

			if (jsonEntity["type"].asString() == "entity")
				e = memory->createEntity(EntityParams{
					vec3(jsonEntity["position"][0].asFloat(), jsonEntity["position"][1].asFloat(), jsonEntity["position"][2].asFloat()),
					vec3(jsonEntity["velocity"][0].asFloat(), jsonEntity["velocity"][1].asFloat(), jsonEntity["velocity"][2].asFloat()),
					vec3(jsonEntity["acceleration"][0].asFloat(), jsonEntity["acceleration"][1].asFloat(), jsonEntity["acceleration"][2].asFloat()),
					jsonEntity["rotation"].asFloat(),
					jsonEntity["mass"].asFloat(),
					m,
					s,
					jsonEntity["title"].asString(),
					def
				});
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
						jsonEntity["radius"].asFloat(),
						jsonEntity["dynamic"].asBool()
				});
			} else {
				cout << "Invalid entity detected! Exiting..." << endl;
				return 1;
			};

			// assign entity textures
			for (unsigned int j = 0; j < gameData["levels"][level]["entities"][i]["textures"].size(); j++) {
				string texture = gameData["levels"][level]["entities"][i]["textures"][j].asString();
				e->getRenderObject()->getTextures()->insert(pair<string, GLuint>(texture, (*textures)[texture]));
			}

			map<string, ISoundSource*>* sounds = lvl->getSounds();
			// assign entity sounds
			map<string, ISoundSource*>* entitySounds = e->getSounds();
			for (unsigned int j = 0; j < gameData["levels"][level]["entities"][i]["sounds"].size(); j++) {
				string sound = gameData["levels"][level]["entities"][i]["sounds"][j].asString();
				entitySounds->insert(pair<string, ISoundSource*>(sound, (*sounds)[sound]));
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
	g->init();
	g->run();
	return 0;
}