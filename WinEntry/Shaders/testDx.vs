cbuffer SpriteBuffer
{
    float3 CenterPosition;
	float pad;
    float2 HalfSize;
    float2 WindowSize;
	float4 TextureRect;
};

struct VIn
{
	float3 position : POSITION;
	float2 texCoord : TEXCOORD; 
};
struct VOut
{
    float4 position     : SV_POSITION;
	float2 texCoord     : TEXCOORD;
};

VOut VShader(VIn pInput)
{
	VOut vOut;
    float3 pos = float3(pInput.position.x * HalfSize.x + CenterPosition.x,
		pInput.position.y * HalfSize.y + CenterPosition.y,
		0.9999f - CenterPosition.z); // 0.9999 so that z can be 0.0
		vOut.position = float4(2 * ((pos.x) / WindowSize.x)-1, 2 *(pos.y / WindowSize.y) - 1, pos.z,1.0);

	//vOut.position = float4(pInput.position, 1.0f);
	
	// Translate texture rect boundaries to proper texCoord
	// texture rect contains values between 0 and 1
	vOut.texCoord = TextureRect.xy + TextureRect.zw * pInput.texCoord;
	
	//vOut.texCoord = pInput.texCoord;
	return vOut;
}