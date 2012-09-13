#include "DxContext.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
		case WM_KEYDOWN:
		{
			if( wParam == VK_ESCAPE )
				DestroyWindow(hWnd);
			return 0;
		}
        case WM_DESTROY:
        {
                PostQuitMessage(0);
                return 0;
        } 
		break;
    }

    return DefWindowProc (hWnd, message, wParam, lParam);
}

DxContext::DxContext(HINSTANCE pInstanceHandle, int p_screenWidth, int p_screenHeight) : IOContext(p_screenWidth, p_screenHeight)
{
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

	initializeWindow();
	initializeSwapChain();
	initializeBackBuffer();
	initializeDepthStencilBuffer();
	initializeDepthStencilState();
	initializeDepthStencilView();
	initializeRasterizerState();
	initializeViewport();
}
DxContext::~DxContext()
{
	m_swapChain->SetFullscreenState(FALSE, NULL);
	m_swapChain->Release();
    m_device->Release();
    m_deviceContext->Release();
	m_backBuffer->Release();
	m_depthStencilView->Release();
	m_depthStencilState->Release();
	m_rasterState->Release();
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
    wc.lpszClassName = L"WindowClass";
    RegisterClassEx(&wc);
    RECT wr = {0, 0, getScreenWidth(), getScreenHeight()};
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
    m_windowHandle = CreateWindowEx(NULL,
                          L"WindowClass",
                          L"Den Lille OstPojken",
                          WS_OVERLAPPEDWINDOW,
                          100,
                          100,
                          wr.right - wr.left,
                          wr.bottom - wr.top,
                          NULL,
                          NULL,
                          m_instanceHandle,
                          NULL);

    ShowWindow(m_windowHandle, SW_SHOW);
	//m_inputHandler.Create(m_windowHandle);
	return 0;
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

	D3D_FEATURE_LEVEL featureLevels[] = {D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0};
    D3D11CreateDeviceAndSwapChain(NULL,
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
                                  &m_deviceContext);
	return 0;
}
int DxContext::initializeBackBuffer()
{
	ID3D11Texture2D *BackBuffer;
    m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&BackBuffer);
	m_device->CreateRenderTargetView(BackBuffer, NULL, &m_backBuffer);
    BackBuffer->Release();
	return 0;
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

	int result = m_device->CreateTexture2D(&depthBufferDesc, 0, &m_depthStencilBuffer);
	if(FAILED(result))
	{
		return 1;
	}
	return 0;
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


	int result = m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
	if(FAILED(result))
	{
		return 1;
	}
	m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);
	//mDeviceContext->OMSetDepthStencilState(0, 0);
	return 0;
}
int DxContext::initializeDepthStencilView()
{
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	// Set up the depth stencil view description.
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	int result = m_device->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilViewDesc, &m_depthStencilView);
	if(FAILED(result))
	{
		return 1;
	}

    m_deviceContext->OMSetRenderTargets(1, &m_backBuffer, m_depthStencilView);
	return 0;
}
int DxContext::initializeRasterizerState()
{
	// Setup the raster description which will determine how and what polygons will be drawn.
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
		return 1;
	}

	// Now set the rasterizer state.
	m_deviceContext->RSSetState(m_rasterState);
	return 0;
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

	return 0;
}
int DxContext::resize()
{
	return 0;
}
int DxContext::update(float p_dt)
{
	MSG msg;
	if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if(msg.message == WM_QUIT)
			setRunning(false);
	}
	return 0;
}
int DxContext::draw(float p_dt)
{
	m_deviceContext->ClearRenderTargetView(m_backBuffer, D3DXCOLOR(0.5f, 0.5f, 0, 1.0f));
	m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);

    m_swapChain->Present(0, 0);
	return true;
}