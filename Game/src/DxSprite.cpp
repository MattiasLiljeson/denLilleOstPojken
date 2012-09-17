#include "DxSprite.h"

DxSprite::DxSprite(ID3D11Device* p_device, ID3D11DeviceContext* p_deviceContext)
{
	m_device = p_device;
	m_deviceContext = p_deviceContext;

	initVB();
	initIB();

	m_shader = new DxSpriteShader(p_device, p_deviceContext);

	m_spriteData.CenterPosition = Vector2(0, 0);
	m_spriteData.HalfSize = Vector2(50, 50);
	m_spriteData.WindowSize = Vector2(800, 600);

	D3DX11CreateShaderResourceViewFromFile(m_device, L"LogoDx.png", NULL, 0, &m_texture, 0);
}
DxSprite::~DxSprite()
{
	m_vb->Release();
	m_ib->Release();
	m_texture->Release();
	delete m_shader;
}
int DxSprite::initVB()
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
	bd.ByteWidth = sizeof(SpriteVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	m_device->CreateBuffer(&bd, &vertexData, &m_vb);
	return 0;
}
int DxSprite::initIB()
{
	unsigned int indices[] = {1, 0, 2, 0, 3, 2};

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.ByteWidth = sizeof(unsigned int) * 6;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	m_device->CreateBuffer(&ibd, &indexData, &m_ib);
	return 0;
}
void DxSprite::setPosition(float p_positionX, float p_positionY)
{
	m_spriteData.CenterPosition = Vector2(p_positionX, p_positionY);
}
void DxSprite::draw()
{
	m_shader->setBuffer(m_spriteData, m_texture);
	m_deviceContext->VSSetShader(m_shader->getVertexShader().Data, 0, 0);
	m_deviceContext->PSSetShader(m_shader->getPixelShader().Data, 0, 0);	
	m_deviceContext->HSSetShader(NULL, 0, 0);
	m_deviceContext->DSSetShader(NULL, 0, 0);
	m_deviceContext->IASetInputLayout(m_shader->getInputLayout());
	UINT stride = sizeof(SpriteVertex);
	UINT offset = 0;
	m_deviceContext->IASetVertexBuffers(0, 1, &m_vb, &stride, &offset);
	m_deviceContext->IASetIndexBuffer(m_ib, DXGI_FORMAT_R32_UINT, 0);
	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_deviceContext->DrawIndexed(6, 0, 0);
}