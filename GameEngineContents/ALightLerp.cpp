#include "PreCompile.h"
#include "ALightLerp.h"

#include "SkyLerp.h"

void ALightLerp::Init(GameEngineActor* _Actor, const ALightLerpParameter& _Para)
{
	LightColor = _Para.Color;

	LightRenderer = _Actor->CreateComponent<GameEngineSpriteRenderer>();
	LightRenderer->SetMaterial("2DTexture_Light");
	LightRenderer->SetSprite(_Para.SpriteName);
	LightRenderer->GetColorData().MulColor = _Para.Color;
	LightRenderer->RenderBaseInfoValue.Target3 = 1;
	if (_Para.Scale != float4::ZERO)
	{
		LightRenderer->GetImageTransform().SetLocalScale(float4(_Para.Scale));
	}
	LightRenderer->Transform.SetLocalPosition(_Para.Position + float4(0.0f, 0.0f, -0.01f));

	UpdateLightLerp();
}

void ALightLerp::SetLightAlpha(float _Alpha)
{
	Alpha = _Alpha;
}

void ALightLerp::SetPosition(const float4& _Pos)
{
	LightRenderer->Transform.SetLocalPosition(_Pos + float4(0.0f, 0.0f, -0.01f));
}

void ALightLerp::UpdateLightLerp()
{
	if (nullptr == LightRenderer)
	{
		MsgBoxAssert("라이트 렌더러가 존재하지 않습니다.");
		return;
	}

	
	const float ALightValue = PlayLevel::GetCurLevel()->GetSkyPtr()->GetALightValue();
	LightRenderer->GetColorData().MulColor.A = LightColor.A * ALightValue * Alpha;
}