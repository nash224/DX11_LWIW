#include "PreCompile.h"
#include "RidingFx.h"

#include "BackDrop_PlayLevel.h"

RidingFx::RidingFx() 
{
}

RidingFx::~RidingFx() 
{
}


void RidingFx::Start()
{
}

void RidingFx::Release()
{
	FxRenderer = nullptr;
}

void RidingFx::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void RidingFx::Init(const float4& _ParentPosition)
{
	if (nullptr == GameEngineSprite::Find("Broom_Ride_Fx_Sample.png"))
	{
		GameEngineSprite::CreateSingle("Broom_Ride_Fx_Sample.png");
	}

	static std::uint32_t FxGroupOrder = 0;
	float4 FxPosition = _ParentPosition;
	FxPosition.Y += 30.0f;
	FxPosition.Z -= 1.0f;

	FxRenderer = CreateComponent<GameEngineSpriteRenderer>(FxGroupOrder);
	FxRenderer->Transform.SetLocalPosition(FxPosition);
	FxRenderer->AutoSpriteSizeOn();
	FxRenderer->CreateAnimation("FX", "Broom_Ride_Fx_Sample.png", 0.08f, 0, 8, false);
	FxRenderer->ChangeAnimation("FX");
	FxRenderer->SetEndEvent("FX", [&](GameEngineSpriteRenderer* _Renderer)
		{
			Death();
		});
}
