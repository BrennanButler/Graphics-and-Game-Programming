#ifndef _COLORSHADERCLASS_H_
#define _COLORSHADERCLASS_H_

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>

class ColorShaderClass {

private:

	struct matrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX projection;
		D3DXMATRIX view;
	};

public:
	ColorShaderClass();
	~ColorShaderClass();

	bool Initialize(ID3D11Device *, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext *, int, D3DXMATRIX, D3DXMATRIX, D3DMATRIX);

private:
	bool InitializeShader(ID3D11Device *, HWND, LPCSTR, LPCSTR);
	void ShutdownShader();
	
	bool SetShaderParameters(ID3D11DeviceContext *, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX);
	void RenderShader(ID3D11DeviceContext *, int);

private:
	ID3D11VertexShader *m_vertexShader;
	ID3D11PixelShader *m_pixelShader;
	ID3D11InputLayout *m_layout;
	ID3D11Buffer *m_matrixBuffer;

};

#endif