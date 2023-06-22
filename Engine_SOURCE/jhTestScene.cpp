#include "jhTestScene.h"
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
			GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player, this);
			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -100.f));
			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(1.f, 1.f, 1.f, 1.f));
			//object::DontDestroyOnLoad(directionalLight);
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
		//GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		//Camera* cameraComp = cameraObj->AddComponent<Camera>();
		////cameraComp->TurnLayerMask(eLayerType::UI, false);
		//cameraObj->AddComponent<CameraScript>();
		////mainCamera = cameraComp;
		//Transform* cameraTr = cameraObj->GetComponent<Transform>();
		////cameraTr->SetPosition(Vector3(-28.7f, 0.f, -7.8f));

		// UI 카메라 오브젝트
		GameObject* UICameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* UICameraComp = UICameraObj->AddComponent<Camera>();
		UICameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		UICameraComp->DisableLayerMasks();
		UICameraComp->TurnLayerMask(eLayerType::UI, true);

		// SMILE RECT(Player)
//		{
//			Player* obj = object::Instantiate<Player>(eLayerType::Player, this);
//			obj->SetName(L"Phoenix");
//			Transform* tr = obj->GetComponent<Transform>();
//			tr->SetPosition(Vector3(-32.5f, 0.5f, 0.f));
//			tr->SetScale(Vector3(14.f, 14.f, 14.f));
//			Collider2D* collider = obj->AddComponent<Collider2D>();
//			collider->SetType(eColliderType::Rect);
//#pragma region CREATE ANIMATION
//			Animator* animator = obj->AddComponent<Animator>();
//			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"PhoenixIdle", L"Portfolio\\Phoenix\\Phoenix_Idle.png");
//			animator->Create(L"PhoenixIdle", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
//				Vector2::Zero, 5, 1, 0.4f);
//			texture = Resources::Load<Texture>(L"PhoenixIdleBlink", L"Portfolio\\Phoenix\\Phoenix_Idle_Blink.png");
//			animator->Create(L"PhoenixIdleBlink", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
//				Vector2::Zero, 3, 1, 0.05f);
//			texture = Resources::Load<Texture>(L"PhoenixIdleTalk", L"Portfolio\\Phoenix\\Phoenix_Idle_Talk.png");
//			animator->Create(L"PhoenixIdleTalk", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
//				Vector2::Zero, 8, 2, 0.05f);
//			texture = Resources::Load<Texture>(L"PhoenixIdleTalkBlink", L"Portfolio\\Phoenix\\Phoenix_Idle_Talk_Blink.png");
//			animator->Create(L"PhoenixIdleTalkBlink", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
//				Vector2::Zero, 3, 1, 0.05f);
//			texture = Resources::Load<Texture>(L"PhoenixIdleTalk2", L"Portfolio\\Phoenix\\Phoenix_Idle_Talk_2.png");
//			animator->Create(L"PhoenixIdleTalk2", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
//				Vector2::Zero, 11, 2, 0.05f);
//			texture = Resources::Load<Texture>(L"PhoenixIdleNod", L"Portfolio\\Phoenix\\Phoenix_Idle_Nod.png");
//			animator->Create(L"PhoenixIdleNod", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
//				Vector2::Zero, 9, 2, 0.05f);
//			texture = Resources::Load<Texture>(L"PhoenixIdleShake", L"Portfolio\\Phoenix\\Phoenix_Idle_Shake.png");
//			animator->Create(L"PhoenixIdleShake", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
//				Vector2::Zero, 12, 2, 0.05f);
//			texture = Resources::Load<Texture>(L"PhoenixThink", L"Portfolio\\Phoenix\\Phoenix_Think.png");
//			animator->Create(L"PhoenixThink", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
//				Vector2::Zero, 4, 5, 0.05f);
//			texture = Resources::Load<Texture>(L"PhoenixThink2", L"Portfolio\\Phoenix\\Phoenix_Think_2.png");
//			animator->Create(L"PhoenixThink2", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
//				Vector2::Zero, 11, 1, 0.05f);
//			texture = Resources::Load<Texture>(L"PhoenixThink3", L"Portfolio\\Phoenix\\Phoenix_Think_3.png");
//			animator->Create(L"PhoenixThink3", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
//				Vector2::Zero, 12, 3, 0.05f);
//			texture = Resources::Load<Texture>(L"PhoenixThink4", L"Portfolio\\Phoenix\\Phoenix_Think_4.png");
//			animator->Create(L"PhoenixThink4", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
//				Vector2::Zero, 6, 1, 0.05f);
//			texture = Resources::Load<Texture>(L"PhoenixThink5", L"Portfolio\\Phoenix\\Phoenix_Think_5.png");
//			animator->Create(L"PhoenixThink5", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
//				Vector2::Zero, 10, 3, 0.05f);
//			texture = Resources::Load<Texture>(L"PhoenixThink6", L"Portfolio\\Phoenix\\Phoenix_Think_6.png");
//			animator->Create(L"PhoenixThink6", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
//				Vector2::Zero, 6, 1, 0.05f);
//			texture = Resources::Load<Texture>(L"PhoenixThinkTalk", L"Portfolio\\Phoenix\\Phoenix_Think_Talk.png");
//			animator->Create(L"PhoenixThinkTalk", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
//				Vector2::Zero, 14, 3, 0.05f);
//			texture = Resources::Load<Texture>(L"PhoenixDeskHit", L"Portfolio\\Phoenix\\Phoenix_Desk_Hit.png");
//			animator->Create(L"PhoenixDeskHit", texture, Vector2(0.f, 0.f), Vector2(1285.f, 980.f),
//				Vector2::Zero, 10, 2, 0.05f);
//			texture = Resources::Load<Texture>(L"PhoenixDeskIdle", L"Portfolio\\Phoenix\\Phoenix_Desk_Idle.png");
//			animator->Create(L"PhoenixDeskIdle", texture, Vector2(0.f, 0.f), Vector2(1285.f, 980.f),
//				Vector2::Zero, 5, 1, 0.4f);
//			texture = Resources::Load<Texture>(L"PhoenixDeskIdleBlink", L"Portfolio\\Phoenix\\Phoenix_Desk_Idle_Blink.png");
//			animator->Create(L"PhoenixDeskIdleBlink", texture, Vector2(0.f, 0.f), Vector2(1285.f, 980.f),
//				Vector2::Zero, 3, 1, 0.05f);
//			texture = Resources::Load<Texture>(L"PhoenixDeskTalk", L"Portfolio\\Phoenix\\Phoenix_Desk_Talk.png");
//			animator->Create(L"PhoenixDeskTalk", texture, Vector2(0.f, 0.f), Vector2(1285.f, 980.f),
//				Vector2::Zero, 7, 6, 0.05f);
//			texture = Resources::Load<Texture>(L"PhoenixPoint", L"Portfolio\\Phoenix\\Phoenix_Point.png");
//			animator->Create(L"PhoenixPoint", texture, Vector2(0.f, 0.f), Vector2(1666.f, 980.f),
//				Vector2::Zero, 6, 4, 0.05f);
//			texture = Resources::Load<Texture>(L"PhoenixPointIdle", L"Portfolio\\Phoenix\\Phoenix_Point_Idle.png");
//			animator->Create(L"PhoenixPointIdle", texture, Vector2(0.f, 0.f), Vector2(1666.f, 980.f),
//				Vector2::Zero, 5, 1, 0.4f);
//			texture = Resources::Load<Texture>(L"PhoenixPointIdleBlink", L"Portfolio\\Phoenix\\Phoenix_Point_Idle_Blink.png");
//			animator->Create(L"PhoenixPointIdleBlink", texture, Vector2(0.f, 0.f), Vector2(1666.f, 980.f),
//				Vector2::Zero, 3, 1, 0.05f);
//			texture = Resources::Load<Texture>(L"PhoenixPointTalk", L"Portfolio\\Phoenix\\Phoenix_Point_Talk.png");
//			animator->Create(L"PhoenixPointTalk", texture, Vector2(0.f, 0.f), Vector2(1666.f, 980.f),
//				Vector2::Zero, 8, 4, 0.05f);
//			texture = Resources::Load<Texture>(L"PhoenixDocument", L"Portfolio\\Phoenix\\Phoenix_Document.png");
//			animator->Create(L"PhoenixDocument", texture, Vector2(0.f, 0.f), Vector2(1146.f, 980.f),
//				Vector2::Zero, 13, 4, 0.07f);
//			texture = Resources::Load<Texture>(L"PhoenixDocumentTalk", L"Portfolio\\Phoenix\\Phoenix_Document_Talk.png");
//			animator->Create(L"PhoenixDocumentTalk", texture, Vector2(0.f, 0.f), Vector2(1146.f, 980.f),
//				Vector2::Zero, 9, 7, 0.05f);
//			texture = Resources::Load<Texture>(L"PhoenixSweatIdle", L"Portfolio\\Phoenix\\Phoenix_Sweat_Idle.png");
//			animator->Create(L"PhoenixSweatIdle", texture, Vector2(0.f, 0.f), Vector2(725.f, 980.f),
//				Vector2::Zero, 12, 2, 0.07f);
//			texture = Resources::Load<Texture>(L"PhoenixSweatTalk", L"Portfolio\\Phoenix\\Phoenix_Sweat_Talk.png");
//			animator->Create(L"PhoenixSweatTalk", texture, Vector2(0.f, 0.f), Vector2(725.f, 980.f),
//				Vector2::Zero, 15, 2, 0.05f);
//			texture = Resources::Load<Texture>(L"PhoenixConfidentIdle", L"Portfolio\\Phoenix\\Phoenix_Confident_Idle.png");
//			animator->Create(L"PhoenixConfidentIdle", texture, Vector2(0.f, 0.f), Vector2(1161.f, 1280.f),
//				Vector2::Zero, 5, 1, 0.4f);
//			texture = Resources::Load<Texture>(L"PhoenixConfidentIdleBlink", L"Portfolio\\Phoenix\\Phoenix_Confident_Idle_Blink.png");
//			animator->Create(L"PhoenixConfidentIdleBlink", texture, Vector2(0.f, 0.f), Vector2(1161.f, 1280.f),
//				Vector2::Zero, 3, 1, 0.05f);
//			texture = Resources::Load<Texture>(L"PhoenixConfidentTalk", L"Portfolio\\Phoenix\\Phoenix_Confident_Talk.png");
//			animator->Create(L"PhoenixConfidentTalk", texture, Vector2(0.f, 0.f), Vector2(1161.f, 1280.f),
//				Vector2::Zero, 7, 6, 0.05f);
//			texture = Resources::Load<Texture>(L"PhoenixShocked", L"Portfolio\\Phoenix\\Phoenix_Shocked.png");
//			animator->Create(L"PhoenixShocked", texture, Vector2(0.f, 0.f), Vector2(1094.f, 1180.f),
//				Vector2::Zero, 7, 5, 0.04f);
//			texture = Resources::Load<Texture>(L"PhoenixAbashedIdle", L"Portfolio\\Phoenix\\Phoenix_Abashed_Idle.png");
//			animator->Create(L"PhoenixAbashedIdle", texture, Vector2(0.f, 0.f), Vector2(1235.f, 980.f),
//				Vector2::Zero, 5, 1, 0.4f);
//			texture = Resources::Load<Texture>(L"PhoenixAbashedIdleBlink", L"Portfolio\\Phoenix\\Phoenix_Abashed_Idle_Blink.png");
//			animator->Create(L"PhoenixAbashedIdleBlink", texture, Vector2(0.f, 0.f), Vector2(1235.f, 980.f),
//				Vector2::Zero, 4, 1, 0.05f);
//			texture = Resources::Load<Texture>(L"PhoenixAbashedTalk", L"Portfolio\\Phoenix\\Phoenix_Abashed_Talk.png");
//			animator->Create(L"PhoenixAbashedTalk", texture, Vector2(0.f, 0.f), Vector2(1235.f, 980.f),
//				Vector2::Zero, 12, 1, 0.05f);
//			texture = Resources::Load<Texture>(L"PhoenixWig", L"Portfolio\\Phoenix\\Phoenix_Wig.png");
//			animator->Create(L"PhoenixWig", texture, Vector2(0.f, 0.f), Vector2(926.f, 980.f),
//				Vector2::Zero, 10, 2, 0.05f);
//#pragma endregion
//			animator->Play(L"PhoenixIdle", false);
//
//			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
//			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
//			std::shared_ptr<Material> material = Resources::Find<Material>(L"SpriteMaterial");
//			mr->SetMaterial(material);
//			mr->SetMesh(mesh);
//			obj->AddComponent<PlayerScript>();
//			//object::DontDestroyOnLoad(obj);
//		}

		// SMILE RECT(Monster)
		//{
		//	Player* obj = object::Instantiate<Player>(eLayerType::Monster);
		//	obj->SetName(L"mSMILE");
		//	Transform* tr = obj->GetComponent<Transform>();
		//	tr->SetPosition(Vector3(2.f, 0.f, 5.f));
		//	//tr->SetRotation(Vector3(0.f, 0.f, XM_PIDIV2));
		//	tr->SetScale(Vector3(2.f, 2.f, 2.f));
		//	Collider2D* collider = obj->AddComponent<Collider2D>();
		//	collider->SetType(eColliderType::Rect);
		//	//collider->SetCenter(Vector2(0.5f, 0.5f));
		//	collider->SetSize(Vector2(2.f, 2.f));
		//	collider->SetRadius(1.f);

		//	SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
		//	std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		//	std::shared_ptr<Material> material = Resources::Find<Material>(L"RectMaterial");
		//	mr->SetMaterial(material);
		//	mr->SetMesh(mesh);
		//	object::DontDestroyOnLoad(obj);
		//}

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
		GameObject* hpBar = object::Instantiate<GameObject>(eLayerType::UI, this);
		hpBar->SetName(L"HPBAR");
		Transform* hpBarTr = hpBar->GetComponent<Transform>();
		hpBarTr->SetPosition(Vector3(-5.f, 3.f, 12.f));
		hpBarTr->SetScale(Vector3(1.f, 1.f, 1.f));
		
		SpriteRenderer* hpSr = hpBar->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> hpMesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> hpSpriteMaterial = Resources::Find<Material>(L"UIMaterial");
		hpSr->SetMesh(hpMesh);
		hpSr->SetMaterial(hpSpriteMaterial);

		//hpBar->Pause();

		// Fade 오브젝트
		GameObject* fadeObj = object::Instantiate<GameObject>(eLayerType::UI, this);
		fadeObj->SetName(L"FADE");
		Transform* fadeTr = fadeObj->GetComponent<Transform>();
		fadeTr->SetPosition(Vector3(0.f, 0.f, 10.f));
		fadeTr->SetScale(Vector3(1.f, 1.f, 1.f));
		
		SpriteRenderer* fadeSr = fadeObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> fadeMesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> fadeMaterial = Resources::Find<Material>(L"FadeMaterial");
		fadeSr->SetMesh(fadeMesh);
		fadeSr->SetMaterial(fadeMaterial);
		FadeScript* fadeScript = fadeObj->AddComponent<FadeScript>();
		fadeScript->SetCamera(UICameraComp);

		// Particle
		/*{
			Player* obj = object::Instantiate<Player>(eLayerType::Particle);
			obj->SetName(L"PARTICLE");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.f, 0.f, 100.f));
			obj->AddComponent<ParticleSystem>();
		}*/

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);
		//CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Player, true);

		Scene::Initialize();
	}

	void TestScene::Update()
	{
		/*if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			SceneManager::LoadScene(eSceneType::Test2);
		}
		else if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			SceneManager::LoadScene(eSceneType::Test3);
		}
		else if (Input::GetKeyDown(eKeyCode::UP))
		{
			SceneManager::LoadScene(eSceneType::Test4);
		}
		else if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			SceneManager::LoadScene(eSceneType::Test5);
		}
		else if (Input::GetKeyDown(eKeyCode::BACKSPACE))
		{
			SceneManager::LoadScene(eSceneType::TitleSelect);
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
