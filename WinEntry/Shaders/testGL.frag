#version 140
in vec3 Pos;
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D gSampler;

void main()
{
     vec4 diffuseTexel = texture2D( gSampler, TexCoord );

     FragColor = diffuseTexel;

     if ( FragColor.a < 0.05f)
        discard;
}

