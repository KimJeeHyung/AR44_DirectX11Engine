#include "jhRenderer.h"
#include "jhResources.h"

namespace jh::renderer
{
	Vertex vertexes[4] = {};
	ConstantBuffer* constantBuffers[(UINT)eCBType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[(UINT)eSamplerType::End] = {};

	void SetUpState()
	{
		// Input Layout (정점 구조 정보)
		D3D11_INPUT_ELEMENT_DESC arrLayoutDesc[3] = {};

		arrLayoutDesc[0].AlignedByteOffset = 0;
		arrLayoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		arrLayoutDesc[0].InputSlot = 0;
		arrLayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[0].SemanticName = "POSITION";
		arrLayoutDesc[0].SemanticIndex = 0;

		arrLayoutDesc[1].AlignedByteOffset = 12;
		arrLayoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayoutDesc[1].InputSlot = 0;
		arrLayoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[1].SemanticName = "COLOR";
		arrLayoutDesc[1].SemanticIndex = 0;

		arrLayoutDesc[2].AlignedByteOffset = 28;
		arrLayoutDesc[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayoutDesc[2].InputSlot = 0;
		arrLayoutDesc[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[2].SemanticName = "TEXCOORD";
		arrLayoutDesc[2].SemanticIndex = 0;

		Shader* shader = Resources::Find<Shader>(L"RectShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3, shader->GetVSBlobBufferPointer(),
			shader->GetVSBlobBufferSize(), shader->GetInputLayoutAddressOf());

		// SamplerState
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
	}

	void LoadBuffer()
	{
		// Create Mesh
		Mesh* mesh = new Mesh();
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
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());

		// 상수 버퍼
		Vector4 pos(0.2f, 0.2f, 0.f, 0.f);
		constantBuffers[(UINT)eCBType::Transform] = new ConstantBuffer();
		constantBuffers[(UINT)eCBType::Transform]->Create(sizeof(Vector4));
		constantBuffers[(UINT)eCBType::Transform]->Bind(&pos);
	}

	void LoadShader()
	{
		Shader* shader = new Shader();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "VS_Test");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "PS_Test");

		Resources::Insert<Shader>(L"RectShader", shader);
	}

	void Initialize()
	{
		// 사각형
		vertexes[0].pos = Vector3(-0.5f, 0.5f, 0.5f);
		vertexes[0].color = Vector4(0.f, 1.f, 0.f, 1.f);
		vertexes[0].uv = Vector2(0.f, 0.f);

		vertexes[1].pos = Vector3(0.5f, 0.5f, 0.5f);
		vertexes[1].color = Vector4(1.f, 1.f, 1.f, 1.f);
		vertexes[1].uv = Vector2(1.f, 0.f);

		vertexes[2].pos = Vector3(0.5f, -0.5f, 0.5f);
		vertexes[2].color = Vector4(1.f, 0.f, 0.f, 1.f);
		vertexes[2].uv = Vector2(1.f, 1.f);

		vertexes[3].pos = Vector3(-0.5f, -0.5f, 0.5f);
		vertexes[3].color = Vector4(0.f, 0.f, 1.f, 1.f);
		vertexes[3].uv = Vector2(0.f, 1.f);

		LoadShader();
		SetUpState();
		LoadBuffer();
	}

	void Release()
	{
		for (size_t i = 0; i < (UINT)eCBType::End; i++)
		{
			delete constantBuffers[i];
			constantBuffers[i] = nullptr;
		}
	}
}
