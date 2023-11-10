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



/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////



void OutLineEffect::Start()
{
	std::shared_ptr<GameEngineRenderTarget> Target = GameEngineCore::GetCurLevel()->GetMainCamera()->GetCameraAllRenderTarget();
	if (nullptr != Target)
	{
		ResultTarget = Target->CreateChildRenderTarget({ 0 });
	}

	EffectUnit.SetMesh("fullrect");
	EffectUnit.SetMaterial("OutLineEffect2D");

	EffectUnit.ShaderResHelper.SetTexture("OutLineTex", Target->GetTexture(static_cast<int>(EEFFECTENUM::OutLine)));
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


void OutLineEffect::SetOutLineColor(const float4& _Color /*= float4::WHITE*/)
{
	OutLineInfo.OutLineColor = _Color;
}

void OutLineEffect::SetOutLineThickness(float _Thickness /*= 1*/)
{
	OutLineInfo.Thickness = _Thickness;
}