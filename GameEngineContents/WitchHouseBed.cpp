#include "PreCompile.h"
#include "WitchHouseBed.h"

#include "PlayLevel.h"
#include "TimeManager.h"

#include "BedUI.h"

WitchHouseBed::WitchHouseBed() 
{
}

WitchHouseBed::~WitchHouseBed() 
{
}


void WitchHouseBed::Start()
{
	InteractiveActor::CreateAndSetCollision(ECOLLISION::Entity, float4(160.0f, 120.0f), float4::ZERO, ColType::AABBBOX2D);
	InteractiveActor::SetInteractionOption(EINTERACTION_BUTTONTYPE::Gear, EINTERACTION_TYPE::Far, ECOLLECTION_METHOD::None, ETOOLTYPE::Nothing);
	InteractiveActor::SetGearName("잠자기");

	StateSetting();
	UISetting();
}

void WitchHouseBed::Update(float _Delta)
{
	InteractiveActor::Update(_Delta);

	State.Update(_Delta);
}

void WitchHouseBed::Release()
{
	InteractiveActor::Release();
}

void WitchHouseBed::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


void WitchHouseBed::UISetting()
{
	BedUIActor = GetLevel()->CreateActor<BedUI>(EUPDATEORDER::UIComponent);
	BedUIActor.lock()->Init();
}

void WitchHouseBed::StateSetting()
{
	CreateStateParameter NotActiveState;
	NotActiveState.Start = std::bind(&WitchHouseBed::StartNotActive, this, std::placeholders::_1);
	NotActiveState.Stay = std::bind(&WitchHouseBed::UpdateNotActive, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EBEDSTATE::NotActive, NotActiveState);

	CreateStateParameter ActiveState;
	ActiveState.Start = std::bind(&WitchHouseBed::StartActive, this, std::placeholders::_1);
	ActiveState.Stay = std::bind(&WitchHouseBed::UpdateActive, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EBEDSTATE::Active, ActiveState);

	const unsigned int CurHour = PlayLevel::GetTimeManager()->GetHour();
	if (CurHour >= Bed_Active_Hour)
	{
		State.ChangeState(EBEDSTATE::Active);
	}
	else
	{
		State.ChangeState(EBEDSTATE::NotActive);
	}
}

void WitchHouseBed::StartNotActive(GameEngineState* _Parent)
{
	if (nullptr == InteractiveActor::InteractiveCol)
	{
		MsgBoxAssert("존재하지 않는 충돌체입니다.");
		return;
	}

	InteractiveActor::InteractiveCol->Off();
}

void WitchHouseBed::StartActive(GameEngineState* _Parent)
{
	if (nullptr == InteractiveActor::InteractiveCol)
	{
		MsgBoxAssert("존재하지 않는 충돌체입니다.");
		return;
	}
	
	InteractiveActor::InteractiveCol->On();
}


void WitchHouseBed::UpdateNotActive(float _Delta, GameEngineState* _Parent)
{
	const unsigned int CurHour = PlayLevel::GetTimeManager()->GetHour();
	if (CurHour >= Bed_Active_Hour)
	{
		State.ChangeState(EBEDSTATE::Active);
		return;
	}
}

void WitchHouseBed::UpdateActive(float _Delta, GameEngineState* _Parent)
{
	if (true == InteractiveActor::IsEnalbeActive)
	{
		if (true == BedUIActor.expired())
		{
			MsgBoxAssert("포인터가 존재하지 않습니다.");
			return;
		}

		BedUIActor.lock()->Open();
	}
}