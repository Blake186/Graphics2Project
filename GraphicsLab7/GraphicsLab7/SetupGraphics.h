#pragma once
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
// TODO: PART 1 STEP 1b
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <dxgi.h>
#include <vector>
#include "Model.h"
#include "My_Matrix.h"


//#include "Math.h"
#pragma comment(lib, "dxgi.lib")
using namespace DirectX;

class SetupGraphics
{
protected:

	IDXGISwapChain* m_SwapChain = nullptr;

	ID3D11Device* m_device = nullptr;

	ID3D11DeviceContext* m_deviceContext = nullptr;

	

	ID3D11RenderTargetView* m_RenderTargetVeiw;

	//HWND							window;
public:
	D3D11_VIEWPORT vp;
	D3D11_VIEWPORT veiwport2;
	static SetupGraphics* GetInstance();
	SetupGraphics();
	~SetupGraphics();
	// Getters 
	ID3D11Device* GetDevice() { return m_device; }
	ID3D11DeviceContext* GetDeviceContext() { return m_deviceContext; }
	ID3D11RenderTargetView** GetRenderTargetView() { return &m_RenderTargetVeiw; }
	IDXGISwapChain* GetSwapChain() { return m_SwapChain; }


	// setters 

	void Set_Device_DeviceContex_SwapChain(HWND _window);
	void CreateConstBuffer(ID3D11Buffer** _ConstBuffer, ObjectMatrix  Matrix1);
	void CreateConstBuffer(ID3D11Buffer** _ConstBuffer, SceneMatrix Matrix2);


	void Map_UnMap_Variables(ID3D11Buffer** _ConstBuffer, ObjectMatrix _Shader);

	void Map_UnMap_Variables(ID3D11Buffer** _ConstBuffer, SceneMatrix _Shader);

	void CreateIndexBuffer(const UINT* indices, UINT _size, ID3D11Buffer** _IndexBuffer);

	void Create_Depth_Stencil(ID3D11Texture2D** _DepthStencil);

	void CreateStencilVeiw(ID3D11Texture2D* __depthStencil, ID3D11DepthStencilView** _DepthVeiw);

	void CreateRasterizer(ID3D11RasterizerState** _Rasterizer, int count);

	void Create_Depth_Stencil_State(ID3D11DepthStencilState**);

//	void CreateVertexBuffer(OBJ_VERT* _Vertex, int _Size, ID3D11Buffer** _VertexBuffer);

	void Create_A_Texture(ID3D11Texture2D** _Texture);

	void Create_Simple_State(ID3D11SamplerState ** _sampler);

	void Create_Resource_Veiw(ID3D11ShaderResourceView** _ResourceVeiw, ID3D11Resource* _resource);

	void Create_Blend_State(ID3D11BlendState** _blend);

	//void CreateVertexBuffer(* _Vertex, int _Size, ID3D11Buffer** _VertexBuffer);

	void Render(UINT _stride, UINT _zero, ID3D11PixelShader** _PixalShader, ID3D11VertexShader** _VertexShader, ID3D11Buffer** _VertexBuffer, ID3D11Buffer** ConstBuffer, ID3D11InputLayout** _InputLayout);
	void Render(UINT _stride, UINT _zero, ID3D11PixelShader** _PixalShader, ID3D11VertexShader** _VertexShader, ID3D11Buffer** _VertexBuffer, ID3D11Buffer** ConstBuffer, ID3D11Buffer** ConstBuffer2, ID3D11InputLayout**_InputLayout, ID3D11Buffer** _IndexBuffer);
};

