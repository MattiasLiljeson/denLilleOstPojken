#version 140
in vec3 Pos;
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D gSampler;

void main()
{
    //if ( TexCoord.x > 0.5f && TexCoord.y > 0.5f )
    //    FragColor = vec4( 0.0, 1.0, 0.0, 1.0 );
    //else if ( TexCoord.x > 0.5f )
    //    FragColor = vec4( 0.0, 0.0, 1.0, 1.0 );
    //else if ( TexCoord.y > 0.5f )
    //    FragColor = vec4( 1.0, 0.0, 0.0, 1.0 );
    //else
    //    FragColor = vec4( 1.0, 1.0, 0.0, 1.0 );
        
     vec4 diffuseTexel = texture2D( gSampler, TexCoord );
	 //diffuseTexel.rgb *= Pos.z;
     FragColor = diffuseTexel;
     // FragColor = vec4(1, 0, 0, 1); //DEBUG:
     if ( FragColor.a == 0 )
        FragColor = vec4( 0, 0, 0, 1 );
}
