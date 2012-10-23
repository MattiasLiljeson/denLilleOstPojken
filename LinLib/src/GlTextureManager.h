#ifndef GLTEXTUREMANAGER_H
#define GLTEXTUREMANAGER_H

#include <GL/glew.h>
#include <GL/glfw.h>

#ifdef _WIN32
#include <GL/wglew.h>
#endif

#include "LodePNG.h"
#include <vector>
#include <string>
#include "GlDebug.h"

using namespace std;

struct TextureWithName
{
	GLuint	textureResource;
	string	textureName;

	TextureWithName(){}
	TextureWithName(GLuint p_textureResource, string p_textureName)
	{
		textureResource = p_textureResource;
		textureName = p_textureName;
	}
};

class GlTextureManager
{
private:
	vector<TextureWithName> m_textures;
	bool m_initialized;

private:
	int loadTexture(string p_filePath, vector<TextureWithName>* p_textures);

public:
	GlTextureManager();
	~GlTextureManager();

	int getTexture(int p_textureIndex, GLuint* out_textureResource);

	int getTexture(string p_filePath);
	int getTexture(string p_filePath, GLuint* out_textureResource);
	
};

#endif
