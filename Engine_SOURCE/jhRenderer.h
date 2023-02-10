#pragma once
#include "CommonInclude.h"
#include "jhMath.h"
#include "jhGraphicDevice_DX11.h"

#include "jhMesh.h"
#include "jhShader.h"

using namespace jh::math;
using namespace jh::graphics;

namespace jh::renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
	};

	// 정점 데이터
	extern Vertex vertexes[4];

	// 메쉬
	extern Mesh* mesh;

	// 버퍼
	//extern Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;
	extern Microsoft::WRL::ComPtr<ID3D11Buffer> triangleConstantBuffer;

	extern Shader* shader;

	//// 버텍스 셰이더
	//extern Microsoft::WRL::ComPtr<ID3DBlob> triangleVSBlob;
	//extern Microsoft::WRL::ComPtr<ID3D11VertexShader> triangleVS;

	//// 픽셀 셰이더
	//extern Microsoft::WRL::ComPtr<ID3DBlob> trianglePSBlob;
	//extern Microsoft::WRL::ComPtr<ID3D11PixelShader> trianglePS;

	//// input layout
	//extern Microsoft::WRL::ComPtr<ID3D11InputLayout> triangleLayout;

	void Initialize();
	void Release();
}

