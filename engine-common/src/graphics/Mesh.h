/******************************************************************************
Class:Mesh
Author:Rich Davison	<richard.davison4@newcastle.ac.uk>
Modified by Gavin Gregory
*//////////////////////////////////////////////////////////////////////////////

#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "../../../engine-io/src/io/Loader.h"
#include <vector>
#include <string>
#include <fstream>

using std::ifstream;
using std::string;

//A handy enumerator, to determine which member of the bufferObject array
//holds which data
enum MeshBuffer {
	VERTEX_BUFFER	= 0,
	COLOUR_BUFFER	= 1, 
	TEXTURE_BUFFER	= 2,
	NORMAL_BUFFER	= 3, 
	TANGENT_BUFFER	= 4,
	INDEX_BUFFER	= 5,
	MAX_BUFFER      = 6
};

class Mesh	{
public:
	Mesh();
	virtual ~Mesh();

	virtual void Draw();
	void GenerateNormals();

	static Mesh* GenerateTriangle();
	static Mesh* GenerateQuad(const float width, const float height, const glm::vec4 colour);
	static Mesh* GenerateCircle(const float r, const int count, const glm::vec4 colour);
	static Mesh* LoadMeshFile(const string &filename);

	GLuint	type;	//Primitive type for this mesh (GL_TRIANGLES...etc)

protected:
	//Buffers all VBO data into graphics memory. Required before drawing!
	void	BufferData();

	//VAO for this mesh
	GLuint	arrayObject;
	//VBOs for this mesh
	GLuint	bufferObject[MAX_BUFFER];
	//Number of vertices for this mesh
	GLuint	numVertices;
	// Normal buffer
	GLuint normalBuffer;

	//Number of indices for this mesh
	GLuint			numIndices;

	//Pointer to vertex position attribute data (badly named...?)
	glm::vec3*		vertices;
	//Pointer to vertex colour attribute data
	glm::vec4*		colours;
	//Pointer to vertex texture coordinate attribute data
	glm::vec2*		textureCoords;
	//Pointer to vertex normals attribute data
	glm::vec3*		normals;
	//Pointer to vertex tangents attribute data
	glm::vec3*		tangents;
	//Pointer to vertex indices attribute data
	unsigned int*	indices;
};

