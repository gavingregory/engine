#version 150 core

uniform sampler2D miner;

uniform vec2 light_pos;
uniform vec4 col;

in Vertex{
	vec4 position;
	vec2 texCoord;
	vec4 colour;
} IN;

out vec4 gl_FragColor;

void main(void)	{
	vec4 texCol = texture ( miner , IN.texCoord );
	gl_FragColor = texCol;
}