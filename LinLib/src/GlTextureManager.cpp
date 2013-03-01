#include "GlTextureManager.h"
#include "ExecutableDirectoryPath.h"
#include <stdio.h>

GlTextureManager::GlTextureManager()
{
}

GlTextureManager::~GlTextureManager()
{
	for(unsigned int i = 0; i < m_textures.size(); i++)
	{
		glDeleteTextures( 1, &m_textures[i].textureResource );
	}
}

int GlTextureManager::loadTexture(string p_filePath,
	vector<TextureWithName>* p_textures)
{
	int textureIndex = -1;

    std::string fullPath = addExecutableDirectoryPath(p_filePath.c_str());

	GLuint texture = 0;

	vector<unsigned char> rawImage;
	lodepng::State state;

    FILE* file;
    if (!(file = fopen(fullPath.c_str(), "r"))) {
        printf("Could not load texture: %s\n", fullPath.c_str());
    }
    fclose(file);

	lodepng::load_file(rawImage, fullPath);
	std::vector<unsigned char> image;

	unsigned int width = 0, height = 0, error = 0;
	error = lodepng::decode(image, width, height, state, rawImage);

	if (error)
	{
		const char* err = lodepng_error_text(error);
		textureIndex = -1;
	}
	else
	{
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, 
			GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		
		textureIndex = (int)m_textures.size();

		p_textures->push_back(TextureWithName(texture, p_filePath));
	}

	return textureIndex;
}

int GlTextureManager::getTexture(int p_textureIndex, GLuint* out_textureResource)
{
	int textureIndex = -1;

	if( p_textureIndex < (int)m_textures.size() )
	{
		*out_textureResource = m_textures[p_textureIndex].textureResource;

		textureIndex = p_textureIndex;
	}

	return textureIndex;
}

int GlTextureManager::getTexture(string p_filePath)
{
	return getTexture(p_filePath, NULL);
}

int GlTextureManager::getTexture(string p_filePath, GLuint* out_textureResource)
{
	int textureIndex = -1;

	for(int i = 0; i < (int)m_textures.size(); i++)
	{
		if( m_textures[i].textureName == p_filePath )
		{
			if( out_textureResource != NULL)
				*out_textureResource = m_textures[i].textureResource;

			textureIndex = i;
			break;
		}
	}

	if(textureIndex == -1)
		textureIndex = loadTexture(p_filePath, &m_textures);

	return textureIndex;
}