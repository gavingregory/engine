#include "src/graphics/window.h"
#include "src/graphics/shader.h"

#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"

#include "src/graphics/Renderer2d.h"
#include "src/graphics/SimpleRenderer2d.h"
#include "src/graphics/BatchRenderer2D.h"

#include "src/graphics/StaticSprite.h"
#include "src/graphics/Sprite.h"

#include <time.h>

#define BATCH_RENDERER 1

int main()
{
	using namespace engine;
	using namespace graphics;

	Window window("Engine", 960, 540);
	// glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glm::mat4 ortho = glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("src/shaders/BasicVert.glsl", "src/shaders/BasicFrag.glsl");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);

	std::vector<Renderable2d*> sprites;

	srand(time(NULL));

	for (float y = 0; y < 9.0f; y += 0.05)
	{
		for (float x = 0; x < 16.0f; x += 0.05)
		{
			sprites.push_back(new
#if BATCH_RENDERER
				Sprite
#else
				StaticSprite
#endif
				(x, y, 0.04f, 0.04f, glm::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)
#if !BATCH_RENDERER
					, shader
#endif

					));
		}
	}


#if BATCH_RENDERER
	Sprite sprite(5, 5, 4, 4, glm::vec4(1, 0, 1, 1));
	Sprite sprite2(7, 1, 2, 3, glm::vec4(0.2f, 0, 1, 1));
	BatchRenderer2d renderer;
#else
	StaticSprite sprite(5, 5, 4, 4, glm::vec4(1, 0, 1, 1), shader);
	StaticSprite sprite2(7, 1, 2, 3, glm::vec4(0.2f, 0, 1, 1), shader);
	SimpleRenderer2d renderer;
#endif

	shader.setUniform2f("light_pos", glm::vec2(4.0f, 1.5f));
	shader.setUniform4f("colour", glm::vec4(0.2f, 0.3f, 0.8f, 1.0f));

	while (!window.closed())
	{
		window.clear();
		shader.setUniform2f("light_pos", glm::vec2((float)(window.getMouseX() * 16.0f / 960.0f), (float)(9.0f - window.getMouseY() * 9.0f / 540.0f)));
#if BATCH_RENDERER
		renderer.begin();
#endif
		for (int i = 0; i < sprites.size(); i++)
		{
			renderer.submit(sprites[i]);
		}
#if BATCH_RENDERER
		renderer.end();
#endif
		renderer.flush();
		printf("Sprites: %d\n", sprites.size());
		window.update();
	}

	return 0;
}