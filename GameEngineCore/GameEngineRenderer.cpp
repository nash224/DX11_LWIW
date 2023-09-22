#include "PreCompile.h"
#include "GameEngineRenderer.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineCamera.h"
#include "GameEngineVertex.h"

#include "GameEngineCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineInputLayOut.h"
#include "GameEngineVertexShader.h"
#include "GameEngineRasterizer.h"
#include "GameEnginePixelShader.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineBlend.h"
#include "GameEngineConstantBuffer.h"

GameEngineRenderer::GameEngineRenderer()
{
}

GameEngineRenderer::~GameEngineRenderer()
{
}

// 카메라 내부에서의 순서 변경
void GameEngineRenderer::SetRenderOrder(int _Order)
{

	if (nullptr == Camera)
	{
		MsgBoxAssert("카메라가 존재하지 않는 랜더러 입니다. 카메라부터 지정해주세요.");
		return;
	}

	Camera->Renderers[GetOrder()].remove(GetDynamic_Cast_This<GameEngineRenderer>());
	GameEngineObject::SetOrder(_Order);
	Camera->Renderers[GetOrder()].push_back(GetDynamic_Cast_This<GameEngineRenderer>());

}

// 날 바라보는 카메라 변경
void GameEngineRenderer::SetCameraOrder(int _Order)
{
	SetViewCameraSelect(_Order);
}

void GameEngineRenderer::Start()
{
	SetCameraOrder(0);
}

void GameEngineRenderer::SetViewCameraSelect(int _Order)
{
	GameEngineLevel* Level = GetLevel();

	std::shared_ptr<GameEngineCamera> FindCamera = Level->GetCamera(_Order);

	if (nullptr == FindCamera)
	{
		MsgBoxAssert("카메라가 존재하지 않는데 랜더러를 넣으려고 했습니다.");
		return;
	}

	if (nullptr != Camera)
	{
		Camera->Renderers[GetOrder()].remove(GetDynamic_Cast_This<GameEngineRenderer>());
	}

	Camera = FindCamera.get();
	Camera->Renderers[GetOrder()].push_back(GetDynamic_Cast_This<GameEngineRenderer>());
	// ViewInfo[Camera.get()] = _Order;
}

void GameEngineRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{
	ResSetting();
	Draw();
}

void GameEngineRenderer::ResSetting()
{
	Mesh->InputAssembler1();
	Material->VertexShader();
	LayOut->Setting();
	Mesh->InputAssembler2();
	Material->Rasterizer();
	Material->PixelShader();
	Material->Blend();

	ShaderResHelper.AllShaderResourcesSetting();

	// 애는 솔직히 랜더 타겟이 가져가야 합니다.
	D3D11_VIEWPORT ViewPort = {};
	ViewPort.Width = GameEngineCore::MainWindow.GetScale().X;
	ViewPort.Height = GameEngineCore::MainWindow.GetScale().Y;
	ViewPort.MinDepth = 0.0f;
	ViewPort.MaxDepth = 1.0f;
	ViewPort.TopLeftX = 0.0f;
	ViewPort.TopLeftY = 0.0f;
	GameEngineCore::GetContext()->RSSetViewports(1, &ViewPort);

	std::shared_ptr<class GameEngineRenderTarget> BackBufferRenderTarget = GameEngineCore::GetBackBufferRenderTarget();
	if (nullptr != BackBufferRenderTarget)
	{
		BackBufferRenderTarget->Setting();
	}


	//	float4x4 WorldViewProjection = Transform.GetWorldViewProjectionMatrix();
	//	//std::shared_ptr<GameEngineConstantBuffer> Buffer = GameEngineConstantBuffer::CreateAndFind(sizeof(TransformData), "TransformData", _shader);
	//	//if (nullptr != Buffer)
	//	//{
	//	//	const TransformData& Data = DataTransform->GetConstTransformDataRef();
	//	//	Buffer->ChangeData(Data);
	//	//	Buffer->Setting(0);
	//	//}

}


void GameEngineRenderer::Draw()
{
	Mesh->Draw();
}

void GameEngineRenderer::SetMesh(std::string_view _Name)
{
	Mesh = GameEngineMesh::Find(_Name);

	if (nullptr == Mesh)
	{
		MsgBoxAssert("존재하지 않는 매쉬를 세팅하려고 했습니다.");
	}

	if (nullptr == LayOut && nullptr != Material)
	{
		LayOut = std::make_shared<GameEngineInputLayOut>();
		LayOut->ResCreate(Mesh->GetVertexBuffer(), Material->GetVertexShader());
	}

}

void GameEngineRenderer::SetMaterial(std::string_view _Name)
{
	Material = GameEngineMaterial::Find(_Name);

	if (nullptr == Material)
	{
		MsgBoxAssert("존재하지 않는 매쉬를 세팅하려고 했습니다.");
	}

	if (nullptr == LayOut && nullptr != Mesh)
	{
		LayOut = std::make_shared<GameEngineInputLayOut>();
		LayOut->ResCreate(Mesh->GetVertexBuffer(), Material->GetVertexShader());
	}

	// 버텍스 쉐이더와 픽셀쉐이더가 다 들어있는 상태다.

	// 랜더러의 쉐이더 리소스 헬퍼에
	// 버텍스와 픽셀쉐이더의 리소스정보들을 복사 받습니다.
	ShaderResHelper.ShaderResCopy(Material->GetVertexShader().get());
	ShaderResHelper.ShaderResCopy(Material->GetPixelShader().get());

	// 이걸 회사의 약속.

	if (ShaderResHelper.IsConstantBuffer("TransformData"))
	{
		const TransformData& Data = Transform.GetConstTransformDataRef();
		ShaderResHelper.ConstantBufferLink("TransformData", Data);
	}

	//	//std::shared_ptr<GameEngineConstantBuffer> Buffer = GameEngineConstantBuffer::CreateAndFind(sizeof(TransformData), "TransformData", _shader);
//	//if (nullptr != Buffer)
//	//{
//	//	const TransformData& Data = DataTransform->GetConstTransformDataRef();
//	//	Buffer->ChangeData(Data);
//	//	Buffer->Setting(0);
//	//}

}
