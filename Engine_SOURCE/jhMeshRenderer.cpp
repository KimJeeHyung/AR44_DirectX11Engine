#include "jhMeshRenderer.h"
#include "jhGameObject.h"
#include "jhTransform.h"

namespace jh
{
	MeshRenderer::MeshRenderer() :
		Component(eComponentType::Mesh)
	{
	}

	MeshRenderer::~MeshRenderer()
	{
	}

	void MeshRenderer::Initialize()
	{
	}

	void MeshRenderer::Update()
	{
	}

	void MeshRenderer::FixedUpdate()
	{
	}

	void MeshRenderer::Render()
	{
		GetOwner()->GetComponent<Transform>()->SetConstantBuffer();

		mShader->Binds();
		mMesh->BindBuffer();

		mMesh->Render();
	}
}