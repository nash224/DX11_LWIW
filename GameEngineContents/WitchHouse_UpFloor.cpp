#include "PreCompile.h"
#include "WitchHouse_UpFloor.h"

#include <GameEngineCore/GameEngineCoreWindow.h>

#include "BackDrop_WitchHouse_UpFloor.h"
#include "BGMManager.h"
#include "CameraControler.h"
#include "Ellie.h"
#include "FadeObject.h"
#include "HouseSkyLerp.h"


WitchHouse_UpFloor::WitchHouse_UpFloor()
{
	float4 Position = GlobalValue::GetWindowScale().Half();
	Position.Y *= -1.0f;
	Position.Z = CAMERA_DEPTH;
	CreateCamera(INT_MIN, ECAMERAORDER::MainNext)->Transform.SetLocalPosition(Position);
}

WitchHouse_UpFloor::~WitchHouse_UpFloor()
{
}


void WitchHouse_UpFloor::Start()
{
	PlayLevel::Start();

	Back = CreateActor<BackDrop_WitchHouse_UpFloor>(EUPDATEORDER::Back);
	SkyPtr = CreateActor<HouseSkyLerp>(EUPDATEORDER::Sky);

	if (nullptr != ContentsLevel::LevelCamera)
	{
		float4 SettingPos = GlobalValue::GetWindowScale().Half();
		SettingPos.Y *= -1.0f;

		ContentsLevel::LevelCamera->SetCameraMode(ECAMERAMODE::Fix);
		ContentsLevel::LevelCamera->SetLocalPostion(SettingPos);
	}


	std::shared_ptr<GameEngineCoreWindow> Window = GameEngineGUI::FindGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow");
	if (nullptr != Window)
	{
		Window->AddDebugRenderTarget(5, "HouseTarget", GetMainCamera()->GetCameraAllRenderTarget());
	}
}

void WitchHouse_UpFloor::Update(float _Delta)
{
	PlayLevel::Update(_Delta);

	AutoPlayBGM();
}

void WitchHouse_UpFloor::LevelStart(class GameEngineLevel* _NextLevel)
{
	PlayLevel::LevelStart(_NextLevel);

	SetPlayerPosAndFade(_NextLevel);
}

void WitchHouse_UpFloor::SetPlayerPosAndFade(class GameEngineLevel* _NextLevel)
{
	if (nullptr == PlayLevel::Player)
	{
		return;
	}

	float4 SpawnPosition;
	if (_NextLevel->GetName() == "WitchHouse_Yard")
	{
		PlayLevel::Player->SetAnimationByDirection(EDIRECTION::UP);
		PlayLevel::Player->Transform.SetLocalPosition(float4(465.0f, -353.0f));

		std::shared_ptr<FadeObject> Fade = CreateActor<FadeObject>(EUPDATEORDER::Fade);
		Fade->CallFadeIn(0.2f);
	}

	if (_NextLevel->GetName() == "DreamLevel")
	{
		PlayLevel::Player->SetAnimationByDirection(EDIRECTION::DOWN);
		PlayLevel::Player->Transform.SetLocalPosition(float4(440.0f, -271.0f));

		std::shared_ptr<FadeObject> Fade = CreateActor<FadeObject>(EUPDATEORDER::Fade);
		Fade->CallFadeIn(1.0f);
	}
}


void WitchHouse_UpFloor::AutoPlayBGM()
{
	if (nullptr != ContentsLevel::MainPlaySound)
	{
		const int bgmType = MainPlaySound->GetPlayType();
		if (static_cast<int>(EPLAYBGMTYPE::House) != bgmType)
		{
			ContentsLevel::MainPlaySound->NoneBGM();
		}
	}
}