#include "jhSceneManager.h"
#include "jhTransform.h"
#include "jhMeshRenderer.h"
#include "jhRenderer.h"
#include "jhResources.h"
#include "jhTexture.h"
#include "jhPlayerScript.h"
#include "jhCamera.h"
#include "jhCameraScript.h"
#include "jhSpriteRenderer.h"

namespace jh
{
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initialize()
	{
		mActiveScene = new Scene();
		//mActiveScene->Initialize();

		// 메인 카메라 오브젝트
		GameObject* cameraObj = new GameObject();
		Transform* cameraTr = new Transform();
		cameraTr->SetPosition(Vector3(0.f, 0.f, 0.f));
		cameraObj->AddComponent(cameraTr);
		Camera* cameraComp = new Camera();
		cameraObj->AddComponent(cameraComp);
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		CameraScript* cameraScript = new CameraScript();
		cameraObj->AddComponent(cameraScript);
		mActiveScene->AddGameObject(cameraObj, eLayerType::Camera);

		// UI 카메라 오브젝트
		GameObject* UICameraObj = new GameObject();
		Transform* UICameraTr = new Transform();
		UICameraTr->SetPosition(Vector3(0.f, 0.f, 0.f));
		UICameraObj->AddComponent(UICameraTr);
		Camera* UICameraComp = new Camera();
		UICameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		UICameraObj->AddComponent(UICameraComp);
		mActiveScene->AddGameObject(UICameraObj, eLayerType::Camera);
		UICameraComp->DisableLayerMasks();
		UICameraComp->TurnLayerMask(eLayerType::UI, true);

		// SMILE RECT
		GameObject* obj = new GameObject();
		obj->SetName(L"SMILE");
		Transform* tr = new Transform();
		tr->SetPosition(Vector3(-3.f, 0.f, 10.f));
		tr->SetRotation(Vector3(0.f, 0.f, XM_PIDIV2));
		tr->SetScale(Vector3(1.f, 1.f, 1.f));
		obj->AddComponent(tr);

		MeshRenderer* mr = new MeshRenderer();
		obj->AddComponent(mr);

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> material = Resources::Find<Material>(L"RectMaterial");

		mr->SetMaterial(material);
		mr->SetMesh(mesh);

		PlayerScript* playerScript = new PlayerScript();
		obj->AddComponent(playerScript);
		mActiveScene->AddGameObject(obj, eLayerType::Player);

		// SMILE RECT CHILD
		GameObject* child = new GameObject();
		child->SetName(L"SMILE CHILD");
		Transform* childTr = new Transform();
		childTr->SetPosition(Vector3(2.f, 0.f, 0.f));
		childTr->SetScale(Vector3(1.f, 1.f, 1.f));
		child->AddComponent(childTr);
		childTr->SetParent(tr);

		MeshRenderer* childMr = new MeshRenderer();
		child->AddComponent(childMr);

		std::shared_ptr<Material> childMaterial = Resources::Find<Material>(L"RectMaterial");
		childMr->SetMaterial(childMaterial);
		childMr->SetMesh(mesh);

		mActiveScene->AddGameObject(child, eLayerType::Player);

		// Light Object
		GameObject* spriteObj = new GameObject();
		spriteObj->SetName(L"LIGHT");
		Transform* spriteTr = new Transform();
		spriteTr->SetPosition(Vector3(5.f, 0.f, 10.f));
		spriteTr->SetScale(Vector3(5.f, 5.f, 1.f));
		spriteObj->AddComponent(spriteTr);

		SpriteRenderer* sr = new SpriteRenderer();
		spriteObj->AddComponent(sr);

		std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"SpriteMaterial");

		//Vector2 vec2(1.f, 1.f);
		//material->SetData(eGPUParam::Vector2, &vec2);

		sr->SetMaterial(spriteMaterial);
		sr->SetMesh(mesh);

		mActiveScene->AddGameObject(spriteObj, eLayerType::Player);

		// HPBar
		GameObject* hpBar = new GameObject();
		hpBar->SetName(L"HPBAR");
		Transform* hpBarTr = new Transform();
		hpBarTr->SetPosition(Vector3(-5.f, 3.f, 12.f));
		hpBarTr->SetScale(Vector3(1.f, 1.f, 1.f));
		hpBar->AddComponent(hpBarTr);

		SpriteRenderer* hpSr = new SpriteRenderer();
		hpBar->AddComponent(hpSr);

		std::shared_ptr<Mesh> hpMesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> hpSpriteMaterial = Resources::Find<Material>(L"UIMaterial");

		hpSr->SetMesh(hpMesh);
		hpSr->SetMaterial(hpSpriteMaterial);
		mActiveScene->AddGameObject(hpBar, eLayerType::UI);

		mActiveScene->Initialize();
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::FixedUpdate()
	{
		mActiveScene->FixedUpdate();
	}

	void SceneManager::Render()
	{
		mActiveScene->Render();
	}

	void SceneManager::Release()
	{
		delete mActiveScene;
		mActiveScene = nullptr;
	}
}
