#ifndef DXTEXTUREMANAGER_H
#define DXTEXTUREMANAGER_H

#include "DxUtility.h"
#include <vector>
#include <string>

using namespace std;

class DxTextureManager
{
private:
	struct TextureWithName
	{
	public:
		ID3D11ShaderResourceView*	textureResource;
		string						textureName;
		TextureWithName(){}
		TextureWithName(ID3D11ShaderResourceView* p_textureResource,
			string p_textureName)
		{
			textureResource = p_textureResource;
			textureName = p_textureName;
		}
	};

private:
	vector<TextureWithName>				m_textures;
	ID3D11Device*						m_device;
	bool								m_initialized;

public:
	DxTextureManager(ID3D11Device* p_device);
	~DxTextureManager();

	int addTexture(string p_filename);
	int getTexture(int p_textureIndex,
		ID3D11ShaderResourceView** p_outTextureResource);
	int getTexture(string p_textureName,
		ID3D11ShaderResourceView** p_outTextureResource);

};

#endif