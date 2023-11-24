#include "PreCompile.h"
#include "DustFx.h"

DustFx::DustFx() 
{
}

DustFx::~DustFx() 
{
}

void DustFx::Release()
{
	DustRenderer = nullptr;
}

void DustFx::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void DustFx::Init(const float4& _ParentPosition, float DustScaleRatio)
{
	if (nullptr == GameEngineSprite::Find("dust_remove.png"))
	{
		GameEngineSprite::CreateCut("dust_remove.png", 22, 1);
	}

	static std::uint32_t FxGroupOrder = 0;
	float4 FxPosition = _ParentPosition;
	FxPosition.Z -= 3.0f;

	DustRenderer = CreateComponent<GameEngineSpriteRenderer>(FxGroupOrder);
	DustRenderer->Transform.SetLocalPosition(FxPosition);
	DustRenderer->AutoSpriteSizeOn();
	DustRenderer->SetAutoScaleRatio(DustScaleRatio);
	DustRenderer->CreateAnimation("FX", "dust_remove.png", 0.06f);
	DustRenderer->ChangeAnimation("FX");
	DustRenderer->SetEndEvent("FX", [&](GameEngineSpriteRenderer* _Renderer)
		{
			Death();
		});
}
