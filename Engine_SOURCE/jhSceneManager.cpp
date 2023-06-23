#include "jhSceneManager.h"
#include "jhTransform.h"
#include "jhMeshRenderer.h"
#include "jhRenderer.h"
#include "jhResources.h"
#include "jhTexture.h"
#include "jhPhoenixScript.h"
#include "jhCamera.h"
#include "jhCameraScript.h"
#include "jhSpriteRenderer.h"
#include "jhGridScript.h"
#include "jhObject.h"
#include "jhFadeScript.h"
#include "jhTestScene.h"
#include "jhMainTitleScene.h"
#include "jhTitleScene.h"
#include "jhEpisodeSelectScene.h"
#include "jhBeforeTalkScene.h"
#include "jhCourtScene.h"

namespace jh
{
	std::vector<Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initialize()
	{
		mScenes.resize((UINT)eSceneType::End);

		mScenes[(UINT)eSceneType::Test] = new TestScene;
		mScenes[(UINT)eSceneType::MainTitle] = new MainTitleScene;
		mScenes[(UINT)eSceneType::Title] = new TitleScene;
		mScenes[(UINT)eSceneType::EpisodeSelect] = new EpisodeSelectScene;
		mScenes[(UINT)eSceneType::BeforeTalk] = new BeforeTalkScene;
		mScenes[(UINT)eSceneType::Court] = new CourtScene;

		mActiveScene = mScenes[(UINT)eSceneType::MainTitle];

		for (Scene* scene : mScenes)
		{
			scene->Initialize();
		}
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::FixedUpdate()
	{
		mActiveScene->FixedUpdate();
	}

	void SceneManager::Render()
	{
		mActiveScene->Render();
	}

	void SceneManager::Destroy()
	{
		mActiveScene->Destroy();
	}

	void SceneManager::Release()
	{
		for (Scene* scene : mScenes)
		{
			delete scene;
			scene = nullptr;
		}
	}

	void SceneManager::LoadScene(eSceneType type)
	{
		if (mActiveScene)
			mActiveScene->OnExit();

		// 씬이 바뀔 때 DontDestroy 오브젝트는 다음 씬으로 같이 넘겨줘야 한다.
		std::vector<GameObject*> gameObjs = mActiveScene->GetDontDestroyGameObjects();
		mActiveScene = mScenes[(UINT)type];

		for (GameObject* obj : gameObjs)
		{
			eLayerType type = obj->GetLayerType();
			mActiveScene->AddGameObject(obj, type);
		}

		mActiveScene->OnEnter();
	}
}
