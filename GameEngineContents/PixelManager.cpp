#include "PreCompile.h"
#include "PixelManager.h"

#include <GameEngineCore/GameEngineCoreWindow.h>
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
	if (false == isCaptureTexture && false == isSetCamera)
	{
		CreatePixelTexture();
		Off();
		isCaptureTexture = true;
	}
	if (true == isSetCamera)
	{
		SetCameraBeforeCaptureTexture();
		isSetCamera = false;
	}
}

void PixelManager::SetCameraBeforeCaptureTexture()
{
	const std::shared_ptr<BackDrop_PlayLevel>& BackDropPtr = PlayLevel::GetPlayLevelPtr()->GetBackDropPtr();
	float4 BackScale;
	if (nullptr != BackDropPtr)
	{
		BackScale = BackDropPtr->GetBackGroundScale();
	}
	else
	{
		BackScale = GlobalValue::GetWindowScale();
	}
	
	const float4 WinScale = GlobalValue::GetWindowScale();

	const float XRatio = BackScale.X / WinScale.X;
	const float YRatio = BackScale.Y / WinScale.Y;

	ZoomRatio = max(XRatio, YRatio);

	if (XRatio > YRatio)
	{
		const float Ratio = XRatio / YRatio;
		BackScale.Y *= Ratio;
	}
	if (XRatio < YRatio)
	{
		const float Ratio = YRatio / XRatio;
		BackScale.X *= Ratio;
	}


	const std::shared_ptr<GameEngineCamera>& CameraPtr = GetLevel()->GetCamera(static_cast<int>(ECAMERAORDER::MainPrev));
	CameraPtr->SetZoomValue(ZoomRatio);
	CameraPtr->Transform.SetLocalPosition(float4(BackScale.hX(), -BackScale.hY(), -1000.0f));
}

void PixelManager::CreatePixelTexture()
{
	const std::shared_ptr<GameEngineRenderTarget>& PrevRenderTarget = GetLevel()->GetCamera(static_cast<int>(ECAMERAORDER::MainPrev))->GetCameraAllRenderTarget();
	PixelTexture = GameEngineTexture::Create(PrevRenderTarget->GetTexture(1)->GetTexure2D());
	PixelTexture->CaptureTexture();
	PixelTexture->NotRefTexture2D();

	const std::shared_ptr<GameEngineCamera>& CameraPtr = GetLevel()->GetCamera(static_cast<int>(ECAMERAORDER::MainPrev));
	CameraPtr->Off();
}

GameEngineColor PixelManager::GetColor(const float4& _Position, GameEngineColor _DefaultColor /*= GameEngineColor::WHITE*/)
{
	if (nullptr == PixelTexture)
	{
		return _DefaultColor;
	}

	// DXGI_FORMAT_B8G8R8A8_UNORM
	float4 CheckPosition = _Position;
	CheckPosition.Y *= -1.0f;
	CheckPosition /= ZoomRatio;

	return PixelTexture->GetColor(CheckPosition, _DefaultColor);
}

