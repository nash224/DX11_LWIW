#include "PreCompile.h"
#include "SilverStarFlower.h"

#include "PlayLevel.h"
#include "TimeManager.h"

#include "Ellie.h"
#include "SilverBellSpawner.h"
#include "UI_Inventory.h"

static constexpr const float RendererYCorrection = 36.0f;
static constexpr const float Light_Off_Time = 0.6f;


SilverStarFlower::SilverStarFlower() 
{
	if (nullptr == GameEngineSound::FindSound("SFX_SliverStarFlower_Ring.wav"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Sound\\Actor\\SliverStarFlower");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pfile : Files)
		{
			GameEngineSound::SoundLoad(pfile.GetStringPath());
		}
	}
}

SilverStarFlower::~SilverStarFlower() 
{
}


void SilverStarFlower::Start()
{
	CreateAndSetCollision(ECOLLISION::Entity, { 20.0f }, float4(0.0f, RendererYCorrection * 0.5f), ColType::SPHERE2D);
	SetInteractionOption(EINTERACTION_BUTTONTYPE::Gathering, EINTERACTION_TYPE::Far, ECOLLECTION_METHOD::None, ETOOLTYPE::Dragonfly);
	if (nullptr != InteractiveCol)
	{
		InteractiveCol->Off();
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

	ShadowRenderer = nullptr;
	UpperALight.Release();
	LowerALight.Release();
}

void SilverStarFlower::Init()
{
	ApplyDepth();
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

	InteractiveActor::BodyRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder);
	InteractiveActor::BodyRenderer->CreateAnimation("Idle", "SilverStarFlower.png", 0.15f, 3, 3, false);
	InteractiveActor::BodyRenderer->CreateAnimation("Touch", "SilverStarFlower.png", 0.15f, 4, 9, false);
	InteractiveActor::BodyRenderer->AutoSpriteSizeOn();
	InteractiveActor::BodyRenderer->Transform.SetLocalPosition({ 0.0f, RendererYCorrection });
	InteractiveActor::BodyRenderer->ChangeAnimation("Idle");


	ShadowRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder);
	ShadowRenderer->Transform.SetLocalPosition({ 0.0f, RendererYCorrection });
	ShadowRenderer->SetSprite("SilverStarFlower.png", 1);
	
}

void SilverStarFlower::LightSetting()
{
	static constexpr const int RenderOrder = 0;

	const float4& LightColor = float4(0.0f, 0.1f, 0.2f, 0.8f);

	UpperALight.Init(this, { LightColor , "Default_Particle.png" , float4(60.0f, 60.0f) ,float4(-10.0f, 30.0f, -0.01f) });
	LowerALight.Init(this, { LightColor , "Default_Particle.png" , float4(30.0f, 30.0f) ,float4(-4.0f, 14.0f, -0.01f) });
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
	if (nullptr != InteractiveCol)
	{
		InteractiveCol->On();
	}

	CreatePollenSpawner();
	SFXFunction::PlaySFX("SFX_SliverStarFlower_Ring.wav");
}

void SilverStarFlower::UnLightStart(GameEngineState* _Parent)
{
	if (nullptr != InteractiveCol)
	{
		InteractiveCol->Off();
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
	const float RecognitionRange = 20.0f;
	const float Net_RecognitionRange = 50.0f;

	const float Distance = CalculateDistanceToEllie();
	bool isEllieTouch = (Distance < RecognitionRange);
	if (isEllieTouch)
	{
		State.ChangeState(ESILVERBELLSTATE::Touch);
		return;
	}

	bool isNetTouch = (Distance < Net_RecognitionRange);
	if (isNetTouch && EELLIE_STATE::ButterflyNet == PlayLevel::GetPlayLevelPtr()->GetPlayerPtr()->GetState())
	{
		State.ChangeState(ESILVERBELLSTATE::Touch);
		return;
	}

	UpperALight.UpdateLightLerp();
	LowerALight.UpdateLightLerp();
}

void SilverStarFlower::TouchUpdate(float _Delta, GameEngineState* _Parent)
{
	static constexpr const float Limit_Collectable_Time = 2.0f;

	if (true == IsEnalbeActive)
	{
		UI_Inventory::PushItem("SilverStarFlower_Collect");

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
	const float4 ElliePos = PlayLevel::GetPlayLevelPtr()->GetPlayerPtr()->Transform.GetLocalPosition();
	float4 MyPos = Transform.GetLocalPosition();
	MyPos.Y += RendererYCorrection * 0.5f;
	float4 Distance = MyPos - ElliePos;

	Distance = DirectX::XMVector2Length(Distance.DirectXVector);
	return Distance.X;
}

void SilverStarFlower::UpdateFlowerLostLight(GameEngineState* _Parent)
{
	const float LightAlpha = 1.0f - _Parent->GetStateTime() / Light_Off_Time;
	if (LightAlpha < 0.1f)
	{
		UpperALight.Off();
		LowerALight.Off();
		return;
	}

	UpperALight.SetLightAlpha(LightAlpha);
	LowerALight.SetLightAlpha(LightAlpha);

	UpperALight.UpdateLightLerp();
	LowerALight.UpdateLightLerp();
}

void SilverStarFlower::CreatePollenSpawner()
{
	std::shared_ptr<SilverBellSpawner> PollenSpawner = GetLevel()->CreateActor<SilverBellSpawner>(EUPDATEORDER::Objects);
	PollenSpawner->Transform.SetLocalPosition(Transform.GetLocalPosition());
}