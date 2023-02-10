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

	// ���� ������
	extern Vertex vertexes[4];

	// �޽�
	extern Mesh* mesh;

	// ����
	//extern Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;
	extern Microsoft::WRL::ComPtr<ID3D11Buffer> triangleConstantBuffer;

	extern Shader* shader;

	//// ���ؽ� ���̴�
	//extern Microsoft::WRL::ComPtr<ID3DBlob> triangleVSBlob;
	//extern Microsoft::WRL::ComPtr<ID3D11VertexShader> triangleVS;

	//// �ȼ� ���̴�
	//extern Microsoft::WRL::ComPtr<ID3DBlob> trianglePSBlob;
	//extern Microsoft::WRL::ComPtr<ID3D11PixelShader> trianglePS;

	//// input layout
	//extern Microsoft::WRL::ComPtr<ID3D11InputLayout> triangleLayout;

	void Initialize();
	void Release();
}

