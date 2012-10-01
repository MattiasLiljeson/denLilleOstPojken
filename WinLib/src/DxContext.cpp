#include "DxContext.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, 
	WPARAM wParam, LPARAM lParam)
{
	static DxContext* dxContext = 0;
	switch(message)
	{
		//Create a reference to the dx context so that 
		//future messages can be passed to it.
		case WM_CREATE:
		{
			CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
			dxContext = (DxContext*)cs->lpCreateParams;
			return 0;
		}
		break;
	}

	if (dxContext)
		return dxContext->handleWindowMessages(message, wParam, lParam);
	else
		return DefWindowProc (hWnd, message, wParam, lParam);
}

DxContext::DxContext(HINSTANCE pInstanceHandle, 
	int p_screenWidth, int p_screenHeight) : IOContext()
{
	m_screenWidth			= p_screenWidth;
	m_screenHeight			= p_screenHeight;
	m_instanceHandle		= pInstanceHandle;
	m_swapChain				= NULL;
	m_device				= NULL;
	m_deviceContext			= NULL; 
	m_windowHandle			= 0;

	m_depthStencilBuffer	= NULL;
	m_backBuffer			= NULL;
	m_depthStencilView		= NULL;
	m_depthStencilState		= NULL;
	m_rasterState			= NULL;
	m_totalGameTime			= 0;
	m_resizing				= false;
	m_initialized			= false;

	//Initialize window and directx functionality
	if (initializeWindow() == GAME_FAIL)
		return;
	if (initializeSwapChain() == GAME_FAIL)
		return;
	if (initializeBackBuffer() == GAME_FAIL)
		return;
	if (initializeDepthStencilBuffer() == GAME_FAIL)
		return;
	if (initializeDepthStencilState() == GAME_FAIL)
		return;
	if (initializeDepthStencilView() == GAME_FAIL)
		return;
	if (initializeRasterizerState() == GAME_FAIL)
		return;
	if (initializeViewport() == GAME_FAIL)
		return;
	if(loadAllTextures() == GAME_FAIL)
		return;


	//Map Windows key IDs to our key ID system.
	m_keyMappings[InputInfo::ESC]	= VK_ESCAPE;
	m_keyMappings[InputInfo::LEFT]	= VK_LEFT;
	m_keyMappings[InputInfo::RIGHT] = VK_RIGHT;
	m_keyMappings[InputInfo::UP]	= VK_UP;
	m_keyMappings[InputInfo::DOWN]	= VK_DOWN;
	m_keyMappings[InputInfo::SPACE] = VK_SPACE;

	//Temporary code to test sprite creation
	m_mascot = new DxSprite(m_device, m_deviceContext, this);

	if (!m_mascot->isInitialized())
		return;

	posX = 400;
	posY = 300;
	//End Temporary

	m_initialized = true;
}
DxContext::~DxContext()
{
	//Destroy the window and free allocated resources
	DestroyWindow(m_windowHandle);
	m_swapChain->SetFullscreenState(FALSE, NULL);
	m_swapChain->Release();
	m_device->Release();
	m_deviceContext->Release();
	m_backBuffer->Release();
	m_depthStencilView->Release();
	m_depthStencilState->Release();
	m_rasterState->Release();
	delete m_mascot;
	delete m_textureManager;
}
int DxContext::initializeWindow()
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = m_instanceHandle;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = "WindowClass";
	RegisterClassEx(&wc);
	RECT wr = {0, 0, getScreenWidth(), getScreenHeight()};
	
	if (AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE) == 0)
		return GAME_FAIL;

	m_windowHandle = CreateWindowEx(NULL,
						  "WindowClass",
						  "Den Lille OstPojken",
						  WS_OVERLAPPEDWINDOW,
						  100,
						  100,
						  wr.right - wr.left,
						  wr.bottom - wr.top,
						  NULL,
						  NULL,
						  m_instanceHandle,
						  this);

	if (!m_windowHandle)
		return GAME_FAIL;

	ShowWindow(m_windowHandle, SW_SHOW);
	return GAME_OK;
}
int DxContext::initializeSwapChain()
{
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferCount					= 1;
	scd.BufferDesc.Format			= DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.Width			= getScreenWidth();
	scd.BufferDesc.Height			= getScreenHeight();
	scd.BufferUsage					= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow				= m_windowHandle;
	scd.SampleDesc.Count			= 1;
	scd.SampleDesc.Quality			= 0;
	scd.Windowed					= TRUE;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferDesc.Scaling			= DXGI_MODE_SCALING_UNSPECIFIED;
	scd.SwapEffect					= DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags						= DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	D3D_FEATURE_LEVEL featureLevels[] = {D3D_FEATURE_LEVEL_11_0, 
		D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0};

	if (D3D11CreateDeviceAndSwapChain(NULL,
								  D3D_DRIVER_TYPE_HARDWARE,
								  NULL,
								  NULL,
								  featureLevels,
								  3,
								  D3D11_SDK_VERSION,
								  &scd,
								  &m_swapChain,
								  &m_device,
								  NULL,
								  &m_deviceContext) != S_OK)
	{
		return GAME_FAIL;
	}

	return GAME_OK;
}
int DxContext::initializeBackBuffer()
{
	ID3D11Texture2D *BackBuffer;
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&BackBuffer);

	if (!BackBuffer)
		return GAME_FAIL;

	if (m_device->CreateRenderTargetView(BackBuffer, NULL, &m_backBuffer) 
		!= S_OK)
	{
		return GAME_FAIL;
	}
	BackBuffer->Release();
	return GAME_OK;
}
int DxContext::initializeDepthStencilBuffer()
{
	// Create the depth/stencil buffer.
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
	depthBufferDesc.Width     = getScreenWidth();
	depthBufferDesc.Height    = getScreenHeight();
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count   = 1; // multisampling must match
	depthBufferDesc.SampleDesc.Quality = 0; // swap chain values.
	depthBufferDesc.Usage          = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags      = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0; 
	depthBufferDesc.MiscFlags      = 0;

	int result = m_device->CreateTexture2D(&depthBufferDesc, 0, 
		&m_depthStencilBuffer);

	if(FAILED(result))
	{
		return GAME_FAIL;
	}
	return GAME_OK;
}
int DxContext::initializeDepthStencilState()
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	// Set up the description of the stencil state.
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;


	int result = m_device->CreateDepthStencilState(&depthStencilDesc, 
		&m_depthStencilState);

	if(FAILED(result))
	{
		return GAME_FAIL;
	}
	m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);
	return GAME_OK;
}
int DxContext::initializeDepthStencilView()
{
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	// Set up the depth stencil view description.
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	int result = m_device->CreateDepthStencilView(m_depthStencilBuffer,
		&depthStencilViewDesc, &m_depthStencilView);

	if(FAILED(result))
	{
		return GAME_FAIL;
	}

	m_deviceContext->OMSetRenderTargets(1, &m_backBuffer, m_depthStencilView);
	return GAME_OK;
}
int DxContext::initializeRasterizerState()
{
	// Setup the raster description which will determine 
	//how and what polygons will be drawn.
	D3D11_RASTERIZER_DESC rasterDesc;
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	// Create the rasterizer state from the description we just filled out.
	int result = m_device->CreateRasterizerState(&rasterDesc, &m_rasterState);
	if(FAILED(result))
	{
		return GAME_FAIL;
	}

	// Now set the rasterizer state.
	m_deviceContext->RSSetState(m_rasterState);
	return GAME_OK;
}
int DxContext::initializeViewport()
{
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = (float)getScreenWidth();
	viewport.Height = (float)getScreenHeight();
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	m_deviceContext->RSSetViewports(1, &viewport);

	return GAME_OK;
}
bool DxContext::isInitialized() const
{
	return m_initialized;
}
int DxContext::setWindowPosition(int p_x, int p_y)
{
	if (SetWindowPos(m_windowHandle, HWND_TOPMOST, 
		p_x, p_y, 0, 0, SWP_NOSIZE) == 0)
	{
		return GAME_FAIL;
	}
	return GAME_OK;
}
int DxContext::setWindowSize(int p_width, int p_height)
{
	RECT wr = {0, 0, p_width, p_height};  
	if (AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE) == 0)
	{
		return GAME_FAIL;
	}
	if (SetWindowPos(m_windowHandle, HWND_TOPMOST, 0, 0, 
		wr.right - wr.left, wr.bottom-wr.top, SWP_NOMOVE) == 0)
	{
		return GAME_FAIL;
	}
	return GAME_OK;
}
int DxContext::resize()
{
	m_initialized = false; 
	RECT wndRect;
	GetClientRect(m_windowHandle, &wndRect);
	m_screenWidth = wndRect.right - wndRect.left;
	m_screenHeight = wndRect.bottom - wndRect.top;
	m_backBuffer->Release();
	m_depthStencilView->Release();
	m_depthStencilBuffer->Release();

	m_swapChain->ResizeBuffers(1, getScreenWidth(), getScreenHeight(), 
		DXGI_FORMAT_R8G8B8A8_UNORM, 0);

	initializeBackBuffer();
	initializeDepthStencilBuffer();
	initializeDepthStencilView();
	initializeViewport();
	m_resizing = false;
	m_initialized = true;
	return GAME_OK;
}
int DxContext::update(float p_dt)
{
	MSG msg;
	while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (!m_resizing)
	{
		m_totalGameTime += p_dt;
		for (int i = 0; i < InputInfo::NUM_KEYS; i++)
		{
			if (GetAsyncKeyState (m_keyMappings[i]) 
				&& GetFocus() == m_windowHandle)
			{
				if (m_input.keys[i] == InputInfo::KEYPRESSED || 
					m_input.keys[i] == InputInfo::KEYDOWN)
				{
					m_input.keys[i] = InputInfo::KEYDOWN;
				}
				else
				{
					m_input.keys[i] = InputInfo::KEYPRESSED;
				}
			}
			else
			{
				if (m_input.keys[i] == InputInfo::KEYPRESSED || 
					m_input.keys[i] == InputInfo::KEYDOWN)
				{
					m_input.keys[i] = InputInfo::KEYRELEASED;
				}
				else
				{
					m_input.keys[i] = InputInfo::KEYUP;
				}
			}
		}

		if (m_totalGameTime - (int)m_totalGameTime < p_dt)
		{
			stringstream ss;
			ss << (int)(1.0f / p_dt);
			string s = ss.str();
			s = "DirectX - " + s + " FPS";
			SetWindowText(m_windowHandle, s.c_str());
		}


		//if (m_input.keys[InputInfo::LEFT] == InputInfo::KEYDOWN)
		//	posX -= 50 * p_dt;
		//else if (m_input.keys[InputInfo::RIGHT] == InputInfo::KEYDOWN)
		//	posX += 50 * p_dt;
		//if (m_input.keys[InputInfo::DOWN] == InputInfo::KEYDOWN)
		//	posY -= 50 * p_dt;
		//else if (m_input.keys[InputInfo::UP] == InputInfo::KEYDOWN)
		//	posY += 50 * p_dt;
		//m_mascot->setPosition(posX, posY);
	}
	return GAME_OK;
}
int DxContext::draw(float p_dt)
{
	if (!m_resizing)
	{
		m_deviceContext->ClearRenderTargetView(m_backBuffer, 
			D3DXCOLOR(0, 0, 0, 1.0f));

		m_deviceContext->ClearDepthStencilView(m_depthStencilView, 
			D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);

		SpriteInfo spriteInfo;
		spriteInfo.transformInfo.translation[TransformInfo::X] = 100;
		spriteInfo.transformInfo.translation[TransformInfo::Y] = 100;
		spriteInfo.transformInfo.scale[TransformInfo::X] = 100;
		spriteInfo.transformInfo.scale[TransformInfo::Y] = 100;

		m_mascot->setSpriteInfo(spriteInfo);
		m_mascot->draw();

		m_swapChain->Present(0, 0);
	}
	return GAME_OK;
}

int DxContext::beginDraw()
{
	if (!m_resizing)
	{
		m_deviceContext->ClearRenderTargetView(m_backBuffer, 
			D3DXCOLOR(0, 0, 0, 1.0f));

		m_deviceContext->ClearDepthStencilView(m_depthStencilView, 
			D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);
	}
	return GAME_OK;
}

int DxContext::drawSprite( SpriteInfo p_spriteInfo )
{
	if (!m_resizing && p_spriteInfo.visible)
	{
		m_mascot->setSpriteInfo(p_spriteInfo);

		if( p_spriteInfo.textureIndex >= 0 )
		{
			if( spriteSetIndexedTexture(&p_spriteInfo) == GAME_FAIL )
				return GAME_FAIL;

		}
		else if( p_spriteInfo.textureIndex == -1 &&
			p_spriteInfo.textureFileName != "" )
		{
			if( spriteSetUnindexedTexture(&p_spriteInfo) == GAME_FAIL )
				return GAME_FAIL;
			
		}
		else if( p_spriteInfo.textureFileName == "" )
		{
			if( spriteSetUnnamedTexture(&p_spriteInfo) == GAME_FAIL )
				return GAME_FAIL;

		}

		m_mascot->draw();	// Careful...
	}
	return GAME_OK;
}

int DxContext::spriteSetIndexedTexture(SpriteInfo* p_spriteInfo)
{
	// Texture id already indexed.
	ID3D11ShaderResourceView* texture = NULL;
	
	m_textureManager->getTexture(p_spriteInfo->textureIndex, &texture);

	if(texture == NULL)
		return GAME_FAIL;

	m_mascot->setTexture(texture);

	return GAME_OK;
}

int DxContext::spriteSetUnindexedTexture(SpriteInfo* p_spriteInfo)
{
	// Texture set but not cached.
	ID3D11ShaderResourceView* texture = NULL;

	// cannot set textureIndex since it's a local copy. <---------------------------------
	p_spriteInfo->textureIndex = m_textureManager->getTexture(
		p_spriteInfo->textureFileName, &texture);

	if(texture == NULL)
		return GAME_FAIL;

	m_mascot->setTexture(texture);

	return GAME_OK;
}

int DxContext::spriteSetUnnamedTexture(SpriteInfo* p_spriteInfo)
{
	// Texture not set -> use default.
	ID3D11ShaderResourceView* texture = NULL;
			
	p_spriteInfo->textureIndex = m_textureManager->getTexture(
		0, &texture);	// (0 is the default texture index.)

	if(texture == NULL)
		return GAME_FAIL;

	m_mascot->setTexture(texture);

	return GAME_OK;
}

int DxContext::endDraw()
{
	if (!m_resizing)
	{
		m_swapChain->Present(0, 0);
	}
	return GAME_OK;
}


int DxContext::getScreenWidth() const
{
	return m_screenWidth;
}
int DxContext::getScreenHeight()  const 
{
	return m_screenHeight;
}

LRESULT DxContext::handleWindowMessages(UINT p_message, 
	WPARAM p_wParam, LPARAM p_lParam)
{
	switch (p_message)
	{
	case WM_SIZE:
		if (p_wParam == SIZE_MAXIMIZED)
		{
			resize();
		}
		else if (p_wParam == SIZE_RESTORED)
		{
			if (!m_resizing)
			{
				resize();
			}
		}
		return 0;
	case WM_ENTERSIZEMOVE:
		m_resizing = true;
		return 0;

	case WM_EXITSIZEMOVE:
		resize();
		return 0;
 
	case WM_DESTROY:
		setRunning(false);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(m_windowHandle, p_message, p_wParam, p_lParam);
}

int DxContext::loadAllTextures()
{
	m_textureManager = new DxTextureManager(m_device);

	m_textureManager->addTexture("..\\Textures\\default.png");
	m_textureManager->addTexture("..\\Textures\\LogoDx.png");
	m_textureManager->addTexture("..\\Textures\\LogoGL.png");
	m_textureManager->addTexture("..\\Textures\\pacman-1974.png");

	return GAME_OK;
}
