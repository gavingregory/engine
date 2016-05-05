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

#define pi2_inv 0.159154943091895335768883763372
// extra changes by @xprogram

float border(vec2 uv, float thickness){
	uv = fract(uv - vec2(0.5));
	uv = min(uv, vec2(1.)-uv)*2.;
	return clamp(max(uv.x,uv.y)-1.+thickness,0.,1.)/thickness;
}

// complex multiplication
vec2 mult(vec2 a, vec2 b){
   return vec2( a.x*b.x - a.y*b.y, a.x*b.y + a.y*b.x);
}

vec2 div(vec2 numerator, vec2 denominator){
   return vec2( numerator.x*denominator.x + numerator.y*denominator.y,
                numerator.y*denominator.x - numerator.x*denominator.y)/
          vec2(denominator.x*denominator.x + denominator.y*denominator.y);
}

vec2 spiralzoom(vec2 domain, vec2 center, float n, float spiral_factor, float zoom_factor, vec2 pos){
	vec2 uv = domain - center * 4.0;
	float d = length(uv);
	return vec2( atan(uv.y, uv.x)*n*pi2_inv + log(d)*spiral_factor*cos(time), -log(d)*zoom_factor) + pos;
}

void main( void ) {
    vec2 resolution = vec2(200, 100);
	vec2 mouse = vec2(300, 300);
	vec2 uv = gl_FragCoord.xy / resolution.xy - mouse + 0.5;
	
	vec2 p1 = vec2(0.25+sin(time*.4)*.1, 0.3-cos(time*.5)*cos(time));
	vec2 p2 = vec2(0.75+sin(time)*.1, 0.7-cos(time)*.5);

	vec2 moebius = div(uv-p2, uv-p1);

	vec2 spiral_uv = spiralzoom(moebius,vec2(-0.2),1.,1.6,1.8,-vec2(0.5,0.5)*time*.6);
	vec2 spiral_uv2 = spiralzoom(moebius,vec2(-0.1),1.,1.9,1.2,-vec2(0.5,0.5)*time*.33);
	vec2 spiral_uv3 = spiralzoom(moebius,vec2(-0.1),1.,1.8,1.6,-vec2(0.5,0.5)*time*.38);

	gl_FragColor = vec4(border(spiral_uv,0.3), border(spiral_uv2,0.1) ,border(spiral_uv3,0.9),1.);

}


//float hash(float x)
//{
//	x *= float(__LINE__);
//	return fract(x*fract(x));
//}
//
//#define divide(what, part) floor(what * part) / part
//
//void main( void ) {
//    vec2 resolution = vec2(10,10);
//
//	vec2 uv = gl_FragCoord.xy / min(resolution.x , resolution.y);
//	uv = divide(uv, 25.0);
//	float h = hash(uv.x+hash(uv.y)+fract(time));
//	
//	gl_FragColor = vec4(h);
//	//vec2 position = ((gl_FragCoord.xy / resolution.xy) * 2. - 1.) * vec2(resolution.x / resolution.y, 1.0);
//	//
//	//float d = abs(0.1 + length(position) - 0.5 * abs(sin(time))) * 5.0;
//	//float e = abs(0.1 + length(position) - 0.5 * abs(sin(time * 0.5 - 2.))) * 5.0;
//	//
//	//gl_FragColor += vec4(0.1/d, 0.1 / d, 0.2 / d, 1);
//	//gl_FragColor += vec4(0.2/e, 0.1 / e, 0.1 / e, 1);
//}