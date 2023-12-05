#include "PreCompile.h"
#include "OutLineEffect.h"

#include "EffectEnum.h"


OutLineEffect::OutLineEffect()
{
	OutLineInfo.ScreenSize = GlobalValue::GetWindowScale();
}

OutLineEffect::~OutLineEffect()
{
}


void OutLineEffect::Start()
{
	std::shared_ptr<GameEngineRenderTarget> AllRenderTarget = GameEngineCore::GetCurLevel()->GetMainCamera()->GetCameraAllRenderTarget();
	if (nullptr != AllRenderTarget)
	{
		ResultTarget = AllRenderTarget->CreateChildRenderTarget({ 0 });
	}

	DefaultSetting();

	EffectUnit.SetMesh("fullrect");
	EffectUnit.SetMaterial("OutLineEffect2D");

	EffectUnit.ShaderResHelper.SetTexture("OutLineTex", AllRenderTarget->GetTexture(static_cast<int>(EEFFECTENUM::OutLine)));
	EffectUnit.ShaderResHelper.SetSampler("OutLineSampler", "POINT");
	EffectUnit.ShaderResHelper.SetConstantBufferLink("OutLineEffectInfo", OutLineInfo);
}

void OutLineEffect::EffectProcess(float _DeltaTime)
{
	ResultTarget->Setting();
	EffectUnit.Render();

	EffectUnit.ShaderResHelper.AllShaderResourcesReset();
	GameEngineRenderTarget::RenderTargetReset();
}

void OutLineEffect::DefaultSetting()
{
	OutLineInfo.OutLineColor = float4::WHITE;
	OutLineInfo.Thickness = 2.0f;
}