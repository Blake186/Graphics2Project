#pragma once
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
// TODO: PART 1 STEP 1b
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <dxgi.h>
#include <vector>
//#include "Math.h"
#pragma comment(lib, "dxgi.lib")
using namespace DirectX;
class Model
{
protected: 
	ID3D11Buffer* VertexBuffer;
	ID3D11Buffer* ConstantBuffer;
	ID3D11Buffer* IndexBuffer;
	XMFLOAT4X4 WorldMatrix;

public:
	Model();
	~Model();
	// Getters 


	// Setters


};

