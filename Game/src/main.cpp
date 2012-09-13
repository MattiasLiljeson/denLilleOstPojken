#include "DxContext.h"
#include "GlContext.h"

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//DxContext g(hInstance, 800, 600);
	GlContext g(800, 600);

	while (g.isRunning())
	{
		g.update(0);
		g.draw(0);
	}
	return 0;
}