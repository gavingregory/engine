#version 150 core

uniform mat4 ml_matrix = mat4(1.0);
uniform mat4 vw_matrix = mat4(1.0); 
uniform mat4 pr_matrix; 

in vec3 position;
in vec2 texCoord;
in vec4 colour;

out Vertex{
	vec4 position;
	vec2 texCoord;
	vec4 colour;
} OUT;

void main(void)	{
	gl_Position = (pr_matrix * vw_matrix * ml_matrix) * vec4(position, 1.0);
	OUT.texCoord = texCoord;
	OUT.colour	 = colour;
	OUT.position = (pr_matrix * vw_matrix * ml_matrix) * vec4(position, 1.0);
}