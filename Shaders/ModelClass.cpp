#include "ModelClass.h"

ModelClass::ModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
}

ModelClass::~ModelClass()
{

}

bool ModelClass::Initialize(ID3D11Device *device)
{
	return InitializeBuffers(device);
}

void ModelClass::Shutdown()
{
	ShutdownBuffers();
}

void ModelClass::Render(ID3D11DeviceContext *deviceContext)
{
	RenderBuffers(deviceContext);
}

int ModelClass::GetIndexCount()
{
	return m_indexCount;
}

bool ModelClass::InitializeBuffers(ID3D11Device *device)
{
	vertexType *vertices;
	unsigned long *indices;

	D3D11_BUFFER_DESC vertextBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertextData, indexData;

	m_vertexCount = 3;
	m_indexCount = 3;

	vertices = new vertexType[m_vertexCount];

	if (!vertices)
		return false;

	indices = new unsigned long[m_indexCount];

	if (!indices)
		return false;

	vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f); //bottom left
	vertices[0].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f); // green

	vertices[1].position = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //top middle
	vertices[1].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[2].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f); //bottom right
	vertices[2].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

	vertextBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertextBufferDesc.ByteWidth = sizeof(vertexType) * m_vertexCount;
	vertextBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertextBufferDesc.CPUAccessFlags = 0;
	vertextBufferDesc.MiscFlags = 0;
	vertextBufferDesc.StructureByteStride = 0;

	vertextData.pSysMem = vertices;
	vertextData.SysMemPitch = 0;
	vertextData.SysMemSlicePitch = 0;

	if (FAILED(device->CreateBuffer(&vertextBufferDesc, &vertextData, &m_vertexBuffer)))
	{
		return false;
	}

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	if (FAILED(device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer)))
	{
		return false;
	}

	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}

void ModelClass::ShutdownBuffers()
{
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
}

void ModelClass::RenderBuffers(ID3D11DeviceContext *deviceContext)
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(vertexType);
	offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}