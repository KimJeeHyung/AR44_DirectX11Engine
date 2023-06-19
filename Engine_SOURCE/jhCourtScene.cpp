#include "jhCourtScene.h"
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
#include "jhCollisionManager.h"
#include "jhAnimator.h"
#include "jhLight.h"
#include "jhPayneScript.h"
#include "jhJudgeScript.h"
#include "jhLarryScript.h"

namespace jh
{
	CourtScene::CourtScene() :
		Scene(eSceneType::Test)
	{
	}

	CourtScene::~CourtScene()
	{
	}

	void CourtScene::Initialize()
	{
		// Directional Light
		{
			GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player, this);
			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -100.f));
			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(1.f, 1.f, 1.f, 1.f));
		}

		// 메인 카메라 오브젝트
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();
		mainCamera = cameraComp;
		Transform* cameraTr = cameraObj->GetComponent<Transform>();
		cameraTr->SetPosition(Vector3(-28.7f, 0.f, -7.8f));

		// UI 카메라 오브젝트
		//GameObject* UICameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		//Camera* UICameraComp = UICameraObj->AddComponent<Camera>();
		//UICameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		//UICameraComp->DisableLayerMasks();
		//UICameraComp->TurnLayerMask(eLayerType::UI, true);

		// 법정 배경
		{
			GameObject* courtBackground = object::Instantiate<GameObject>(eLayerType::Background, this);
			courtBackground->SetName(L"CourtBackground");
			Transform* bgTr = courtBackground->GetComponent<Transform>();
			bgTr->SetPosition(Vector3(0.f, 0.f, 0.f));
			bgTr->SetScale(Vector3(73.6f, 9.f, 1.f));
			SpriteRenderer* spriteRenderer = courtBackground->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> rectMesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"CourtMaterial");
			spriteRenderer->SetMesh(rectMesh);
			spriteRenderer->SetMaterial(spriteMaterial);
		}
		{
			GameObject* judgeBackground = object::Instantiate<GameObject>(eLayerType::Background, this);
			judgeBackground->SetName(L"JudgeBackground");
			Transform* bgTr = judgeBackground->GetComponent<Transform>();
			bgTr->SetPosition(Vector3(0.f, 9.f, 0.f));
			bgTr->SetScale(Vector3(16.f, 9.f, 1.f));
			SpriteRenderer* spriteRenderer = judgeBackground->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> rectMesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"JudgeBackMaterial");
			spriteRenderer->SetMesh(rectMesh);
			spriteRenderer->SetMaterial(spriteMaterial);
		}
		{
			GameObject* desk1 = object::Instantiate<GameObject>(eLayerType::Desk, this);
			desk1->SetName(L"Desk1");
			Transform* desk1Tr = desk1->GetComponent<Transform>();
			desk1Tr->SetPosition(Vector3(-28.9f, -3.5f, 0.f));
			desk1Tr->SetScale(Vector3(16.f, 2.f, 1.f));
			SpriteRenderer* spriteRenderer = desk1->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> rectMesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"Desk1Material");
			spriteRenderer->SetMesh(rectMesh);
			spriteRenderer->SetMaterial(spriteMaterial);
		}
		{
			GameObject* desk2 = object::Instantiate<GameObject>(eLayerType::Desk, this);
			desk2->SetName(L"Desk2");
			Transform* desk2Tr = desk2->GetComponent<Transform>();
			desk2Tr->SetPosition(Vector3(28.9f, -3.5f, 0.f));
			desk2Tr->SetScale(Vector3(16.f, 2.f, 1.f));
			SpriteRenderer* spriteRenderer = desk2->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> rectMesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"Desk2Material");
			spriteRenderer->SetMesh(rectMesh);
			spriteRenderer->SetMaterial(spriteMaterial);
		}
		{
			GameObject* desk3 = object::Instantiate<GameObject>(eLayerType::Desk, this);
			desk3->SetName(L"Desk3");
			Transform* desk3Tr = desk3->GetComponent<Transform>();
			desk3Tr->SetPosition(Vector3(0.f, -3.4f, 0.f));
			desk3Tr->SetScale(Vector3(16.f, 2.25f, 1.f));
			SpriteRenderer* spriteRenderer = desk3->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> rectMesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"Desk3Material");
			spriteRenderer->SetMesh(rectMesh);
			spriteRenderer->SetMaterial(spriteMaterial);
		}

		// 나루호도
		{
			Player* obj = object::Instantiate<Player>(eLayerType::Player, this);
			obj->SetName(L"Phoenix");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(-32.5f, 0.5f, 0.f));
			tr->SetScale(Vector3(14.f, 14.f, 14.f));
			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
#pragma region CREATE ANIMATION
			Animator* animator = obj->AddComponent<Animator>();
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"PhoenixIdle", L"Portfolio\\Phoenix\\Phoenix_Idle.png");
			animator->Create(L"PhoenixIdle", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
				Vector2::Zero, 5, 1, 0.4f);
			texture = Resources::Load<Texture>(L"PhoenixIdleBlink", L"Portfolio\\Phoenix\\Phoenix_Idle_Blink.png");
			animator->Create(L"PhoenixIdleBlink", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
				Vector2::Zero, 3, 1, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixIdleTalk", L"Portfolio\\Phoenix\\Phoenix_Idle_Talk.png");
			animator->Create(L"PhoenixIdleTalk", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
				Vector2::Zero, 8, 2, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixIdleTalkBlink", L"Portfolio\\Phoenix\\Phoenix_Idle_Talk_Blink.png");
			animator->Create(L"PhoenixIdleTalkBlink", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
				Vector2::Zero, 3, 1, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixIdleTalk2", L"Portfolio\\Phoenix\\Phoenix_Idle_Talk_2.png");
			animator->Create(L"PhoenixIdleTalk2", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
				Vector2::Zero, 11, 2, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixIdleNod", L"Portfolio\\Phoenix\\Phoenix_Idle_Nod.png");
			animator->Create(L"PhoenixIdleNod", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
				Vector2::Zero, 9, 2, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixIdleShake", L"Portfolio\\Phoenix\\Phoenix_Idle_Shake.png");
			animator->Create(L"PhoenixIdleShake", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
				Vector2::Zero, 12, 2, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixThink", L"Portfolio\\Phoenix\\Phoenix_Think.png");
			animator->Create(L"PhoenixThink", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
				Vector2::Zero, 4, 5, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixThink2", L"Portfolio\\Phoenix\\Phoenix_Think_2.png");
			animator->Create(L"PhoenixThink2", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
				Vector2::Zero, 11, 1, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixThink3", L"Portfolio\\Phoenix\\Phoenix_Think_3.png");
			animator->Create(L"PhoenixThink3", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
				Vector2::Zero, 12, 3, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixThink4", L"Portfolio\\Phoenix\\Phoenix_Think_4.png");
			animator->Create(L"PhoenixThink4", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
				Vector2::Zero, 6, 1, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixThink5", L"Portfolio\\Phoenix\\Phoenix_Think_5.png");
			animator->Create(L"PhoenixThink5", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
				Vector2::Zero, 10, 3, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixThink6", L"Portfolio\\Phoenix\\Phoenix_Think_6.png");
			animator->Create(L"PhoenixThink6", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
				Vector2::Zero, 6, 1, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixThinkTalk", L"Portfolio\\Phoenix\\Phoenix_Think_Talk.png");
			animator->Create(L"PhoenixThinkTalk", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
				Vector2::Zero, 14, 3, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixDeskHit", L"Portfolio\\Phoenix\\Phoenix_Desk_Hit.png");
			animator->Create(L"PhoenixDeskHit", texture, Vector2(0.f, 0.f), Vector2(1285.f, 980.f),
				Vector2::Zero, 10, 2, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixDeskIdle", L"Portfolio\\Phoenix\\Phoenix_Desk_Idle.png");
			animator->Create(L"PhoenixDeskIdle", texture, Vector2(0.f, 0.f), Vector2(1285.f, 980.f),
				Vector2::Zero, 5, 1, 0.4f);
			texture = Resources::Load<Texture>(L"PhoenixDeskIdleBlink", L"Portfolio\\Phoenix\\Phoenix_Desk_Idle_Blink.png");
			animator->Create(L"PhoenixDeskIdleBlink", texture, Vector2(0.f, 0.f), Vector2(1285.f, 980.f),
				Vector2::Zero, 3, 1, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixDeskTalk", L"Portfolio\\Phoenix\\Phoenix_Desk_Talk.png");
			animator->Create(L"PhoenixDeskTalk", texture, Vector2(0.f, 0.f), Vector2(1285.f, 980.f),
				Vector2::Zero, 7, 6, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixPoint", L"Portfolio\\Phoenix\\Phoenix_Point.png");
			animator->Create(L"PhoenixPoint", texture, Vector2(0.f, 0.f), Vector2(1666.f, 980.f),
				Vector2::Zero, 6, 4, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixPointIdle", L"Portfolio\\Phoenix\\Phoenix_Point_Idle.png");
			animator->Create(L"PhoenixPointIdle", texture, Vector2(0.f, 0.f), Vector2(1666.f, 980.f),
				Vector2::Zero, 5, 1, 0.4f);
			texture = Resources::Load<Texture>(L"PhoenixPointIdleBlink", L"Portfolio\\Phoenix\\Phoenix_Point_Idle_Blink.png");
			animator->Create(L"PhoenixPointIdleBlink", texture, Vector2(0.f, 0.f), Vector2(1666.f, 980.f),
				Vector2::Zero, 3, 1, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixPointTalk", L"Portfolio\\Phoenix\\Phoenix_Point_Talk.png");
			animator->Create(L"PhoenixPointTalk", texture, Vector2(0.f, 0.f), Vector2(1666.f, 980.f),
				Vector2::Zero, 8, 4, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixDocument", L"Portfolio\\Phoenix\\Phoenix_Document.png");
			animator->Create(L"PhoenixDocument", texture, Vector2(0.f, 0.f), Vector2(1146.f, 980.f),
				Vector2::Zero, 13, 4, 0.07f);
			texture = Resources::Load<Texture>(L"PhoenixDocumentTalk", L"Portfolio\\Phoenix\\Phoenix_Document_Talk.png");
			animator->Create(L"PhoenixDocumentTalk", texture, Vector2(0.f, 0.f), Vector2(1146.f, 980.f),
				Vector2::Zero, 9, 7, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixSweatIdle", L"Portfolio\\Phoenix\\Phoenix_Sweat_Idle.png");
			animator->Create(L"PhoenixSweatIdle", texture, Vector2(0.f, 0.f), Vector2(725.f, 980.f),
				Vector2::Zero, 12, 2, 0.07f);
			texture = Resources::Load<Texture>(L"PhoenixSweatTalk", L"Portfolio\\Phoenix\\Phoenix_Sweat_Talk.png");
			animator->Create(L"PhoenixSweatTalk", texture, Vector2(0.f, 0.f), Vector2(725.f, 980.f),
				Vector2::Zero, 15, 2, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixConfidentIdle", L"Portfolio\\Phoenix\\Phoenix_Confident_Idle.png");
			animator->Create(L"PhoenixConfidentIdle", texture, Vector2(0.f, 0.f), Vector2(1161.f, 1280.f),
				Vector2::Zero, 5, 1, 0.4f);
			texture = Resources::Load<Texture>(L"PhoenixConfidentIdleBlink", L"Portfolio\\Phoenix\\Phoenix_Confident_Idle_Blink.png");
			animator->Create(L"PhoenixConfidentIdleBlink", texture, Vector2(0.f, 0.f), Vector2(1161.f, 1280.f),
				Vector2::Zero, 3, 1, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixConfidentTalk", L"Portfolio\\Phoenix\\Phoenix_Confident_Talk.png");
			animator->Create(L"PhoenixConfidentTalk", texture, Vector2(0.f, 0.f), Vector2(1161.f, 1280.f),
				Vector2::Zero, 7, 6, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixShocked", L"Portfolio\\Phoenix\\Phoenix_Shocked.png");
			animator->Create(L"PhoenixShocked", texture, Vector2(0.f, 0.f), Vector2(1094.f, 1180.f),
				Vector2::Zero, 7, 5, 0.04f);
			texture = Resources::Load<Texture>(L"PhoenixAbashedIdle", L"Portfolio\\Phoenix\\Phoenix_Abashed_Idle.png");
			animator->Create(L"PhoenixAbashedIdle", texture, Vector2(0.f, 0.f), Vector2(1235.f, 980.f),
				Vector2::Zero, 5, 1, 0.4f);
			texture = Resources::Load<Texture>(L"PhoenixAbashedIdleBlink", L"Portfolio\\Phoenix\\Phoenix_Abashed_Idle_Blink.png");
			animator->Create(L"PhoenixAbashedIdleBlink", texture, Vector2(0.f, 0.f), Vector2(1235.f, 980.f),
				Vector2::Zero, 4, 1, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixAbashedTalk", L"Portfolio\\Phoenix\\Phoenix_Abashed_Talk.png");
			animator->Create(L"PhoenixAbashedTalk", texture, Vector2(0.f, 0.f), Vector2(1235.f, 980.f),
				Vector2::Zero, 12, 1, 0.05f);
			texture = Resources::Load<Texture>(L"PhoenixWig", L"Portfolio\\Phoenix\\Phoenix_Wig.png");
			animator->Create(L"PhoenixWig", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
				Vector2::Zero, 10, 2, 0.05f);
#pragma endregion
			animator->Play(L"PhoenixIdle", false);

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> material = Resources::Find<Material>(L"SpriteMaterial");
			mr->SetMaterial(material);
			mr->SetMesh(mesh);
			obj->AddComponent<PlayerScript>();
		}

		// 아우치
		{
			Player* obj = object::Instantiate<Player>(eLayerType::Player, this);
			obj->SetName(L"Payne");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(32.8f, 0.5f, 0.f));
			tr->SetScale(Vector3(14.f, 14.f, 14.f));
			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
#pragma region CREATE ANIMATION
			Animator* animator = obj->AddComponent<Animator>();
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"PayneIdle", L"Portfolio\\Payne\\Payne_Idle.png");
			animator->Create(L"PayneIdle", texture, Vector2(0.f, 0.f), Vector2(749.f, 980.f),
				Vector2::Zero, 1, 1, 0.4f);
			texture = Resources::Load<Texture>(L"PayneIdleTalk", L"Portfolio\\Payne\\Payne_Idle_Talk.png");
			animator->Create(L"PayneIdleTalk", texture, Vector2(0.f, 0.f), Vector2(749.f, 980.f),
				Vector2::Zero, 8, 1, 0.15f);
			texture = Resources::Load<Texture>(L"PayneSweat", L"Portfolio\\Payne\\Payne_Sweat.png");
			animator->Create(L"PayneSweat", texture, Vector2(0.f, 0.f), Vector2(749.f, 980.f),
				Vector2::Zero, 4, 1, 0.15f);
			texture = Resources::Load<Texture>(L"PayneSweatTalk", L"Portfolio\\Payne\\Payne_Sweat_Talk.png");
			animator->Create(L"PayneSweatTalk", texture, Vector2(0.f, 0.f), Vector2(749.f, 980.f),
				Vector2::Zero, 4, 1, 0.15f);
#pragma endregion
			animator->Play(L"PayneIdle", false);

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> material = Resources::Find<Material>(L"SpriteMaterial");
			mr->SetMaterial(material);
			mr->SetMesh(mesh);
			obj->AddComponent<PayneScript>();
		}

		// 재판관
		{
			Player* obj = object::Instantiate<Player>(eLayerType::Player, this);
			obj->SetName(L"Judge");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.f, 9.95f, 0.f));
			tr->SetScale(Vector3(14.f, 14.f, 14.f));
			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
#pragma region CREATE ANIMATION
			Animator* animator = obj->AddComponent<Animator>();
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"JudgeIdle", L"Portfolio\\Judge\\Judge_Idle.png");
			animator->Create(L"JudgeIdle", texture, Vector2(0.f, 0.f), Vector2(775.f, 780.f),
				Vector2::Zero, 18, 4, 0.05f);
			texture = Resources::Load<Texture>(L"JudgeIdleTalk", L"Portfolio\\Judge\\Judge_Idle_Talk.png");
			animator->Create(L"JudgeIdleTalk", texture, Vector2(0.f, 0.f), Vector2(775.f, 780.f),
				Vector2::Zero, 9, 7, 0.05f);
			texture = Resources::Load<Texture>(L"JudgeNod", L"Portfolio\\Judge\\Judge_Nod.png");
			animator->Create(L"JudgeNod", texture, Vector2(0.f, 0.f), Vector2(775.f, 780.f),
				Vector2::Zero, 9, 2, 0.05f);
			texture = Resources::Load<Texture>(L"JudgeShake", L"Portfolio\\Judge\\Judge_Shake.png");
			animator->Create(L"JudgeShake", texture, Vector2(0.f, 0.f), Vector2(775.f, 780.f),
				Vector2::Zero, 9, 2, 0.05f);
			texture = Resources::Load<Texture>(L"JudgeSurprisedIdle", L"Portfolio\\Judge\\Judge_Surprised_Idle.png");
			animator->Create(L"JudgeSurprisedIdle", texture, Vector2(0.f, 0.f), Vector2(775.f, 780.f),
				Vector2::Zero, 9, 7, 0.05f);
			texture = Resources::Load<Texture>(L"JudgeSurprisedTalk", L"Portfolio\\Judge\\Judge_Surprised_Talk.png");
			animator->Create(L"JudgeSurprisedTalk", texture, Vector2(0.f, 0.f), Vector2(775.f, 780.f),
				Vector2::Zero, 8, 6, 0.05f);
			texture = Resources::Load<Texture>(L"JudgeSternIdle", L"Portfolio\\Judge\\Judge_Stern_Idle.png");
			animator->Create(L"JudgeSternIdle", texture, Vector2(0.f, 0.f), Vector2(775.f, 780.f),
				Vector2::Zero, 19, 3, 0.08f);
			texture = Resources::Load<Texture>(L"JudgeSternTalk", L"Portfolio\\Judge\\Judge_Stern_Talk.png");
			animator->Create(L"JudgeSternTalk", texture, Vector2(0.f, 0.f), Vector2(775.f, 780.f),
				Vector2::Zero, 8, 6, 0.08f);
			texture = Resources::Load<Texture>(L"JudgeThink", L"Portfolio\\Judge\\Judge_Think.png");
			animator->Create(L"JudgeThink", texture, Vector2(0.f, 0.f), Vector2(775.f, 780.f),
				Vector2::Zero, 1, 1, 0.4f);
#pragma endregion
			animator->Play(L"JudgeIdle", true);

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> material = Resources::Find<Material>(L"SpriteMaterial");
			mr->SetMaterial(material);
			mr->SetMesh(mesh);
			obj->AddComponent<JudgeScript>();
		}

		// 야하리
		{
			Player* obj = object::Instantiate<Player>(eLayerType::Player, this);
			obj->SetName(L"Larry");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.4f, -0.5f, 0.f));
			tr->SetScale(Vector3(14.f, 14.f, 14.f));
			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
#pragma region CREATE ANIMATION
			Animator* animator = obj->AddComponent<Animator>();
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"LarryIdle", L"Portfolio\\Larry\\Larry_Idle.png");
			animator->Create(L"LarryIdle", texture, Vector2(0.f, 0.f), Vector2(1172.f, 1380.f),
				Vector2::Zero, 5, 1, 0.4f);
			texture = Resources::Load<Texture>(L"LarryIdleBlink", L"Portfolio\\Larry\\Larry_Idle_Blink.png");
			animator->Create(L"LarryIdleBlink", texture, Vector2(0.f, 0.f), Vector2(1172.f, 1380.f),
				Vector2::Zero, 3, 1, 0.05f);
			texture = Resources::Load<Texture>(L"LarryIdleTalk", L"Portfolio\\Larry\\Larry_Idle_Talk.png");
			animator->Create(L"LarryIdleTalk", texture, Vector2(0.f, 0.f), Vector2(1172.f, 1380.f),
				Vector2::Zero, 10, 3, 0.05f);
			texture = Resources::Load<Texture>(L"LarryConfidentIdle", L"Portfolio\\Larry\\Larry_Confident_Idle.png");
			animator->Create(L"LarryConfidentIdle", texture, Vector2(0.f, 0.f), Vector2(1172.f, 1380.f),
				Vector2::Zero, 12, 5, 0.05f);
#pragma endregion
			animator->Play(L"LarryConfidentIdle", true);

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> material = Resources::Find<Material>(L"SpriteMaterial");
			mr->SetMaterial(material);
			mr->SetMesh(mesh);
			obj->AddComponent<LarryScript>();
		}

		Scene::Initialize();
	}

	void CourtScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::BACKSPACE))
		{
			SceneManager::LoadScene(eSceneType::MainTitle);
		}

		Scene::Update();
	}

	void CourtScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void CourtScene::Render()
	{
		Scene::Render();
	}

	void CourtScene::OnEnter()
	{
	}

	void CourtScene::OnExit()
	{
	}
}
