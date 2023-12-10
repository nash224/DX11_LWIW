#include "PreCompile.h"
#include "PlayerEffect.h"
#include <GameEngineCore/GameEngineCore.h>

PlayerEffect::PlayerEffect() 
{
}

PlayerEffect::~PlayerEffect() 
{
}




void PlayerEffect::Start()
{
	std::shared_ptr<GameEngineRenderTarget> Target = GameEngineCore::GetCurLevel()->GetMainCamera()->GetCameraAllRenderTarget();

	if (nullptr != Target)
	{
		ResultTarget = Target->CreateChildRenderTarget({ 0 });
	}

	if (nullptr == GameEngineMaterial::Find("PlayerEffect2D"))
	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("PlayerEffect2D");
		Mat->SetVertexShader("PlayerEffect_VS");
		Mat->SetPixelShader("PlayerEffect_PS");
		Mat->SetDepthState("AlwaysDepth");
	}

	EffectUnit.SetMesh("fullrect");
	EffectUnit.SetMaterial("PlayerEffect2D");

	//EffectUnit.ShaderResHelper.SetSampler("Tex0Sampler", "POINT");
	//EffectUnit.ShaderResHelper.SetSampler("Tex1Sampler", "POINT");
}

void PlayerEffect::EffectProcess(float _DeltaTime)
{
	ResultTarget->Setting();
	EffectUnit.Render();

	GameEngineRenderTarget::RenderTargetReset();
}