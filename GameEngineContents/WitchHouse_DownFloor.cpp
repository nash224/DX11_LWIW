#include "PreCompile.h"
#include "WitchHouse_DownFloor.h"

#include "WorkSpaceSkyLerp.h"
#include "BackDrop_WitchHouse_DownFloor.h"
#include "BGMManager.h"
#include "CameraControler.h"
#include "FadeObject.h"

#include "Ellie.h"


WitchHouse_DownFloor::WitchHouse_DownFloor()
{
	float4 Position = GlobalValue::GetWindowScale().Half();
	Position.Y *= -1.0f;
	Position.Z = CAMERA_DEPTH;
	CreateCamera(INT_MIN, ECAMERAORDER::MainNext)->Transform.SetLocalPosition(Position);
}

WitchHouse_DownFloor::~WitchHouse_DownFloor()
{
}


void WitchHouse_DownFloor::Start()
{
	PlayLevel::Start();

	
	Back = CreateActor<BackDrop_WitchHouse_DownFloor>(EUPDATEORDER::Back);

	if (nullptr != ContentsLevel::LevelCamera)
	{
		float4 SettingPos = GlobalValue::GetWindowScale().Half();
		SettingPos.Y *= -1.0f;

		ContentsLevel::LevelCamera->SetCameraMode(ECAMERAMODE::Fix);
		ContentsLevel::LevelCamera->SetLocalPostion(SettingPos);
	}

	SkyPtr = CreateActor<WorkSpaceSkyLerp>(EUPDATEORDER::Sky);
}

void WitchHouse_DownFloor::Update(float _Delta)
{
	PlayLevel::Update(_Delta);

	AutoPlayBGM();
}

void WitchHouse_DownFloor::LevelStart(class GameEngineLevel* _NextLevel)
{
	PlayLevel::LevelStart(_NextLevel);
}

void WitchHouse_DownFloor::LevelEnd(class GameEngineLevel* _NextLevel)
{
	PlayLevel::LevelEnd(_NextLevel);
}


void WitchHouse_DownFloor::AutoPlayBGM()
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