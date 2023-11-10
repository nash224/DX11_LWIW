#include "PreCompile.h"
#include "SilverStarFlower.h"


#include "PlayLevel.h"
#include "TimeManager.h"

#include "Ellie.h"
#include "SilverBellSpawner.h"
#include "UI_Inventory.h"

SilverStarFlower::SilverStarFlower() 
{
}

SilverStarFlower::~SilverStarFlower() 
{
}


void SilverStarFlower::Start()
{
	CreateAndSetCollision(ECOLLISION::Entity, { 20.0f }, float4(0.0f, RendererYCorrection * 0.5f), ColType::SPHERE2D);
	SetInteractionOption(EINTERACTION_BUTTONTYPE::Gathering, EINTERACTION_TYPE::Far, ECOLLECTION_METHOD::None, ETOOLTYPE::Dragonfly);
	if (nullptr != m_InteractiveCol)
	{
		m_InteractiveCol->Off();
	}
}

void SilverStarFlower::Update(float _Delta)
{
	StaticEntity::Update(_Delta);

	State.Update(_Delta);
}

void SilverStarFlower::Release()
{
	StaticEntity::Release();

	m_Shadow = nullptr;
	UpperALight.LightRenderer = nullptr;
	LowerALight.LightRenderer = nullptr;
}

void SilverStarFlower::LevelEnd(class GameEngineLevel* _NextLevel)
{
		
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void SilverStarFlower::Init()
{
	ApplyDepth(Transform.GetLocalPosition());
	RendererSetting();
	LightSetting();
	StateSetting();
}

void SilverStarFlower::RendererSetting()
{
	if (nullptr == GameEngineSprite::Find("SilverStarFlower.png"))
	{
		GameEngineSprite::CreateCut("SilverStarFlower.png", 4, 3);
	}

	static constexpr const int RenderOrder = 0;

	m_Body = CreateComponent<GameEngineSpriteRenderer>(RenderOrder);
	m_Body->CreateAnimation("Idle", "SilverStarFlower.png", 0.15f, 3, 3, false);
	m_Body->CreateAnimation("Touch", "SilverStarFlower.png", 0.15f, 4, 9, false);
	m_Body->AutoSpriteSizeOn();
	m_Body->Transform.SetLocalPosition({ 0.0f, RendererYCorrection });
	m_Body->ChangeAnimation("Idle");


	m_Shadow = CreateComponent<GameEngineSpriteRenderer>(RenderOrder);
	m_Shadow->Transform.SetLocalPosition({ 0.0f, RendererYCorrection });
	m_Shadow->SetSprite("SilverStarFlower.png", 1);
	
}

void SilverStarFlower::LightSetting()
{
	static constexpr const int RenderOrder = 0;

	const float4& LightColor = float4(0.0f, 0.1f, 0.2f, 0.8f);

	UpperALight.LightRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder);
	UpperALight.SetLightRendererSetting(LightColor);
	UpperALight.LightRenderer->SetSprite("Default_Particle.png");
	UpperALight.LightRenderer->GetImageTransform().SetLocalScale(float4(60.0f, 60.0f));
	UpperALight.LightRenderer->Transform.AddLocalPosition(float4(-10.0f, 30.0f));


	LowerALight.LightRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder);
	LowerALight.SetLightRendererSetting(LightColor);
	LowerALight.LightRenderer->SetSprite("Default_Particle.png");
	LowerALight.LightRenderer->GetImageTransform().SetLocalScale(float4(30.0f, 30.0f));
	LowerALight.LightRenderer->Transform.AddLocalPosition(float4(-4.0f, 14.0f));
}

void SilverStarFlower::StateSetting()
{
	CreateStateParameter DayState;
	DayState.Stay = std::bind(&SilverStarFlower::DayUpdate, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(ESILVERBELLSTATE::Day, DayState);

	CreateStateParameter LightState;
	LightState.Stay = std::bind(&SilverStarFlower::LightUpdate, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(ESILVERBELLSTATE::Light, LightState);

	CreateStateParameter TouchState;
	TouchState.Start = std::bind(&SilverStarFlower::TouchStart, this, std::placeholders::_1);
	TouchState.Stay = std::bind(&SilverStarFlower::TouchUpdate, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(ESILVERBELLSTATE::Touch, TouchState);

	CreateStateParameter UnLightState;
	UnLightState.Start = std::bind(&SilverStarFlower::UnLightStart, this, std::placeholders::_1);
	State.CreateState(ESILVERBELLSTATE::UnLight, UnLightState);

	State.ChangeState(ESILVERBELLSTATE::Day);
}

void SilverStarFlower::TouchStart(GameEngineState* _Parent)
{
	if (nullptr != m_InteractiveCol)
	{
		m_InteractiveCol->On();
	}

	CreatePollenSpawner();
	// SFX
}

void SilverStarFlower::UnLightStart(GameEngineState* _Parent)
{
	if (nullptr != m_InteractiveCol)
	{
		m_InteractiveCol->Off();
	}
}


void SilverStarFlower::DayUpdate(float _Delta, GameEngineState* _Parent)
{
	if (nullptr != PlayLevel::s_TimeManager)
	{
		if (EDAYSTATE::Night == PlayLevel::s_TimeManager->GetDayState())
		{
			State.ChangeState(ESILVERBELLSTATE::Light);
		}
	}
}

void SilverStarFlower::LightUpdate(float _Delta, GameEngineState* _Parent)
{
	if (nullptr != Ellie::MainEllie)
	{
		float Distance = CalculateDistanceToEllie();
		bool isEllieTouch = (Distance < RecognitionRange);
		if (isEllieTouch)
		{
			State.ChangeState(ESILVERBELLSTATE::Touch);
			return;
		}

		bool isNetTouch = (Distance < NetRecognitionRange);
		if (isNetTouch)
		{
			State.ChangeState(ESILVERBELLSTATE::Touch);
			return;
		}
	}

	UpperALight.UpdateLightLerp();
	LowerALight.UpdateLightLerp();
}

void SilverStarFlower::TouchUpdate(float _Delta, GameEngineState* _Parent)
{
	if (true == IsEnalbeActive)
	{
		if (nullptr != UI_Inventory::MainInventory)
		{
			UI_Inventory::MainInventory->PushItem("SilverStarFlower_Collect");
		}

		State.ChangeState(ESILVERBELLSTATE::UnLight);
		return;
	}

	float AccTime = _Parent->GetStateTime();
	if (AccTime > Limit_Collectable_Time)
	{
		State.ChangeState(ESILVERBELLSTATE::UnLight);
		return;
	}

	if (AccTime < Light_Off_Time)
	{
		UpdateFlowerLostLight(_Parent);
	}
}

float SilverStarFlower::CalculateDistanceToEllie()
{
	const float4& ElliePos = Ellie::MainEllie->Transform.GetLocalPosition();
	float4 MyPos = Transform.GetLocalPosition();
	MyPos.Y += RendererYCorrection * 0.5f;
	float4 Distance = MyPos - ElliePos;

	Distance = DirectX::XMVector2Length(Distance.DirectXVector);
	return Distance.X;
}

void SilverStarFlower::UpdateFlowerLostLight(GameEngineState* _Parent)
{
	float PlusLightAlpha = 1.0f - _Parent->GetStateTime() / Light_Off_Time;
	if (PlusLightAlpha < 0.1f)
	{
		UpperALight.LightRenderer->Off();
		LowerALight.LightRenderer->Off();
		return;
	}

	UpperALight.SetPlusAlpha(PlusLightAlpha);
	LowerALight.SetPlusAlpha(PlusLightAlpha);

	UpperALight.UpdateLightLerp();
	LowerALight.UpdateLightLerp();
}

void SilverStarFlower::CreatePollenSpawner()
{
	std::shared_ptr<SilverBellSpawner> PollenSpawner = GetLevel()->CreateActor<SilverBellSpawner>(EUPDATEORDER::Objects);
	PollenSpawner->Transform.SetLocalPosition(Transform.GetLocalPosition());
}