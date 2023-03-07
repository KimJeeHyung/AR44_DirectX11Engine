#include "jhCollisionManager.h"
#include "jhScene.h"
#include "jhSceneManager.h"

namespace jh
{
	std::bitset<(UINT)eLayerType::End> CollisionManager::mLayerCollisionMatrix[(UINT)eLayerType::End] = {};
	std::map<UINT64, bool> CollisionManager::mCollisionMap;

	void CollisionManager::Initialize()
	{
	}

	void CollisionManager::Update()
	{
		Scene* scene = SceneManager::GetActiveScene();

		for (UINT row = 0; row < (UINT)eLayerType::End; row++)
		{
			for (UINT column = 0; column < (UINT)eLayerType::End; column++)
			{
				if (mLayerCollisionMatrix[row][column])
				{
					LayerCollision(scene, (eLayerType)row, (eLayerType)column);
				}
			}
		}
	}

	void CollisionManager::FixedUpdate()
	{
	}

	void CollisionManager::Render()
	{
	}

	void CollisionManager::CollisionLayerCheck(eLayerType left, eLayerType right, bool enable)
	{
	}

	void CollisionManager::LayerCollision(Scene* scene, eLayerType left, eLayerType right)
	{
		const std::vector<GameObject*>& lefts = scene->GetGameObjects(left);
		const std::vector<GameObject*>& rights = scene->GetGameObjects(right);

		for (GameObject* left : lefts)
		{
			if (left->GetState() != GameObject::Active)
				continue;
			if (left->GetComponent<Collider2D>() == nullptr)
				continue;

			for (GameObject* right : rights)
			{
				if (right->GetState() != GameObject::Active)
					continue;
				if (right->GetComponent<Collider2D>() == nullptr)
					continue;
				if (left == right)
					continue;

				ColliderCollision(left->GetComponent<Collider2D>(),
					right->GetComponent<Collider2D>());
			}
		}
	}

	void CollisionManager::ColliderCollision(Collider2D* left, Collider2D* right)
	{
		// 두 충돌체 레이어로 구성된 ID 확인
		ColliderID colliderID;
		colliderID.left = (UINT)left;
		colliderID.right = (UINT)right;

		// 이전 충돌 정보를 검색한다.
		// 만약에 충돌 정보가 없는 상태라면
		// 충돌 정보를 생성해준다.
		std::map<UINT64, bool>::iterator iter = mCollisionMap.find(colliderID.id);
		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(colliderID.id, false));
			iter = mCollisionMap.find(colliderID.id);
		}

		// 충돌체크를 해준다.
		if (Intersect(left, right))	// 충돌을 한 상태
		{
			// 이전 프레임에 충돌 중이 아니었다면
			// 이제 막 충돌 중인 상태이므로 Enter
			if (iter->second == false)
			{
				if (left->IsTrigger())
					left->OnTriggerEnter(right);
				else
					left->OnCollisionEnter(right);

				if (right->IsTrigger())
					right->OnTriggerEnter(left);
				else
					right->OnCollisionEnter(left);

				iter->second = true;
			}
			else // 이전 프레임에도 충돌 중이었다면 Stay
			{
				if (left->IsTrigger())
					left->OnTriggerStay(right);
				else
					left->OnCollisionStay(right);

				if (right->IsTrigger())
					right->OnTriggerStay(left);
				else
					right->OnCollisionStay(left);
			}
		}
		else // 충돌하지 않은 상태
		{
			// 이전 프레임에 충돌 중이었다면 Exit
			if (iter->second == true)
			{
				if (left->IsTrigger())
					left->OnTriggerExit(right);
				else
					left->OnCollisionExit(right);

				if (right->IsTrigger())
					right->OnTriggerExit(left);
				else
					right->OnCollisionExit(left);
			}
		}
	}

	bool CollisionManager::Intersect(Collider2D* left, Collider2D* right)
	{
		return true;
	}
}
