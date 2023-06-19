#include "jhTitleSelectScene.h"
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
	TitleSelectScene::TitleSelectScene() :
		Scene(eSceneType::TitleSelect)
	{
	}

	TitleSelectScene::~TitleSelectScene()
	{
	}

	void TitleSelectScene::Initialize()
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
			GameObject* selectBackground = object::Instantiate<GameObject>(eLayerType::Background, this);
			selectBackground->SetName(L"SelectBackground");
			Transform* bgTr = selectBackground->GetComponent<Transform>();
			bgTr->SetPosition(Vector3(0.f, 0.f, 0.1f));
			bgTr->SetScale(Vector3(16.f, 9.f, 1.f));
			SpriteRenderer* spriteRenderer = selectBackground->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> rectMesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"SBMaterial");
			spriteRenderer->SetMesh(rectMesh);
			spriteRenderer->SetMaterial(spriteMaterial);
		}

		// 1화 이미지
		{
			GameObject* ep1Image = object::Instantiate<GameObject>(eLayerType::UI, this);
			ep1Image->SetName(L"ep1Image");
			Transform* ep1iTr = ep1Image->GetComponent<Transform>();
			ep1iTr->SetPosition(Vector3(0.f, 0.f, 0.1f));
			ep1iTr->SetScale(Vector3(6.15f, 9.f, 1.f));
			SpriteRenderer* spriteRenderer = ep1Image->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> rectMesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"EP1IMaterial");
			spriteRenderer->SetMesh(rectMesh);
			spriteRenderer->SetMaterial(spriteMaterial);
		}
		// 1화 텍스트
		{
			GameObject* ep1Text = object::Instantiate<GameObject>(eLayerType::UI, this);
			ep1Text->SetName(L"ep1Text");
			Transform* ep1tTr = ep1Text->GetComponent<Transform>();
			ep1tTr->SetPosition(Vector3(0.f, -3.5f, 0.1f));
			ep1tTr->SetScale(Vector3(3.f, 1.5f, 1.f));
			SpriteRenderer* spriteRenderer = ep1Text->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> rectMesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"EP1TMaterial");
			spriteRenderer->SetMesh(rectMesh);
			spriteRenderer->SetMaterial(spriteMaterial);
		}

		// 타이틀 선택 프레임
		{
			GameObject* selectFrame = object::Instantiate<GameObject>(eLayerType::UI, this);
			selectFrame->SetName(L"TitleSelectFrame");
			Transform* sfTr = selectFrame->GetComponent<Transform>();
			sfTr->SetPosition(Vector3(0.f, 0.f, 0.1f));
			sfTr->SetScale(Vector3(6.15f, 9.f, 1.f));
			SpriteRenderer* spriteRenderer = selectFrame->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> rectMesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"SFMaterial");
			spriteRenderer->SetMesh(rectMesh);
			spriteRenderer->SetMaterial(spriteMaterial);
		}

		Scene::Initialize();
	}

	void TitleSelectScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::ENTER))
		{
			SceneManager::LoadScene(eSceneType::BeforeTalk);
		}
		else if (Input::GetKeyDown(eKeyCode::BACKSPACE))
		{
			SceneManager::LoadScene(eSceneType::Title);
		}

		Scene::Update();
	}

	void TitleSelectScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void TitleSelectScene::Render()
	{
		Scene::Render();
	}

	void TitleSelectScene::OnEnter()
	{
	}

	void TitleSelectScene::OnExit()
	{
	}
}
