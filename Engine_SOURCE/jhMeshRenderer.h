#pragma once
#include "jhComponent.h"
#include "jhMesh.h"
#include "jhShader.h"

using namespace jh::graphics;
namespace jh
{
	class MeshRenderer : public Component
	{
	public:
		MeshRenderer();
		virtual ~MeshRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void SetMesh(Mesh* mesh) { mMesh = mesh; }
		void SetShader(Shader* shader) { mShader = shader; }

	private:
		Mesh* mMesh;
		Shader* mShader;
	};
}
