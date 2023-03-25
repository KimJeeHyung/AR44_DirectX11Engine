#include "jhRenderer.h"
#include "jhResources.h"
#include "jhMaterial.h"
#include "jhSceneManager.h"
#include "jhPaintShader.h"

namespace jh::renderer
{
	Vertex vertexes[4] = {};
	ConstantBuffer* constantBuffers[(UINT)eCBType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[(UINT)eSamplerType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};

	Camera* mainCamera = nullptr;
	std::vector<Camera*> cameras[(UINT)eSceneType::End];
	std::vector<DebugMesh> debugMeshes;
	std::vector<LightAttribute> lights;
	StructedBuffer* lightsBuffer = nullptr;

	void LoadMesh()
	{
		// 사각형
		vertexes[0].pos = Vector4(-0.5f, 0.5f, 0.f, 1.f);
		vertexes[0].color = Vector4(0.f, 1.f, 0.f, 1.f);
		vertexes[0].uv = Vector2(0.f, 0.f);

		vertexes[1].pos = Vector4(0.5f, 0.5f, 0.f, 1.f);
		vertexes[1].color = Vector4(1.f, 1.f, 1.f, 1.f);
		vertexes[1].uv = Vector2(1.f, 0.f);

		vertexes[2].pos = Vector4(0.5f, -0.5f, 0.f, 1.f);
		vertexes[2].color = Vector4(1.f, 0.f, 0.f, 1.f);
		vertexes[2].uv = Vector2(1.f, 1.f);

		vertexes[3].pos = Vector4(-0.5f, -0.5f, 0.f, 1.f);
		vertexes[3].color = Vector4(0.f, 0.f, 1.f, 1.f);
		vertexes[3].uv = Vector2(0.f, 1.f);

		// Create Mesh
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"RectMesh", mesh);
		mesh->CreateVertexBuffer(vertexes, 4);

		// 인덱스 버퍼
		std::vector<UINT> indexes;
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);
		indexes.push_back(0);
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());

		// 사각형 충돌체
		vertexes[0].pos = Vector4(-0.5f, 0.5f, -0.00001f, 1.0f);
		vertexes[0].color = Vector4(0.f, 1.f, 0.f, 1.f);
		vertexes[0].uv = Vector2(0.f, 0.f);

		vertexes[1].pos = Vector4(0.5f, 0.5f, -0.00001f, 1.0f);
		vertexes[1].color = Vector4(1.f, 1.f, 1.f, 1.f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector4(0.5f, -0.5f, -0.00001f, 1.0f);
		vertexes[2].color = Vector4(1.f, 0.f, 0.f, 1.f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector4(-0.5f, -0.5f, -0.00001f, 1.0f);
		vertexes[3].color = Vector4(0.f, 0.f, 1.f, 1.f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		std::shared_ptr<Mesh> debugMesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"DebugRectMesh", debugMesh);
		debugMesh->CreateVertexBuffer(vertexes, 4);
		debugMesh->CreateIndexBuffer(indexes.data(), indexes.size());

		// 원
		std::vector<Vertex> circleVertexes;
		Vertex center = {};
		center.pos = Vector4(0.f, 0.f, -0.00001f, 1.f);
		center.color = Vector4(0.f, 1.f, 0.f, 1.f);
		center.uv = Vector2::Zero;

		circleVertexes.push_back(center);

		int iSlice = 80;
		float fRadius = 0.5f;
		float fTheta = XM_2PI / (float)iSlice;

		for (size_t i = 0; i < iSlice; i++)
		{
			Vertex vtx = {};
			vtx.pos = Vector4(fRadius * cosf(fTheta * (float)i),
				fRadius * sinf(fTheta * (float)i), -0.00001f, 1.f);
			vtx.color = center.color;

			circleVertexes.push_back(vtx);
		}

		// 인덱스 버퍼
		indexes.clear();

		for (size_t i = 0; i < iSlice - 2; i++)
		{
			indexes.push_back((UINT)i + 1);
		}
		indexes.push_back(1);

		// Create Mesh
		std::shared_ptr<Mesh> circleMesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"CircleMesh", circleMesh);
		circleMesh->CreateVertexBuffer(circleVertexes.data(), circleVertexes.size());
		circleMesh->CreateIndexBuffer(indexes.data(), indexes.size());
	}

	void SetUpState()
	{
		// Input Layout (정점 구조 정보)
#pragma region Input Layout
		D3D11_INPUT_ELEMENT_DESC arrLayoutDesc[3] = {};

		arrLayoutDesc[0].AlignedByteOffset = 0;
		arrLayoutDesc[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayoutDesc[0].InputSlot = 0;
		arrLayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[0].SemanticName = "POSITION";
		arrLayoutDesc[0].SemanticIndex = 0;

		arrLayoutDesc[1].AlignedByteOffset = 16;
		arrLayoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayoutDesc[1].InputSlot = 0;
		arrLayoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[1].SemanticName = "COLOR";
		arrLayoutDesc[1].SemanticIndex = 0;

		arrLayoutDesc[2].AlignedByteOffset = 32;
		arrLayoutDesc[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayoutDesc[2].InputSlot = 0;
		arrLayoutDesc[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[2].SemanticName = "TEXCOORD";
		arrLayoutDesc[2].SemanticIndex = 0;

		std::shared_ptr<Shader> defaultShader = Resources::Find<Shader>(L"RectShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3, defaultShader->GetVSBlobBufferPointer(),
			defaultShader->GetVSBlobBufferSize(), defaultShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3, spriteShader->GetVSBlobBufferPointer(),
			spriteShader->GetVSBlobBufferSize(), spriteShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3, uiShader->GetVSBlobBufferPointer(),
			uiShader->GetVSBlobBufferSize(), uiShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> gridShader = Resources::Find<Shader>(L"GridShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3, gridShader->GetVSBlobBufferPointer(),
			gridShader->GetVSBlobBufferSize(), gridShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> fadeShader = Resources::Find<Shader>(L"FadeShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3, fadeShader->GetVSBlobBufferPointer(),
			fadeShader->GetVSBlobBufferSize(), fadeShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> debugShader = Resources::Find<Shader>(L"DebugShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3, debugShader->GetVSBlobBufferPointer(),
			debugShader->GetVSBlobBufferSize(), debugShader->GetInputLayoutAddressOf());
#pragma endregion

#pragma region SamplerState
		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.Filter = D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;

		GetDevice()->CreateSamplerState(&samplerDesc,
			samplerStates[(UINT)eSamplerType::Point].GetAddressOf());

		samplerDesc.Filter = D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
		GetDevice()->CreateSamplerState(&samplerDesc,
			samplerStates[(UINT)eSamplerType::Linear].GetAddressOf());

		samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSamplerState(&samplerDesc,
			samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf());

		GetDevice()->BindsSamplers((UINT)eSamplerType::Point, 1,
			samplerStates[(UINT)eSamplerType::Point].GetAddressOf());
		GetDevice()->BindsSamplers((UINT)eSamplerType::Linear, 1,
			samplerStates[(UINT)eSamplerType::Linear].GetAddressOf());
		GetDevice()->BindsSamplers((UINT)eSamplerType::Anisotropic, 1,
			samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf());
#pragma endregion

#pragma region RasterizerState
		D3D11_RASTERIZER_DESC rsDesc = {};
		rsDesc.FillMode = D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_BACK;

		GetDevice()->CreateRasterizerState(&rsDesc,
			rasterizerStates[(UINT)eRSType::SolidBack].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_FRONT;

		GetDevice()->CreateRasterizerState(&rsDesc,
			rasterizerStates[(UINT)eRSType::SolidFront].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_NONE;

		GetDevice()->CreateRasterizerState(&rsDesc,
			rasterizerStates[(UINT)eRSType::SolidNone].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_WIREFRAME;
		rsDesc.CullMode = D3D11_CULL_NONE;

		GetDevice()->CreateRasterizerState(&rsDesc,
			rasterizerStates[(UINT)eRSType::WireframeNone].GetAddressOf());
#pragma endregion

#pragma region DepthStencilState
		D3D11_DEPTH_STENCIL_DESC dsDesc = {};
		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&dsDesc,
			depthStencilStates[(UINT)eDSType::Less].GetAddressOf());

		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_GREATER;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&dsDesc,
			depthStencilStates[(UINT)eDSType::Greater].GetAddressOf());

		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		dsDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&dsDesc,
			depthStencilStates[(UINT)eDSType::NoWrite].GetAddressOf());

		dsDesc.DepthEnable = false;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		dsDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&dsDesc,
			depthStencilStates[(UINT)eDSType::None].GetAddressOf());
#pragma endregion

#pragma region BlendState
		blendStates[(UINT)eBSType::Default] = nullptr;

		D3D11_BLEND_DESC bsDesc = {};
		bsDesc.AlphaToCoverageEnable = false;
		bsDesc.IndependentBlendEnable = false;
		bsDesc.RenderTarget[0].BlendEnable = true;
		bsDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		bsDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		bsDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		bsDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

		bsDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&bsDesc,
			blendStates[(UINT)eBSType::AlphaBlend].GetAddressOf());

		bsDesc.AlphaToCoverageEnable = false;
		bsDesc.IndependentBlendEnable = false;
		bsDesc.RenderTarget[0].BlendEnable = true;
		bsDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		bsDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;

		bsDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&bsDesc,
			blendStates[(UINT)eBSType::OneOne].GetAddressOf());
#pragma endregion
	}

	void LoadBuffer()
	{
		// 상수 버퍼
		constantBuffers[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffers[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));

		constantBuffers[(UINT)eCBType::Material] = new ConstantBuffer(eCBType::Material);
		constantBuffers[(UINT)eCBType::Material]->Create(sizeof(MaterialCB));

		constantBuffers[(UINT)eCBType::Grid] = new ConstantBuffer(eCBType::Grid);
		constantBuffers[(UINT)eCBType::Grid]->Create(sizeof(GridCB));

		constantBuffers[(UINT)eCBType::Fade] = new ConstantBuffer(eCBType::Fade);
		constantBuffers[(UINT)eCBType::Fade]->Create(sizeof(FadeCB));

		constantBuffers[(UINT)eCBType::Animation] = new ConstantBuffer(eCBType::Animation);
		constantBuffers[(UINT)eCBType::Animation]->Create(sizeof(AnimationCB));

		constantBuffers[(UINT)eCBType::Light] = new ConstantBuffer(eCBType::Light);
		constantBuffers[(UINT)eCBType::Light]->Create(sizeof(LightCB));

		// Structured Buffer
		lightsBuffer = new StructedBuffer();
		lightsBuffer->Create(sizeof(LightAttribute), 128, eSRVType::None, nullptr);
	}

	void LoadShader()
	{
		// Default
		std::shared_ptr<Shader> defaultShader = std::make_shared<Shader>();
		defaultShader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		defaultShader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");

		Resources::Insert<Shader>(L"RectShader", defaultShader);

		// Sprite
		std::shared_ptr<Shader> spriteShader = std::make_shared<Shader>();
		spriteShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		spriteShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");

		Resources::Insert<Shader>(L"SpriteShader", spriteShader);

		// UI
		std::shared_ptr<Shader> uiShader = std::make_shared<Shader>();
		uiShader->Create(eShaderStage::VS, L"UserInterfaceVS.hlsl", "main");
		uiShader->Create(eShaderStage::PS, L"UserInterfacePS.hlsl", "main");

		Resources::Insert<Shader>(L"UIShader", uiShader);

		// Grid
		std::shared_ptr<Shader> gridShader = std::make_shared<Shader>();
		gridShader->Create(eShaderStage::VS, L"GridVS.hlsl", "main");
		gridShader->Create(eShaderStage::PS, L"GridPS.hlsl", "main");
		gridShader->SetRSState(eRSType::SolidNone);
		gridShader->SetDSState(eDSType::NoWrite);
		gridShader->SetBSState(eBSType::AlphaBlend);

		Resources::Insert<Shader>(L"GridShader", gridShader);

		// FadeInOut
		std::shared_ptr<Shader> fadeShader = std::make_shared<Shader>();
		fadeShader->Create(eShaderStage::VS, L"FadeInOutVS.hlsl", "main");
		fadeShader->Create(eShaderStage::PS, L"FadeInOutPS.hlsl", "main");
		fadeShader->SetRSState(eRSType::SolidNone);
		fadeShader->SetDSState(eDSType::NoWrite);
		fadeShader->SetBSState(eBSType::AlphaBlend);

		Resources::Insert<Shader>(L"FadeShader", fadeShader);

		// Debug Shader
		std::shared_ptr<Shader> debugShader = std::make_shared<Shader>();
		debugShader->Create(eShaderStage::VS, L"DebugVS.hlsl", "main");
		debugShader->Create(eShaderStage::PS, L"DebugPS.hlsl", "main");
		debugShader->SetRSState(eRSType::SolidNone);
		debugShader->SetDSState(eDSType::NoWrite);
		debugShader->SetBSState(eBSType::AlphaBlend);
		debugShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

		Resources::Insert<Shader>(L"DebugShader", debugShader);

		// PaintShader
		std::shared_ptr<PaintShader> paintShader = std::make_shared<PaintShader>();
		paintShader->Create(L"PaintCS.hlsl", "main");
		Resources::Insert<PaintShader>(L"PaintShader", paintShader);
	}

	void LoadTexture()
	{
		Resources::Load<Texture>(L"SmileTexture", L"Smile.png");
		Resources::Load<Texture>(L"DefaultSprite", L"Light.png");
		Resources::Load<Texture>(L"HPBarTexture", L"HPBar.png");

		std::shared_ptr<Texture> uavTexture = std::make_shared<Texture>();
		uavTexture->Create(1024, 1024, DXGI_FORMAT_R8G8B8A8_UNORM,
			D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);
		Resources::Insert<Texture>(L"PaintTexture", uavTexture);

		// MainTitle
		Resources::Load<Texture>(L"MainBackground", L"title_back.png");
		Resources::Load<Texture>(L"MainTitle", L"titlek.png");
		Resources::Load<Texture>(L"MainCopy", L"copy.png");
		// Titles
		Resources::Load<Texture>(L"gs1Title", L"titlegs1k.png");
		Resources::Load<Texture>(L"gs1Copy", L"copygs1.png");
	}

	void LoadMaterial()
	{
		// Default
		{
			std::shared_ptr<Texture> defaultTexture = Resources::Find<Texture>(L"PaintTexture");
			std::shared_ptr<Shader> defaultShader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> defaultMaterial = std::make_shared<Material>();
			defaultMaterial->SetShader(defaultShader);
			defaultMaterial->SetTexture(defaultTexture);
			Resources::Insert<Material>(L"RectMaterial", defaultMaterial);
		}
		//Sprite
		{
			std::shared_ptr<Texture> spriteTexture = Resources::Find<Texture>(L"DefaultSprite");
			std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(spriteTexture);
			Resources::Insert<Material>(L"SpriteMaterial", spriteMaterial);
		}
		// UI
		std::shared_ptr<Texture> uiTexture = Resources::Find<Texture>(L"HPBarTexture");
		std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
		std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
		uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
		uiMaterial->SetShader(uiShader);
		uiMaterial->SetTexture(uiTexture);
		Resources::Insert<Material>(L"UIMaterial", uiMaterial);
		// Grid
		{
			std::shared_ptr<Shader> gridShader = Resources::Find<Shader>(L"GridShader");
			std::shared_ptr<Material> gridMaterial = std::make_shared<Material>();
			gridMaterial->SetShader(gridShader);
			Resources::Insert<Material>(L"GridMaterial", gridMaterial);
		}
		// FadeInOut
		{
			std::shared_ptr<Shader> fadeShader = Resources::Find<Shader>(L"FadeShader");
			std::shared_ptr<Material> fadeMaterial = std::make_shared<Material>();
			fadeMaterial->SetRenderingMode(eRenderingMode::Transparent);
			fadeMaterial->SetShader(fadeShader);
			Resources::Insert<Material>(L"FadeMaterial", fadeMaterial);
		}
		// Debug(Collider)
		{
			std::shared_ptr<Shader> debugShader = Resources::Find<Shader>(L"DebugShader");
			std::shared_ptr<Material> debugMaterial = std::make_shared<Material>();
			debugMaterial->SetRenderingMode(eRenderingMode::Transparent);
			debugMaterial->SetShader(debugShader);
			Resources::Insert<Material>(L"DebugMaterial", debugMaterial);
		}

#pragma region Portfolio
		// Main
		{
			// Background
			std::shared_ptr<Texture> mbTexture = Resources::Find<Texture>(L"MainBackground");
			std::shared_ptr<Material> mbMaterial = std::make_shared<Material>();
			mbMaterial->SetRenderingMode(eRenderingMode::Transparent);
			mbMaterial->SetShader(uiShader);
			mbMaterial->SetTexture(mbTexture);
			Resources::Insert<Material>(L"MBMaterial", mbMaterial);

			// Title
			std::shared_ptr<Texture> mtTexture = Resources::Find<Texture>(L"MainTitle");
			std::shared_ptr<Material> mtMaterial = std::make_shared<Material>();
			mtMaterial->SetRenderingMode(eRenderingMode::Transparent);
			mtMaterial->SetShader(uiShader);
			mtMaterial->SetTexture(mtTexture);
			Resources::Insert<Material>(L"MTMaterial", mtMaterial);

			// Copy
			std::shared_ptr<Texture> mcTexture = Resources::Find<Texture>(L"MainCopy");
			std::shared_ptr<Material> mcMaterial = std::make_shared<Material>();
			mcMaterial->SetRenderingMode(eRenderingMode::Transparent);
			mcMaterial->SetShader(uiShader);
			mcMaterial->SetTexture(mcTexture);
			Resources::Insert<Material>(L"MCMaterial", mcMaterial);
		}
		//GS1
		{
			// Title
			std::shared_ptr<Texture> gs1tTexture = Resources::Find<Texture>(L"gs1Title");
			std::shared_ptr<Material> gs1tMaterial = std::make_shared<Material>();
			gs1tMaterial->SetRenderingMode(eRenderingMode::Transparent);
			gs1tMaterial->SetShader(uiShader);
			gs1tMaterial->SetTexture(gs1tTexture);
			Resources::Insert<Material>(L"GS1TMaterial", gs1tMaterial);

			// Copy
			std::shared_ptr<Texture> gs1cTexture = Resources::Find<Texture>(L"gs1Copy");
			std::shared_ptr<Material> gs1cMaterial = std::make_shared<Material>();
			gs1cMaterial->SetRenderingMode(eRenderingMode::Transparent);
			gs1cMaterial->SetShader(uiShader);
			gs1cMaterial->SetTexture(gs1cTexture);
			Resources::Insert<Material>(L"GS1CMaterial", gs1cMaterial);
		}
#pragma endregion
	}

	void Initialize()
	{
		LoadMesh();
		LoadShader();
		SetUpState();
		LoadBuffer();
		LoadTexture();
		LoadMaterial();
	}

	void Render()
	{
		BindLights();

		eSceneType type = SceneManager::GetActiveScene()->GetSceneType();
		for (Camera* cam : cameras[(UINT)type])
		{
			if (cam == nullptr)
				continue;

			cam->Render();
		}

		cameras[(UINT)type].clear();
		renderer::lights.clear();
	}

	void Release()
	{
		for (size_t i = 0; i < (UINT)eCBType::End; i++)
		{
			delete constantBuffers[i];
			constantBuffers[i] = nullptr;
		}

		delete lightsBuffer;
		lightsBuffer = nullptr;
	}

	void PushLightAttribute(LightAttribute lightAttribute)
	{
		lights.push_back(lightAttribute);
	}

	void BindLights()
	{
		lightsBuffer->Bind(lights.data(), lights.size());
		lightsBuffer->SetPipeline(eShaderStage::VS, 13);
		lightsBuffer->SetPipeline(eShaderStage::PS, 13);

		renderer::LightCB trCB = {};
		trCB.numberOfLight = lights.size();

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Light];
		cb->Bind(&trCB);
		cb->SetPipeline(eShaderStage::VS);
		cb->SetPipeline(eShaderStage::PS);
	}
}
