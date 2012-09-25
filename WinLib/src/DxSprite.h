#ifndef DXSPRITE_H
#define DXSPRITE_H

#include "DxSpriteShader.h"
#include "SpriteInfo.h"

class DxContext;

class DxSprite
{
private:
	ID3D11Device*				m_device;
	ID3D11DeviceContext*		m_deviceContext;
	ID3D11Buffer*				m_vb;
	ID3D11Buffer*				m_ib;
	ID3D11ShaderResourceView*	m_texture;
	SpriteBuffer				m_spriteData;
	DxSpriteShader*				m_shader;
	DxContext*					m_context;
	SpriteInfo					m_spriteInfo;

	bool						m_initialized;

private:
	int initVB();
	int initIB();
public:
				DxSprite(ID3D11Device* p_device, ID3D11DeviceContext* 
					p_deviceContext, DxContext* p_context);
	virtual		~DxSprite();
	void		setPosition(float p_positionX, float p_positionY);
	void		draw();
	void		setSpriteInfo(SpriteInfo p_spriteInfo);
	bool		isInitialized();
};

#endif