#include "jhTransform.h"
#include "jhRenderer.h"
#include "jhCamera.h"

namespace jh
{
	Transform::Transform() :
		Component(eComponentType::Transform),
		mFoward(Vector3::Forward),
		mRight(Vector3::Right),
		mUp(Vector3::Up),
		mScale(Vector3::One),
		mRotation(Vector3::Zero),
		mPosition(Vector3::Zero),
		mParent(nullptr)
	{
	}

	Transform::~Transform()
	{
	}

	void Transform::Initialize()
	{
	}

	void Transform::Update()
	{
		// 실제 로직 상 캐릭터 이동 처리
	}

	void Transform::FixedUpdate()
	{
		// 렌더링에 사용될 위치값들을 업데이트

		// 월드 행렬 생성

		// 크기 변환 행렬
		Matrix scale = Matrix::CreateScale(mScale);

		// 회전 변환 행렬
		Matrix rotation;
		rotation = Matrix::CreateRotationX(mRotation.x);
		rotation *= Matrix::CreateRotationY(mRotation.y);
		rotation *= Matrix::CreateRotationZ(mRotation.z);

		// 이동 변환 행렬
		Matrix position;
		position.Translation(mPosition);

		mWorld = scale * rotation * position;

		mFoward = Vector3::TransformNormal(Vector3::Forward, rotation);
		mRight = Vector3::TransformNormal(Vector3::Right, rotation);
		mUp = Vector3::TransformNormal(Vector3::Up, rotation);

		// 카메라 컴포넌트에서 세팅해준다.
		// 뷰행렬 세팅
		// 투영행렬 세팅

		if (mParent)
		{
			mWorld *= mParent->mWorld;
		}
	}

	void Transform::Render()
	{
	}

	void Transform::SetConstantBuffer()
	{
		renderer::TransformCB trCB = {};
		trCB.world = mWorld;
		trCB.view = Camera::GetGpuViewMatrix();
		trCB.projection = Camera::GetGpuProjectionMatrix();
		
		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Transform];
		cb->Bind(&trCB);
		cb->SetPipeline(eShaderStage::VS);
	}
}
