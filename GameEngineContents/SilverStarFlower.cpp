#include "PreCompile.h"
#include "SilverStarFlower.h"


#include "PlayLevel.h"
#include "TimeManager.h"

#include "Ellie.h"

SilverStarFlower::SilverStarFlower() 
{
}

SilverStarFlower::~SilverStarFlower() 
{
}


void SilverStarFlower::Start()
{
	CreateAndSetCollision(ECOLLISION::Entity, { 60.0f }, float4::ZERO, ColType::SPHERE2D);
	SetInteractionOption(EINTERACTION_BUTTONTYPE::Gathering, EINTERACTION_TYPE::Far, ECOLLECTION_METHOD::None, ETOOLTYPE::Nothing);
}

void SilverStarFlower::Update(float _Delta)
{
	StaticEntity::Update(_Delta);
}

void SilverStarFlower::Release()
{
	StaticEntity::Release();

	m_Plant = nullptr;
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

	m_Plant = CreateComponent<GameEngineSpriteRenderer>(RenderOrder);
	m_Plant->CreateAnimation("Idle", "SilverStarFlower.png", 0.15f, 3, 3, false);
	m_Plant->CreateAnimation("Touch", "SilverStarFlower.png", 0.15f, 4, 9, false);
	m_Plant->AutoSpriteSizeOn();
	m_Plant->Transform.SetLocalPosition({ 0.0f, RendererYCorrection });
	m_Plant->ChangeAnimation("Idle");


	m_Shadow = CreateComponent<GameEngineSpriteRenderer>(RenderOrder);
	m_Shadow->Transform.SetLocalPosition({ 0.0f, RendererYCorrection });
	m_Shadow->SetSprite("SilverStarFlower.png", 1);
}

void SilverStarFlower::LightSetting()
{

}

void SilverStarFlower::StateSetting()
{
	CreateStateParameter DayState;
	DayState.Stay = std::bind(&SilverStarFlower::DayUpdate, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(ESILVERBELLSTATE::Day, DayState);

	CreateStateParameter LightState;
	LightState. Start = std::bind(&SilverStarFlower::LightStart, this, std::placeholders::_1);
	LightState.Stay = std::bind(&SilverStarFlower::LightUpdate, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(ESILVERBELLSTATE::Light, LightState);

	CreateStateParameter TouchState;
	TouchState.Start = std::bind(&SilverStarFlower::TouchStart, this, std::placeholders::_1);
	State.CreateState(ESILVERBELLSTATE::Touch, TouchState);

	State.ChangeState(ESILVERBELLSTATE::Day);
}

void SilverStarFlower::LightStart(GameEngineState* _Parent)
{
	
}

void SilverStarFlower::TouchStart(GameEngineState* _Parent)
{
	// SFX
	/*GetLevel()->CreateActor<>(EUPDATEORDER::Entity);*/
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
		float4 ElliePos = Ellie::MainEllie->Transform.GetLocalPosition();
		float4 MyPos = Transform.GetLocalPosition();
		MyPos.Y += RendererYCorrection * 0.5f;
		float4 Distance = MyPos - ElliePos;

		Distance = DirectX::XMVector2Length(Distance.DirectXVector);
		bool isEllieTouch = (Distance.X < RecognitionRange);
		if (isEllieTouch)
		{
			State.ChangeState(ESILVERBELLSTATE::Touch);
			return;
		}

		bool isNetTouch = (Distance.X < NetRecognitionRange);
		if (isNetTouch)
		{
			State.ChangeState(ESILVERBELLSTATE::Touch);
			return;
		}
	}
}