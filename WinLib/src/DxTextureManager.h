#ifndef DXTEXTUREMANAGER_H
#define DXTEXTUREMANAGER_H

#include "DxUtility.h"
#include <vector>
#include <string>

using namespace std;

class DxTextureManager
{
private:
	vector<ID3D11ShaderResourceView*>	m_textures;
	ID3D11Device*						m_device;
	bool								m_initialized;

public:
	DxTextureManager(ID3D11Device* p_device);
	~DxTextureManager();

	HRESULT addTexture(string p_filename);


};

#endif