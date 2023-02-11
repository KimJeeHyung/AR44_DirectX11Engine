#pragma once
#include "jhGraphics.h"

using namespace jh::enums;

namespace jh::graphics
{
	class ConstantBuffer : GpuBuffer
	{
	public:
		ConstantBuffer();
		virtual ~ConstantBuffer();

		bool Create(size_t size);
		void Bind(void* data);
		void SetPipeline(eShaderStage stage);

	private:
		const eCBType mType;
	};
}
