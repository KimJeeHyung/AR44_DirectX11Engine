#include "jhTestScene.h"
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
#include "jhLight.h"
#include "jhPaintShader.h"
#include "jhParticleSystem.h"

namespace jh
{
	TestScene::TestScene() :
		Scene(eSceneType::Test)
	{
	}

	TestScene::~TestScene()
	{
	}

	void TestScene::Initialize()
	{
		// PaintShader
		/*std::shared_ptr<PaintShader> paintShader = Resources::Find<PaintShader>(L"PaintShader");
		std::shared_ptr<Texture> paintTexture = Resources::Find<Texture>(L"PaintTexture");
		paintShader->SetTarget(paintTexture);
		paintShader->OnExcute();*/

		// Directional Light
		{
			GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player);
			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -100.f));
			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(1.f, 1.f, 1.f, 1.f));
		}

		// Point Light
		/*{
			GameObject* pointLight = object::Instantiate<GameObject>(eLayerType::Player);
			pointLight->GetComponent<Transform>()->SetPosition(Vector3(3.f, 0.f, 0.f));
			Light* lightComp = pointLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Point);
			lightComp->SetRadius(10.f);
			lightComp->SetDiffuse(Vector4(1.f, 0.f, 0.f, 1.f));
		}*/

		// 메인 카메라 오브젝트
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();
		mainCamera = cameraComp;

		// UI 카메라 오브젝트
		//GameObject* UICameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		//Camera* UICameraComp = UICameraObj->AddComponent<Camera>();
		//UICameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		//UICameraComp->DisableLayerMasks();
		//UICameraComp->TurnLayerMask(eLayerType::UI, true);

		// SMILE RECT(Player)
		{
			Player* obj = object::Instantiate<Player>(eLayerType::Player);
			obj->SetName(L"Phoenix");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(-1.f, 0.f, 5.f));
			tr->SetScale(Vector3(5.f, 5.f, 5.f));
			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
#pragma region CREATE ANIMATION
			Animator* animator = obj->AddComponent<Animator>();
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"PhoenixIdle", L"Portfolio\\Phoenix_Idle.png");
			animator->Create(L"PhoenixIdle", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
				Vector2::Zero, 5, 1, 0.4f);
			texture = Resources::Load<Texture>(L"PhoenixIdleBlink", L"Portfolio\\Phoenix_Idle_Blink.png");
			animator->Create(L"PhoenixIdleBlink", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
				Vector2::Zero, 3, 1, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixIdleTalk", L"Portfolio\\Phoenix_Idle_Talk.png");
			animator->Create(L"PhoenixIdleTalk", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
				Vector2::Zero, 8, 2, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixIdleTalkBlink", L"Portfolio\\Phoenix_Idle_Talk_Blink.png");
			animator->Create(L"PhoenixIdleTalkBlink", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
				Vector2::Zero, 3, 1, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixIdleTalk2", L"Portfolio\\Phoenix_Idle_Talk_2.png");
			animator->Create(L"PhoenixIdleTalk2", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
				Vector2::Zero, 11, 2, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixIdleNod", L"Portfolio\\Phoenix_Idle_Nod.png");
			animator->Create(L"PhoenixIdleNod", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
				Vector2::Zero, 9, 2, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixIdleShake", L"Portfolio\\Phoenix_Idle_Shake.png");
			animator->Create(L"PhoenixIdleShake", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
				Vector2::Zero, 12, 2, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixThink", L"Portfolio\\Phoenix_Think.png");
			animator->Create(L"PhoenixThink", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
				Vector2::Zero, 4, 5, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixThink2", L"Portfolio\\Phoenix_Think_2.png");
			animator->Create(L"PhoenixThink2", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
				Vector2::Zero, 11, 1, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixThink3", L"Portfolio\\Phoenix_Think_3.png");
			animator->Create(L"PhoenixThink3", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
				Vector2::Zero, 12, 3, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixThink4", L"Portfolio\\Phoenix_Think_4.png");
			animator->Create(L"PhoenixThink4", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
				Vector2::Zero, 6, 1, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixThink5", L"Portfolio\\Phoenix_Think_5.png");
			animator->Create(L"PhoenixThink5", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
				Vector2::Zero, 10, 3, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixThink6", L"Portfolio\\Phoenix_Think_6.png");
			animator->Create(L"PhoenixThink6", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
				Vector2::Zero, 6, 1, 0.05f); 
			texture = Resources::Load<Texture>(L"PhoenixThinkTalk", L"Portfolio\\Phoenix_Think_Talk.png");
			animator->Create(L"PhoenixThinkTalk", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
				Vector2::Zero, 14, 3, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixDeskHit", L"Portfolio\\Phoenix_Desk_Hit.png");
			animator->Create(L"PhoenixDeskHit", texture, Vector2(0.f, 0.f), Vector2(1285.f, 980.f),
				Vector2::Zero, 10, 2, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixDeskIdle", L"Portfolio\\Phoenix_Desk_Idle.png");
			animator->Create(L"PhoenixDeskIdle", texture, Vector2(0.f, 0.f), Vector2(1285.f, 980.f),
				Vector2::Zero, 5, 1, 0.4f);
			texture = Resources::Load<Texture>(L"PhoenixDeskIdleBlink", L"Portfolio\\Phoenix_Desk_Idle_Blink.png");
			animator->Create(L"PhoenixDeskIdleBlink", texture, Vector2(0.f, 0.f), Vector2(1285.f, 980.f),
				Vector2::Zero, 3, 1, 0.05f);
#pragma endregion
			animator->Play(L"PhoenixIdle", false);

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> material = Resources::Find<Material>(L"SpriteMaterial");
			mr->SetMaterial(material);
			mr->SetMesh(mesh);
			obj->AddComponent<PlayerScript>();
			//object::DontDestroyOnLoad(obj);
		}

		// SMILE RECT(Monster)
		{
			Player* obj = object::Instantiate<Player>(eLayerType::Monster);
			obj->SetName(L"mSMILE");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(2.f, 0.f, 5.f));
			//tr->SetRotation(Vector3(0.f, 0.f, XM_PIDIV2));
			tr->SetScale(Vector3(2.f, 2.f, 2.f));
			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			//collider->SetCenter(Vector2(0.5f, 0.5f));
			collider->SetSize(Vector2(2.f, 2.f));
			collider->SetRadius(1.f);

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> material = Resources::Find<Material>(L"RectMaterial");
			mr->SetMaterial(material);
			mr->SetMesh(mesh);
			object::DontDestroyOnLoad(obj);
		}

		// SMILE RECT CHILD
		//GameObject* child = object::Instantiate<GameObject>(eLayerType::Player, tr);
		//child->SetName(L"SMILE CHILD");
		//Transform* childTr = child->GetComponent<Transform>();
		//childTr->SetPosition(Vector3(2.f, 0.f, 0.f));
		//childTr->SetScale(Vector3(1.f, 1.f, 1.f));
		////childTr->SetParent(tr);
		//
		//MeshRenderer* childMr = child->AddComponent<MeshRenderer>();
		//std::shared_ptr<Material> childMaterial = Resources::Find<Material>(L"RectMaterial");
		//childMr->SetMaterial(childMaterial);
		//childMr->SetMesh(mesh);

		// Light Object
		//GameObject* spriteObj = object::Instantiate<GameObject>(eLayerType::Player);
		//spriteObj->SetName(L"LIGHT");
		//Transform* spriteTr = spriteObj->GetComponent<Transform>();
		//spriteTr->SetPosition(Vector3(5.f, 0.f, 10.f));
		//spriteTr->SetScale(Vector3(5.f, 5.f, 1.f));
		//
		//SpriteRenderer* sr = spriteObj->AddComponent<SpriteRenderer>();
		//std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"SpriteMaterial");
		//sr->SetMaterial(spriteMaterial);
		//sr->SetMesh(mesh);

		// HPBar
		//GameObject* hpBar = object::Instantiate<GameObject>(eLayerType::UI);
		//hpBar->SetName(L"HPBAR");
		//Transform* hpBarTr = hpBar->GetComponent<Transform>();
		//hpBarTr->SetPosition(Vector3(-5.f, 3.f, 12.f));
		//hpBarTr->SetScale(Vector3(1.f, 1.f, 1.f));
		//
		//SpriteRenderer* hpSr = hpBar->AddComponent<SpriteRenderer>();
		//std::shared_ptr<Mesh> hpMesh = Resources::Find<Mesh>(L"RectMesh");
		//std::shared_ptr<Material> hpSpriteMaterial = Resources::Find<Material>(L"UIMaterial");
		//hpSr->SetMesh(hpMesh);
		//hpSr->SetMaterial(hpSpriteMaterial);

		//hpBar->Pause();

		// Fade 오브젝트
		//GameObject* fadeObj = object::Instantiate<GameObject>(eLayerType::UI);
		//fadeObj->SetName(L"FADE");
		//Transform* fadeTr = fadeObj->GetComponent<Transform>();
		//fadeTr->SetPosition(Vector3(0.f, 0.f, 10.f));
		//fadeTr->SetScale(Vector3(1.f, 1.f, 1.f));
		//
		//SpriteRenderer* fadeSr = fadeObj->AddComponent<SpriteRenderer>();
		//std::shared_ptr<Mesh> fadeMesh = Resources::Find<Mesh>(L"RectMesh");
		//std::shared_ptr<Material> fadeMaterial = Resources::Find<Material>(L"FadeMaterial");
		//fadeSr->SetMesh(fadeMesh);
		//fadeSr->SetMaterial(fadeMaterial);
		//FadeScript* fadeScript = fadeObj->AddComponent<FadeScript>();
		//fadeScript->SetCamera(cameraComp);

		// Particle
		{
			Player* obj = object::Instantiate<Player>(eLayerType::Particle);
			obj->SetName(L"PARTICLE");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.f, 0.f, 100.f));
			obj->AddComponent<ParticleSystem>();
		}

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);
		//CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Player, true);

		Scene::Initialize();
	}

	void TestScene::Update()
	{
		/*if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Play);
		}*/

		Scene::Update();
	}

	void TestScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void TestScene::Render()
	{
		Scene::Render();
	}

	void TestScene::OnEnter()
	{
	}

	void TestScene::OnExit()
	{
	}
}
