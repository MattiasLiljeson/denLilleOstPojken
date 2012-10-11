#version 140
uniform vec2 ScreenSize;
uniform vec2 HalfScale;
uniform vec4 CenterPosition;
uniform vec4 TextureRect;
in vec3 MCVertex;
in vec2 MCTexCoord;
out vec3 Pos;
out vec2 TexCoord;
void main()
{
	vec3 outvec;
    outvec = vec3(
		MCVertex.x * HalfScale.x + CenterPosition.x,
		MCVertex.y * HalfScale.y + CenterPosition.y,
		CenterPosition.z
	);
    gl_Position = vec4(
		2 * ((outvec.x) / ScreenSize.x)-1,
		2 *(outvec.y / ScreenSize.y) - 1,
		0.9999f - outvec.z,
		1.0f
		);
    Pos = vec3(gl_Position.x, gl_Position.y, gl_Position.z);
    TexCoord = TextureRect.xy + TextureRect.zw * MCTexCoord;
}