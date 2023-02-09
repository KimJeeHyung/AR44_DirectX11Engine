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

	// ���� ������
	extern Vertex vertexes[4];

	// ���ؽ� ����
	extern ID3D11Buffer* triangleBuffer;
	extern ID3DBlob* errorBlob;

	// �ε��� ����
	extern ID3D11Buffer* triangleIndexBuffer;
	extern ID3D11Buffer* triangleConstantBuffer;

	// ���ؽ� ���̴�
	extern ID3DBlob* triangleVSBlob;
	extern ID3D11VertexShader* triangleVS;

	// �ȼ� ���̴�
	extern ID3DBlob* trianglePSBlob;
	extern ID3D11PixelShader* trianglePS;

	// input layout
	extern ID3D11InputLayout* triangleLayout;

	void Initialize();
	void Release();
}

