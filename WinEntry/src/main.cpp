#include <DxContext.h>
#include <WinTimer.h>
#include <IOContext.h>

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	IOContext* context = new DxContext(hInstance, 400, 400);

	context->setWindowSize(800, 600);

	context->setWindowPosition(900, 50);

	if (!context->isInitialized())
	{
		delete context;
		return 1;
	}

	Timer* t = new WinTimer();
	t->start();
	while (context->isRunning())
	{
		t->tick();
		float dt = (float)t->getDeltaTime();
		context->update(dt);
		context->draw(dt);

		if (context->getInput().keys[InputInfo::ESC] == InputInfo::KEYDOWN)
		{
			break;
		}
	}
	delete t;
	delete context;
	return 0;
}