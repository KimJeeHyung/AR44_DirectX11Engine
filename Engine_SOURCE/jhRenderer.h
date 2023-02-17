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
		Vector4 pos;
		Vector4 color;
		Vector2 uv;
	};

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Vector4 pos;
	};

	CBUFFER(MaterialCB, CBSLOT_MATERIAL)
	{
		int iData;
		float fData;
		Vector2 xy;
		Vector3 xyz;
		Vector4 xyzw;
		Matrix matrix;
	};

	// 정점 데이터
	extern Vertex vertexes[4];
	// 상수버퍼
	extern ConstantBuffer* constantBuffers[];
	// 샘플러
	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[];

	void Initialize();
	void Release();
}

