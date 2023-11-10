#include "PreCompile.h"
#include "SilverStarPollen.h"


#include "UI_Inventory.h"

SilverStarPollen::SilverStarPollen() 
{
}

SilverStarPollen::~SilverStarPollen() 
{
}


void SilverStarPollen::Start()
{
}

void SilverStarPollen::Update(float _Delta)
{
	UpdateState(_Delta);
}

void SilverStarPollen::Release()
{
	PollenRenderer = nullptr;
	ParticleRenderer = nullptr;
}

void SilverStarPollen::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void SilverStarPollen::Init()
{
	RendererSetting();
	MoveSetting();
}

void SilverStarPollen::RendererSetting()
{
	if (nullptr == GameEngineSprite::Find("SilverStarFlower_particle_Light.png"))
	{
		GameEngineSprite::CreateCut("SilverStarFlower_particle_Light.png", 4, 1);
		GameEngineSprite::CreateCut("SilverStarFlower_particle.png", 4, 1);
	}

	static constexpr const int RenderOrder = 0;

	PollenRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder);
	PollenRenderer->Transform.AddLocalPosition(float4::BACKWARD);
	PollenRenderer->AutoSpriteSizeOn();
	PollenRenderer->CreateAnimation("Move", "SilverStarFlower_particle.png");
	PollenRenderer->ChangeAnimation("Move");
	PollenRenderer->RenderBaseInfoValue.Target3 = 1;

	ParticleRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder);
	ParticleRenderer->Transform.AddLocalPosition(float4::BACKWARD);
	ParticleRenderer->AutoSpriteSizeOn();
	ParticleRenderer->CreateAnimation("Move", "SilverStarFlower_particle_Light.png");
	ParticleRenderer->ChangeAnimation("Move");
	ParticleRenderer->RenderBaseInfoValue.Target3 = 1;
}

void SilverStarPollen::MoveSetting()
{
	GameEngineRandom RandomClass;
	RandomClass.SetSeed(reinterpret_cast<__int64>(this) + GlobalValue::GetSeedValue());

	MovePower = RandomClass.RandomFloat(0.0f, MovementRadius);
}

void SilverStarPollen::UpdateState(float _Delta)
{
	float AccTime = GetLiveTime();

	
	PollenRenderer->Transform.AddLocalPosition(float4::LEFT * MovePower * _Delta);
	ParticleRenderer->Transform.AddLocalPosition(float4::DOWN * MovePower * _Delta);

	float Scale = 1.0f - AccTime * 0.5f;
	Transform.SetLocalScale(float4(Scale, Scale));
	
	if (AccTime > LiveTime)
	{
		Death();
	}
}