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
		int row = 0;
		int column = 0;

		if ((UINT)left <= (UINT)right)
		{
			row = (UINT)left;
			column = (UINT)right;
		}
		else
		{
			row = (UINT)right;
			column = (UINT)left;
		}

		mLayerCollisionMatrix[row][column] = enable;
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
		// �� �浹ü ���̾�� ������ ID Ȯ��
		ColliderID colliderID;
		colliderID.left = (UINT)left->GetID();
		colliderID.right = (UINT)right->GetID();

		// ���� �浹 ������ �˻��Ѵ�.
		// ���࿡ �浹 ������ ���� ���¶��
		// �浹 ������ �������ش�.
		std::map<UINT64, bool>::iterator iter = mCollisionMap.find(colliderID.id);
		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(colliderID.id, false));
			iter = mCollisionMap.find(colliderID.id);
		}

		// �浹üũ�� ���ش�.
		if (Intersect(left, right))	// �浹�� �� ����
		{
			// ���� �����ӿ� �浹 ���� �ƴϾ��ٸ�
			// ���� �� �浹 ���� �����̹Ƿ� Enter
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
			else // ���� �����ӿ��� �浹 ���̾��ٸ� Stay
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
		else // �浹���� ���� ����
		{
			// ���� �����ӿ� �浹 ���̾��ٸ� Exit
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
		// Rect vs Rect
		if (left->GetType() == eColliderType::Rect && right->GetType() == eColliderType::Rect)
		{
			// 0 --- 1
			// |     |
			// 3 --- 2
			static const Vector3 arrLocalPos[4] =
			{
				Vector3(-0.5f, 0.5f, 0.f),
				Vector3(0.5f, 0.5f, 0.f),
				Vector3(0.5f, -0.5f, 0.f),
				Vector3(-0.5f, -0.5f, 0.f)
			};

			Transform* leftTr = left->GetOwner()->GetComponent<Transform>();
			Transform* rightTr = right->GetOwner()->GetComponent<Transform>();

			Matrix leftMat = leftTr->GetWorldMatrix();
			Matrix rightMat = rightTr->GetWorldMatrix();

			// �и��� ���� 4�� ���ϱ�
			Vector3 Axis[4] = {};
			Axis[0] = Vector3::Transform(arrLocalPos[1], leftMat);
			Axis[1] = Vector3::Transform(arrLocalPos[3], leftMat);
			Axis[2] = Vector3::Transform(arrLocalPos[1], rightMat);
			Axis[3] = Vector3::Transform(arrLocalPos[3], rightMat);

			Axis[0] -= Vector3::Transform(arrLocalPos[0], leftMat);
			Axis[1] -= Vector3::Transform(arrLocalPos[0], leftMat);
			Axis[2] -= Vector3::Transform(arrLocalPos[0], rightMat);
			Axis[3] -= Vector3::Transform(arrLocalPos[0], rightMat);

			for (size_t i = 0; i < 4; i++)
			{
				Axis[i].z = 0.f;
			}

			Vector3 vc = left->GetPosition() - right->GetPosition();
			vc.z = 0.f;

			Vector3 centerDir = vc;
			for (size_t i = 0; i < 4; i++)
			{
				Vector3 vA = Axis[i];
				vA.Normalize();

				float projDist = 0.f;
				for (size_t j = 0; j < 4; j++)
				{
					projDist += fabsf(Axis[j].Dot(vA) * 0.5f);
				}

				if (projDist < fabsf(centerDir.Dot(vA)))
				{
					return false;
				}
			}

			return true;
		}
		// Circle vs Circle
		else if (left->GetType() == eColliderType::Circle && right->GetType() == eColliderType::Circle)
		{
			Vector3 vc = left->GetPosition() - right->GetPosition();
			vc.z = 0.f;

			float leftRadius = left->GetSize().x * 0.5f;
			float righttRadius = right->GetSize().x * 0.5f;

			if ((leftRadius + righttRadius) < vc.Length())
			{
				return false;
			}

			return true;
		}

		return false;
	}
}
