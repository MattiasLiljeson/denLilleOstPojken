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
		if(m_textures[i].textureResource)
			m_textures[i].textureResource->Release();
	}
}

int DxTextureManager::loadTexture(string p_filePath)
{
	int textureIndex = -1;
	ID3D11ShaderResourceView* texture = NULL;

	HRESULT res = D3DX11CreateShaderResourceViewFromFile(m_device, 
		p_filePath.c_str(), NULL, 0, &texture, 0);

	if(res == S_OK)
	{
		m_textures.push_back(TextureWithName(texture, p_filePath));
		textureIndex = (int)m_textures.size() - 1;
	}

	return textureIndex;
}

int DxTextureManager::getTexture(int p_textureIndex,
	ID3D11ShaderResourceView** p_outTextureResource)
{
	int textureIndex = -1;

	if( p_textureIndex < (int)m_textures.size() )
	{
		*p_outTextureResource = m_textures[p_textureIndex].textureResource;

		textureIndex = p_textureIndex;
	}

	return textureIndex;
}

int DxTextureManager::getTexture(string p_filePath,
	ID3D11ShaderResourceView** p_outTextureResource)
{
	int textureIndex = -1;

	for(int i = 0; i < (int)m_textures.size(); i++)
	{
		if( m_textures[i].textureName == p_filePath )
		{
			*p_outTextureResource = m_textures[i].textureResource;

			textureIndex = i;
			break;
		}
	}

	if(textureIndex == -1)
		textureIndex = loadTexture(p_filePath);

	return textureIndex;
}

