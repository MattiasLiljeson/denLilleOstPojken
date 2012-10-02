#ifndef DXSPRITESHADER_H
#define DXSPRITESHADER_H

#include "DxUtility.h"

struct VertexShaderData
{
	ID3D10Blob* CompiledData;
	ID3D11VertexShader* Data;
};

struct PixelShaderData
{
	ID3D10Blob* CompiledData;
	ID3D11PixelShader* Data;
};

struct SpriteBuffer
{
	Vector3 CenterPosition;
	float pad;
	Vector2 HalfSize;
	Vector2 WindowSize;
};

class DxSpriteShader
{
private:
	ID3D11Device*				m_device;
	ID3D11DeviceContext*		m_deviceContext;
	VertexShaderData			m_vsd;
	PixelShaderData				m_psd;
	ID3D11InputLayout*			m_inputLayout;
	ID3D11Buffer*				m_buffer;
	bool						m_initialized;
public:
						DxSpriteShader(ID3D11Device* p_device, 
							ID3D11DeviceContext* p_deviceContext);
	virtual				~DxSpriteShader();
	void				setBuffer(SpriteBuffer p_buffer, 
							ID3D11ShaderResourceView* p_texture);
	VertexShaderData	getVertexShader();
	PixelShaderData		getPixelShader();
	ID3D11InputLayout*	getInputLayout();
	bool				isInitialized();
};

#endif