#include "GlSprite.h"

GlSprite::GlSprite()
{
	initializeShaders();
	initializeGeometry();
	
	m_positionX = 0;
	m_positionY = 0;
	load("LogoGL.png");
	m_sampler = glGetUniformLocation(m_shader, "gSampler");
}
char* GlSprite::readShader(char* p_path)
{
    FILE* file;
    long length;
 
	//Open file for binary reading
    file = fopen(p_path, "rb");
    if (!file)
        return NULL;

	//Determine the size of the file
    fseek(file, 0, SEEK_END);
    length = ftell(file);

	//Allocate a buffer for the data
    char* data = (char*)malloc(length+1);

	//Read the file into the data buffer
    fseek(file, 0, SEEK_SET);
    fread(data, length, 1, file);
    data[length] = 0;

	//Close the file
	fclose(file);
 
    return data;
}
int GlSprite::initializeShaders()
{
	//Variables holding shader data
	GLuint vertexShader, fragmentShader;
	GLint vsCompiled, fsCompiled, linked;

	//Load the shader code
	const char* vsCode = readShader("testGL.vert");
	const char* fsCode = readShader("testGL.frag");

	if (!vsCode || !fsCode)
		return 1;

	//Create the shaders
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//Initialize and compile the shaders with the given source
	glShaderSource(vertexShader, 1, (const GLchar**)&vsCode, NULL);
	glShaderSource(fragmentShader, 1, (const GLchar**)&fsCode, NULL);	
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, (GLint*)&vsCompiled);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, (GLint*)&fsCompiled);

	delete[] vsCode;
	delete[] fsCode;

	if (!vsCompiled || !fsCompiled)
		return 1;

	//Create the combined shader program
	m_shader = glCreateProgram();
	glAttachShader(m_shader, vertexShader);
	glAttachShader(m_shader, fragmentShader);
	
	glLinkProgram(m_shader);
	glGetProgramiv(m_shader,GL_LINK_STATUS,&linked);
	if (!linked)
		return 1;

	//Get a reference to the vertex index used as input to the vertex shader.
	//This is needed by the IA stage.
	m_vertexIndex = glGetAttribLocation(m_shader, "MCVertex");
	m_texCoordIndex = glGetAttribLocation(m_shader, "MCTexCoord");
	m_CenterPositionIndex = glGetUniformLocation(m_shader, "CenterPosition");
	m_sampler = glGetUniformLocation(m_shader, "gSampler");

	return 0;
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(SpriteVertex)*6, vertices, GL_STATIC_DRAW);

	//Map the CPU data to the shader data for the input assembler.
	glVertexAttribPointer (m_vertexIndex, 3, GL_FLOAT, GL_FALSE, sizeof(SpriteVertex), (void*)offsetof(SpriteVertex,x));
	glVertexAttribPointer (m_texCoordIndex, 2, GL_FLOAT, GL_FALSE, sizeof(SpriteVertex), (void*)offsetof(SpriteVertex,s));
	return 0;
}
void GlSprite::setPosition(float p_positionX, float p_positionY)
{
	m_positionX = p_positionX;
	m_positionY = p_positionY;
}
int GlSprite::draw()
{
	glUseProgram(m_shader);
	 
	
	glUniform2f(m_CenterPositionIndex, m_positionX, m_positionY);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glEnableVertexAttribArray(m_vertexIndex);
	glEnableVertexAttribArray(m_texCoordIndex);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(m_vertexIndex);
	glDisableVertexAttribArray(m_texCoordIndex);
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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	//free(data);
	return TRUE;
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