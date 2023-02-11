#include "jhSceneManager.h"
#include "jhTransform.h"
#include "jhMeshRenderer.h"

namespace jh
{
	Scene* SceneManager::mPlayScene = nullptr;

	void SceneManager::Initialize()
	{
		mPlayScene = new Scene();
		mPlayScene->Initialize();

		GameObject* obj = new GameObject();
		Transform* tr = new Transform();
		tr->SetPosition(Vector3(-0.2f, 0.2f, 0.f));
		obj->AddComponent(tr);

		//MeshRenderer* meshRenderer = new MeshRenderer();
		//obj->AddComponent(meshRenderer);

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
