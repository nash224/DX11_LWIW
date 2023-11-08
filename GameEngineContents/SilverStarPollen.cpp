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
	DynamicEntity::Start();
}

void SilverStarPollen::Update(float _Delta)
{
	DynamicEntity::Update(_Delta);

	UpdateState(_Delta);
}

void SilverStarPollen::Release()
{
	DynamicEntity::Release();
}

void SilverStarPollen::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void SilverStarPollen::Init()
{
	ApplyDepth(Transform.GetLocalPosition());
	RendererSetting();
}

void SilverStarPollen::RendererSetting()
{
	if (nullptr != GameEngineSprite::Find("SilverStarFlower_particle_Light.png"))
	{
		GameEngineSprite::CreateCut("SilverStarFlower_particle_Light.png", 4, 1);
		GameEngineSprite::CreateCut("SilverStarFlower_particle.png", 4, 1);
	}

	static constexpr const int RenderOrder = 0;

	m_Body = CreateComponent<GameEngineSpriteRenderer>(RenderOrder);
	m_Body->AutoSpriteSizeOn();
	m_Body->Transform.SetLocalPosition(float4(0.0f, RenderYCorrection));
	m_Body->CreateAnimation("Move", "SilverStarFlower_particle.png");
	m_Body->ChangeAnimation("Move");
	m_Body->RenderBaseInfoValue.Target3 = 1;
}


void SilverStarPollen::UpdateState(float _Delta)
{
	if (true == IsEnalbeActive)
	{
		if (nullptr != UI_Inventory::MainInventory)
		{
			UI_Inventory::MainInventory->PushItem("SilverStarFlower_Collect");
		}
	}

	UpdateMovement(_Delta);
}

void SilverStarPollen::UpdateMovement(float _Delta)
{

}