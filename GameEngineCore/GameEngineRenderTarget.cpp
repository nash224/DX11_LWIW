#include "PreCompile.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineCore.h"

GameEngineRenderTarget::GameEngineRenderTarget() 
{
}

GameEngineRenderTarget::~GameEngineRenderTarget() 
{
}


// 다이렉트에서 무슨일을 하건 우리는 결국 device와 컨텍스트에
void GameEngineRenderTarget::Clear()
{
	for (size_t i = 0; i < RTV.size(); i++)
	{
		GameEngineCore::GetContext()->ClearRenderTargetView(RTV[i], ClearColor[i].Arr1D);
	}
}

void GameEngineRenderTarget::Setting()
{
	if (0 >=  RTV.size())
	{
		MsgBoxAssert("만들어지지 않은 랜더타겟을 세팅하려고 했습니다.");
		return;
	}

	GameEngineCore::GetContext()->OMSetRenderTargets(static_cast<UINT>(RTV.size()), &RTV[0], nullptr);
}


void GameEngineRenderTarget::CreateDepthTexture(int _Index)
{
	// 텍스처를 직접 만드는 첫번째 작업
	D3D11_TEXTURE2D_DESC Desc;

	// 텍스처를 3차원으로 만들것이냐인데.
	Desc.ArraySize = 1;

	Desc.Width = Textures[_Index]->GetScale().uiX();
	Desc.Height = Textures[_Index]->GetScale().uiY();

	// 0~부터 1사이의 float이기 때문에. 
	// 1바이트를 남기고 24비트 float을 만듭니다.
	// 남은 8비트를 스텐실이라는 것으로 사용하는데 내일 설명드리겠습니다.
	Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

}