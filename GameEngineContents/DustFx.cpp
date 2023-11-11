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


void DustFx::Init(const float4& _ParentPosition)
{
	if (nullptr == GameEngineSprite::Find("dust_remove.png"))
	{
		GameEngineSprite::CreateCut("dust_remove.png", 22, 1);
	}

	static std::uint32_t FxGroupOrder = 0;
	float4 FxPosition = _ParentPosition;
	FxPosition.Z -= 1.0f;

	DustRenderer = CreateComponent<GameEngineSpriteRenderer>(FxGroupOrder);
	DustRenderer->Transform.SetLocalPosition(FxPosition);
	DustRenderer->AutoSpriteSizeOn();
	DustRenderer->CreateAnimation("FX", "Broom_Ride_Fx_Sample.png", 0.12f);
	DustRenderer->ChangeAnimation("FX");
	DustRenderer->SetEndEvent("FX", [&](GameEngineSpriteRenderer* _Renderer)
		{
			Death();
		});
}
