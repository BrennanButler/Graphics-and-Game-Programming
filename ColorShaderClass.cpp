#include "ColorShaderClass.h"

ColorShaderClass::ColorShaderClass()
{
	m_vertexShader = 0;
	m_pixelShader = 0;
	m_matrixBuffer = 0;
	m_layout = 0;
}

ColorShaderClass::~ColorShaderClass()
{
}

bool ColorShaderClass::Initialize(ID3D11Device *device, HWND hwnd)
{
	return InitializeShader(device, hwnd, "/Shaders/VColour.hlsl", "/Shaders/PColour.hlsl");
}

void ColorShaderClass::Shutdown()
{
	ShutdownShader();
}

void ColorShaderClass::Shutdown()
{


}

bool ColorShaderClass::Render(ID3D11DeviceContext *deviceContext, int indexCount, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX projection)
{
	if (!SetShaderParameters(deviceContext, world, view, projection))
		return false;

	RenderShader(deviceContext, indexCount);

	return true;
}

bool ColorShaderClass::InitializeShader(ID3D11Device *device, HWND hwnd, LPCSTR vertexShader, LPCSTR pixelShader)
{
	ID3D10Blob *errorMessage;
	ID3D10Blob *vertexBuffer;
	ID3D10Blob *pixelBuffer;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;

	errorMessage = 0;
	vertexBuffer = 0;
	pixelBuffer = 0;

	if (FAILED(D3DX10CompileFromFile(vertexShader, NULL, NULL, "VertexColourShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &vertexBuffer, &errorMessage, NULL)))
	{
		if (errorMessage)
		{
			//output error
		}
		else
		{
			MessageBox(NULL, "Shader file not found!", "ERROR", MB_OK);
		}
		return false;
	}

	if (FAILED(D3DX10CompileFromFile(pixelShader, NULL, NULL, "ColourPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &pixelBuffer, &errorMessage, NULL)))
	{
		if (errorMessage)
		{
			//output error
		}
		else
		{
			MessageBox(NULL, "Shader file not found!", "ERROR", MB_OK);
		}
		return false;
	}

	if (FAILED(device->CreateVertexShader(vertexBuffer->GetBufferPointer(), vertexBuffer->GetBufferSize(), NULL, &m_vertexShader)))
	{
		return false;
	}

	if (FAILED(device->CreatePixelShader(pixelBuffer->GetBufferPointer(), pixelBuffer->GetBufferSize, NULL, &m_pixelShader)))
	{
		return false;
	}
}

void ColorShaderClass::ShutdownShader()
{
	if (m_layout)
	{
		m_layout->Release();
		m_layout = 0;
	}
	if (m_matrixBuffer)
	{
		m_matrixBuffer->Release();
		m_matrixBuffer = 0;
	}
	if (m_vertexShader)
	{
		m_vertexShader->Release();
		m_vertexShader = 0;
	}
	if (m_pixelShader)
	{
		m_vertexShader->Release();
		m_vertexShader = 0;
	}
}

void ColorShaderClass::RenderShader(ID3D11DeviceContext *context, int indexCount)
{
	context->IASetInputLayout(m_layout);

	context->VSSetShader(m_vertexShader, NULL, 0);
	context->PSSetShader(m_pixelShader, NULL, 0);

	context->DrawIndexed(indexCount, 0, 0);
}