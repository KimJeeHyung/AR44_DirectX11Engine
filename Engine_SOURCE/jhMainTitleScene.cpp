#include "jhMainTitleScene.h"
#include "jhTransform.h"
#include "jhMeshRenderer.h"
#include "jhRenderer.h"
#include "jhResources.h"
#include "jhTexture.h"
#include "jhPlayerScript.h"
#include "jhCamera.h"
#include "jhCameraScript.h"
#include "jhSpriteRenderer.h"
#include "jhGridScript.h"
#include "jhObject.h"
#include "jhFadeScript.h"
#include "jhInput.h"
#include "jhCollider2D.h"
#include "jhPlayer.h"
#include "jhMonster.h"
#include "jhCollisionManager.h"

namespace jh
{
	MainTitleScene::MainTitleScene() :
		Scene(eSceneType::MainTitle)
	{
	}

	MainTitleScene::~MainTitleScene()
	{
	}

	void MainTitleScene::Initialize()
	{
		// 메인 카메라
		//GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		//Camera* cameraComp = cameraObj->AddComponent<Camera>();
		//cameraComp->TurnLayerMask(eLayerType::UI, false);
		//cameraComp->TurnLayerMask(eLayerType::Background, false);
		//cameraObj->AddComponent<CameraScript>();
		//mainCamera = cameraComp;

		// UI 카메라
		GameObject* UICameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* UICameraComp = UICameraObj->AddComponent<Camera>();
		UICameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		UICameraComp->DisableLayerMasks();
		UICameraComp->TurnLayerMask(eLayerType::UI, true);
		UICameraComp->TurnLayerMask(eLayerType::Background, true);
		//mainCamera = UICameraComp;

		// 메인화면 배경
		{
			GameObject* mainBackground = object::Instantiate<GameObject>(eLayerType::Background, this);
			mainBackground->SetName(L"MainBackground");
			Transform* bgTr = mainBackground->GetComponent<Transform>();
			bgTr->SetPosition(Vector3(0.f, 0.f, 0.1f));
			bgTr->SetScale(Vector3(16.f, 9.f, 1.f));
			SpriteRenderer* spriteRenderer = mainBackground->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> rectMesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"MBMaterial");
			spriteRenderer->SetMesh(rectMesh);
			spriteRenderer->SetMaterial(spriteMaterial);
		}

		// 메인화면 타이틀
		{
			GameObject* mainTitle = object::Instantiate<GameObject>(eLayerType::UI, this);
			mainTitle->SetName(L"MainTitle");
			Transform* mtTr = mainTitle->GetComponent<Transform>();
			mtTr->SetPosition(Vector3(0.f, 1.f, 0.1f));
			mtTr->SetScale(Vector3(14.f, 5.5f, 1.f));
			SpriteRenderer* spriteRenderer = mainTitle->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> rectMesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"MTMaterial");
			spriteRenderer->SetMesh(rectMesh);
			spriteRenderer->SetMaterial(spriteMaterial);
		}

		// 메인화면 저작권
		{
			GameObject* mainCopy = object::Instantiate<GameObject>(eLayerType::UI, this);
			mainCopy->SetName(L"MainCopy");
			Transform* mcTr = mainCopy->GetComponent<Transform>();
			mcTr->SetPosition(Vector3(0.f, -4.f, 0.1f));
			mcTr->SetScale(Vector3(9.5f, 0.45f, 1.f));
			SpriteRenderer* spriteRenderer = mainCopy->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> rectMesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"MCMaterial");
			spriteRenderer->SetMesh(rectMesh);
			spriteRenderer->SetMaterial(spriteMaterial);
		}

		Scene::Initialize();
	}

	void MainTitleScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::ENTER))
		{
			SceneManager::LoadScene(eSceneType::Title);
		}

		Scene::Update();
	}

	void MainTitleScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void MainTitleScene::Render()
	{
		Scene::Render();
	}

	void MainTitleScene::OnEnter()
	{
	}

	void MainTitleScene::OnExit()
	{
	}
}
