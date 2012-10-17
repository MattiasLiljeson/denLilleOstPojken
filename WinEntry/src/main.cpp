//#define SCREEN_WIDTH 1920
//#define SCREEN_HEIGHT 1080
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
//#define SCREEN_WIDTH 500
//#define SCREEN_HEIGHT 1050

#define SCREEN_START_X 0
#define SCREEN_START_Y 0


#define USE_DIRECTX

#include <IOContext.h>
#include <Game.h>

#ifdef _WIN32

#ifdef USE_DIRECTX

// DirectX Windows
#include <DxContext.h>
#include <WinTimer.h>
#include <crtdbg.h>

int WINAPI WinMain(HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpCmdLine,
					int nCmdShow)
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	IOContext* context = new DxContext(hInstance, SCREEN_WIDTH, SCREEN_HEIGHT);
	
	//context->setWindowSize(800, 600);

	context->setWindowPosition(SCREEN_START_X, SCREEN_START_Y);

	if (!context->isInitialized())
	{
		delete context;
		return 1;
	}

	Timer* timer = new WinTimer();

	Game* game = new Game(timer, context);

	game->run();
	
	delete timer;
	delete context;
	delete game;
	return 0;
}
#else

// OpenGl Windows
#include <GlContext.h>
#include <WinTimer.h>

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	IOContext* context = new GlContext(SCREEN_WIDTH, SCREEN_HEIGHT);

//	context->setWindowSize(800, 600);

	context->setWindowPosition(SCREEN_START_X, SCREEN_START_Y);

	if (!context->isInitialized())
	{
		delete context;
		return 1;
	}

	Timer* timer = new WinTimer();

	Game* game = new Game(timer, context);

	game->run();


	delete timer;
	delete context;
	delete game;
	return 0;
}
	#endif
#else

// OpenGl Linux
#include <GlContext.h>
#include <LinTimer.h>

int main(int argc, char** argv)
{
	cout<<"Running Linux Build...";
	IOContext* context = new GlContext(SCREEN_WIDTH, SCREEN_HEIGHT);

//	context->setWindowSize(800, 600);

	context->setWindowPosition(SCREEN_START_X, SCREEN_START_Y);

	if (!context->isInitialized())
	{
		delete context;
		return 1;
	}

	Timer* timer = new LinTimer();

	Game* game = new Game(timer, context);

	game->run();


	delete timer;
	delete context;
	delete game;
	return 0;
}

#endif
