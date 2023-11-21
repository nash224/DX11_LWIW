#include "PreCompile.h"
#include "SkyLightEffect.h"


#include "EffectEnum.h"

SkyLightEffect::SkyLightEffect()
{
}

SkyLightEffect::~SkyLightEffect()
{
}

void SkyLightEffect::Start()
{
	std::shared_ptr<GameEngineRenderTarget> AllRenderTarget = GameEngineCore::GetCurLevel()->GetMainCamera()->GetCameraAllRenderTarget();
	if (nullptr != AllRenderTarget)
	{
		ResultTarget = AllRenderTarget->CreateChildRenderTarget({ 0 });
	}

	EffectUnit.SetMesh("fullrect");
	EffectUnit.SetMaterial("SKyLightEffect2D");

	EffectUnit.ShaderResHelper.SetTexture("SkyTex", AllRenderTarget->GetTexture(static_cast<int>(EEFFECTENUM::SkyLight)));
	EffectUnit.ShaderResHelper.SetTexture("LightTex", AllRenderTarget->GetTexture(static_cast<int>(EEFFECTENUM::Illuminant)));

	EffectUnit.ShaderResHelper.SetSampler("SkySampler", "POINT");
	EffectUnit.ShaderResHelper.SetSampler("LightSampler", "POINT");
}

void SkyLightEffect::EffectProcess(float _DeltaTime)
{
	ResultTarget->Setting();
	EffectUnit.Render();

	EffectUnit.ShaderResHelper.AllShaderResourcesReset();
	GameEngineRenderTarget::RenderTargetReset();
}
