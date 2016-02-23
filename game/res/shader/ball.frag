#version 150 core

uniform vec2 light_pos;
uniform vec4 col;

in Vertex{
	vec4 position;
	vec2 texCoord;
	vec4 colour;
} IN;

out vec4 gl_FragColor;

void main(void)	{
	float intensity = 1.0 / length(IN.position.xy - light_pos);
	gl_FragColor = col; //IN.colour; // * intensity;
}