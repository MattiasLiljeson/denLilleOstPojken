#include "GlSprite.h"
#include "GlContext.h"

GlSprite::GlSprite(GlContext* p_context)
{
	m_initialized	= false;
	m_context		= p_context;
	m_spriteShader	= new GlSpriteShader();
	if (!m_spriteShader->isInitialized())
		return;
	if (initializeGeometry() != GAME_OK)
		return;
	
	m_positionX = 0;
	m_positionY = 0;
	load("..\\Textures\\LogoGL.png");
	m_initialized = true;
}
GlSprite::~GlSprite()
{
	delete m_spriteShader;
}
int GlSprite::initializeGeometry()
{
	SpriteVertex vertices[] = {  
		SpriteVertex(-1.0f,  1.0f, 0.0f, 0.0f, 0.0f),  
		SpriteVertex(-1.0f, -1.0f, 0.0f, 0.0f, 1.0f),
		SpriteVertex(1.0f, -1.0f, 0.0f, 1.0f, 1.0f),
		SpriteVertex(1.0f, -1.0f, 0.0f, 1.0f, 1.0f),
		SpriteVertex(1.0f, 1.0f, 0.0f, 1.0f, 0.0f),
		SpriteVertex(-1.0f, 1.0f, 0.0f, 0.0f, 0.0f),
						};

	//Create a buffer and add the vertices to it.
	//Buffer must be bound when the vertices are added.
	glGenBuffers(1,&m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SpriteVertex)*6, 
		vertices, GL_STATIC_DRAW);

	//Map the CPU data to the shader data for the input assembler.
	glVertexAttribPointer (m_spriteShader->getPostionIndex(), 3, GL_FLOAT, 
		GL_FALSE, sizeof(SpriteVertex), (void*)offsetof(SpriteVertex,x));
	glVertexAttribPointer (m_spriteShader->getTexCoordIndex(), 2, GL_FLOAT, 
		GL_FALSE, sizeof(SpriteVertex), (void*)offsetof(SpriteVertex,s));
	return 0;
}
void GlSprite::setPosition(float p_positionX, float p_positionY)
{
	m_positionX = p_positionX;
	m_positionY = p_positionY;
}
int GlSprite::draw()
{
	glUseProgram(m_spriteShader->getID());
	 
	
	glUniform2f(m_spriteShader->getCenterPositionConstant(), 
		m_spriteInfo.transformInfo.translation[TransformInfo::X],
		m_spriteInfo.transformInfo.translation[TransformInfo::Y]
	);
	glUniform2f(m_spriteShader->getHalfScaleConstant(),
		m_spriteInfo.transformInfo.scale[TransformInfo::X] / 2,
		m_spriteInfo.transformInfo.scale[TransformInfo::Y] / 2
	);
	glUniform2f(m_spriteShader->getScreenSizeConstant(), 
		(GLfloat)m_context->getScreenWidth(), (GLfloat)m_context->getScreenHeight());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glEnableVertexAttribArray(m_spriteShader->getPostionIndex());
	glEnableVertexAttribArray(m_spriteShader->getTexCoordIndex());
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(m_spriteShader->getPostionIndex());
	glDisableVertexAttribArray(m_spriteShader->getTexCoordIndex());
	return 0;
}

GLboolean GlSprite::load(string path)
{
	vector<unsigned char> rawImage;
	lodepng::State state;

	lodepng::load_file(rawImage, path);
	std::vector<unsigned char> image;

	unsigned width, height;
	unsigned error = lodepng::decode(image, width, height, state, rawImage);

	if (error)
	{
		const char* err = lodepng_error_text(error);
		return FALSE;
	}

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, 
		GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	//free(data);
	return TRUE;
}
bool GlSprite::isInitialized()
{
	return m_initialized;
}

void GlSprite::setSpriteInfo( SpriteInfo p_spriteInfo )
{
	m_spriteInfo = p_spriteInfo;
}


	/*int width = 20;
	int height = 20;
	GLubyte* data = (GLubyte*)malloc( sizeof(GLubyte) * width * height * 3);
	memset(data, 0, sizeof(GLubyte) * width * height * 3);
	for (int i = 0; i < height; ++i ) {
	for (int j = 0; j < width; ++j ) {
		int pixelIdx = i*width*3 + j*3;
		data[pixelIdx+0] = 255; //bitmap->buffer[i*bitmap->width + j];
		data[pixelIdx+1] = 255; //bitmap->buffer[i*bitmap->width + j];
		data[pixelIdx+2] = 0; //bitmap->buffer[i*bitmap->width + j];
	}
	}*/