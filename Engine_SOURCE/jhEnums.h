#pragma once

namespace jh::enums
{
	enum class eSceneType
	{
		Test,
		Test2,
		Test3,
		Test4,
		Test5,
		MainTitle,
		Title,
		TitleSelect,
		BeforeTalk,
		Court,
		End,
	};

	enum class eLayerType
	{
		None = 0,
		Camera,
		Grid,
		Background,
		Monster,
		Player,
		Desk,

		Particle,
		UI,
		End = 16,
	};

	enum class eComponentType
	{
		None,
		Transform,	// 위치 데이터 수정하는 컴포넌트
		Camera,
		Mesh,
		Collider,
		MeshRenderer,
		SpriteRenderer,
		Animator,
		ParticleSystem,
		Light,
		UI,
		Script,
		End,
	};

	enum class eResourceType
	{
		Mesh,
		Texture,
		Material,
		Sound,
		//Font,
		Prefab,
		MeshData,
		GraphicShader,
		ComputeShader,
		Script,
		End,
	};

	enum class eColliderType
	{
		None,
		Rect,
		Circle,
		Box,
		Sphere,
		End,
	};

	enum class eAnimationType
	{
		None,
		SecondDimension,
		ThirdDimension,
		End,
	};

	enum class eLightType
	{
		Directional,
		Point,
		Spot,
		End,
	};
}