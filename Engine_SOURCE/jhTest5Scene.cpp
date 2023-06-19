#include "jhTest5Scene.h"
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
#include "jhPlayer.h"
#include "jhFadeScript.h"
#include "jhInput.h"
#include "jhAnimator.h"
#include "jhLarryScript.h"

namespace jh
{
	Test5Scene::Test5Scene() :
		Scene(eSceneType::Test5)
	{
	}

	Test5Scene::~Test5Scene()
	{
	}

	void Test5Scene::Initialize()
	{
		//GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		//Camera* cameraComp = cameraObj->AddComponent<Camera>();
		//cameraComp->TurnLayerMask(eLayerType::UI, false);
		//cameraObj->AddComponent<CameraScript>();

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
			obj->SetName(L"Larry");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(-1.f, 0.f, 5.f));
			tr->SetScale(Vector3(5.f, 5.f, 5.f));
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
			animator->Play(L"LarryIdle", false);

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> material = Resources::Find<Material>(L"SpriteMaterial");
			mr->SetMaterial(material);
			mr->SetMesh(mesh);
			obj->AddComponent<LarryScript>();
		}*/

		Scene::Initialize();
	}

	void Test5Scene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::BACKSPACE))
		{
			SceneManager::LoadScene(eSceneType::Test);
		}

		Scene::Update();
	}

	void Test5Scene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void Test5Scene::Render()
	{
		Scene::Render();
	}

	void Test5Scene::OnEnter()
	{
	}

	void Test5Scene::OnExit()
	{
	}
}
