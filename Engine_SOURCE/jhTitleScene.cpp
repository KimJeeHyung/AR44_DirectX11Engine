#include "jhTitleScene.h"
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
	TitleScene::TitleScene() :
		Scene(eSceneType::Title)
	{
	}

	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Initialize()
	{
		// 메인 카메라 오브젝트
		//GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		//Camera* cameraComp = cameraObj->AddComponent<Camera>();
		//cameraComp->RegisterCameraInRenderer();
		//cameraComp->TurnLayerMask(eLayerType::UI, false);
		//cameraObj->AddComponent<CameraScript>();
		//mainCamera = cameraComp;

		// UI 카메라 오브젝트
		GameObject* UICameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* UICameraComp = UICameraObj->AddComponent<Camera>();
		UICameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		UICameraComp->DisableLayerMasks();
		UICameraComp->TurnLayerMask(eLayerType::UI, true);
		UICameraComp->TurnLayerMask(eLayerType::Background, true);

		// 타이틀 선택화면 배경
		{
			GameObject* mainBackground = object::Instantiate<GameObject>(eLayerType::Background,this);
			mainBackground->SetName(L"TitleBackground");
			Transform* bgTr = mainBackground->GetComponent<Transform>();
			bgTr->SetPosition(Vector3(0.f, 0.f, 0.1f));
			bgTr->SetScale(Vector3(16.f, 9.f, 1.f));
			SpriteRenderer* spriteRenderer = mainBackground->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> rectMesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"MBMaterial");
			spriteRenderer->SetMesh(rectMesh);
			spriteRenderer->SetMaterial(spriteMaterial);
		}

		// 역재1 타이틀
		{
			GameObject* gs1Title = object::Instantiate<GameObject>(eLayerType::UI, this);
			gs1Title->SetName(L"gs1Title");
			Transform* gs1tTr = gs1Title->GetComponent<Transform>();
			gs1tTr->SetPosition(Vector3(0.f, 1.3f, 0.1f));
			gs1tTr->SetScale(Vector3(11.f, 5.8f, 1.f));
			SpriteRenderer* spriteRenderer = gs1Title->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> rectMesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"GS1TMaterial");
			spriteRenderer->SetMesh(rectMesh);
			spriteRenderer->SetMaterial(spriteMaterial);
		}

		// 역재1 저작권
		{
			GameObject* gs1Copy = object::Instantiate<GameObject>(eLayerType::UI, this);
			gs1Copy->SetName(L"gs1Copy");
			Transform* gs1cTr = gs1Copy->GetComponent<Transform>();
			gs1cTr->SetPosition(Vector3(0.f, -4.f, 0.1f));
			gs1cTr->SetScale(Vector3(9.5f, 0.45f, 1.f));
			SpriteRenderer* spriteRenderer = gs1Copy->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> rectMesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"GS1CMaterial");
			spriteRenderer->SetMesh(rectMesh);
			spriteRenderer->SetMaterial(spriteMaterial);
		}

		Scene::Initialize();
	}

	void TitleScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::BACKSPACE))
		{
			SceneManager::LoadScene(eSceneType::MainTitle);
		}

		Scene::Update();
	}

	void TitleScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void TitleScene::Render()
	{
		Scene::Render();
	}

	void TitleScene::OnEnter()
	{
	}

	void TitleScene::OnExit()
	{
	}
}
