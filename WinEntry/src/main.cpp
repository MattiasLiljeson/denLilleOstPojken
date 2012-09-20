
#include <IOContext.h>
#include <DxContext.h>
#include <GlContext.h>
#include <WinTimer.h>
#include <LinTimer.h>

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	IOContext* context2 = new GlContext(400, 400);
	IOContext* context = new DxContext(hInstance, 400, 400);
	context->setWindowSize(800, 600);
	context2->setWindowSize(800, 600);

	context->setWindowPosition(900, 50);
	context2->setWindowPosition(50, 50);

	if (!context->isInitialized() || !context2->isInitialized())
	{
		delete context;
		delete context2;
		return 1;
	}

	Timer* t = new WinTimer();
	t->start();
	while (context->isRunning() && context2->isRunning())
	{
		t->tick();
		float dt = (float)t->getDeltaTime();
		context->update(dt);
		context2->update(dt);
		context->draw(dt);
		context2->draw(dt);

		if (context->getInput().keys[InputInfo::ESC] == InputInfo::KEYDOWN)
		{
			break;
		}
		if (context2->getInput().keys[InputInfo::ESC] == InputInfo::KEYDOWN)
		{
			break;
		}
	}
	delete t;
	delete context;
	delete context2;
	return 0;
}