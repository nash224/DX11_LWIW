#include "PreCompile.h"
#include "ALightLerp.h"

#include "SkyLerp.h"

class AlightInitial
{
public:
	AlightInitial()
	{
		SetLightDepth();
	}

	void SetLightDepth();

};

void AlightInitial::SetLightDepth()
{
	ALightLerp::LightDepth = GlobalUtils::CalculateFixDepth(ERENDERDEPTH::illuminant);
}


float ALightLerp::LightDepth = 0.0f;
AlightInitial AlightInit;
void ALightLerp::SetColor(const float4& _Color)
{
	if (nullptr == LightRenderer)
	{
		MsgBoxAssert("라이트 렌더러가 존재하지 않습니다.");
		return;
	}

	LightColor = _Color;
	LightRenderer->GetColorData().MulColor = _Color;
	UpdateLightLerp();
}

void ALightLerp::SetLightRendererSetting()
{
	if (nullptr == LightRenderer)
	{
		MsgBoxAssert("라이트 렌더러가 존재하지 않습니다.");
		return;
	}

	LightRenderer->Transform.SetLocalPosition(float4(0.0f, 0.0f, LightDepth));
	LightRenderer->SetMaterial("2DTexture_Light");
	LightRenderer->RenderBaseInfoValue.Target3 = 1;
}

void ALightLerp::UpdateLightLerp()
{
	if (nullptr == LightRenderer)
	{
		MsgBoxAssert("라이트 렌더러가 존재하지 않습니다.");
		return;
	}

	const float ALightValue = SkyLerp::MainSkyManager->GetALightValue();

	float Alpha = LightColor.A * ALightValue;
	LightRenderer->GetColorData().MulColor.A = Alpha;
}