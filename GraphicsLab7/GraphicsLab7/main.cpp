// D3D LAB 1a "Line Land".
// Author: L.Norri CD DRX, FullSail University

// Introduction:
// Welcome to the first lab of the Direct3D Graphics Programming class.
// This is the ONLY guided lab in this course! 
// Future labs will demand the habits & foundation you develop right now!  
// It is CRITICAL that you follow each and every step. ESPECIALLY THE READING!!!

// TO BEGIN: Open the word document that acompanies this lab and start from the top.

//************************************************************
//************ INCLUDES & DEFINES ****************************
//************************************************************

#include <iostream>
#include <ctime>
#include "XTime.h"
#include <Windows.h>
#include <memory.h>
#include <WinBase.h>
#include "Cube.h"
#include "texture1.h"
#include "GridVertexShader.csh"

using namespace std;

// BEGIN PART 1
// TODO: PART 1 STEP 1a
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
// TODO: PART 1 STEP 1b
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <dxgi.h>
#include <vector>
#include "Math.h"
#include "SetupGraphics.h"

#pragma comment(lib, "dxgi.lib")
using namespace DirectX;
// TODO: PART 2 STEP 6
#include "Trivial_PS.csh"
#include "Trivial_VS.csh"
#include "VertexShader.csh"
#include "brickwall.h"
#include "GridPixelShader.csh"
#include "numbers_test.h"
#include <fstream>
#include "DDSTextureLoader.h"
#include "PixelShaderGundam.csh"
#define BACKBUFFER_WIDTH	500
#define BACKBUFFER_HEIGHT	500
//_DEBUG(D3D11_CREATE_DEVICE_DEBUG);
#define TRUE 1
#define FALSE 0

#define Lab7 0
#define Lab8 1
#define Lab9 1
#define Lab10 1
//************************************************************
//************ SIMPLE WINDOWS APP CLASS **********************
//************************************************************

IDXGISwapChain* m_SwapChain;
ID3D11Device* m_device;

ID3D11DeviceContext* m_deviceContext;
D3D11_VIEWPORT vp;
ID3D11RenderTargetView* m_RenderTargetVeiw;
ID3D11DepthStencilView* pDSV;
ID3D11Texture2D* m_DepthBuffer;
ID3D11DepthStencilState* DepthState;
ID3D11RasterizerState * g_pRasterState;
ID3D11RasterizerState* g_pRasterState2;
MY_Matrix ProjectionMatrix;
static class DEMO_APP
{
	HINSTANCE						application;
	WNDPROC							appWndProc;
	HWND							window;
	// TODO: PART 1 STEP 2






	// TODO: PART 2 STEP 2
	ID3D11Buffer* m_buffer;
	//ID3D11Buffer* TriangleVertexBuffer;
	//ID3D11Buffer* m_InterVertex[2];
	//ID3D11Buffer* m_SquareBuffer;
	UINT VertCount;


	// BEGIN PART 5
	// TODO: PART 5 STEP 1

	// TODO: PART 2 STEP 4
	ID3D11PixelShader* m_PixalShader;
	ID3D11VertexShader* m_VertexShader;

	ID3D11PixelShader* m_GridPixalShader;
	ID3D11VertexShader* m_GridVertexShader;

	ID3D11PixelShader* GundamPixalShader;

	ID3D11InputLayout* m_InputLayout;
	ID3D11InputLayout* m_InputLayoutGrid;


	ID3D11Texture2D* m_texture;
	ID3D11SamplerState* Sampler;
	// BEGIN PART 3
	// TODO: PART 3 STEP 1
	ID3D11Buffer* m_ConstantBuffer;
	ID3D11Buffer* m_IndexBuffer;
	ID3D11Buffer* m_GridIndexBuffer;
	ID3D11Buffer* PixalConstbuffer;
	// TODO: PART 3 STEP 2b
	struct SEND_TO_VRAM
	{
		FLOAT m_ConstantColor[4];
		FLOAT m_ConstantOffset[2];
		FLOAT m_Padding[2];
		//FLOAT[16]


	};

	struct Object
	{
		//FLOAT WORLDMATRIX[16];
		XMFLOAT4X4 m_WorldMatrix;
	};
	struct Scene
	{
		//FLOAT VEIWMATRIX[16];
		//FLOAT PROJECIONMATRIX[16];
		XMFLOAT4X4 m_VeiwMatrix;
		XMFLOAT4X4 m_ProjectionMatrix;

	};
	struct Animation
	{
		float frame;
		int width;
		float totalframes;
		float height;

	};
	ID3D11Buffer* VertexBuffer;

	// Starts Index and Vertex Buffer
	ID3D11Buffer* Vertex_Buffer_Star;
	ID3D11Buffer* m_Index_Buffer_Star;

	ID3D11Buffer* GridVertexBuffer;
	ID3D11Buffer* m_ConstbufferObject;
	ID3D11Buffer*m_ConstbufferObjectGrid;
	ID3D11Buffer* m_ConstbufferSeen;

	ID3D11Resource* m_Resource;
	ID3D11Resource* m_Gundam;
	ID3D11ShaderResourceView* m_Gundamveiw;
	ID3D11ShaderResourceView* ResourceVeiw;
	// TODO: PART 3 STEP 4a
	SEND_TO_VRAM toShader;
	//std::vector<ID3D11Buffer*> m_Checkeard;

	ID3D11BlendState* m_blendstate;


	IDXGIFactory* m_factory;
	IDXGIAdapter* m_adapter;
	ID3D11Buffer* PixalBuffer;


	vector<XMFLOAT3> vertices;
	vector<XMFLOAT2> uvs;
	vector<XMFLOAT3> normals;
	vector<unsigned int> Index;



public:
	// BEGIN PART 2
	// TODO: PART 2 STEP 1

	struct SIMPLE_VERTEX
	{
		XMFLOAT4 m_position;
		XMFLOAT4 m_Color;
		XMFLOAT2 UV;
		XMFLOAT2 Nrm;
	};
	Animation numberanimations;
	POINT m_position;
	float m_timer = 0.0f;
	FLOAT Translate[4];
	XTime m_time;
	Object vs_shaderWorld;
	Object vs_worldMatrix;
	Scene vs_shaderVeiwProjection;
	//MY_Matrix WorldMatrix;
	MY_Matrix WorldMatrixGrid;
	MY_Matrix VeiwMAtrix;
	MY_Matrix WolrdSpaceCamrea;
	SIMPLE_VERTEX Gundam[10359];




	bool LoadObj(const char* Path, vector<XMFLOAT3>& out_vertices, vector<XMFLOAT2>& out_uvs, vector<XMFLOAT3>& out_normals, vector<unsigned int>&Index);

	SIMPLE_VERTEX Triangle[22];
	SIMPLE_VERTEX Grid[89];
	float numbertimer = 0.0f;
	XMFLOAT4X4 WorldMatrix;
	XMFLOAT4X4 VeiwMatrix;
	XMFLOAT4X4 ProjectionMatrix;
	//std::vector<SIMPLE_VERTEX*> m_Checkers;
	DEMO_APP(HINSTANCE hinst, WNDPROC proc);
	bool Run();
	bool ShutDown();
	void CreateVertexBuffer(vector<SIMPLE_VERTEX>* _Vertex, int _Size, ID3D11Buffer** _VertexBuffer);
	void CreateVertexBuffer(SIMPLE_VERTEX* _Vertex, int _Size, ID3D11Buffer** _VertexBuffer);
	void CreateConstBuffer(ID3D11Buffer** _ConstBuffer, Object _matrix);
	void CreateConstBuffer(ID3D11Buffer** _ConstBuffer, Scene _matrix2);
	void CreateConstBuffer(ID3D11Buffer** _ConstBuffer, Animation _animate);
	void DrawLineStrip();
	void ClearBuffer(float* _RGBA);
	void Map_UnMap_Variables(ID3D11Buffer** _ConstBuffer, Animation _Shader);
	void Map_UnMap_Variables(ID3D11Buffer** _ConstBuffer, Object _Shader);
	void Map_UnMap_Variables(ID3D11Buffer** _ConstBuffer, Scene _Shader);
	void Set_PS_VS_INPUTLAYOUT_VB_CB(UINT _stride, UINT _zero, ID3D11PixelShader** _PixalShader, ID3D11VertexShader** _VertexShader, ID3D11Buffer** _VertexBuffer, ID3D11Buffer** ConstBuffer, ID3D11InputLayout** _InputLayout);
	void DrawVerts(UINT VertextCount, D3D11_PRIMITIVE_TOPOLOGY _pTopology);
	void CreateIndexBuffer(vector<unsigned int>* indices, UINT _size, ID3D11Buffer** _IndexBuffer);
	void CreateIndexBuffer(const UINT* indices, UINT _size, ID3D11Buffer** _IndexBuffer);
	void Create_Depth_Stencil(ID3D11Texture2D** _DepthStencil);
	void CreateStencilVeiw(ID3D11Texture2D* __depthStencil, ID3D11DepthStencilView** _DepthVeiw);
	void CreateRasterizer(ID3D11RasterizerState** _Rasterizer, int count);
	void Create_Depth_Stencil_State(ID3D11DepthStencilState**);
	void CreateVertexBuffer(OBJ_VERT* _Vertex, int _Size, ID3D11Buffer** _VertexBuffer);
	void Create_A_Texture(ID3D11Texture2D** _Texture);
	void Create_Simple_State(ID3D11SamplerState ** _sampler);
	void Create_Resource_Veiw(ID3D11ShaderResourceView** _ResourceVeiw, ID3D11Resource* _resource);
	void Create_Blend_State(ID3D11BlendState** _blend);
	void Make_A_Model(vector<XMFLOAT3> _verts, SIMPLE_VERTEX* _Model, UINT _Index, ID3D11Buffer** VertexBuffer, ID3D11Buffer** IndexBuffer, const vector<unsigned int> Index);

};

//************************************************************
//************ CREATION OF OBJECTS & RESOURCES ***************
//************************************************************
void DEMO_APP::CreateVertexBuffer(SIMPLE_VERTEX* _Vertex, int _Size, ID3D11Buffer** _VertexBuffer) // Double Pointer is sending in the Memory address of the variable and then returning it
{
	// This is zeroing out Teh memory of The Paramater;
	D3D11_BUFFER_DESC _BufferDes;
	ZeroMemory(&_BufferDes, sizeof(_BufferDes));
	_BufferDes.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	_BufferDes.ByteWidth = sizeof(SIMPLE_VERTEX) * _Size;
	_BufferDes.CPUAccessFlags = 0;
	_BufferDes.MiscFlags = 0;
	_BufferDes.StructureByteStride = 0;
	_BufferDes.Usage = D3D11_USAGE_IMMUTABLE;
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = _Vertex;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;


	SetupGraphics::GetInstance()->GetDevice()->CreateBuffer(&_BufferDes, &InitData, _VertexBuffer);


}
void DEMO_APP::CreateVertexBuffer(vector<SIMPLE_VERTEX>* _Vertex, int _Size, ID3D11Buffer** _VertexBuffer) // Double Pointer is sending in the Memory address of the variable and then returning it
{
	// This is zeroing out Teh memory of The Paramater;
	D3D11_BUFFER_DESC _BufferDes;
	ZeroMemory(&_BufferDes, sizeof(_BufferDes));
	_BufferDes.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	_BufferDes.ByteWidth = sizeof(SIMPLE_VERTEX) * _Size;
	_BufferDes.CPUAccessFlags = 0;
	_BufferDes.MiscFlags = 0;
	_BufferDes.StructureByteStride = 0;
	_BufferDes.Usage = D3D11_USAGE_IMMUTABLE;
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = _Vertex;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;


	SetupGraphics::GetInstance()->GetDevice()->CreateBuffer(&_BufferDes, &InitData, _VertexBuffer);


}
void DEMO_APP::CreateVertexBuffer(OBJ_VERT* _Vertex, int _Size, ID3D11Buffer** _VertexBuffer) // Double Pointer is sending in the Memory address of the variable and then returning it
{
	// This is zeroing out Teh memory of The Paramater;
	D3D11_BUFFER_DESC _BufferDes;
	ZeroMemory(&_BufferDes, sizeof(_BufferDes));
	_BufferDes.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	_BufferDes.ByteWidth = sizeof(OBJ_VERT) * _Size;
	_BufferDes.CPUAccessFlags = 0;
	_BufferDes.MiscFlags = 0;
	_BufferDes.StructureByteStride = 0;
	_BufferDes.Usage = D3D11_USAGE_IMMUTABLE;
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = _Vertex;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;


	SetupGraphics::GetInstance()->GetDevice()->CreateBuffer(&_BufferDes, &InitData, _VertexBuffer);


}
void  DEMO_APP::Create_Depth_Stencil(ID3D11Texture2D** _DepthStencil)
{
	D3D11_TEXTURE2D_DESC DescDepthBuffer;
	DescDepthBuffer.Width = BACKBUFFER_WIDTH;
	DescDepthBuffer.Height = BACKBUFFER_HEIGHT;
	DescDepthBuffer.MipLevels = 1;
	DescDepthBuffer.ArraySize = 1;
	DescDepthBuffer.Format = DXGI_FORMAT_D32_FLOAT;
	DescDepthBuffer.SampleDesc.Count = 1;
	DescDepthBuffer.SampleDesc.Quality = 0;
	DescDepthBuffer.Usage = D3D11_USAGE_DEFAULT;
	DescDepthBuffer.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	DescDepthBuffer.CPUAccessFlags = 0;
	DescDepthBuffer.MiscFlags = 0;

	SetupGraphics::GetInstance()->GetDevice()->CreateTexture2D(&DescDepthBuffer, NULL, _DepthStencil);
}
void DEMO_APP::CreateIndexBuffer(vector<unsigned int>* indices, UINT _size, ID3D11Buffer** _IndexBuffer)
{
	D3D11_BUFFER_DESC IndexBufferDesc;
	IndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	IndexBufferDesc.ByteWidth = sizeof(unsigned int) * _size;
	IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	IndexBufferDesc.CPUAccessFlags = 0;
	IndexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA IndexInitData;
	IndexInitData.pSysMem = indices;
	IndexInitData.SysMemPitch = 0;
	IndexInitData.SysMemSlicePitch = 0;


	SetupGraphics::GetInstance()->GetDevice()->CreateBuffer(&IndexBufferDesc, &IndexInitData, _IndexBuffer);


}
void DEMO_APP::CreateIndexBuffer(const UINT* indices, UINT _size, ID3D11Buffer** _IndexBuffer)
{
	D3D11_BUFFER_DESC IndexBufferDesc;
	IndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	IndexBufferDesc.ByteWidth = sizeof(unsigned int) * _size;
	IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	IndexBufferDesc.CPUAccessFlags = 0;
	IndexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA IndexInitData;
	IndexInitData.pSysMem = indices;
	IndexInitData.SysMemPitch = 0;
	IndexInitData.SysMemSlicePitch = 0;


	SetupGraphics::GetInstance()->GetDevice()->CreateBuffer(&IndexBufferDesc, &IndexInitData, _IndexBuffer);


}
void DEMO_APP::CreateRasterizer(ID3D11RasterizerState** _Rasterizer, int count)
{
	D3D11_RASTERIZER_DESC rasterizerState;
	ZeroMemory(&rasterizerState, sizeof(rasterizerState));
	rasterizerState.FillMode = D3D11_FILL_SOLID;
	if (count == 1)
		rasterizerState.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;

	if (count == 0)
		rasterizerState.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;


	rasterizerState.FrontCounterClockwise = false;
	rasterizerState.AntialiasedLineEnable = true;
	rasterizerState.DepthClipEnable = true;
	rasterizerState.ScissorEnable = FALSE;
	rasterizerState.MultisampleEnable = false;
	SetupGraphics::GetInstance()->GetDevice()->CreateRasterizerState(&rasterizerState, _Rasterizer);


}
void DEMO_APP::Create_Depth_Stencil_State(ID3D11DepthStencilState** _depth)
{
	D3D11_DEPTH_STENCIL_DESC dsDesc;

	// Depth test parameters
	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

	// Stencil test parameters
	dsDesc.StencilEnable = FALSE;
	dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	dsDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

	// Stencil operations if pixel is front-facing
	dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing
	dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	SetupGraphics::GetInstance()->GetDevice()->CreateDepthStencilState(&dsDesc, _depth);
}
void DEMO_APP::CreateConstBuffer(ID3D11Buffer** _ConstBuffer, Object _matrix)
{

	D3D11_BUFFER_DESC m_constbuff;
	ZeroMemory(&m_constbuff, sizeof(m_constbuff));
	m_constbuff.ByteWidth = sizeof(_matrix);
	m_constbuff.Usage = D3D11_USAGE_DYNAMIC;
	m_constbuff.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	m_constbuff.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	m_constbuff.MiscFlags = 0;
	m_constbuff.StructureByteStride = 0;



	SetupGraphics::GetInstance()->GetDevice()->CreateBuffer(&m_constbuff, NULL, _ConstBuffer);

}
void DEMO_APP::CreateConstBuffer(ID3D11Buffer** _ConstBuffer, Scene _matrix2)
{


	D3D11_BUFFER_DESC m_constbuff;
	ZeroMemory(&m_constbuff, sizeof(m_constbuff));
	m_constbuff.ByteWidth = sizeof(_matrix2);
	m_constbuff.Usage = D3D11_USAGE_DYNAMIC;
	m_constbuff.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	m_constbuff.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	m_constbuff.MiscFlags = 0;
	m_constbuff.StructureByteStride = 0;



	SetupGraphics::GetInstance()->GetDevice()->CreateBuffer(&m_constbuff, NULL, _ConstBuffer);
}
void DEMO_APP::CreateConstBuffer(ID3D11Buffer** _ConstBuffer, Animation _animate)
{
	D3D11_BUFFER_DESC m_constbuff;
	ZeroMemory(&m_constbuff, sizeof(m_constbuff));
	m_constbuff.ByteWidth = sizeof(_animate);
	m_constbuff.Usage = D3D11_USAGE_DYNAMIC;
	m_constbuff.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	m_constbuff.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	m_constbuff.MiscFlags = 0;
	m_constbuff.StructureByteStride = 0;



	SetupGraphics::GetInstance()->GetDevice()->CreateBuffer(&m_constbuff, NULL, _ConstBuffer);
}
void DEMO_APP::DrawVerts(UINT _VertextCount, D3D11_PRIMITIVE_TOPOLOGY _pTopology)
{
	m_deviceContext->IASetPrimitiveTopology(_pTopology);
	m_deviceContext->Draw(_VertextCount, 0);

}
void DEMO_APP::Map_UnMap_Variables(ID3D11Buffer** _ConstBuffer, Animation _Shader)
{
	D3D11_MAPPED_SUBRESOURCE m_MapSource;
	SetupGraphics::GetInstance()->GetDeviceContext()->Map(*_ConstBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &m_MapSource);
	memcpy(m_MapSource.pData, &_Shader, sizeof(_Shader));
	SetupGraphics::GetInstance()->GetDeviceContext()->Unmap(*_ConstBuffer, NULL);

}
void DEMO_APP::Map_UnMap_Variables(ID3D11Buffer** _ConstBuffer, Object _Shader)
{
	D3D11_MAPPED_SUBRESOURCE m_MapSource;
	SetupGraphics::GetInstance()->GetDeviceContext()->Map(*_ConstBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &m_MapSource);
	memcpy(m_MapSource.pData, &_Shader, sizeof(Object));
	SetupGraphics::GetInstance()->GetDeviceContext()->Unmap(*_ConstBuffer, NULL);

}
void DEMO_APP::Map_UnMap_Variables(ID3D11Buffer** _ConstBuffer, Scene _Shader)
{
	D3D11_MAPPED_SUBRESOURCE m_MapSource;
	SetupGraphics::GetInstance()->GetDeviceContext()->Map(*_ConstBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &m_MapSource);
	memcpy(m_MapSource.pData, &_Shader, sizeof(Scene));
	SetupGraphics::GetInstance()->GetDeviceContext()->Unmap(*_ConstBuffer, NULL);
}
void DEMO_APP::ClearBuffer(float* _RGBA)
{
	SetupGraphics::GetInstance()->GetDeviceContext()->ClearRenderTargetView(*SetupGraphics::GetInstance()->GetRenderTargetView(), _RGBA);

}
void DEMO_APP::Set_PS_VS_INPUTLAYOUT_VB_CB(UINT _stride, UINT _zero, ID3D11PixelShader** _PixalShader, ID3D11VertexShader** _VertexShader, ID3D11Buffer** _VertexBuffer, ID3D11Buffer** ConstBuffer, ID3D11InputLayout** _InputLayout)
{
	_stride = sizeof(SIMPLE_VERTEX);

	m_deviceContext->IASetVertexBuffers(0, 1, _VertexBuffer, &_stride, &_zero);
	m_deviceContext->PSSetShader(*_PixalShader, 0, 0);
	m_deviceContext->VSSetShader(*_VertexShader, 0, 0);
	m_deviceContext->IASetInputLayout(*_InputLayout);
	m_deviceContext->VSSetConstantBuffers(0, 1, ConstBuffer);




}
void DEMO_APP::CreateStencilVeiw(ID3D11Texture2D* __depthStencil, ID3D11DepthStencilView** _DepthVeiw)
{
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	descDSV.Format = DXGI_FORMAT_D32_FLOAT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	descDSV.Flags = 0;
	descDSV.ViewDimension;
	SetupGraphics::GetInstance()->GetDevice()->CreateDepthStencilView(__depthStencil, NULL, _DepthVeiw);


}
void DEMO_APP::Create_A_Texture(ID3D11Texture2D** _Texture)
{

	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
	desc.Width = numbers_test_width;
	desc.Height = numbers_test_height;
	desc.ArraySize = 1;
	desc.MipLevels = 8;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	//desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitalData[numbers_test_numlevels];
	for (int i = 0; i < numbers_test_numlevels; i++)
	{
		unsigned int temp = 0;

		InitalData[i].pSysMem = &numbers_test_pixels[numbers_test_leveloffsets[i]];
		InitalData[i].SysMemPitch = (numbers_test_width >> i) * sizeof(UINT);
		InitalData[i].SysMemSlicePitch = 0;
	}
	//InitalData
	SetupGraphics::GetInstance()->GetDevice()->CreateTexture2D(&desc, InitalData, _Texture);
}
void DEMO_APP::Create_Simple_State(ID3D11SamplerState ** _sampler)
{
	D3D11_SAMPLER_DESC Sample;
	Sample.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	Sample.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	Sample.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	Sample.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	Sample.MinLOD = -3.402823466e+38F;
	Sample.MaxLOD = 3.402823466e+38F;
	Sample.MipLODBias = 0.0f;
	Sample.MaxAnisotropy = 1;
	Sample.ComparisonFunc = D3D11_COMPARISON_NEVER;
	Sample.MipLODBias = 0.0f;

	SetupGraphics::GetInstance()->GetDevice()->CreateSamplerState(&Sample, _sampler);
}
void DEMO_APP::Create_Resource_Veiw(ID3D11ShaderResourceView** _ResourceVeiw, ID3D11Resource* _resource)
{
	D3D11_SHADER_RESOURCE_VIEW_DESC m_ResourceVeiw;
	m_ResourceVeiw.Texture2D.MipLevels = 8;
	m_ResourceVeiw.Texture2D.MostDetailedMip = 0;
	m_ResourceVeiw.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	m_ResourceVeiw.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SetupGraphics::GetInstance()->GetDevice()->CreateShaderResourceView(_resource, &m_ResourceVeiw, _ResourceVeiw);

}
void DEMO_APP::Create_Blend_State(ID3D11BlendState** _blend)
{
	D3D11_BLEND_DESC Blend;
	ZeroMemory(&Blend, sizeof(Blend));
	Blend.RenderTarget[0].BlendEnable = TRUE;
	Blend.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	Blend.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	Blend.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	Blend.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	Blend.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	Blend.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	Blend.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;


	SetupGraphics::GetInstance()->GetDevice()->CreateBlendState(&Blend, _blend);
}
void DEMO_APP::Make_A_Model(vector<XMFLOAT3> _vertes, SIMPLE_VERTEX* _model, UINT _Index, ID3D11Buffer** _VertexBuffer, ID3D11Buffer** IndexBuffer, const vector<unsigned int> Index)
{
	vector<SIMPLE_VERTEX>_Model;

	for (unsigned int i = 0; i < _vertes.size(); i++)
	{
		_model[i].m_position.x = (_vertes[i].x);
		_model[i].m_position.y = (_vertes[i].y);
		_model[i].m_position.z = (_vertes[i].z);
		_model[i].m_position.w = 1;
		_Model.push_back(_model[i]);
	}

	vector<unsigned int> index;
	for (int i = 0; i < Index.size(); i++)
	{
		index.push_back(Index[i]);
	}




	CreateVertexBuffer(&_Model, sizeof(_Model.size()), _VertexBuffer);
	CreateIndexBuffer(&index, index.size(), IndexBuffer);


}
bool DEMO_APP::LoadObj(const char* Path, vector<XMFLOAT3>& out_vertices, vector<XMFLOAT2>& out_uvs, vector<XMFLOAT3>& out_normals, vector<unsigned int>&Index)
{

	vector<XMFLOAT3> temp_vertices;
	vector<XMFLOAT2> temp_uvs;
	vector<XMFLOAT3> temp_normals;
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	//fstream* fin;
	FILE* file = fopen(Path, "r");

	if (file == NULL){
		printf("Impossible to open the file !\n");
		return false;
	}
	while (true)
	{
		char lineheader[128];
		int res = fscanf(file, "%s", lineheader);
		if (res == EOF)
		{
			break;
		}

		if (strcmp(lineheader, "v") == 0)
		{
			XMFLOAT3 vertex;
			fscanf(file, "%f %f %f \n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineheader, "vt") == 0)
		{
			XMFLOAT2 vertexuv;
			fscanf(file, "%f %f\n", &vertexuv.x, &vertexuv.y);
			vertexuv.x = vertexuv.x;
			vertexuv.y = 1 - vertexuv.y;
			temp_uvs.push_back(vertexuv);
		}
		else if (strcmp(lineheader, "vn") == 0)
		{
			XMFLOAT3 vertexn;
			fscanf(file, "%f %f %f \n", &vertexn.x, &vertexn.y, &vertexn.z);
			temp_normals.push_back(vertexn);
		}
		else if (strcmp(lineheader, "f") == 0)
		{
			string m_vertex1, m_vertex2, m_vertex3;
			unsigned int m_vertexindex[3], m_UVIndex[3], normalIndex[3];
			int matches = fscanf(file, " %d/%d/%d %d/%d/%d %d/%d/%d \n", &m_vertexindex[0], &m_UVIndex[0], &normalIndex[0], &m_vertexindex[1], &m_UVIndex[1], &normalIndex[1], &m_vertexindex[2], &m_UVIndex[2], &normalIndex[2]);
			if (matches != 9){
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(m_vertexindex[0]);
			vertexIndices.push_back(m_vertexindex[1]);
			vertexIndices.push_back(m_vertexindex[2]);

			uvIndices.push_back(m_UVIndex[0]);
			uvIndices.push_back(m_UVIndex[1]);
			uvIndices.push_back(m_UVIndex[2]);

			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);


		}





	}

	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		unsigned int VertexIndex = vertexIndices[i];
		XMFLOAT3 temp = temp_vertices[VertexIndex - 1];
		Index.push_back(VertexIndex - 1);
	}

	for (unsigned int i = 0; i < temp_vertices.size(); i++)
		out_vertices.push_back(temp_vertices[i]);

	for (unsigned int i = 0; i < temp_uvs.size(); i++)
	{
		out_uvs.push_back(temp_uvs[i]);
	}






}
DEMO_APP::DEMO_APP(HINSTANCE hinst, WNDPROC proc)
{
	// ****************** BEGIN WARNING ***********************// 
	// WINDOWS CODE, I DON'T TEACH THIS YOU MUST KNOW IT ALREADY! 
#pragma region Setting Up WinMian
	application = hinst;
	appWndProc = proc;

	WNDCLASSEX  wndClass;
	ZeroMemory(&wndClass, sizeof(wndClass));
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.lpfnWndProc = appWndProc;
	wndClass.lpszClassName = L"DirectXApplication";
	wndClass.hInstance = application;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOWFRAME);
	//wndClass.hIcon   = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_FSICON));
	RegisterClassEx(&wndClass);

	RECT window_size = { 0, 0, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT };
	AdjustWindowRect(&window_size, WS_OVERLAPPEDWINDOW, false);

	window = CreateWindow(L"DirectXApplication", L"Lab 1a Line Land", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, window_size.right - window_size.left, window_size.bottom - window_size.top,
		NULL, NULL, application, this);

	ShowWindow(window, SW_SHOW);

#pragma endregion

	CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&m_factory);

	SetupGraphics::GetInstance()->Set_Device_DeviceContex_SwapChain(window);
#pragma region Setting up the Swapchain And Device

	//	DXGI_SWAP_CHAIN_DESC sd;
	//	HRESULT m_result;
	//	ZeroMemory(&sd, sizeof(sd));
	//	sd.BufferCount = 1;
	//	sd.BufferDesc.Width = 500;
	//	sd.BufferDesc.Height = 500;
	//	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//	sd.BufferDesc.RefreshRate.Numerator = 60;
	//	sd.BufferDesc.RefreshRate.Denominator = 1;
	//	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//	sd.OutputWindow = window;
	//	sd.SampleDesc.Count = 1;
	//	sd.SampleDesc.Quality = 0;
	//	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	//	sd.Windowed = true;
	//
	//	// TODO: PART 1 STEP 3b
	//	//
	//	const D3D_FEATURE_LEVEL Featurelevel = D3D_FEATURE_LEVEL_11_0;
	//	D3D_FEATURE_LEVEL RequestedLevel;
	//	UINT CreateDeviceFlags = 0;
	//#ifdef _DEBUG
	//	CreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	//#endif
	//
	//	m_result = D3D11CreateDeviceAndSwapChain(NULL,
	//		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE,
	//
	//		NULL,
	//		CreateDeviceFlags,
	//		&Featurelevel,
	//		1, D3D11_SDK_VERSION,
	//		&sd, &m_SwapChain,
	//		&m_device, 0,
	//		&m_deviceContext);
	//
	//	if (m_result == E_INVALIDARG)
	//	{
	//		m_result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &Featurelevel, 0, D3D11_SDK_VERSION, &sd, &m_SwapChain, &m_device, &RequestedLevel, &m_deviceContext);
	//	}
	//
	//	//if (FAILED(m_result))
	//	//	return m_result;
	//
	//	ID3D11Texture2D* pBackBuffer;
	//	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	//	m_device->CreateRenderTargetView(pBackBuffer, NULL, &m_RenderTargetVeiw);
	//
	//	vp.Width = 500;
	//	vp.Height = 500;
	//	vp.MinDepth = 0.0f;
	//	vp.MaxDepth = 1.0f;
	//	vp.TopLeftX = 0;
	//	vp.TopLeftY = 0;
	//	pBackBuffer->Release();
	//	m_position.x = 0;
	//	m_position.y = 0;
	//
	//	Translate[0] = 0.0f;
	//	Translate[1] = 0.0f;
	//	Translate[2] = 0.0f;
	//	Translate[3] = 0.0f;
#pragma endregion


#if Lab9
#pragma region Setting Up the World,Veiw,Projection Matrix


	/*m_time.Restart();
	float _XYZ[4];
	_XYZ[0] = 0;
	_XYZ[1] = 0;
	_XYZ[2] = 0;
	_XYZ[3] = 0;

	float _xyz[4];
	_xyz[0] = 0;
	_xyz[1] = 0;
	_xyz[2] = 5.f;
	_xyz[3] = 0;

	float Xscale;
	float Yscale;
	Yscale = (1 / tan(65 * ((3.1459f / 180)) / 2));
	Xscale = Yscale * (float)((float)BACKBUFFER_WIDTH / (float)BACKBUFFER_HEIGHT);
	VeiwMAtrix = Matrix4x4Identity();
	VeiwMAtrix = Matrix4X4Multiplication(&Translation(_XYZ), &VeiwMAtrix);
	VeiwMAtrix = Inverse(VeiwMAtrix);
	ProjectionMatrix = PrespectiveProjection(Xscale, Yscale, 0.1f, 100);

	XMMATRIX proj = XMMatrixPerspectiveFovLH(65.f, BACKBUFFER_WIDTH / BACKBUFFER_HEIGHT, 0.1f, 100.f);
	memcpy_s(&ProjectionMatrix.m_matrix4x4, sizeof(XMMATRIX), &proj, sizeof(XMMATRIX));

	WorldMatrix = Matrix4x4Identity();
	WorldMatrix = Translation(_xyz);*/
#pragma endregion


	SIMPLE_VERTEX Cube[776];
	for (int i = 0; i < 776; i++)
	{
		Cube[i].m_position.x = Cube_data[i].pos[0];
		Cube[i].m_position.y = Cube_data[i].pos[1];
		Cube[i].m_position.z = Cube_data[i].pos[2];
		Cube[i].m_position.w = 1;

		Cube[i].UV.x = Cube_data[i].uvw[0];
		Cube[i].UV.y = Cube_data[i].uvw[1];

		Cube[i].Nrm.x = Cube_data[i].nrm[0];
		Cube[i].Nrm.y = Cube_data[i].nrm[1];

		Cube[i].m_Color.x = 1;
		Cube[i].m_Color.y = 1;
		Cube[i].m_Color.z = 1;
		Cube[i].m_Color.w = 1;
	}

#pragma region Triangle Verts


	// 0
	Triangle[0].m_position.x = 0.0f;
	Triangle[0].m_position.y = 0.0f;
	Triangle[0].m_position.z = 0;
	Triangle[0].m_position.w = 1;
	// 1
	Triangle[1].m_position.x = -0.5f;
	Triangle[1].m_position.y = 0.5f;
	Triangle[1].m_position.z = 0;
	Triangle[1].m_position.w = 1;
	// 2
	Triangle[2].m_position.x = 0.5f;
	Triangle[2].m_position.y = 0.5f;
	Triangle[2].m_position.z = 0;
	Triangle[2].m_position.w = 1;


	//3
	Triangle[3].m_position.x = 0.0f;
	Triangle[3].m_position.y = 2.0f;
	Triangle[3].m_position.z = 0;
	Triangle[3].m_position.w = 1;

	// 4					 
	Triangle[4].m_position.x = 2.0f;
	Triangle[4].m_position.y = 0.0f;
	Triangle[4].m_position.z = 0;
	Triangle[4].m_position.w = 1;
	//5						 
	Triangle[5].m_position.x = 0.5f;
	Triangle[5].m_position.y = -0.5f;
	Triangle[5].m_position.z = 0;
	Triangle[5].m_position.w = 1;

	//6						 
	Triangle[6].m_position.x = 0.0f;
	Triangle[6].m_position.y = -1.1f;
	Triangle[6].m_position.z = 0;
	Triangle[6].m_position.w = 1;

	Triangle[7].m_position.x = -2.0f;
	Triangle[7].m_position.y = 0.0f;
	Triangle[7].m_position.z = 0;
	Triangle[7].m_position.w = 1;

	Triangle[8].m_position.x = -0.5f;
	Triangle[8].m_position.y = -0.5f;
	Triangle[8].m_position.z = 0;
	Triangle[8].m_position.w = 1;

	Triangle[9].m_position.x = -1.5f;
	Triangle[9].m_position.y = -2.0f;
	Triangle[9].m_position.z = 0;
	Triangle[9].m_position.w = 1;


	Triangle[10].m_position.x = 1.5f;
	Triangle[10].m_position.y = -2.0f;
	Triangle[10].m_position.z = 0;
	Triangle[10].m_position.w = 1;

	// 3D Space
	Triangle[11].m_position.x = 0.0f;
	Triangle[11].m_position.y = 0.0f;
	Triangle[11].m_position.z = 0.5;
	Triangle[11].m_position.w = 1;
	// 1
	Triangle[12].m_position.x = -0.5f;
	Triangle[12].m_position.y = 0.5f;
	Triangle[12].m_position.z = 0.5;
	Triangle[12].m_position.w = 1;
	// 2
	Triangle[13].m_position.x = 0.5f;
	Triangle[13].m_position.y = 0.5f;
	Triangle[13].m_position.z = 0.5;
	Triangle[13].m_position.w = 1;


	//3
	Triangle[14].m_position.x = 0.0f;
	Triangle[14].m_position.y = 2.0f;
	Triangle[14].m_position.z = 0.5;
	Triangle[14].m_position.w = 1;

	// 4
	Triangle[15].m_position.x = 2.0f;
	Triangle[15].m_position.y = 0.0f;
	Triangle[15].m_position.z = 0.5;
	Triangle[15].m_position.w = 1;
	//5
	Triangle[16].m_position.x = 0.5f;
	Triangle[16].m_position.y = -0.5f;
	Triangle[16].m_position.z = 0.5;
	Triangle[16].m_position.w = 1;

	//6
	Triangle[17].m_position.x = 0.0f;
	Triangle[17].m_position.y = -1.1f;
	Triangle[17].m_position.z = 0.5;
	Triangle[17].m_position.w = 1;

	Triangle[18].m_position.x = -2.0f;
	Triangle[18].m_position.y = 0.0f;
	Triangle[18].m_position.z = 0.5;
	Triangle[18].m_position.w = 1;

	Triangle[19].m_position.x = -0.5f;
	Triangle[19].m_position.y = -0.5f;
	Triangle[19].m_position.z = 0.5;
	Triangle[19].m_position.w = 1;

	Triangle[20].m_position.x = -1.5f;
	Triangle[20].m_position.y = -2.0f;
	Triangle[20].m_position.z = 0.5;
	Triangle[20].m_position.w = 1;


	Triangle[21].m_position.x = 1.5f;
	Triangle[21].m_position.y = -2.0f;
	Triangle[21].m_position.z = 0.5;
	Triangle[21].m_position.w = 1;

	for (int i = 0; i < 21; i++)
	{
		Triangle[i].m_Color.x = Triangle[i].m_position.x;
		Triangle[i].m_Color.y = Triangle[i].m_position.y;
		Triangle[i].m_Color.z = Triangle[i].m_position.z;
		Triangle[i].m_Color.w = Triangle[i].m_position.w;
	}

	//CreateVertexBuffer(Triangle, 22, &VertexBuffer);
#pragma endregion
	CreateVertexBuffer(Cube, 776, &VertexBuffer);
	CreateVertexBuffer(Triangle, 22, &Vertex_Buffer_Star);



#endif
#if Lab10

#pragma region Setting Up the World,Veiw,Projection Matrix


	m_time.Restart();
	float _XYZ[4];
	_XYZ[0] = 0;
	_XYZ[1] = 0;
	_XYZ[2] = 0;
	_XYZ[3] = 0;

	float _xyz[4];
	_xyz[0] = 0;
	_xyz[1] = 1.0f;
	_xyz[2] = 0;
	_xyz[3] = 0;

	float Xscale;
	float Yscale;


	Yscale = (1 / tan(65 * ((3.1459f / 180)) / 2));
	Xscale = Yscale * (float)((float)BACKBUFFER_WIDTH / (float)BACKBUFFER_HEIGHT);

	XMMATRIX matrix1;
	matrix1 = XMLoadFloat4x4(&VeiwMatrix);
	matrix1 = XMMatrixIdentity();
	matrix1 = XMMatrixMultiply(matrix1, XMMatrixTranslation(0.0f, 0.0f, 0.0f));
	VeiwMAtrix = Matrix4x4Identity();
	VeiwMAtrix = Matrix4X4Multiplication(&Translation(_XYZ), &VeiwMAtrix);
	XMVECTOR vertex;
	XMFLOAT3 vertex1;
	vertex1.x = 0;
	vertex1.y = 0;
	vertex1.z = 1;
	vertex = XMLoadFloat3(&vertex1);
	XMMatrixInverse(&vertex, matrix1);
	XMStoreFloat4x4(&VeiwMatrix, matrix1);
	//ProjectionMatrix = PrespectiveProjection(Xscale, Yscale, 0.1f, 100);
	XMMATRIX pmatrix;
	pmatrix = XMMatrixPerspectiveFovLH(65.f, BACKBUFFER_WIDTH / BACKBUFFER_HEIGHT, 0.1f, 100.f);
	XMStoreFloat4x4(&ProjectionMatrix, pmatrix);

	float XYZ[4];
	XYZ[0] = 0.0f;
	XYZ[1] = 0.0f;
	XYZ[2] = 0.0f;
	XYZ[3] = 0.0f;
	XMMATRIX matrix2;
	matrix2 = XMLoadFloat4x4(&WorldMatrix);
	matrix2 = XMMatrixIdentity();
	matrix2 = XMMatrixTranslation(0, 1.0f, 0);

	XMStoreFloat4x4(&WorldMatrix, matrix2);
	/*WorldMatrix = Matrix4x4Identity();
	WorldMatrix = Translation(_xyz)*/;

	WorldMatrixGrid = Matrix4x4Identity();
	WorldMatrixGrid = Translation(XYZ);
#pragma endregion
	/*float Spacing = 0.1f;
	float startx = -0.5f;
	float startz = -0.5f;
	float endX = 3.5f;
	float endZ = 1.5f;
	for (int i = 0; i < 44; i += 2)
	{
	Grid[i].m_position[0] = startx;
	Grid[i].m_position[1] = 0;
	Grid[i].m_position[2] = startz;
	Grid[i].m_position[3] = 1;

	Grid[i + 1].m_position[0] = endX;
	Grid[i + 1].m_position[1] = 0;
	Grid[i + 1].m_position[2] = startz;
	Grid[i + 1].m_position[3] = 1;

	startz += Spacing;*/



	//Spacing = 0.2f;
	//startx = -0.5f;
	//endX = 1.5f;
	//startz = -0.5f;
	//endZ = 1.5f;

	//for (int i = 45; i < 89; i += 2)
	//{
	//	Grid[i].m_position[0] = startx;
	//	Grid[i].m_position[1] = 0;
	//	Grid[i].m_position[2] = startz;
	//	Grid[i].m_position[3] = 1;

	//	Grid[i + 1].m_position[0] = startx;
	//	Grid[i + 1].m_position[1] = 0;
	//	Grid[i + 1].m_position[2] = endZ;
	//	Grid[i + 1].m_position[3] = 1;

	//	startx += Spacing;

	//};

	//CreateVertexBuffer(Grid, 89, &GridVertexBuffer);

	//unsigned int Lines[] = {

	//	0, 1,
	//	2, 3,
	//	4, 5,
	//	6, 7,
	//	8, 9,
	//	10, 11,
	//	12, 13,
	//	14, 15,
	//	16, 17,
	//	18, 19,
	//	20, 21,
	//	22, 23,
	//	24, 25,
	//	26, 27,
	//	28, 29,
	//	30, 31,
	//	32, 33,
	//	34, 35,
	//	36, 37,
	//	38, 39,
	//	40, 41,
	//	45, 46,
	//	47, 48,
	//	49, 50,
	//	51, 52,
	//	53, 54,
	//	55, 56,
	//	57, 58,
	//	59, 60,
	//	61, 62,
	//	63, 64,
	//	65, 66,
	//	67, 68,
	//	69, 70,
	//	71, 72,
	//	73, 74,
	//	75, 76,
	//	77, 78,
	//	79, 80,
	//	81, 82,
	//	83, 84,
	//	85, 86,


	//};
	//CreateIndexBuffer(Lines, ARRAYSIZE(Lines), &m_GridIndexBuffer);
	numberanimations.frame = 0;
	numberanimations.totalframes = 4;
	numberanimations.width = 512 / 4;


#endif
#pragma region ForLoop Setting World Matrix Projection Matrix


	vs_shaderWorld.m_WorldMatrix = WorldMatrix;
	vs_shaderVeiwProjection.m_VeiwMatrix = VeiwMatrix;
	vs_shaderVeiwProjection.m_ProjectionMatrix = ProjectionMatrix;

#pragma endregion

#pragma region Creating a Pixal Shader and Vertex Shader

	// TODO: PART 2 STEP 7
	SetupGraphics::GetInstance()->GetDevice()->CreatePixelShader(Trivial_PS, sizeof(Trivial_PS), NULL, &m_PixalShader);
	SetupGraphics::GetInstance()->GetDevice()->CreateVertexShader(VertexShader, sizeof(VertexShader), NULL, &m_VertexShader);

	// this is the grid Vertex buffer
	SetupGraphics::GetInstance()->GetDevice()->CreatePixelShader(GridPixelShader, sizeof(GridPixelShader), NULL, &m_GridPixalShader);
	SetupGraphics::GetInstance()->GetDevice()->CreateVertexShader(GridVertexShader, sizeof(GridVertexShader), NULL, &m_GridVertexShader);
	SetupGraphics::GetInstance()->GetDevice()->CreatePixelShader(PixelShaderGundam, sizeof(PixelShaderGundam), NULL, &GundamPixalShader);


#pragma endregion
#pragma region Input layouts  and Creating them plus Creating a raster blend state


	D3D11_INPUT_ELEMENT_DESC Layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UVCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NmrCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }

	};

	D3D11_INPUT_ELEMENT_DESC GridLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },

	};
	// TODO: PART 2 STEP 8b

	SetupGraphics::GetInstance()->GetDevice()->CreateInputLayout(Layout,
		4, VertexShader, sizeof(VertexShader), &m_InputLayout);

	SetupGraphics::GetInstance()->GetDevice()->CreateInputLayout(GridLayout,
		1, GridVertexShader, sizeof(GridVertexShader), &m_InputLayoutGrid);

	Create_A_Texture(&m_texture);
	Create_Resource_Veiw(&ResourceVeiw, m_texture);
	Create_Simple_State(&Sampler);
	Create_Blend_State(&m_blendstate);
#pragma endregion
#if Lab8
	unsigned int verts[] = {
		0, 1, 3,
		2, 0, 3,
		0, 2, 4,
		4, 5, 0,
		7, 1, 0,
		0, 8, 7,
		0, 9, 8,
		0, 6, 9,
		0, 10, 6,
		5, 10, 0,
		14, 12, 11,
		11, 13, 14,
		15, 13, 11,
		11, 16, 15,
		21, 16, 11,
		17, 21, 11,
		11, 12, 18,
		18, 19, 11,
		11, 19, 20,
		17, 11, 20,
		2, 3, 14,
		14, 13, 2,
		4, 2, 15,
		13, 15, 2,
		5, 4, 15,
		15, 16, 5,
		10, 5, 16,
		16, 21, 10,
		6, 10, 21,
		21, 17, 6,
		9, 6, 17,
		17, 20, 9,
		8, 9, 20,
		20, 19, 8,
		7, 8, 19,
		19, 18, 7,
		1, 7, 18,
		18, 12, 1,
		3, 1, 12,
		12, 14, 3

	};
	CreateIndexBuffer(Cube_indicies, ARRAYSIZE(Cube_indicies), &m_IndexBuffer);
	CreateIndexBuffer(verts, ARRAYSIZE(verts), &m_Index_Buffer_Star);

#endif
#pragma region Making ConstBuffers making a zbuffer 

	CreateConstBuffer(&m_ConstbufferObject, vs_shaderWorld);
	CreateConstBuffer(&m_ConstbufferSeen, vs_shaderVeiwProjection);
	CreateConstBuffer(&PixalBuffer, numberanimations);
	Create_Depth_Stencil(&m_DepthBuffer);
	// TODO: PART 3 STEP 4b
	CreateStencilVeiw(m_DepthBuffer, &pDSV);
	CreateRasterizer(&g_pRasterState, 1);
	CreateRasterizer(&g_pRasterState2, 0);
	Create_Depth_Stencil_State(&DepthState);
#pragma endregion


#pragma region Load Object file to Be Renderd

	LoadObj("GundamStrike.obj", vertices, uvs, normals, Index);

	//Make_A_Model(vertices, Gundam,Index.size(), &Vertex_Buffer_Star, &m_Index_Buffer_Star,Index);
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		Gundam[i].m_position.x = (vertices[i].x * 0.01f);
		Gundam[i].m_position.y = (vertices[i].y * 0.01f);
		Gundam[i].m_position.z = (vertices[i].z * 0.01f);
		Gundam[i].m_position.w = 1;


	}
	for (unsigned int i = 0; i < uvs.size(); i++)
	{
		Gundam[i].UV.x = uvs[i].x;
		Gundam[i].UV.y = uvs[i].y;
	}
	unsigned int Indecies[10359];
	for (unsigned int i = 0; i < Index.size(); i++)
		Indecies[i] = Index[i];


	CreateVertexBuffer(Gundam, 4211, &Vertex_Buffer_Star);
	CreateIndexBuffer(Indecies, sizeof(Indecies), &m_Index_Buffer_Star);

	CreateDDSTextureFromFile(SetupGraphics::GetInstance()->GetDevice(), L"FreedomRen.dds", &m_Gundam, &m_Gundamveiw);



#pragma endregion
}

//************************************************************
//************ EXECUTION *************************************
//************************************************************

bool DEMO_APP::Run()
{

	m_time.Signal();

	D3D11_RECT rects[1];
	rects[0].left = 0;
	rects[0].right = 500;
	rects[0].top = 0;
	rects[0].bottom = 500;

#if !Lab8
	// TODO: PART 4 STEP 2	
	m_deviceContext->OMSetRenderTargets(1, &m_RenderTargetVeiw, pDSV);
	m_deviceContext->RSSetViewports(1, &vp);
	m_deviceContext->ClearDepthStencilView(pDSV, D3D11_CLEAR_FLAG::D3D11_CLEAR_STENCIL, 1, NULL);
	float ARGB[] = { 0, 0, 1, 1 };
	ClearBuffer(ARGB); // Made a Function to Clear the BackBuffer to a Certain Color; 


#else
#pragma region Camrea Movement

	// WorldMatrix = Matrix4x4Identity(); 
	float temp[4] = { 0, 0.5, 0, 0 };
	//	WorldMatrix = Translation(temp);
	//WorldMatrix = Inverse(WorldMatrix);
	float m_position[4];
	/*m_position[0] = WorldMatrix._41;
	m_position[1] = WorldMatrix._42;
	m_position[2] = WorldMatrix._43;
	m_position[3] = WorldMatrix._44;*/

	XMMATRIX matrix1;
	XMMATRIX matrix2;
	matrix1 = XMLoadFloat4x4(&WorldMatrix);
	matrix1 = XMMatrixIdentity();
	matrix1 = XMMatrixMultiply(XMMatrixRotationY(m_time.Delta()), matrix1);
	matrix1 = XMMatrixMultiply( matrix1,XMMatrixRotationX(m_time.Delta()));
	XMStoreFloat4x4(&WorldMatrix, matrix1);
	/* = Matrix4X4Multiplication(&Matrix4x4_Roation_on_Y_Axis(), &WorldMatrix);
	WorldMatrix = Matrix4X4Multiplication(&Matrix4x4_Roation_on_X_Axis(m_time.Delta()), &WorldMatrix);*/

	//WorldMatrix = Matrix4X4Multiplication(&WorldMatrix,&TempMatrixY);
	/*WorldMatrix._41 = m_position[0];
	WorldMatrix._42 = m_position[1];
	WorldMatrix._43 = m_position[2];
	WorldMatrix._44 = m_position[3];*/
	// = Inverse(WorldMatrix);
	POINT m_mouse;
	HCURSOR m_cursor;

	
	vs_shaderWorld.m_WorldMatrix = WorldMatrix;
	


	MY_Matrix NewViewMatrix = VeiwMAtrix;

	if (GetAsyncKeyState('W') && m_timer <= 0)
	{
		m_timer = 24.0;
	//	Translate[2] -= m_time.Delta() * 15.5f;
		matrix1 = XMLoadFloat4x4(&VeiwMatrix);
		matrix1 = XMMatrixMultiply(XMMatrixTranslation(0,0 , -m_time.Delta() * 15.5f), matrix1);
		XMStoreFloat4x4(&VeiwMatrix, matrix1);
		//VeiwMAtrix = Matrix4X4Multiplication(&Translation(Translate), &VeiwMAtrix);
	}

	if (GetAsyncKeyState('S') && m_timer <= 0)
	{
		m_timer = 24.0;
		Translate[2] += m_time.Delta()* 15.5f;
		matrix1 = XMLoadFloat4x4(&VeiwMatrix);
		matrix1 = XMMatrixMultiply(XMMatrixTranslation(0,0,m_time.Delta() * 15.5f), matrix1);
		XMStoreFloat4x4(&VeiwMatrix, matrix1);
		VeiwMAtrix = Matrix4X4Multiplication(&Translation(Translate), &VeiwMAtrix);
	}

	if (GetAsyncKeyState('A') && m_timer <= 0)
	{
		m_timer = 24.0;
		Translate[0] -= m_time.Delta() * 15.5f;
		VeiwMAtrix = Matrix4X4Multiplication(&Translation(Translate), &VeiwMAtrix);

		matrix1 = XMLoadFloat4x4(&VeiwMatrix);
		matrix1 = XMMatrixMultiply(XMMatrixTranslation(m_time.Delta() * 15.5f,0,0), matrix1);
		XMStoreFloat4x4(&VeiwMatrix, matrix1);
	}

	if (GetAsyncKeyState('D') && m_timer <= 0)
	{
		m_timer = 24.0;
		Translate[0] += m_time.Delta() * 15.5f;
		VeiwMAtrix = Matrix4X4Multiplication(&Translation(Translate), &VeiwMAtrix);
		matrix1 = XMLoadFloat4x4(&VeiwMatrix);
		matrix1 = XMMatrixMultiply(XMMatrixTranslation(-m_time.Delta() * 15.5f, 0, 0), matrix1);
		XMStoreFloat4x4(&VeiwMatrix, matrix1);
	}

	if (GetAsyncKeyState(VK_SPACE) && m_timer <= 0)
	{
		m_timer = 24.0;
		//Translate[1] += Translate[1];
		Translate[1] -= m_time.Delta()*15.7f;
		VeiwMAtrix = Matrix4X4Multiplication(&Translation(Translate), &VeiwMAtrix);

		matrix1 = XMLoadFloat4x4(&VeiwMatrix);
		matrix1 = XMMatrixMultiply(XMMatrixTranslation(0,m_time.Delta() * 15.5f, 0), matrix1);
		XMStoreFloat4x4(&VeiwMatrix, matrix1);
	}
	else if (GetAsyncKeyState(VK_LSHIFT) && m_timer <= 0)
	{
		m_timer = 24.0;
		Translate[1] += m_time.Delta()*15.7f;
		VeiwMAtrix = Matrix4X4Multiplication(&Translation(Translate), &VeiwMAtrix);

		matrix1 = XMLoadFloat4x4(&VeiwMatrix);
		matrix1 = XMMatrixMultiply(XMMatrixTranslation(0, -m_time.Delta() * 15.5f, 0), matrix1);
		XMStoreFloat4x4(&VeiwMatrix, matrix1);
	}
	else if (GetCursorPos(&m_mouse) && GetAsyncKeyState(VK_LBUTTON) && m_timer <= 0)
	{
		m_timer = 24.0;
		VeiwMAtrix = Inverse(VeiwMAtrix);
		float m_position[3];
		m_position[0] = VeiwMAtrix.m_matrix4x42D[3][0];
		m_position[1] = VeiwMAtrix.m_matrix4x42D[3][1];
		m_position[2] = VeiwMAtrix.m_matrix4x42D[3][2];

		MY_Matrix TempMatrixX = Matrix4x4Identity();
		TempMatrixX = Matrix4X4Multiplication(&TempMatrixX, &Matrix4x4_Roation_on_X_Axis(0.01));

		VeiwMAtrix = Matrix4X4Multiplication(&TempMatrixX, &VeiwMAtrix);
		VeiwMAtrix.m_matrix4x42D[3][0] = m_position[0];
		VeiwMAtrix.m_matrix4x42D[3][1] = m_position[1];
		VeiwMAtrix.m_matrix4x42D[3][2] = m_position[2];
		VeiwMAtrix = Inverse(VeiwMAtrix);

	}
	else if (GetCursorPos(&m_mouse) && GetAsyncKeyState(VK_RBUTTON) && m_timer <= 0)
	{
		m_timer = 24.0f;
		VeiwMAtrix = Inverse(VeiwMAtrix);
		float m_position[3];
		m_position[0] = VeiwMAtrix.m_matrix4x42D[3][0];
		m_position[1] = VeiwMAtrix.m_matrix4x42D[3][1];
		m_position[2] = VeiwMAtrix.m_matrix4x42D[3][2];
		MY_Matrix TempMatrixY = Matrix4x4Identity();
		TempMatrixY = Matrix4X4Multiplication(&TempMatrixY, &Matrix4x4_Roation_on_Y_Axis(0.01));
		VeiwMAtrix = Matrix4X4Multiplication(&VeiwMAtrix, &TempMatrixY);
		VeiwMAtrix.m_matrix4x42D[3][0] = m_position[0];
		VeiwMAtrix.m_matrix4x42D[3][1] = m_position[1];
		VeiwMAtrix.m_matrix4x42D[3][2] = m_position[2];
		//VeiwMAtrix = Matrix4X4Multiplication(&VeiwMAtrix, &Translation(Translate));
		VeiwMAtrix = Inverse(VeiwMAtrix);

	}
	else
	{
		Translate[1] = 0;
		Translate[0] = 0;
		Translate[2] = 0;
	}

	//VeiwMAtrix = Inverse(VeiwMAtrix);
#pragma endregion




	

		vs_shaderVeiwProjection.m_VeiwMatrix = VeiwMatrix;
	
	numberanimations.height = (numberanimations.frame / numberanimations.totalframes) * numberanimations.width;
	Map_UnMap_Variables(&PixalBuffer, numberanimations);
	Map_UnMap_Variables(&m_ConstbufferObject, vs_shaderWorld);
	Map_UnMap_Variables(&m_ConstbufferSeen, vs_shaderVeiwProjection);


	UINT m_srtide = sizeof(SIMPLE_VERTEX);
	UINT m_zero = 0;
	SetupGraphics::GetInstance()->GetDeviceContext()->ClearDepthStencilView(pDSV, D3D11_CLEAR_FLAG::D3D11_CLEAR_DEPTH, 1, NULL);

	float ARGB[] = { 0, 0, 0, 1 };
	ClearBuffer(ARGB);
	SetupGraphics::GetInstance()->GetDeviceContext()->OMSetBlendState(m_blendstate, 0, 0xFFFFFFFF);
#pragma region Setting All Your Variables to do your first draw 

	SetupGraphics::GetInstance()->GetDeviceContext()->PSSetSamplers(0, 1, &Sampler);
	SetupGraphics::GetInstance()->GetDeviceContext()->RSSetState(g_pRasterState);
	SetupGraphics::GetInstance()->GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &m_srtide, &m_zero);
	SetupGraphics::GetInstance()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	SetupGraphics::GetInstance()->GetDeviceContext()->IASetInputLayout(m_InputLayout);

	SetupGraphics::GetInstance()->GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	//VS
	SetupGraphics::GetInstance()->GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	SetupGraphics::GetInstance()->GetDeviceContext()->VSSetConstantBuffers(0, 1, &m_ConstbufferObject);
	SetupGraphics::GetInstance()->GetDeviceContext()->VSSetConstantBuffers(1, 1, &m_ConstbufferSeen);
	//m_deviceContext->VSSetShaderResources(0, 1, &ResourceVeiw);
	//m_deviceContext->VSSetShaderResources(1, 1, &ResourceVeiw);
	//RS
	//m_deviceContext->RSSetScissorRects(1, rects);
	SetupGraphics::GetInstance()->GetDeviceContext()->RSSetViewports(1, &SetupGraphics::GetInstance()->vp);
	//m_deviceContext->RSSetState(g_pRasterState);
	//->RSSetState(g_pRasterState);
	//PS
	SetupGraphics::GetInstance()->GetDeviceContext()->PSSetConstantBuffers(0, 1, &PixalBuffer);
	SetupGraphics::GetInstance()->GetDeviceContext()->PSSetShader(m_PixalShader, NULL, 0);
	SetupGraphics::GetInstance()->GetDeviceContext()->PSSetShaderResources(0, 1, &ResourceVeiw);
	//OM
	//m_deviceContext->OMSetDepthStencilState(DepthState, 1);SSSSSSSSSSSSSSSSSSSWWWWWWWWWWWWWWWWWWWWWWSSSSSSSSSSSSSSSSSSSSSSSS
	SetupGraphics::GetInstance()->GetDeviceContext()->OMSetRenderTargets(1, SetupGraphics::GetInstance()->GetRenderTargetView(), pDSV);

	SetupGraphics::GetInstance()->GetDeviceContext()->DrawIndexed(1692, 0, 0);
#pragma endregion
#pragma region Setting all the variables To do the Second Draw 

	SetupGraphics::GetInstance()->GetDeviceContext()->RSSetState(g_pRasterState2);

	/*Map_UnMap_Variables(&m_ConstbufferSeen, vs_shaderVeiwProjection);
	Map_UnMap_Variables(&m_ConstbufferObject, vs_worldMatrix);
*/


	SetupGraphics::GetInstance()->GetDeviceContext()->IASetVertexBuffers(0, 1, &GridVertexBuffer, &m_srtide, &m_zero);
	SetupGraphics::GetInstance()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	SetupGraphics::GetInstance()->GetDeviceContext()->IASetInputLayout(m_InputLayoutGrid);
	SetupGraphics::GetInstance()->GetDeviceContext()->IASetIndexBuffer(m_GridIndexBuffer, DXGI_FORMAT_R32_UINT, 0);


	SetupGraphics::GetInstance()->GetDeviceContext()->VSSetConstantBuffers(0, 1, &m_ConstbufferObject);
	SetupGraphics::GetInstance()->GetDeviceContext()->VSSetConstantBuffers(1, 1, &m_ConstbufferSeen);
	SetupGraphics::GetInstance()->GetDeviceContext()->VSSetShader(m_GridVertexShader, NULL, 0);
	SetupGraphics::GetInstance()->GetDeviceContext()->PSSetShader(m_GridPixalShader, NULL, 0);

	SetupGraphics::GetInstance()->GetDeviceContext()->DrawIndexed(84, 0, 0);
#pragma endregion
#pragma region Setting All Your Variables to do your Thrid draw 

	SetupGraphics::GetInstance()->GetDeviceContext()->IASetVertexBuffers(0, 1, &Vertex_Buffer_Star, &m_srtide, &m_zero);
	SetupGraphics::GetInstance()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	SetupGraphics::GetInstance()->GetDeviceContext()->IASetInputLayout(m_InputLayout);

	SetupGraphics::GetInstance()->GetDeviceContext()->IASetIndexBuffer(m_Index_Buffer_Star, DXGI_FORMAT_R32_UINT, 0);
	////VS
	SetupGraphics::GetInstance()->GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	SetupGraphics::GetInstance()->GetDeviceContext()->VSSetConstantBuffers(0, 1, &m_ConstbufferObject);
	SetupGraphics::GetInstance()->GetDeviceContext()->VSSetConstantBuffers(1, 1, &m_ConstbufferSeen);
	////RS
	
	////PS
	SetupGraphics::GetInstance()->GetDeviceContext()->PSSetShader(GundamPixalShader, NULL, 0);
	SetupGraphics::GetInstance()->GetDeviceContext()->PSSetShaderResources(0, 1, &m_Gundamveiw);
	////OM
	SetupGraphics::GetInstance()->GetDeviceContext()->DrawIndexed(Index.size(), 0, 0);
#pragma endregion

	if (m_timer > 0 || numbertimer > 0)
	{
		m_timer -= 1;
		numbertimer -= 1;
	}
	if (numbertimer <= 0)
	{
		numbertimer = 6000.0f;
		numberanimations.frame += 1;
	}


	if (numberanimations.frame == 4)
	{
		numberanimations.frame = 0;
		numberanimations.height = 0;

	}

#endif

#if Lab7
	Set_PS_VS_INPUTLAYOUT_VB_CB(m_srtide, m_zero, &m_PixalShader, &m_VertexShader, &m_buffer, &m_ConstantBuffer, &m_InputLayout);
	DrawVerts(VertCount, D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	Set_PS_VS_INPUTLAYOUT_VB_CB(m_srtide, m_zero, &m_PixalShader, &m_VertexShader, &m_InterVertex[0], &m_ConstantBuffer, &m_InputLayout);
	DrawVerts(VertCount, D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);


	Set_PS_VS_INPUTLAYOUT_VB_CB(m_srtide, m_zero, &m_PixalShader, &m_VertexShader, &m_InterVertex[1], &m_ConstantBuffer, &m_InputLayout);
	DrawVerts(VertCount, D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	//Set_PS_VS_INPUTLAYOUT_VB_CB(m_srtide, m_zero, &m_PixalShader, &m_VertexShader, &TriangleVertexBuffer, &m_ConstantBuffer, &m_InputLayout);
	//DrawVerts(VertCount, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	for (size_t i = 0; i < 50; i++)
	{
		Set_PS_VS_INPUTLAYOUT_VB_CB(m_srtide, m_zero, &m_PixalShader, &m_VertexShader, &m_Checkeard[i], &m_ConstantBuffer, &m_InputLayout);
		DrawVerts(4, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	}
#endif

	SetupGraphics::GetInstance()->GetSwapChain()->Present(0, 0);

	return true;
	}

//************************************************************
//************ DESTRUCTION ***********************************
//************************************************************

bool DEMO_APP::ShutDown()
{
	// TODO: PART 1 STEP 6
	//	m_device->Release();
	//m_deviceContext->Release();
	//m_RenderTargetVeiw->Release();
	//m_buffer->Release();
	//	m_ConstantBuffer->Release();
	m_InputLayout->Release();
	m_RenderTargetVeiw->Release();
	m_SwapChain->Release();
	m_PixalShader->Release();
	m_VertexShader->Release();
	m_ConstbufferObject->Release();
	m_DepthBuffer->Release();
	//	GridVertexBuffer->Release();
	m_IndexBuffer->Release();
	g_pRasterState->Release();
	g_pRasterState2->Release();
	pDSV->Release();
	DepthState->Release();
	m_ConstbufferSeen->Release();
	m_GridPixalShader->Release();
	m_GridVertexShader->Release();
	m_InputLayoutGrid->Release();
	//	m_GridIndexBuffer->Release();
	pDSV->Release();
	Sampler->Release();
	m_blendstate->Release();
	m_texture->Release();
	//m_Resource->Release();
	ResourceVeiw->Release();
	//PixalConstbuffer->Release();
	m_factory->Release();
	//	m_buffer->Release();
	PixalBuffer->Release();
	UnregisterClass(L"DirectXApplication", application);

	return true;
}

//************************************************************
//************ WINDOWS RELATED *******************************
//************************************************************

// ****************** BEGIN WARNING ***********************// 
// WINDOWS CODE, I DON'T TEACH THIS YOU MUST KNOW IT ALREADY!

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int)
{
	srand(unsigned int(time(0)));
	DEMO_APP myApp(hInstance, (WNDPROC)WndProc);
	MSG msg; ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT && myApp.Run())
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	myApp.ShutDown();
	return 0;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (GetAsyncKeyState(VK_ESCAPE))
		message = WM_DESTROY;
	switch (message)
	{
	case (WM_DESTROY) : { PostQuitMessage(0); }

	case (WM_SIZE) :
	{
#pragma region Rezing the Window 

		//m_deviceContext->OMSetRenderTargets(0, 0, 0);
		//m_RenderTargetVeiw->Release();
		pDSV->Release();
		m_DepthBuffer->Release();
		DepthState->Release();
		m_deviceContext->Flush();
		m_SwapChain->ResizeBuffers(1, 0, 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0x2);
		//DXGI_SWAP_CHAIN_DESC swap;
		DXGI_SWAP_CHAIN_DESC swap;
		m_SwapChain->GetDesc(&swap);
		//swap.OutputWindow = window;
		swap.SampleDesc.Count = 1;
		swap.SampleDesc.Quality = 0;
		swap.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		ID3D11Texture2D* Buffer;
		m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&Buffer);
		m_device->CreateRenderTargetView(Buffer, NULL, &m_RenderTargetVeiw);
		//m_SwapChain->Release();
		Buffer->Release();
		D3D11_DEPTH_STENCIL_DESC dsDesc;
		//		g_pRasterState->Release();
		//	g_pRasterState2->Release();
		// Depth test parameters
		dsDesc.DepthEnable = true;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
		// Stencil test parameters
		dsDesc.StencilEnable = FALSE;
		dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
		dsDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
		// Stencil operations if pixel is front-facing
		dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		// Stencil operations if pixel is back-facing
		dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		m_device->CreateDepthStencilState(&dsDesc, &DepthState);
		D3D11_TEXTURE2D_DESC DescDepthBuffer;
		DescDepthBuffer.Width = swap.BufferDesc.Width;
		DescDepthBuffer.Height = swap.BufferDesc.Height;
		DescDepthBuffer.MipLevels = 1;
		DescDepthBuffer.ArraySize = 1;
		DescDepthBuffer.Format = DXGI_FORMAT_D32_FLOAT;
		DescDepthBuffer.SampleDesc.Count = 1;
		DescDepthBuffer.SampleDesc.Quality = 0;
		DescDepthBuffer.Usage = D3D11_USAGE_DEFAULT;
		DescDepthBuffer.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		DescDepthBuffer.CPUAccessFlags = 0;
		DescDepthBuffer.MiscFlags = 0;
		m_device->CreateTexture2D(&DescDepthBuffer, NULL, &m_DepthBuffer);
		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		descDSV.Format = DXGI_FORMAT_D32_FLOAT;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;
		descDSV.Flags = 0;
		descDSV.ViewDimension;
		m_device->CreateDepthStencilView(m_DepthBuffer, NULL, &pDSV);
		m_deviceContext->OMSetRenderTargets(1, &m_RenderTargetVeiw, pDSV);
		vp.Height = swap.BufferDesc.Height;
		vp.Width = swap.BufferDesc.Width;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		m_deviceContext->RSSetViewports(1, &vp);

		XMMATRIX proj = XMMatrixPerspectiveFovLH(65.f, swap.BufferDesc.Width / swap.BufferDesc.Height, 0.1f, 100.f);
		memcpy_s(&ProjectionMatrix.m_matrix4x4, sizeof(XMMATRIX), &proj, sizeof(XMMATRIX));
		break;
#pragma endregion

	}

	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}



//********************* END WARNING ************************//