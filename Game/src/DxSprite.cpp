#include "DxSprite.h"

DxSprite::DxSprite(ID3D11Device* p_device, ID3D11DeviceContext* p_deviceContext)
{
	m_device = p_device;
	m_deviceContext = p_deviceContext;

	initVB();
	initIB();
	initShader();

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
	m_buffer->Release();
	m_inputLayout->Release();
	m_vsd.CompiledData->Release();
	m_psd.CompiledData->Release();
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
int DxSprite::initShader()
{
	D3DX11CompileFromFile(L"testDx.vs", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &m_vsd.CompiledData, 0, 0);
    D3DX11CompileFromFile(L"testDx.ps", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &m_psd.CompiledData, 0, 0);

	m_device->CreateVertexShader(m_vsd.CompiledData->GetBufferPointer(), m_vsd.CompiledData->GetBufferSize(), NULL, &m_vsd.Data);
	m_device->CreatePixelShader(m_psd.CompiledData->GetBufferPointer(), m_psd.CompiledData->GetBufferSize(), NULL, &m_psd.Data);

	D3D11_INPUT_ELEMENT_DESC PositionNormalTexCoord[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	m_device->CreateInputLayout(PositionNormalTexCoord, 2, m_vsd.CompiledData->GetBufferPointer(), m_vsd.CompiledData->GetBufferSize(), &m_inputLayout);

	D3D11_BUFFER_DESC BufferDesc;
	BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	BufferDesc.ByteWidth = sizeof(SpriteBuffer);
	BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	BufferDesc.MiscFlags = 0;
	BufferDesc.StructureByteStride = 0;
	m_device->CreateBuffer(&BufferDesc, NULL, &m_buffer);
	return 0;
}
void DxSprite::setPosition(float p_positionX, float p_positionY)
{
	m_spriteData.CenterPosition = Vector2(p_positionX, p_positionY);
}
void DxSprite::draw()
{
	//Set matrix buffer
	D3D11_MAPPED_SUBRESOURCE resource;
	SpriteBuffer* buffer;
	m_deviceContext->Map(m_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);

	buffer = (SpriteBuffer*)resource.pData;
	buffer->CenterPosition = m_spriteData.CenterPosition;
	buffer->HalfSize = m_spriteData.HalfSize;
	buffer->WindowSize = m_spriteData.WindowSize;

	m_deviceContext->Unmap(m_buffer, 0);

	m_deviceContext->PSSetShaderResources(0, 1, &m_texture);

	unsigned int bufferNumber = 0;
	m_deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_buffer);




	m_deviceContext->VSSetShader(m_vsd.Data, 0, 0);
	m_deviceContext->PSSetShader(m_psd.Data, 0, 0);	
	m_deviceContext->HSSetShader(NULL, 0, 0);
	m_deviceContext->DSSetShader(NULL, 0, 0);
	m_deviceContext->IASetInputLayout(m_inputLayout);
	UINT stride = sizeof(SpriteVertex);
	UINT offset = 0;
	m_deviceContext->IASetVertexBuffers(0, 1, &m_vb, &stride, &offset);
	m_deviceContext->IASetIndexBuffer(m_ib, DXGI_FORMAT_R32_UINT, 0);
	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_deviceContext->DrawIndexed(6, 0, 0);
}