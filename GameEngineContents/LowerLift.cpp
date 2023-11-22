#include "PreCompile.h"
#include "LowerLift.h"

#include "FadeObject.h"

#include "Ellie.h"

LowerLift::LowerLift() 
{
}

LowerLift::~LowerLift() 
{
}


void LowerLift::Start()
{
	InteractiveActor::CreateAndSetCollision(ECOLLISION::Entity, float4{ 64.0f , 88.0f }, float4(0.0f, 22.0f), ColType::AABBBOX2D);
	InteractiveActor::SetInteractionOption(EINTERACTION_BUTTONTYPE::Gear, EINTERACTION_TYPE::Far, ECOLLECTION_METHOD::None, ETOOLTYPE::Nothing);
}

void LowerLift::Update(float _Delta)
{
	StaticEntity::Update(_Delta);

	UpdateLift(_Delta);
}

void LowerLift::Release()
{
	StaticEntity::Release();
}

void LowerLift::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void LowerLift::UpdateLift(float _Delta)
{
	if (true == InteractiveActor::IsEnalbeActive)
	{
		if (nullptr != InteractiveActor::InteractiveCol)
		{
			InteractiveActor::InteractiveCol->Off();
		}

		if (nullptr == Ellie::MainEllie)
		{
			MsgBoxAssert("플레이어가 존재하지 않습니다.");
			return;
		}

		Ellie::MainEllie->OffControl();
		

		std::weak_ptr<FadeObject> Fade = GetLevel()->CreateActor<FadeObject>(EUPDATEORDER::Entity);
		Fade.lock()->CallFadeOut("WitchHouse_UpFloor", 1.2f);
	}
}