

#include <IOContext.h>
#include <DxContext.h>
#include <GlContext.h>
#include <WinTimer.h>
#include <LinTimer.h>
#include <Game.h>

int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,
				   int nCmdShow)
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	IOContext* context = new DxContext(hInstance, 400, 400);
	context->setWindowSize(800, 600);

	context->setWindowPosition(50, 50);

	if (!context->isInitialized())
	{
		delete context;
		return 1;
	}

	Timer* timer = new WinTimer();

	Game* game = new Game(timer, context);

	game->run();

	/*
	timer->start();
	while (context->isRunning())
	{
		timer->tick();
		float dt = (float)timer->getDeltaTime();
		context->update(dt);
		context->draw(dt);

		if (context->getInput().keys[InputInfo::ESC] == InputInfo::KEYDOWN)
		{
			break;
		}
	}
	*/

	delete timer;
	delete context;
	delete game;
	return 0;
}