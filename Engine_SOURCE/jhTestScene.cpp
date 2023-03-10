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
		// 메인 카메라 오브젝트
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
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
			obj->SetName(L"Zelda");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(-1.f, 0.f, 5.f));
			//tr->SetRotation(Vector3(0.f, 0.f, XM_PIDIV2));
			//tr->SetScale(Vector3(2.f, 2.f, 2.f));
			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			//collider->SetCenter(Vector2(0.5f, 0.5f));
			//collider->SetSize(Vector2(2.f, 2.f));
			//collider->SetRadius(2.f);
			Animator* animator = obj->AddComponent<Animator>();
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Zelda", L"Zelda.png");
			animator->Create(L"Idle", texture, Vector2(0.f, 0.f), Vector2(120.f, 130.f),
				Vector2::Zero, 3, 0.1f);
			animator->Play(L"Idle", true);

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> material = Resources::Find<Material>(L"SpriteMaterial");
			mr->SetMaterial(material);
			mr->SetMesh(mesh);
			obj->AddComponent<PlayerScript>();
			object::DontDestroyOnLoad(obj);
		}

		// SMILE RECT(Monster)
		//{
		//	Player* obj = object::Instantiate<Player>(eLayerType::Monster);
		//	obj->SetName(L"mSMILE");
		//	Transform* tr = obj->GetComponent<Transform>();
		//	tr->SetPosition(Vector3(2.f, 0.f, 5.f));
		//	//tr->SetRotation(Vector3(0.f, 0.f, XM_PIDIV2));
		//	//tr->SetScale(Vector3(2.f, 2.f, 2.f));
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

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);
		//CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::UI, false);

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
