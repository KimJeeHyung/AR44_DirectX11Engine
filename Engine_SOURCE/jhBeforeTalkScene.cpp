#include "jhBeforeTalkScene.h"
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
#include "jhAnimator.h"
#include "jhMiaScript.h"

namespace jh
{
	BeforeTalkScene::BeforeTalkScene() :
		Scene(eSceneType::BeforeTalk)
	{
	}

	BeforeTalkScene::~BeforeTalkScene()
	{
	}

	void BeforeTalkScene::Initialize()
	{
		// 메인 카메라 오브젝트
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		//cameraObj->AddComponent<CameraScript>();
		Transform* cameraTr = cameraObj->GetComponent<Transform>();
		cameraTr->SetPosition(Vector3(0.f, 0.f, -7.8f));

		// UI 카메라 오브젝트
		//GameObject* UICameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		//Camera* UICameraComp = UICameraObj->AddComponent<Camera>();
		//UICameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		//UICameraComp->DisableLayerMasks();
		//UICameraComp->TurnLayerMask(eLayerType::UI, true);
		//UICameraComp->TurnLayerMask(eLayerType::Background, true);

		// Directional Light
		{
			GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player, this);
			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, 0.f));
			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(1.f, 1.f, 1.f, 1.f));
		}

		// 배경
		{
			GameObject* btBackground = object::Instantiate<GameObject>(eLayerType::Background, this);
			btBackground->SetName(L"WaitingRoomBackground");
			Transform* bgTr = btBackground->GetComponent<Transform>();
			bgTr->SetPosition(Vector3(0.f, 0.f, 0.f));
			bgTr->SetScale(Vector3(16.f, 9.f, 1.f));
			SpriteRenderer* spriteRenderer = btBackground->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> rectMesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"WaitingRoomMaterial");
			spriteRenderer->SetMesh(rectMesh);
			spriteRenderer->SetMaterial(spriteMaterial);
		}

		// 치히로
		{
			Player* obj = object::Instantiate<Player>(eLayerType::Player, this);
			obj->SetName(L"Mia");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(-0.15f, 0.35f, 0.f));
			tr->SetScale(Vector3(14.f, 14.f, 14.f));
			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
#pragma region CREATE ANIMATION
			Animator* animator = obj->AddComponent<Animator>();
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"MiaFowardIdle", L"Portfolio\\Mia\\Mia_Foward_Idle.png");
			animator->Create(L"MiaFowardIdle", texture, Vector2(0.f, 0.f), Vector2(727.f, 1180.f),
				Vector2::Zero, 5, 1, 0.4f);
			texture = Resources::Load<Texture>(L"MiaFowardIdleBlink", L"Portfolio\\Mia\\Mia_Foward_Idle_Blink.png");
			animator->Create(L"MiaFowardIdleBlink", texture, Vector2(0.f, 0.f), Vector2(727.f, 1180.f),
				Vector2::Zero, 6, 1, 0.05f);
			texture = Resources::Load<Texture>(L"MiaFowardTalk", L"Portfolio\\Mia\\Mia_Foward_Talk.png");
			animator->Create(L"MiaFowardTalk", texture, Vector2(0.f, 0.f), Vector2(727.f, 1180.f),
				Vector2::Zero, 7, 5, 0.05f);
			texture = Resources::Load<Texture>(L"MiaFowardGrin", L"Portfolio\\Mia\\Mia_Foward_Grin.png");
			animator->Create(L"MiaFowardGrin", texture, Vector2(0.f, 0.f), Vector2(727.f, 1180.f),
				Vector2::Zero, 10, 3, 0.05f);
			texture = Resources::Load<Texture>(L"MiaFowardSmileIdle", L"Portfolio\\Mia\\Mia_Foward_Smile_Idle.png");
			animator->Create(L"MiaFowardSmileIdle", texture, Vector2(0.f, 0.f), Vector2(727.f, 1180.f),
				Vector2::Zero, 5, 1, 0.4f);
			texture = Resources::Load<Texture>(L"MiaFowardSmileIdleBlink", L"Portfolio\\Mia\\Mia_Foward_Smile_Idle_Blink.png");
			animator->Create(L"MiaFowardSmileIdleBlink", texture, Vector2(0.f, 0.f), Vector2(727.f, 1180.f),
				Vector2::Zero, 3, 1, 0.05f);
			texture = Resources::Load<Texture>(L"MiaFowardSmileTalk", L"Portfolio\\Mia\\Mia_Foward_Smile_Talk.png");
			animator->Create(L"MiaFowardSmileTalk", texture, Vector2(0.f, 0.f), Vector2(727.f, 1180.f),
				Vector2::Zero, 7, 5, 0.05f);
			texture = Resources::Load<Texture>(L"MiaFowardShock", L"Portfolio\\Mia\\Mia_Foward_Shock.png");
			animator->Create(L"MiaFowardShock", texture, Vector2(0.f, 0.f), Vector2(727.f, 1180.f),
				Vector2::Zero, 11, 8, 0.05f);
			texture = Resources::Load<Texture>(L"MiaFowardShockTalk", L"Portfolio\\Mia\\Mia_Foward_Shock_Talk.png");
			animator->Create(L"MiaFowardShockTalk", texture, Vector2(0.f, 0.f), Vector2(727.f, 1180.f),
				Vector2::Zero, 17, 2, 0.05f);
			texture = Resources::Load<Texture>(L"MiaCounselIdle", L"Portfolio\\Mia\\Mia_Counsel_Idle.png");
			animator->Create(L"MiaCounselIdle", texture, Vector2(0.f, 0.f), Vector2(518.f, 1080.f),
				Vector2::Zero, 5, 1, 0.4f);
			texture = Resources::Load<Texture>(L"MiaCounselIdleBlink", L"Portfolio\\Mia\\Mia_Counsel_Idle_Blink.png");
			animator->Create(L"MiaCounselIdleBlink", texture, Vector2(0.f, 0.f), Vector2(518.f, 1080.f),
				Vector2::Zero, 7, 1, 0.05f);
			texture = Resources::Load<Texture>(L"MiaCounselIdleTalk", L"Portfolio\\Mia\\Mia_Counsel_Idle_Talk.png");
			animator->Create(L"MiaCounselIdleTalk", texture, Vector2(0.f, 0.f), Vector2(518.f, 1080.f),
				Vector2::Zero, 10, 4, 0.08f);
			texture = Resources::Load<Texture>(L"MiaCounselShock", L"Portfolio\\Mia\\Mia_Counsel_Shock.png");
			animator->Create(L"MiaCounselShock", texture, Vector2(0.f, 0.f), Vector2(518.f, 1080.f),
				Vector2::Zero, 12, 10, 0.07f);
			texture = Resources::Load<Texture>(L"MiaCounselShockTalk", L"Portfolio\\Mia\\Mia_Counsel_Shock_Talk.png");
			animator->Create(L"MiaCounselShockTalk", texture, Vector2(0.f, 0.f), Vector2(518.f, 1080.f),
				Vector2::Zero, 9, 4, 0.05f);
			texture = Resources::Load<Texture>(L"MiaCounselIdleSad", L"Portfolio\\Mia\\Mia_Counsel_Idle_Sad.png");
			animator->Create(L"MiaCounselIdleSad", texture, Vector2(0.f, 0.f), Vector2(518.f, 1080.f),
				Vector2::Zero, 5, 1, 0.4f);
			texture = Resources::Load<Texture>(L"MiaCounselIdleSadBlink", L"Portfolio\\Mia\\Mia_Counsel_Idle_Sad_Blink.png");
			animator->Create(L"MiaCounselIdleSadBlink", texture, Vector2(0.f, 0.f), Vector2(518.f, 1080.f),
				Vector2::Zero, 8, 1, 0.05f);
			texture = Resources::Load<Texture>(L"MiaCounselIdleSadTalk", L"Portfolio\\Mia\\Mia_Counsel_Idle_Sad_Talk.png");
			animator->Create(L"MiaCounselIdleSadTalk", texture, Vector2(0.f, 0.f), Vector2(518.f, 1080.f),
				Vector2::Zero, 12, 5, 0.05f);
			texture = Resources::Load<Texture>(L"MiaCounselExasperateIdle", L"Portfolio\\Mia\\Mia_Counsel_Exasperate_Idle.png");
			animator->Create(L"MiaCounselExasperateIdle", texture, Vector2(0.f, 0.f), Vector2(609.f, 1080.f),
				Vector2::Zero, 5, 1, 0.4f);
			texture = Resources::Load<Texture>(L"MiaCounselExasperateIdleBlink", L"Portfolio\\Mia\\Mia_Counsel_Exasperate_Idle_Blink.png");
			animator->Create(L"MiaCounselExasperateIdleBlink", texture, Vector2(0.f, 0.f), Vector2(609.f, 1080.f),
				Vector2::Zero, 8, 1, 0.05f);
			texture = Resources::Load<Texture>(L"MiaCounselExasperateTalk", L"Portfolio\\Mia\\Mia_Counsel_Exasperate_Talk.png");
			animator->Create(L"MiaCounselExasperateTalk", texture, Vector2(0.f, 0.f), Vector2(609.f, 1080.f),
				Vector2::Zero, 12, 5, 0.05f);
#pragma endregion
			animator->Play(L"MiaFowardIdle", false);

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> material = Resources::Find<Material>(L"SpriteMaterial");
			mr->SetMaterial(material);
			mr->SetMesh(mesh);
			obj->AddComponent<MiaScript>();
		}

		Scene::Initialize();
	}

	void BeforeTalkScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::ENTER))
		{
			SceneManager::LoadScene(eSceneType::Court);
		}
		else if (Input::GetKeyDown(eKeyCode::BACKSPACE))
		{
			SceneManager::LoadScene(eSceneType::TitleSelect);
		}

		Scene::Update();
	}

	void BeforeTalkScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void BeforeTalkScene::Render()
	{
		Scene::Render();
	}

	void BeforeTalkScene::OnEnter()
	{
	}

	void BeforeTalkScene::OnExit()
	{
	}
}
