#include "PreCompile.h"
#include "ALightLerp.h"

#include "SkyLerp.h"

void ALightLerp::Init(GameEngineActor* _Actor, const ALightLerpParameter& _Para)
{
	LightRenderer = _Actor->CreateComponent<GameEngineSpriteRenderer>();
	SetLightRendererSetting(_Para.Color);
	LightRenderer->SetSprite(_Para.SpriteName);
	LightRenderer->GetImageTransform().SetLocalScale(float4(_Para.Scale));
	LightRenderer->Transform.SetLocalPosition(_Para.Position);

}

void ALightLerp::SetLightRendererSetting(const float4& _Color)
{
	if (nullptr == LightRenderer)
	{
		MsgBoxAssert("라이트 렌더러가 존재하지 않습니다.");
		return;
	}

	LightRenderer->SetMaterial("2DTexture_Light");
	LightRenderer->GetColorData().MulColor = _Color;
	LightRenderer->RenderBaseInfoValue.Target3 = 1;
	LightRenderer->Transform.AddLocalPosition(float4(0.0f, 0.0f, -0.01f));
	LightColor = _Color;
	UpdateLightLerp();
}

void ALightLerp::SetLightAlpha(float _Alpha)
{
	Alpha = _Alpha;
}

void ALightLerp::SetPosition(const float4& _Pos)
{
	LightRenderer->Transform.SetLocalPosition(_Pos);
}

void ALightLerp::UpdateLightLerp()
{
	if (nullptr == LightRenderer)
	{
		MsgBoxAssert("라이트 렌더러가 존재하지 않습니다.");
		return;
	}

	const float ALightValue = SkyLerp::MainSkyManager->GetALightValue();

	float LightAlpha = LightColor.A * ALightValue * Alpha;
	LightRenderer->GetColorData().MulColor.A = LightAlpha;
}