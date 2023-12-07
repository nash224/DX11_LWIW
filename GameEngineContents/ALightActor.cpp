#include "PreCompile.h"
#include "ALightActor.h"

ALightActor::ALightActor() 
{
}

ALightActor::~ALightActor() 
{
}



void ALightActor::Release()
{
	LightRenderer = nullptr;
	ALightRenderer = nullptr;
}

void ALightActor::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}



void ALightActor::Init()
{
	LightRenderer = CreateComponent<ContentsSpriteRenderer>();
	LightRenderer->SetMaterial("ContentsLight2DTexture");
	LightRenderer->SetSprite("Circle.png");
	LightRenderer->GetTransparentInfo().iTransparent = 1;
	LightRenderer->GetTransparentInfo().Inner = 0.2f;
	LightRenderer->GetTransparentInfo().Outter = 1.0f;
	LightRenderer->GetColorData().MulColor.A = 0.1f;

	ALightRenderer = CreateComponent<ContentsSpriteRenderer>();
	ALightRenderer->SetMaterial("ContentsLight2DTexture");
	ALightRenderer->SetSprite("Circle.png");
	ALightRenderer->GetTransparentInfo().iTransparent = 1;
	ALightRenderer->GetTransparentInfo().Inner = 0.2f;
	ALightRenderer->GetTransparentInfo().Outter = 1.0f;
	ALightRenderer->RenderBaseInfoValue.Target0 = 0;
	ALightRenderer->RenderBaseInfoValue.Target4 = 1;
}

void ALightActor::SetColor(const float4& _Color) const
{
	if (nullptr == LightRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 않고 사용할 수 없는 기능입니다.");
		return;
	}

	LightRenderer->GetColorData().MulColor = _Color;
	LightRenderer->GetColorData().MulColor.A = _Color.A * AlphaCorrection;
}

void ALightActor::SetAlpha(float _Alpha)
{
	if (nullptr == LightRenderer || nullptr == ALightRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 않고 사용할 수 없는 기능입니다.");
		return;
	}

	Alpha = _Alpha;
	LightRenderer->GetColorData().MulColor.A = _Alpha * AlphaCorrection;
	ALightRenderer->GetColorData().MulColor.A = _Alpha;
}

void ALightActor::SetAlphaCorrection(float _AlphaCorrection)
{
	if (nullptr == LightRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 않고 사용할 수 없는 기능입니다.");
		return;
	}

	LightRenderer->GetColorData().MulColor.A = Alpha * AlphaCorrection;
	AlphaCorrection = _AlphaCorrection;
}

void ALightActor::SetInner(float _Inner) const
{
	if (nullptr == LightRenderer || nullptr == ALightRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 않고 사용할 수 없는 기능입니다.");
		return;
	}

	LightRenderer->GetTransparentInfo().Inner = _Inner;
	ALightRenderer->GetTransparentInfo().Inner = _Inner;
}

void ALightActor::SetOutter(float _Outter) const
{
	if (nullptr == LightRenderer || nullptr == ALightRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 않고 사용할 수 없는 기능입니다.");
		return;
	}

	LightRenderer->GetTransparentInfo().Outter = _Outter;
	ALightRenderer->GetTransparentInfo().Outter = _Outter;
}

void ALightActor::SetImageScale(const float4& _Scale)
{
	if (nullptr == LightRenderer || nullptr == ALightRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 않고 사용할 수 없는 기능입니다.");
		return;
	}

	LightRenderer->GetImageTransform().SetLocalScale(float4(_Scale.X, _Scale.Y));
	ALightRenderer->GetImageTransform().SetLocalScale(float4(_Scale.X, _Scale.Y));
}