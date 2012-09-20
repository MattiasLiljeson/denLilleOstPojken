cbuffer SpriteBuffer
{
    float2 CenterPosition;
    float2 HalfSize;
    float2 WindowSize;
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
    float3 pos = float3(pInput.position.x * HalfSize.x + CenterPosition.x, pInput.position.y * HalfSize.y + CenterPosition.y, pInput.position.z);
    vOut.position = float4(2 * ((pos.x) / WindowSize.x)-1, 2 *(pos.y / WindowSize.y) - 1, pos.z,1.0);

	//vOut.position = float4(pInput.position, 1.0f);
	vOut.texCoord = pInput.texCoord;
	return vOut;
}