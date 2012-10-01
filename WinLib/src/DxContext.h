#ifndef DX11APPLICATION_H
#define DX11APPLICATION_H

#include "DxUtility.h"
#include <IOContext.h>
#include "DxSpriteInfoRenderer.h"
#include "DxTextureManager.h"

class DxContext: public IOContext
{
private:
	int						m_screenWidth;
	int						m_screenHeight;
	IDXGISwapChain*			m_swapChain;
	ID3D11Device*			m_device;
	ID3D11DeviceContext*	m_deviceContext; 
	HWND					m_windowHandle;
	HINSTANCE				m_instanceHandle;

	ID3D11Texture2D*			m_depthStencilBuffer;
	ID3D11RenderTargetView*		m_backBuffer;
	ID3D11DepthStencilView*		m_depthStencilView;
	ID3D11DepthStencilState*	m_depthStencilState;
	ID3D11RasterizerState*		m_rasterState;

	DxTextureManager*			m_textureManager;

	float	m_totalGameTime;
	int		m_keyMappings[InputInfo::NUM_KEYS];
	bool	m_resizing;

	//temporary for displaying sprites
	float posX;
	float posY;
	DxSpriteInfoRenderer* m_spriteInfoRendererHolder; // Pre allocated for speed

private:
	int initializeWindow();
	int initializeSwapChain();
	int initializeBackBuffer();
	int initializeDepthStencilBuffer();
	int initializeDepthStencilState();
	int initializeDepthStencilView();
	int initializeRasterizerState();
	int initializeViewport();
	int	loadAllTextures();	// HACK!

	int addSprite( SpriteInfo* p_spriteInfo );

	int spriteSetIndexedTexture(SpriteInfo* p_spriteInfo);
	int spriteSetUnindexedTexture(SpriteInfo* p_spriteInfo);
	int spriteSetUnnamedTexture(SpriteInfo* p_spriteInfo);

public:
				DxContext(HINSTANCE pInstanceHandle, 
					int p_screenWidth, int p_screenHeight);
	virtual		~DxContext();
	bool		isInitialized() const;
	int			setWindowPosition(int p_x, int p_y);
	int			setWindowSize(int p_width, int p_height);
	int			resize();
	int			update(float p_dt);
	int			draw(float p_dt);  //HACK: replace by using drawSprite(), beginDraw() and endDraw()

	int			beginDraw();
	int			drawSprite(SpriteInfo* p_spriteInfo);
	int			endDraw();

	int			getScreenWidth() const;
	int			getScreenHeight() const;

	LRESULT		handleWindowMessages(UINT p_message, 
					WPARAM p_wParam, LPARAM p_lParam);
};

#endif