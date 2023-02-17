#include "jhSceneManager.h"
#include "jhTransform.h"
#include "jhMeshRenderer.h"
#include "jhRenderer.h"
#include "jhResources.h"
#include "jhTexture.h"

namespace jh
{
	Scene* SceneManager::mPlayScene = nullptr;

	void SceneManager::Initialize()
	{
		mPlayScene = new Scene();
		mPlayScene->Initialize();

		GameObject* obj = new GameObject();
		Transform* tr = new Transform();
		tr->SetPosition(Vector3(0.f, 0.f, 0.f));
		obj->AddComponent(tr);

		MeshRenderer* mr = new MeshRenderer();
		obj->AddComponent(mr);

		Mesh* mesh = Resources::Find<Mesh>(L"RectMesh");
		Material* material = Resources::Find<Material>(L"RectMaterial");

		Vector2 vec2(1.f, 1.f);
		material->SetData(eGPUParam::Vector2, &vec2);

		mr->SetMaterial(material);
		mr->SetMesh(mesh);

		Texture* texture = Resources::Load<Texture>(L"SmileTexture", L"Smile.png");
		texture->BindShader(eShaderStage::PS, 0);

		mPlayScene->AddGameObject(obj, eLayerType::Player);
	}

	void SceneManager::Update()
	{
		mPlayScene->Update();
	}

	void SceneManager::FixedUpdate()
	{
		mPlayScene->FixedUpdate();
	}

	void SceneManager::Render()
	{
		mPlayScene->Render();
	}
}
