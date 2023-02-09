#pragma once
#include "CommonInclude.h"
#include "yaMath.h"
#include "yaGraphicDevice_DX11.h"

using namespace ya::math;
using namespace ya::graphics;

namespace ya::renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
	};

	// 정점 데이터
	extern Vertex vertexes[4];

	// 버텍스 버퍼
	extern ID3D11Buffer* triangleBuffer;
	extern ID3DBlob* errorBlob;

	// 인덱스 버퍼
	extern ID3D11Buffer* triangleIndexBuffer;
	extern ID3D11Buffer* triangleConstantBuffer;

	// 버텍스 셰이더
	extern ID3DBlob* triangleVSBlob;
	extern ID3D11VertexShader* triangleVS;

	// 픽셀 셰이더
	extern ID3DBlob* trianglePSBlob;
	extern ID3D11PixelShader* trianglePS;

	// input layout
	extern ID3D11InputLayout* triangleLayout;

	void Initialize();
	void Release();
}

