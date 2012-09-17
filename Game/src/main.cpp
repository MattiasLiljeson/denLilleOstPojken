#include "DxContext.h"
#include "GlContext.h"
#include "WinTimer.h"

GLboolean load(string path);

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	IOContext* gl = new GlContext(800, 600);
	IOContext* dx = new DxContext(hInstance, 800, 600);

	gl->setWindowPosition(50, 50);
	dx->setWindowPosition(900, 50);

	if (!gl->isInitialized() || !dx->isInitialized())
	{
		delete gl;
		delete dx;
		return 1;
	}

	Timer* t = new WinTimer();
	t->start();
	while (gl->isRunning() && dx->isRunning())
	{
		t->tick();
		float dt = (float)t->getDeltaTime();
		gl->update(dt);
		dx->update(dt);
		gl->draw(dt);
		dx->draw(dt);
	}
	delete t;
	delete gl;
	delete dx;
	return 0;
}

GLboolean load(string path)
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
 
    // allocate a texture name
	GLuint texture;
	glGenTextures(1, &texture);
 
	// select our current texture
	glBindTexture(GL_TEXTURE_2D, texture);
 
	// select modulate to mix texture with color for shading
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL);
 
	// when texture area is small, bilinear filter the closest mipmap
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	// when texture area is large, bilinear filter the first mipmap
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 
	// texture should tile
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
 
	// build our texture
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);

	return TRUE;


	/*glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);*/



	/*size.x = decoder.getWidth();
	size.y = decoder.getHeight();
	imageSize = image.size();
	colorDepth = decoder.getBpp();
	format = GL_RGBA;
	type = GL_UNSIGNED_BYTE;*/
	/*GLubyte* pixmap = new GLubyte[image.size()];
	
	//
	// Flip and invert the PNG image since OpenGL likes to load everything
	// backwards from what is considered normal!
	//
	unsigned char *imagePtr = &image[0];
	int halfTheHeightInPixels = height / 2;
	int heightInPixels = height;
	
	// Assuming RGBA for 4 components per pixel.
	int numColorComponents = 4;
	// Assuming each color component is an unsigned char.
	int widthInChars = width * numColorComponents;
	unsigned char *top = NULL;

	unsigned char *bottom = NULL;
	unsigned char temp = 0;
	for( int h = 0; h < halfTheHeightInPixels; ++h )

	{

		top = imagePtr + h * widthInChars;
		bottom = imagePtr + (heightInPixels - h - 1) * widthInChars;
		for( int w = 0; w < widthInChars; ++w )
		{

			// Swap the chars around.
			temp = *top;
			*top = *bottom;
			*bottom = temp;
			++top;
			++bottom;
		}
	}
	
	unsigned int c=0;
	for (unsigned int x = 0; x < width; x++)
	{
		for (unsigned int y=0; y< height; y++)
		{
			for (unsigned int co=0; co<numColorComponents; co++)
				((GLubyte*)pixmap)[c++]=image[c];
		}
	}

	return TRUE;*/
}