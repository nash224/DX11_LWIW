#include "PreCompile.h"
#include "WitchHouse_Yard.h"

#include "CameraControler.h"

#include "BackDrop_WitchHouse_Yard.h"
#include "Ellie.h"
#include "FadeObject.h"

WitchHouse_Yard::WitchHouse_Yard() 
{
	PlayLevel::LocationKRName = "마녀의 정원";
}

WitchHouse_Yard::~WitchHouse_Yard() 
{
}


void WitchHouse_Yard::Start()
{
	FieldLevel::Start();

	Back = CreateActor<BackDrop_WitchHouse_Yard>(EUPDATEORDER::Objects);

	if (nullptr != ContentsLevel::LevelCamera)
	{
		float4 SettingPos = GlobalValue::GetWindowScale().Half();
		SettingPos.Y *= -1.0f;

		ContentsLevel::LevelCamera->SetCameraMode(ECAMERAMODE::Fix);
		ContentsLevel::LevelCamera->SetLocalPostion(SettingPos);
	}
}

void WitchHouse_Yard::Update(float _Delta)
{
	FieldLevel::Update(_Delta);
}

void WitchHouse_Yard::LevelStart(class GameEngineLevel* _NextLevel)
{
	FieldLevel::LevelStart(_NextLevel);
	SetPlayerPositionAndFade(_NextLevel);
}

void WitchHouse_Yard::LevelEnd(class GameEngineLevel* _NextLevel)
{
	FieldLevel::LevelEnd(_NextLevel);
}



void WitchHouse_Yard::SetPlayerPositionAndFade(class GameEngineLevel* _NextLevel)
{
	if (nullptr == PlayLevel::Player)
	{
		MsgBoxAssert("앨리를 생성하지 않았습니다.");
		return;
	}

	if (nullptr == _NextLevel)
	{
		PlayLevel::Player->Transform.SetLocalPosition(float4(GlobalValue::GetWindowScale().hX(), -450.0f));

		std::shared_ptr<FadeObject> Fade = CreateActor<FadeObject>(EUPDATEORDER::Fade);
		Fade->CallFadeIn(1.0f);
	}
	else if (_NextLevel->GetName() == "Field_Center")
	{
		PlayLevel::Player->Transform.SetLocalPosition(float4(480.0f, -461.0f));
		PlayLevel::Player->SetAnimationByDirection(EDIRECTION::UP);

		std::shared_ptr<FadeObject> Fade = CreateActor<FadeObject>(EUPDATEORDER::Fade);
		Fade->CallFadeIn(0.2f);
	}
	else if (_NextLevel->GetName() == "WitchHouse_UpFloor")
	{
		PlayLevel::Player->Transform.SetLocalPosition(float4(485.0f, -337.0f));
		PlayLevel::Player->SetAnimationByDirection(EDIRECTION::DOWN);

		std::shared_ptr<FadeObject> Fade = CreateActor<FadeObject>(EUPDATEORDER::Fade);
		Fade->CallFadeIn(0.2f);
	}
	else 
	{
		PlayLevel::Player->Transform.SetLocalPosition(float4(GlobalValue::GetWindowScale().hX(), -450.0f));

		std::shared_ptr<FadeObject> Fade = CreateActor<FadeObject>(EUPDATEORDER::Fade);
		Fade->CallFadeIn(1.0f);
	}
}