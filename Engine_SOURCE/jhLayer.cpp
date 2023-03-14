#include "jhLayer.h"
#include "jhRenderer.h"
#include "jhTransform.h"

namespace jh
{
	// Z�� ����
	/*static bool CompareGameObjectByZAxis(GameObject* a, GameObject* b)
	{
		Transform* aTr = a->GetComponent<Transform>();
		Transform* bTr = b->GetComponent<Transform>();

		if (aTr->GetPosition().z <= bTr->GetPosition().z)
		{
			return true;
		}

		return false;
	}*/

	Layer::Layer()
	{
	}

	Layer::~Layer()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;

			delete obj;
			obj = nullptr;
		}
	}

	void Layer::Initialize()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->Initialize();
		}
	}

	void Layer::Update()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;
			if (obj->GetState() != GameObject::eState::Active)
				continue;

			obj->Update();
		}
	}

	void Layer::FixedUpdate()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;
			if (obj->GetState() != GameObject::eState::Active)
				continue;

			obj->FixedUpdate();
		}

		// Sort Z Axis
	}

	void Layer::Render()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;
			if (obj->GetState() != GameObject::eState::Active)
				continue;

			obj->Render();
		}
	}

	void Layer::Destroy()
	{
		std::set<GameObject*> deleteObjects;
		// ������ ������Ʈ���� ���� ã�ƿ´�.
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj->GetState() == GameObject::eState::Dead)
			{
				deleteObjects.insert(gameObj);
			}
		}

		// ������ �� ������Ʈ���� ���ӿ�����Ʈ ���� �ȿ��� ����
		for (GameObjectIter iter = mGameObjects.begin(); iter != mGameObjects.end();)
		{
			std::set<GameObject*>::iterator deleteIter = deleteObjects.find(*iter);

			if (deleteIter != deleteObjects.end())
			{
				iter = mGameObjects.erase(iter);
			}
			else
			{
				iter++;
			}
		}

		// ������ ������Ʈ���� ���� ��(�޸�)���� ����
		for (GameObject* gameObj : deleteObjects)
		{
			delete gameObj;
			gameObj = nullptr;
		}
	}

	void Layer::AddGameObject(GameObject* gameObject)
	{
		if (gameObject == nullptr)
			return;

		mGameObjects.push_back(gameObject);
	}

	std::vector<GameObject*> Layer::GetDontDestroyGameObjects()
	{
		std::vector<GameObject*> donts;
		for (GameObjectIter iter = mGameObjects.begin(); iter != mGameObjects.end();)
		{
			if ((*iter)->IsDontDestroy() == true)
			{
				donts.push_back((*iter));
				iter = mGameObjects.erase(iter);
			}
			else
			{
				iter++;
			}
		}

		return donts;
	}
}