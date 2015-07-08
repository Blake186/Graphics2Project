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
class Camera
{
	XMFLOAT4X4 VeiwMatrix;
	XMFLOAT4X4 WorldMatrix;
	XMFLOAT4X4 ProjectionMatrix;
public:
	Camera();
	~Camera();
};

