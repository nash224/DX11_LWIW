#include "PreCompile.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineCore.h"

GameEngineRenderTarget::GameEngineRenderTarget() 
{
}

GameEngineRenderTarget::~GameEngineRenderTarget() 
{
}


// ���̷�Ʈ���� �������� �ϰ� �츮�� �ᱹ device�� ���ؽ�Ʈ��
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
		MsgBoxAssert("��������� ���� ����Ÿ���� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	GameEngineCore::GetContext()->OMSetRenderTargets(static_cast<UINT>(RTV.size()), &RTV[0], nullptr);
}


void GameEngineRenderTarget::CreateDepthTexture(int _Index)
{
	// �ؽ�ó�� ���� ����� ù��° �۾�
	D3D11_TEXTURE2D_DESC Desc;

	// �ؽ�ó�� 3�������� ������̳��ε�.
	Desc.ArraySize = 1;

	Desc.Width = Textures[_Index]->GetScale().uiX();
	Desc.Height = Textures[_Index]->GetScale().uiY();

	// 0~���� 1������ float�̱� ������. 
	// 1����Ʈ�� ����� 24��Ʈ float�� ����ϴ�.
	// ���� 8��Ʈ�� ���ٽ��̶�� ������ ����ϴµ� ���� ����帮�ڽ��ϴ�.
	Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

}