#pragma once
#include "jhComponent.h"
#include "jhMesh.h"
#include "jhMaterial.h"

using namespace jh::graphics;
namespace jh
{
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void SetMesh(std::shared_ptr<Mesh> mesh) { mMesh = mesh; }
		void SetMaterial(std::shared_ptr<Material> material) { mMaterial = material; }

	private:
		std::shared_ptr<Mesh> mMesh;
		std::shared_ptr<Material> mMaterial;
	};
}
