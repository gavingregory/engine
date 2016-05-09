#version 150 core

uniform sampler2D tex;

uniform vec2 light_pos;
uniform vec4 col;
uniform float time;

in Vertex{
	vec4 position;
	vec2 texCoord;
	vec4 colour;
} IN;

out vec4 gl_FragColor;

void main( void ) {
	vec2 resolution = vec2(1600,1200);
	vec2 pos = ((gl_FragCoord.xy / resolution.xy) * 2. - 1.) * vec2(resolution.x / resolution.y, 1.0);
	
	float d = abs(0.1 + length(pos) - 0.5 * abs(sin(time - cos(time * 0.01) * 9.0 * length(pos)))) * 5.0;
	float e = abs(0.1 + length(pos) - 0.5 * abs(sin(time * 0.5 - 2.))) * 10.0;
	
	gl_FragColor += vec4(0.1/d, 0.1/d, 0.1/d, 1);
	gl_FragColor += vec4(0.2/e, 0.2/e, 0.2/e, 1);
}