#pragma once
#include "CommonInclude.h"
#include "jhMath.h"
#include "jhGraphicDevice_DX11.h"

#include "jhMesh.h"
#include "jhShader.h"
#include "jhConstantBuffer.h"

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
	// ���̴�
	extern Shader* shader;
	// �������
	extern ConstantBuffer* constantBuffers[];

	void Initialize();
	void Release();
}

