#include "DxSpriteShader.h"

DxSpriteShader::DxSpriteShader(ID3D11Device* p_device, 
	ID3D11DeviceContext* p_deviceContext)
{
	m_device			= p_device;
	m_deviceContext		= p_deviceContext;
	m_initialized		= false;
	m_buffer			= NULL;
	m_inputLayout		= NULL;
	m_vsd.CompiledData	= NULL;
	m_vsd.Data			= NULL;
	m_psd.CompiledData	= NULL;
	m_vsd.Data			= NULL;

	HRESULT vsRes = D3DX11CompileFromFile("..\\Shaders\\testDx.vs", 0, 0,
		"VShader", "vs_4_0", 0, 0, 0, &m_vsd.CompiledData, 0, 0);
	if (vsRes != S_OK)
		return;
	HRESULT psRes = D3DX11CompileFromFile("..\\Shaders\\testDx.ps", 0, 0,
		"PShader", "ps_4_0", 0, 0, 0, &m_psd.CompiledData, 0, 0);
	if (psRes != S_OK)
		return;

	ID3D10Blob* compVs = m_vsd.CompiledData;
	vsRes = m_device->CreateVertexShader(compVs->GetBufferPointer(), 
		compVs->GetBufferSize(), NULL, &m_vsd.Data);
	if (vsRes != S_OK)
		return;

	ID3D10Blob* compPs = m_psd.CompiledData;
	psRes = m_device->CreatePixelShader(compPs->GetBufferPointer(), 
		compPs->GetBufferSize(), NULL, &m_psd.Data);
	if (psRes != S_OK)
		return;

	D3D11_INPUT_ELEMENT_DESC PositionNormalTexCoord[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, 
			D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, 
			D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	
	HRESULT ilRes = m_device->CreateInputLayout(PositionNormalTexCoord, 
		2, m_vsd.CompiledData->GetBufferPointer(), 
			m_vsd.CompiledData->GetBufferSize(), &m_inputLayout);
	if (ilRes != S_OK)
		return;

	D3D11_BUFFER_DESC BufferDesc;
	BufferDesc.Usage				= D3D11_USAGE_DYNAMIC;
	BufferDesc.ByteWidth			= sizeof(SpriteBuffer);
	BufferDesc.BindFlags			= D3D11_BIND_CONSTANT_BUFFER;
	BufferDesc.CPUAccessFlags		= D3D11_CPU_ACCESS_WRITE;
	BufferDesc.MiscFlags			= 0;
	BufferDesc.StructureByteStride	= 0;


	HRESULT bufRes = m_device->CreateBuffer(&BufferDesc, NULL, &m_buffer);
	if (bufRes != S_OK)
		return;

	BufferDesc.Usage				= D3D11_USAGE_DYNAMIC;
	BufferDesc.ByteWidth			= sizeof(PostProcessBuffer);
	BufferDesc.BindFlags			= D3D11_BIND_CONSTANT_BUFFER;
	BufferDesc.CPUAccessFlags		= D3D11_CPU_ACCESS_WRITE;
	BufferDesc.MiscFlags			= 0;
	BufferDesc.StructureByteStride	= 0;


	bufRes = m_device->CreateBuffer(&BufferDesc, NULL, &m_ppBuffer);
	if (bufRes != S_OK)
		return;

	m_initialized = true;
}
DxSpriteShader::~DxSpriteShader()
{
	if (m_buffer)
		m_buffer->Release();
	if (m_inputLayout)
		m_inputLayout->Release();
	if (m_vsd.CompiledData)
		m_vsd.CompiledData->Release();
	if (m_vsd.Data)
		m_vsd.Data->Release();
	if (m_vsd.CompiledData)
		m_psd.CompiledData->Release();
	if (m_psd.Data)
		m_psd.Data->Release();
}
void DxSpriteShader::setBuffer(SpriteBuffer p_buffer, PostProcessBuffer p_ppBuffer,
	ID3D11ShaderResourceView* p_texture)
{
	D3D11_MAPPED_SUBRESOURCE resource;
	SpriteBuffer* buffer;
	PostProcessBuffer* ppBuffer;

	m_deviceContext->Map(m_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	buffer = (SpriteBuffer*)resource.pData;
	buffer->CenterPosition = p_buffer.CenterPosition;
	buffer->HalfSize = p_buffer.HalfSize;
	buffer->WindowSize = p_buffer.WindowSize;
	buffer->TextureRect = p_buffer.TextureRect;
	m_deviceContext->Unmap(m_buffer, 0);

	m_deviceContext->Map(m_ppBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	ppBuffer = (PostProcessBuffer*)resource.pData;
	ppBuffer->ppEffects = p_ppBuffer.ppEffects;
	ppBuffer->colorOverlay = p_ppBuffer.colorOverlay;
	m_deviceContext->Unmap(m_ppBuffer, 0);


	m_deviceContext->PSSetShaderResources(0, 1, &p_texture);

	unsigned int bufferNumber = 0;
	m_deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_buffer);
	m_deviceContext->PSSetConstantBuffers(bufferNumber, 1, &m_ppBuffer);
}
VertexShaderData DxSpriteShader::getVertexShader()
{
	return m_vsd;
}
PixelShaderData DxSpriteShader::getPixelShader()
{
	return m_psd;
}
ID3D11InputLayout* DxSpriteShader::getInputLayout()
{
	return m_inputLayout;
}
bool DxSpriteShader::isInitialized()
{
	return m_initialized;
}