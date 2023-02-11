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

	// 정점 데이터
	extern Vertex vertexes[4];
	// 메쉬
	extern Mesh* mesh;
	// 셰이더
	extern Shader* shader;
	// 상수버퍼
	extern ConstantBuffer* constantBuffers[];

	void Initialize();
	void Release();
}

