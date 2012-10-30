#version 140
in vec3 Pos;
in vec2 TexCoord;
uniform float bwFraction;
uniform float fadeToBlack;
out vec4 FragColor;

uniform sampler2D gSampler;

void main()
{
     vec4 diffuseTexel = texture2D( gSampler, TexCoord );

     FragColor = diffuseTexel;
     if ( FragColor.a < 0.05f)
        discard;
		
	float value = (FragColor.x + FragColor.y + FragColor.z) / 3; 
	vec4 bw = vec4(0, 0, 0, FragColor.a);
    bw.x = value;
    bw.y = value;
    bw.z = value;
	
	FragColor = bwFraction * bw + (1 - bwFraction) * FragColor;
	FragColor *= (1-fadeToBlack);
}