/******************************************************************************
Main
Author:Gavin Gregory
Description:This currently initialises all of the sub systems and creates a new
GameManager instance (and executes it with a call to run). currently it also
reads in game data from the game.json file and creates the game objects. Ideally
this would be in its own class.

General notes about the "engine":

* Physics implemented with box2d
* Audio implemented with Irrklang
* All objects on the heap get instantiated through factory methods in the memory
  manager. This keeps track of allocated objects and destroys them on program
  exit. Eventually this would be upgraded to allocate memory more efficiently.
* Window is provided with glfw.
* Game input is loaded from JSON files.
* Meshes are loaded from JSON files.
* Most objects are associated with a Level class. The idea of this is that you
  are able to destroy and create a new level between level transitions.

I started following Sparky tutorial (did about 7 videos?) but at this point I 
left it and tried to fuse what i'd done with some classes from nclgl. The rest
of the engine I did myself. I know it's awful, however I had no idea how to 
make a game engine so the result is a mish mash of failed attempts at achieving 
things and trying OTHER things. If i did it again, I would have implemented it
completely differently.

There are A LOT of static pointers. Again, a lot of this was done to fix circular
references until I could figure out a better way - which I never did. Oh well!

The game demo:
Obviously not finished, just shows that most functionality of the engine is at
least hanging on by a thread. Use keys W,A,D to nagivate to the GOAL, at which
point the level will exit gracefully.

*//////////////////////////////////////////////////////////////////////////////

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <time.h>
#include <math.h>
#include <Box2D/Box2D.h>
#include "../engine-core/src/graphics/GameManager.h"
#include "../engine-common/src/graphics/Shader.h"
#include "../../../engine-physics/src/Physics.h"
#include "../engine-common/src/graphics/Texture.h"
#include "src/input/GameInput.h"
#include "src/memory/GameMemoryManager.h"
#include "../engine-common/src/graphics/RenderObject.h"
#include "../engine-common/src/graphics/Renderer.h"
#include "../engine-common/src/graphics/Mesh.h"
#include "src/entities/PlayerEntity.h"
#include "../engine-io/src/io/Loader.h"
#include "src/game/GameLogic.h"

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
	GameMemoryManager* memory = new GameMemoryManager();
	Physics* physics = new Physics(-0.0001f);
	GameInput* input = new GameInput(audio);
	BaseLogic* logic = new GameLogic(memory, physics, input, audio);
	Renderer* renderer = new Renderer();
	GameManager* g = new GameManager(GameManagerParams{ memory, input, logic, audio, physics, renderer, gameData.get("title", "Default Title").asString(), gameData.get("width", 1024).asInt(), gameData.get("height", 768).asInt() });

	// For each level in JSON
	for (unsigned int level = 0; level < gameData["levels"].size(); level++) {

		// Create a new Level
		Level* lvl = memory->createLevel(LevelParams{renderer});
		Level::LevelStack.push(lvl); // push this level?
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
				cout << "Mesh problem!" << endl;
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
		for (unsigned int i = 0; i < gameData["levels"][level]["entities"].size(); i++) {

			Json::Value jsonEntity = gameData["levels"][level]["entities"][i];
			Json::Value jsonCollision = jsonEntity["collision"];
			Mesh* m = meshes->at(jsonEntity["mesh"].asString());
			Shader* s = shaders->at(jsonEntity["shader"].asString());

			// create entity
			Entity* e = nullptr;

			// box2d
			b2BodyDef def;
			def.type = (jsonEntity["dynamic"].asBool() ? b2_dynamicBody : b2_staticBody);
			def.angle = jsonEntity["rotation"].asFloat() * ( (float)3.14159 / (float)180);
			def.linearVelocity = b2Vec2(jsonEntity["velocity"][0].asFloat(), jsonEntity["velocity"][1].asFloat());
			def.fixedRotation = true;
			def.position.Set(jsonEntity["position"][0].asFloat(), jsonEntity["position"][1].asFloat());

			// create polygon shape
			b2PolygonShape shape;
			shape.SetAsBox(jsonCollision["width"].asFloat(), jsonCollision["height"].asFloat());
			
			string categoryString = jsonEntity["category"].asString();
			EntityCategory category = EC_NONE;
			if (categoryString == "player") category = EC_PLAYER;
			else if (categoryString == "platform") category = EC_PLATFORM;
			else if (categoryString == "exit") category = EC_EXIT;
			else if (categoryString == "none") category = EC_NONE;

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
					category,
					jsonEntity["hasPhysics"].asBool(),
					def,
					shape
				});
			else if (jsonEntity["type"].asString() == "player")
				e = memory->createPlayerEntity(PlayerEntityParams{
				vec3(jsonEntity["position"][0].asFloat(), jsonEntity["position"][1].asFloat(), jsonEntity["position"][2].asFloat()),
				vec3(jsonEntity["velocity"][0].asFloat(), jsonEntity["velocity"][1].asFloat(), jsonEntity["velocity"][2].asFloat()),
					vec3(jsonEntity["acceleration"][0].asFloat(), jsonEntity["acceleration"][1].asFloat(), jsonEntity["acceleration"][2].asFloat()),
					jsonEntity["rotation"].asFloat(),
					jsonEntity["mass"].asFloat(),
					m,
					s,
					jsonEntity["title"].asString(),
					category,
					jsonEntity["hasPhysics"].asBool(),
					def,
					shape
			});
			else {
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