#pragma once

#include <GL/glew.h>
#include <SOIL.h>
#include <string>

class Texture {
public:
	static GLuint Load(string path) {
		GLuint t = SOIL_load_OGL_texture(path.c_str(), 0, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
		glGenTextures(1, &t);
		if (t == 0) { cout << "Error loading texture " << path << " with SOIL."; }
		return t;
	}
};