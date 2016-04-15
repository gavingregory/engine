#version 150 core

uniform vec3 light_src = vec3(0,0,300);
uniform vec3 camera_pos;

in Vertex{
	vec4 position;
	vec2 texCoord;
	vec4 colour;
	vec3 normal;
} IN;

void main(void)	{

	float lightRadius = 500.0;
	vec4 lightColour = vec4(1,1,1,1);

	vec3 incident = normalize(light_src - IN.position.xyz);
	vec3 viewDir = normalize(camera_pos - IN.position.xyz);
	vec3 halfDir = normalize(incident + viewDir);
	
	float dist = length ( light_src - IN.position.xyz);
	float atten = 1.0 - clamp ( dist / lightRadius , 0.0 , 1.0);
	float lambert = max (0.0 , dot ( incident , IN.normal ));
	float rFactor = max (0.0 , dot ( halfDir , IN.normal ));
	float sFactor = pow ( rFactor , 50.0 );
	//vec4 texCol = texture ( smileyTex , IN.texCoord );
	vec3 ambient = IN.colour.rgb * lightColour.rgb * 0.7;
	vec3 diffuse = IN.colour.rgb * lightColour.rgb * lambert * atten ;
	vec3 specular = lightColour.xyz * sFactor * atten ;
	gl_FragColor = vec4 ( ambient + diffuse + specular , IN.colour.a );
}
