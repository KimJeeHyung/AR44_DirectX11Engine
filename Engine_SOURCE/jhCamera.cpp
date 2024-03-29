#include "jhCamera.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhApplication.h"
#include "jhRenderer.h"
#include "jhScene.h"
#include "jhSceneManager.h"
#include "jhMaterial.h"
#include "jhBaseRenderer.h"
#include "jhSceneManager.h"

extern jh::Application application;

namespace jh
{
	Matrix Camera::View = Matrix::Identity;
	Matrix Camera::Projection = Matrix::Identity;

	Camera::Camera() :
		Component(eComponentType::Camera),
		mType(eProjectionType::Perspective),
		mAspectRatio(1.f),
		mNear(1.f),
		mFar(1000.f),
		mScale(1.f)
	{
		EnableLayerMasks();
	}

	Camera::~Camera()
	{
	}

	void Camera::Initialize()
	{
		RegisterCameraInRenderer();
	}

	void Camera::Update()
	{
	}

	void Camera::FixedUpdate()
	{
		CreateViewMatrix();
		CreateProjectionMatrix();

		RegisterCameraInRenderer();
	}

	void Camera::Render()
	{
		View = mView;
		Projection = mProjection;

		sortGameObjects();

		renderOpaque();
		renderCutOut();
		renderTransparent();
	}

	void Camera::CreateViewMatrix()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		// Create Translate view matrix
		mView = Matrix::Identity;
		mView *= Matrix::CreateTranslation(-pos);

		// ȸ�� ����
		Vector3 up = tr->Up();
		Vector3 right = tr->Right();
		Vector3 foward = tr->Foward();

		Matrix viewRotate;
		viewRotate._11 = right.x; viewRotate._12 = up.x; viewRotate._13 = foward.x;
		viewRotate._21 = right.y; viewRotate._22 = up.y; viewRotate._23 = foward.y;
		viewRotate._31 = right.z; viewRotate._32 = up.z; viewRotate._33 = foward.z;

		mView *= viewRotate;
	}

	void Camera::CreateProjectionMatrix()
	{
		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);

		float width = (winRect.right - winRect.left) * mScale;
		float height = (winRect.bottom - winRect.top) * mScale;
		mAspectRatio = width / height;

		if (mType == eProjectionType::Perspective)
		{
			mProjection = Matrix::CreatePerspectiveFieldOfViewLH(XM_2PI / 6.f, mAspectRatio,
				mNear, mFar);
		}
		else
		{
			mProjection = Matrix::CreateOrthographicLH(width / 100.f, height / 100.f,
				mNear, mFar);
		}
	}

	void Camera::RegisterCameraInRenderer()
	{
		eSceneType type = SceneManager::GetActiveScene()->GetSceneType();
		renderer::cameras[(UINT)type].push_back(this);
	}

	void Camera::TurnLayerMask(eLayerType layer, bool enable)
	{
		mLayerMasks.set((UINT)layer, enable);
	}

	void Camera::sortGameObjects()
	{
		mOpaqueGameObjects.clear();
		mCutOutGameObjects.clear();
		mTransparentGameObjects.clear();

		Scene* scene = SceneManager::GetActiveScene();
		for (size_t i = 0; i < (UINT)eLayerType::End; i++)
		{
			if (mLayerMasks[i] == true)
			{
				Layer& layer = scene->GetLayer((eLayerType)i);
				GameObjects gameObjects = layer.GetGameObjects();
				if (gameObjects.size() == 0)
					continue;

				for (GameObject* obj : gameObjects)
				{
					pushGameObjectToRenderingModes(obj);
				}
			}
		}
	}

	void Camera::renderOpaque()
	{
		for (GameObject* obj : mOpaqueGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->Render(); 
		}
	}

	void Camera::renderCutOut()
	{
		for (GameObject* obj : mCutOutGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->Render();
		}
	}

	void Camera::renderTransparent()
	{
		for (GameObject* obj : mTransparentGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->Render();
		}
	}

	void Camera::pushGameObjectToRenderingModes(GameObject* gameObj)
	{
		BaseRenderer* renderer = gameObj->GetComponent<BaseRenderer>();
		if (renderer == nullptr)
			return;

		std::shared_ptr<Material> material = renderer->GetMaterial();
		eRenderingMode mode = material->GetRenderingMode();

		switch (mode)
		{
		case jh::graphics::eRenderingMode::Opaque:
			mOpaqueGameObjects.push_back(gameObj);
			break;
		case jh::graphics::eRenderingMode::CutOut:
			mCutOutGameObjects.push_back(gameObj);
			break;
		case jh::graphics::eRenderingMode::Transparent:
			mTransparentGameObjects.push_back(gameObj);
			break;
		default:
			break;
		}
	}
}