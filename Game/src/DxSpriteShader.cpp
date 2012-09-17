#include "DxSpriteShader.h"

DxSpriteShader::DxSpriteShader(ID3D11Device* p_device, ID3D11DeviceContext* p_deviceContext)
{
	m_device = p_device;
	m_deviceContext = p_deviceContext;

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
}
DxSpriteShader::~DxSpriteShader()
{
	m_buffer->Release();
	m_inputLayout->Release();
	m_vsd.CompiledData->Release();
	m_psd.CompiledData->Release();
}
void DxSpriteShader::setBuffer(SpriteBuffer p_buffer, ID3D11ShaderResourceView* p_texture)
{
	D3D11_MAPPED_SUBRESOURCE resource;
	SpriteBuffer* buffer;
	m_deviceContext->Map(m_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);

	buffer = (SpriteBuffer*)resource.pData;
	buffer->CenterPosition = p_buffer.CenterPosition;
	buffer->HalfSize = p_buffer.HalfSize;
	buffer->WindowSize = p_buffer.WindowSize;

	m_deviceContext->Unmap(m_buffer, 0);

	m_deviceContext->PSSetShaderResources(0, 1, &p_texture);

	unsigned int bufferNumber = 0;
	m_deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_buffer);
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