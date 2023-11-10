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
	LightRenderer->Transform.AddLocalPosition(float4(0.0f, 0.0f, -0.00009f));
	LightColor = _Color;
	UpdateLightLerp();
}

void ALightLerp::SetPlusAlpha(float _Alpha)
{
	PlusAlpha = _Alpha;
}

void ALightLerp::UpdateLightLerp()
{
	if (nullptr == LightRenderer)
	{
		MsgBoxAssert("라이트 렌더러가 존재하지 않습니다.");
		return;
	}

	const float ALightValue = SkyLerp::MainSkyManager->GetALightValue();

	float Alpha = LightColor.A * ALightValue * PlusAlpha;
	LightRenderer->GetColorData().MulColor.A = Alpha;
}