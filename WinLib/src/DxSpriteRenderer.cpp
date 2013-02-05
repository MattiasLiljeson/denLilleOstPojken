#include "DxSpriteRenderer.h"
#include "DxContext.h"

DxSpriteRenderer::DxSpriteRenderer(ID3D11Device* p_device, ID3D11DeviceContext* 
	p_deviceContext, DxContext* p_context)
{
	m_initialized	= false;
	m_device		= p_device;
	m_deviceContext = p_deviceContext;
	m_context		= p_context;
	m_shader		= NULL;
	m_vb = m_ib		= NULL;
	m_texture		= NULL;

	if (initVB() != GAME_OK)
		return;
	if (initIB() != GAME_OK)
		return;

	m_shader = new DxSpriteShader(p_device, p_deviceContext);

	if (!m_shader->isInitialized())
		return;

	m_spriteData.CenterPosition		= Vector3( 0, 0, 0 );
	m_spriteData.HalfSize			= Vector2( 50, 50 );
	m_spriteData.WindowSize			= Vector2( 800, 600 );

	m_initialized = true;
}
DxSpriteRenderer::~DxSpriteRenderer()
{
	if (m_vb)
		m_vb->Release();

	if (m_ib)
		m_ib->Release();

	if (m_texture)
		m_texture->Release();

	if (m_shader)
		delete m_shader;
}
int DxSpriteRenderer::initVB()
{
	SpriteVertex vertices[] = {  
		SpriteVertex(-1.0f,  1.0f, 0.0f, 0.0f, 0.0f),  
		SpriteVertex(-1.0f, -1.0f, 0.0f, 0.0f, 1.0f),
		SpriteVertex(1.0f, -1.0f, 0.0f, 1.0f, 1.0f),
		SpriteVertex(1.0f, 1.0f, 0.0f, 1.0f, 0.0f),
					};

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth		= sizeof(SpriteVertex) * 4;
	bd.BindFlags		= D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags	= D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem			= vertices;
	vertexData.SysMemPitch		= 0;
	vertexData.SysMemSlicePitch = 0;

	HRESULT res = m_device->CreateBuffer(&bd, &vertexData, &m_vb);
	if (res != S_OK)
		return GAME_FAIL;

	return GAME_OK;
}
int DxSpriteRenderer::initIB()
{
	unsigned int indices[] = {1, 0, 2, 0, 3, 2};

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.ByteWidth			= sizeof(unsigned int) * 6;
	ibd.BindFlags			= D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags		= 0;
	ibd.MiscFlags			= 0;
	ibd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem			= indices;
	indexData.SysMemPitch		= 0;
	indexData.SysMemSlicePitch	= 0;

	HRESULT res = m_device->CreateBuffer(&ibd, &indexData, &m_ib);
	if (res != S_OK)
		return GAME_FAIL;

	return GAME_OK;
}
void DxSpriteRenderer::setPosition(float p_positionX, float p_positionY, float p_positionZ)
{
	m_spriteData.CenterPosition = Vector3(p_positionX, p_positionY, p_positionZ);
}
void DxSpriteRenderer::draw()
{
	m_spriteData.WindowSize = Vector2(
		(float)m_context->getScreenWidth(), 
		(float)m_context->getScreenHeight());

	// Translate
	m_spriteData.CenterPosition = Vector3(
		m_spriteInfo->transformInfo.translation[TransformInfo::X],
		m_spriteInfo->transformInfo.translation[TransformInfo::Y],
		m_spriteInfo->transformInfo.translation[TransformInfo::Z]);
	
	// Scale
	m_spriteData.HalfSize = Vector2(
		m_spriteInfo->transformInfo.scale[TransformInfo::X] / 2,
		m_spriteInfo->transformInfo.scale[TransformInfo::Y] / 2);
	
	// Texture rectangle
	D3D11_TEXTURE2D_DESC textureDesc;
	ID3D11Texture2D* texture2D;
	m_texture->GetResource((ID3D11Resource**)&texture2D);
	texture2D->GetDesc(&textureDesc);
	texture2D->Release();

	
	m_spriteData.TextureRect = Vector4(
		(float)m_spriteInfo->textureRect.x / textureDesc.Width,
		(float)m_spriteInfo->textureRect.y / textureDesc.Height,
		(float)m_spriteInfo->textureRect.width / textureDesc.Width,
		(float)m_spriteInfo->textureRect.height / textureDesc.Height);

	//Added by Anton
	PostProcessBuffer ppbuffer;
	ppbuffer.ppEffects = Vector4(m_spriteInfo->bwFraction, m_spriteInfo->sepiaFraction, m_spriteInfo->fadeToBlackFraction, 0);
	ppbuffer.colorOverlay = Vector4(m_spriteInfo->overlay[0], m_spriteInfo->overlay[1], m_spriteInfo->overlay[2], m_spriteInfo->overlay[3]);

 	m_shader->setBuffer(m_spriteData, ppbuffer, m_texture);
	m_deviceContext->VSSetShader(m_shader->getVertexShader().Data, 0, 0);
	m_deviceContext->PSSetShader(m_shader->getPixelShader().Data, 0, 0);
	m_deviceContext->HSSetShader(NULL, 0, 0);
	m_deviceContext->DSSetShader(NULL, 0, 0);
	m_deviceContext->IASetInputLayout(m_shader->getInputLayout());
	UINT stride = sizeof(SpriteVertex);
	UINT offset = 0;
	m_deviceContext->IASetVertexBuffers(0, 1, &m_vb, &stride, &offset);
	m_deviceContext->IASetIndexBuffer(m_ib, DXGI_FORMAT_R32_UINT, 0);
	m_deviceContext->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_deviceContext->DrawIndexed(6, 0, 0);
}
bool DxSpriteRenderer::isInitialized()
{
	return m_initialized;
}

void DxSpriteRenderer::setSpriteInfo( SpriteInfo* p_spriteInfo )
{
	m_spriteInfo = p_spriteInfo;
}

void DxSpriteRenderer::setTexture(ID3D11ShaderResourceView* p_texture)
{
	m_texture = p_texture;
}