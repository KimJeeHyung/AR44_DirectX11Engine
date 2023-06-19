#include "jhTest3Scene.h"
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
#include "jhPayneScript.h"

namespace jh
{
	Test3Scene::Test3Scene() :
		Scene(eSceneType::Test3)
	{
	}

	Test3Scene::~Test3Scene()
	{
	}

	void Test3Scene::Initialize()
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
			obj->SetName(L"Payne");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(-1.f, 0.f, 5.f));
			tr->SetScale(Vector3(5.f, 5.f, 5.f));
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
		}*/

		Scene::Initialize();
	}

	void Test3Scene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::BACKSPACE))
		{
			SceneManager::LoadScene(eSceneType::Test);
		}

		Scene::Update();
	}

	void Test3Scene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void Test3Scene::Render()
	{
		Scene::Render();
	}

	void Test3Scene::OnEnter()
	{
	}

	void Test3Scene::OnExit()
	{
	}
}
