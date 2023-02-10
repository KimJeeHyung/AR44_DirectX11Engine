#include "jhSceneManager.h"
#include "jhTransform.h"
#include "jhMeshRenderer.h"

namespace jh
{
	void SceneManager::Initialize()
	{
		mPlayScene = new Scene();
		mPlayScene->Initialize();

		GameObject* obj = new GameObject();
		Transform* tr = new Transform();
		obj->AddComponent(tr);

		MeshRenderer* meshRenderer = new MeshRenderer();
		obj->AddComponent(meshRenderer);

		//mPlayScene->AddGameObject(obj);
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
