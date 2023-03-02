#include "jhEditor.h"
#include "jhMesh.h"
#include "jhResources.h"
#include "jhMaterial.h"
#include "jhTransform.h"
#include "jhMeshRenderer.h"

namespace jh
{
	void Editor::Initialize()
	{
		// 충돌체의 종류 갯수만큼만 있으면 된다.
		mDebugObjects.resize((UINT)eColliderType::End);

		std::shared_ptr<Mesh> rectMesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> rectMaterial = Resources::Find<Material>(L"RectMaterial");

		mDebugObjects[(UINT)eColliderType::Rect] = new DebugObject();
		mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<Transform>();
		MeshRenderer* renderer = mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<MeshRenderer>();

		renderer->SetMaterial(rectMaterial);
		renderer->SetMesh(rectMesh);


	}

	void Editor::Run()
	{
		Update();
		FixedUpdate();
		Render();
	}

	void Editor::Update()
	{
	}

	void Editor::FixedUpdate()
	{
	}

	void Editor::Render()
	{
	}

	void Editor::Release()
	{
	}

	void Editor::DebugRender(graphics::DebugMesh& mesh)
	{
	}
}