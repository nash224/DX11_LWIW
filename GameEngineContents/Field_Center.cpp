#include "PreCompile.h"
#include "Field_Center.h"

#include <GameEngineCore/GameEngineCoreWindow.h>

#include "CameraControler.h"
#include "BackDrop_CenterField.h"
#include "Ellie.h"
#include "FadeObject.h"

Field_Center::Field_Center() 
{
	PlayLevel::LocationKRName = "초록숲 평원";
}

Field_Center::~Field_Center() 
{
}

void Field_Center::Start()
{
	FieldLevel::Start();

	Back = CreateActor<BackDrop_CenterField>(EUPDATEORDER::Back);

	if (nullptr != ContentsLevel::LevelCamera)
	{
		ContentsLevel::LevelCamera->SetCameraMode(ECAMERAMODE::Play);
		ContentsLevel::LevelCamera->SetBackDropScale(Back->GetBackGroundScale());
	}

	std::shared_ptr<GameEngineCoreWindow> Window = GameEngineGUI::FindGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow");
	if (nullptr != Window)
	{
		Window->AddDebugRenderTarget(2, "CenterRenderTarget", GetMainCamera()->GetCameraAllRenderTarget());
		Window->AddDebugRenderTarget(4, "CenterPixelTarget", GetCamera(static_cast<int>(ECAMERAORDER::MainPrev))->GetCameraAllRenderTarget());
	}
}

void Field_Center::Update(float _Delta)
{
	FieldLevel::Update(_Delta);
}

void Field_Center::LevelStart(class GameEngineLevel* _NextLevel)
{
	FieldLevel::LevelStart(_NextLevel);

	SetPlayerPosAndFade(_NextLevel);
	CameraSetting();
}


void Field_Center::SetPlayerPosAndFade(class GameEngineLevel* _NextLevel)
{
	if (nullptr == PlayLevel::Player)
	{
		MsgBoxAssert("레벨에 플레이어가 존재하지 않습니다.");
		return;
	}

	if (_NextLevel->GetName() == "WitchHouse_Yard")
	{
		PlayLevel::Player->Transform.SetLocalPosition(float4(1430.0f, -50.0f));
		PlayLevel::Player->SetAnimationByDirection(EDIRECTION::DOWN);

		std::shared_ptr<FadeObject> Fade = CreateActor<FadeObject>(EUPDATEORDER::Fade);
		Fade->CallFadeIn(0.2f);
	}
	else
	{
		PlayLevel::Player->Transform.SetLocalPosition(float4(1430.0f, -50.0f));
		PlayLevel::Player->SetAnimationByDirection(EDIRECTION::DOWN);

		std::shared_ptr<FadeObject> Fade = CreateActor<FadeObject>(EUPDATEORDER::Fade);
		Fade->CallFadeIn(1.0f);
	}

	
}

void Field_Center::CameraSetting()
{
	if (nullptr != ContentsLevel::LevelCamera)
	{
		if (nullptr == Player)
		{
			MsgBoxAssert("플레이어가 존재하지 않습니다.");
			return;
		}

		ContentsLevel::LevelCamera->SetFocusActor(PlayLevel::Player.get());
		ContentsLevel::LevelCamera->SetAutoInitialPosition(PlayLevel::Player->Transform.GetWorldPosition());
	}
}