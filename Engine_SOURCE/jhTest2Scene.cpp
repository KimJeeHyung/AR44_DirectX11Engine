#include "jhTest2Scene.h"
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
#include "jhPlayer.h"
#include "jhFadeScript.h"
#include "jhInput.h"
#include "jhAnimator.h"
#include "jhMiaScript.h"

namespace jh
{
	Test2Scene::Test2Scene() :
		Scene(eSceneType::Test2)
	{
	}

	Test2Scene::~Test2Scene()
	{
	}

	void Test2Scene::Initialize()
	{
		/*GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();*/

		// Directional Light
		{
			GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player, this);
			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -100.f));
			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(1.f, 1.f, 1.f, 1.f));
		}

		// SMILE RECT(Player)
		/*{
			Player* obj = object::Instantiate<Player>(eLayerType::Player, this);
			obj->SetName(L"Mia");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(-1.f, 0.f, 5.f));
			tr->SetScale(Vector3(5.f, 5.f, 5.f));
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
		}*/

		Scene::Initialize();
	}

	void Test2Scene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::BACKSPACE))
		{
			SceneManager::LoadScene(eSceneType::Test);
		}

		Scene::Update();
	}

	void Test2Scene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void Test2Scene::Render()
	{
		Scene::Render();
	}

	void Test2Scene::OnEnter()
	{
	}

	void Test2Scene::OnExit()
	{
	}
}
