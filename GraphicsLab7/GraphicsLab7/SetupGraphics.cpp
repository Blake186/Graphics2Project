#include "SetupGraphics.h"


SetupGraphics::SetupGraphics()
{
}


SetupGraphics::~SetupGraphics()
{
}

void SetupGraphics::Set_Device_DeviceContex_SwapChain(HWND _window)
{
	DXGI_SWAP_CHAIN_DESC sd;
	HRESULT m_result;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = 500;
	sd.BufferDesc.Height = 500;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = _window;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	sd.Windowed = true;

	// TODO: PART 1 STEP 3b
	//
	const D3D_FEATURE_LEVEL Featurelevel = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL RequestedLevel;
	UINT CreateDeviceFlags = 0;
#ifdef _DEBUG
	CreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	m_result = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE,

		NULL,
		CreateDeviceFlags,
		&Featurelevel,
		1, D3D11_SDK_VERSION,
		&sd, &m_SwapChain,
		&m_device, 0,
		&m_deviceContext);

	if (m_result == E_INVALIDARG)
	{
		m_result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &Featurelevel, 0, D3D11_SDK_VERSION, &sd, &m_SwapChain, &m_device, &RequestedLevel, &m_deviceContext);
	}

	//if (FAILED(m_result))
	//	return m_result;

	ID3D11Texture2D* pBackBuffer;
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	m_device->CreateRenderTargetView(pBackBuffer, NULL, &m_RenderTargetVeiw);

	vp.Width = 500;
	vp.Height = 500;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	pBackBuffer->Release();
	


}

SetupGraphics* SetupGraphics::GetInstance()
{
	static SetupGraphics m_Instance;

	return &m_Instance;

}


//void SetupGraphics::Render(UINT _stride, UINT _zero, ID3D11PixelShader** _PixalShader, ID3D11VertexShader** _VertexShader, ID3D11Buffer** _VertexBuffer, 
//	ID3D11Buffer** ConstBuffer1, ID3D11Buffer** ConstBuffer2, ID3D11Buffer** PixalBuffer, ID3D11InputLayout** _InputLayout, ID3D11Buffer** _indexBuffer)
//{
//	GetDeviceContext()->IASetVertexBuffers(0, 1, _VertexBuffer, &_stride, &_zero);
//	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//	GetDeviceContext()->IASetInputLayout(*_InputLayout);
//
//	GetDeviceContext()->IASetIndexBuffer(*_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
//	//VS
//	GetDeviceContext()->VSSetShader(*_VertexShader, NULL, 0);
//	GetDeviceContext()->VSSetConstantBuffers(0, 1, ConstBuffer1);
//	GetDeviceContext()->VSSetConstantBuffers(1, 1, ConstBuffer2);
//	SetupGraphics::GetInstance()->GetDeviceContext()->PSSetConstantBuffers(0, 1, PixalBuffer);
//	SetupGraphics::GetInstance()->GetDeviceContext()->PSSetShader(*_PixalShader, NULL, 0);
//	SetupGraphics::GetInstance()->GetDeviceContext()->PSSetShaderResources(0, 1, Get);
//
//
//}