#include "jhTest4Scene.h"
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
#include "jhJudgeScript.h"

namespace jh
{
	Test4Scene::Test4Scene() :
		Scene(eSceneType::Test4)
	{
	}

	Test4Scene::~Test4Scene()
	{
	}

	void Test4Scene::Initialize()
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
			obj->SetName(L"Judge");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(-1.f, 0.f, 5.f));
			tr->SetScale(Vector3(5.f, 5.f, 5.f));
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
		}*/

		Scene::Initialize();
	}

	void Test4Scene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::BACKSPACE))
		{
			SceneManager::LoadScene(eSceneType::Test);
		}

		Scene::Update();
	}

	void Test4Scene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void Test4Scene::Render()
	{
		Scene::Render();
	}

	void Test4Scene::OnEnter()
	{
	}

	void Test4Scene::OnExit()
	{
	}
}
