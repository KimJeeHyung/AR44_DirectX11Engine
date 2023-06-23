#include "jhMainTitleScene.h"
#include "jhTransform.h"
#include "jhMeshRenderer.h"
#include "jhRenderer.h"
#include "jhResources.h"
#include "jhTexture.h"
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
#include "jhAudioClip.h"
#include "jhAudioSource.h"
#include "jhAudioListener.h"
//#include "jhFontWrapper.h"
#include "jhTextScript.h"

namespace jh
{
	MainTitleScene::MainTitleScene() :
		Scene(eSceneType::MainTitle),
		mFadeObj(nullptr)
	{
	}

	MainTitleScene::~MainTitleScene()
	{
	}

	void MainTitleScene::Initialize()
	{
		// 메인 카메라
		//GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		//Camera* cameraComp = cameraObj->AddComponent<Camera>();
		////cameraComp->TurnLayerMask(eLayerType::UI, false);
		//cameraComp->TurnLayerMask(eLayerType::Background, false);
		//cameraObj->AddComponent<CameraScript>();
		////mainCamera = cameraComp;

		// UI 카메라
		GameObject* UICameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* UICameraComp = UICameraObj->AddComponent<Camera>();
		UICameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		UICameraComp->DisableLayerMasks();
		UICameraComp->TurnLayerMask(eLayerType::UI, true);
		UICameraComp->TurnLayerMask(eLayerType::Background, true);
		Transform* cameraTr = UICameraObj->GetComponent<Transform>();
		cameraTr->SetPosition(Vector3(0.f, 0.f, 1.f));
		//mainCamera = UICameraComp;

		AudioListener* audioListener = UICameraObj->AddComponent<AudioListener>();

		// 메인화면 배경
		{
			GameObject* mainBackground = object::Instantiate<GameObject>(eLayerType::Background, this);
			mainBackground->SetName(L"MainBackground");
			Transform* bgTr = mainBackground->GetComponent<Transform>();
			bgTr->SetPosition(Vector3(0.f, 0.f, 12.f));
			bgTr->SetScale(Vector3(16.f, 9.f, 1.f));
			SpriteRenderer* spriteRenderer = mainBackground->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> rectMesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"MBMaterial");
			spriteRenderer->SetMesh(rectMesh);
			spriteRenderer->SetMaterial(spriteMaterial);

			AudioSource* audioSource = mainBackground->AddComponent<AudioSource>();
			std::shared_ptr<AudioClip> mainBGM = Resources::Load<AudioClip>(L"MainBGM", L"..\\Resources\\Portfolio\\Sound\\bgm200_Title.wav");
			audioSource->SetClip(mainBGM);
			audioSource->SetLoop(true);
			audioSource->Play();
		}

		// 메인화면 타이틀
		{
			GameObject* mainTitle = object::Instantiate<GameObject>(eLayerType::UI, this);
			mainTitle->SetName(L"MainTitle");
			Transform* mtTr = mainTitle->GetComponent<Transform>();
			mtTr->SetPosition(Vector3(0.f, 1.f, 12.f));
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
			mcTr->SetPosition(Vector3(0.f, -4.f, 12.f));
			mcTr->SetScale(Vector3(9.5f, 0.45f, 1.f));
			SpriteRenderer* spriteRenderer = mainCopy->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> rectMesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"MCMaterial");
			spriteRenderer->SetMesh(rectMesh);
			spriteRenderer->SetMaterial(spriteMaterial);
		}

		// 메인화면 버튼
		{
			GameObject* mainButton = object::Instantiate<GameObject>(eLayerType::UI, this);
			mainButton->SetName(L"MainButton");
			Transform* mcTr = mainButton->GetComponent<Transform>();
			mcTr->SetPosition(Vector3(0.f, -3.f, 12.f));
			mcTr->SetScale(Vector3(2.5f, 0.45f, 1.f));
			SpriteRenderer* spriteRenderer = mainButton->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> rectMesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"SBTNMaterial");
			spriteRenderer->SetMesh(rectMesh);
			spriteRenderer->SetMaterial(spriteMaterial);

			TextScript* textScript = mainButton->AddComponent<TextScript>();
			textScript->SetText(L"처음부터", 743.f, 730.f, 30.f, FONT_RGBA(255, 255, 255, 255));
		}

		// Fade 오브젝트
		{
			mFadeObj = object::Instantiate<GameObject>(eLayerType::UI, this);
			mFadeObj->SetName(L"FADE");
			Transform* fadeTr = mFadeObj->GetComponent<Transform>();
			fadeTr->SetPosition(Vector3(0.f, 0.f, 10.f));
			fadeTr->SetScale(Vector3(1.f, 1.f, 1.f));

			SpriteRenderer* fadeSr = mFadeObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> fadeMesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> fadeMaterial = Resources::Find<Material>(L"FadeMaterial");
			fadeSr->SetMesh(fadeMesh);
			fadeSr->SetMaterial(fadeMaterial);
			FadeScript* fadeScript = mFadeObj->AddComponent<FadeScript>();
			fadeScript->SetCamera(UICameraComp);
			fadeScript->SetFadeTime(0.5f);
		}

		Scene::Initialize();
	}

	void MainTitleScene::Update()
	{
		FadeScript* fadeScript = (FadeScript*)mFadeObj->GetScripts()[0];

		if (Input::GetKeyDown(eKeyCode::ENTER))
		{
			fadeScript->FadeOut();
		}

		if (fadeScript->GetFadeComplete() == true)
		{
			fadeScript->SetFadeComplete(false);
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
		FadeScript* fadeScript = (FadeScript*)mFadeObj->GetScripts()[0];
		fadeScript->FadeIn();
	}

	void MainTitleScene::OnExit()
	{
	}
}
