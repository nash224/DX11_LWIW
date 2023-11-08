#include "PreCompile.h"
#include "VirgilHat.h"


VirgilHat::VirgilHat() 
{
}

VirgilHat::~VirgilHat() 
{
}



/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////



void VirgilHat::Start()
{
	std::shared_ptr<GameEngineRenderTarget> Target = GameEngineCore::GetCurLevel()->GetMainCamera()->GetCameraAllRenderTarget();

	if (nullptr != Target)
	{
		ResultTarget = Target->CreateChildRenderTarget({ 0 });
	}

	if (nullptr == GameEngineMaterial::Find("VirgilEffect2D"))
	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("VirgilEffect2D");
		Mat->SetVertexShader("VirgilEffect_VS");
		Mat->SetPixelShader("VirgilEffect_PS");
		Mat->SetDepthState("AlwaysDepth");
	}

	EffectUnit.SetMesh("fullrect");
	EffectUnit.SetMaterial("VirgilEffect2D");

	EffectUnit.ShaderResHelper.SetTexture("Texure0", Target->GetTexture(1));
	EffectUnit.ShaderResHelper.SetTexture("Texure1", Target->GetTexture(2));

	EffectUnit.ShaderResHelper.SetSampler("Tex0Sampler", "POINT");
	EffectUnit.ShaderResHelper.SetSampler("Tex1Sampler", "POINT");
}

void VirgilHat::EffectProcess(float _DeltaTime)
{
	ResultTarget->Setting();
	EffectUnit.Render();

	EffectUnit.ShaderResHelper.AllShaderResourcesReset();

	GameEngineRenderTarget::RenderTargetReset();
}
