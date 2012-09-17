#ifndef DXSPRITE_H
#define DXSPRITE_H

#include "Utility.h"

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
	Vector2 CenterPosition;
	Vector2 HalfSize;
	Vector2 WindowSize;
	Vector2 Pad;
};

class DxSprite
{
private:
	ID3D11Device*				m_device;
	ID3D11DeviceContext*		m_deviceContext;
	ID3D11Buffer*				m_vb;
	ID3D11Buffer*				m_ib;

	VertexShaderData			m_vsd;
	PixelShaderData				m_psd;
	ID3D11InputLayout*			m_inputLayout;

	ID3D11Buffer*				m_buffer;
	ID3D11ShaderResourceView*	m_texture;

	SpriteBuffer				m_spriteData;

private:
	int initVB();
	int initIB();
	int initShader();
public:
	DxSprite(ID3D11Device* p_device, ID3D11DeviceContext* p_deviceContext);
	virtual ~DxSprite();
	void setPosition(float p_positionX, float p_positionY);
	void draw();
};

#endif