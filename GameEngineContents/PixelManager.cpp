#include "PreCompile.h"
#include "PixelManager.h"

#include <GameEngineCore/GameEngineRenderTarget.h>

#include "BackDrop_PlayLevel.h"


PixelManager::PixelManager() 
{
	
}

PixelManager::~PixelManager() 
{
}

void PixelManager::Update(float _Delta)
{
	if (false == isCaptureTexture && false == isFirstFrame)
	{
		CreatePixelRenderTarget();
		CopyRenderData();
		isCaptureTexture = true;
	}

	isFirstFrame = false;
}

void PixelManager::CreatePixelRenderTarget()
{
	float4 BackScale;
	if (true)
	{
		BackScale = GlobalValue::GetWindowScale();
	}
	else
	{
		BackScale = PlayLevel::GetPlayLevelPtr()->GetBackDropPtr()->GetBackGroundScale();
	}

	PixelRenderTarget = GameEngineRenderTarget::Create();
	PixelRenderTarget->AddNewTexture(DXGI_FORMAT_R8G8B8A8_UNORM, BackScale, float4::ZERONULL);
}

void PixelManager::CopyRenderData()
{
	if (nullptr == PixelRenderTarget)
	{
		MsgBoxAssert("렌더타겟을 세팅하지 않고 복사할 수 없습니다.");
		return;
	}

	const std::shared_ptr<GameEngineRenderTarget>& PrevRenderTarget = GetLevel()->GetCamera(static_cast<int>(ECAMERAORDER::MainPrev))->GetCameraAllRenderTarget();
	PixelRenderTarget->GetTexture(0)->CaptureTexture(PrevRenderTarget->GetTexture(1)->GetTexure2D());
}


GameEngineColor PixelManager::GetColor(const float4& _Position, GameEngineColor _DefaultColor /*= GameEngineColor::WHITE*/)
{
	// DXGI_FORMAT_B8G8R8A8_UNORM
	float4 CheckPosition = _Position;
	CheckPosition.Y *= -1.0f;

	return PixelRenderTarget->GetTexture(0)->GetColor(CheckPosition, _DefaultColor);
}

