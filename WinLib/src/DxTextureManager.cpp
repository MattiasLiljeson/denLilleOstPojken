#include "DxTextureManager.h"

DxTextureManager::DxTextureManager(ID3D11Device* p_device)
{
	m_initialized = false;
	m_device = p_device;

}

DxTextureManager::~DxTextureManager()
{
	for(unsigned int i = 0; i < m_textures.size(); i++)
	{
		if(m_textures[i])
			delete m_textures[i];
	}
}

HRESULT DxTextureManager::addTexture(string p_filename)
{
	m_textures.push_back(NULL);

	HRESULT res = D3DX11CreateShaderResourceViewFromFile(m_device, 
		p_filename.c_str(), NULL, 0, &m_textures.back(), 0);

	return res;
}