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

	void Initialize();
	void Release();
}

