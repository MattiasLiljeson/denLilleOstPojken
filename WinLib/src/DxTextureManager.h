#ifndef DXTEXTUREMANAGER_H
#define DXTEXTUREMANAGER_H

#include "DxUtility.h"
#include <vector>
#include <string>

using namespace std;

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

class DxTextureManager
{
private:
	vector<TextureWithName>				m_textures;
	ID3D11Device*						m_device;
	bool								m_initialized;
	
private:
	int loadTexture(string p_filePath, vector<TextureWithName>* p_textures);

public:
	DxTextureManager(ID3D11Device* p_device);
	~DxTextureManager();

	int getTexture(int p_textureIndex,
		ID3D11ShaderResourceView** out_textureResource);

	int getTexture(string p_filePath);
	int getTexture(string p_filePath,
		ID3D11ShaderResourceView** out_textureResource);

};

#endif