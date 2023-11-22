#include "PreCompile.h"
#include "WitchHouse_Yard.h"

#include <GameEngineCore/GameEngineCoreWindow.h>

#include "CameraControler.h"
#include "TimeManager.h"
#include "SkyLerp.h"

#include "BackDrop_WitchHouse_Yard.h"
#include "Ellie.h"
#include "UI_Alert_Enter.h"
#include "UI_Alert_Quest.h"



WitchHouse_Yard::WitchHouse_Yard() 
{
}

WitchHouse_Yard::~WitchHouse_Yard() 
{
}


void WitchHouse_Yard::Start()
{
	FieldLevel::Start();

	if (nullptr != LevelCamera)
	{
		LevelCamera->SetCameraMode(ECAMERAMODE::Fix);
	}

	SetLocationName("마녀의 정원");
}

void WitchHouse_Yard::Update(float _Delta)
{
	FieldLevel::Update(_Delta);
}

void WitchHouse_Yard::LevelStart(class GameEngineLevel* _NextLevel)
{
	FieldLevel::LevelStart(_NextLevel);

	LoadTexture();
	LoadActor();

	SetElliePosToEnter(_NextLevel);

	CameraSetting();
}

void WitchHouse_Yard::LevelEnd(class GameEngineLevel* _NextLevel)
{
	FieldLevel::LevelEnd(_NextLevel);

	ReleaseTexture();
}



void WitchHouse_Yard::LoadTexture()
{
	std::vector<GameEngineDirectory> Dirs = FileLoadFunction::GetAllDirInPath("Resources\\PlayContents\\WitchHouse_Yard");
	for (GameEngineDirectory& Dir : Dirs)
	{
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pFile : Files)
		{
			GameEngineTexture::Load(pFile.GetStringPath());
		}
	}
}


void WitchHouse_Yard::LoadActor()
{
	if (nullptr == m_BackDrop)
	{
		m_BackDrop = CreateActor<BackDrop_WitchHouse_Yard>(EUPDATEORDER::Objects);
	}
}

void WitchHouse_Yard::SetElliePosToEnter(class GameEngineLevel* _NextLevel)
{
	if (nullptr == Player)
	{
		MsgBoxAssert("앨리를 생성하지 않았습니다.");
		return;
	}

	const float4& HWinScale = GlobalValue::GetWindowScale().Half();
	float4 SpawnPosition = float4::ZERO;

	if (nullptr == _NextLevel)
	{
		SpawnPosition = { HWinScale.X , -450.0f };
	}
	else if (_NextLevel->GetName() == "Field_Center")
	{
		SpawnPosition = { 480.0f , -461.0f };
		Player->SetAnimationByDirection(EDIRECTION::UP);
	}
	else if (_NextLevel->GetName() == "WitchHouse_UpFloor")
	{
		SpawnPosition = { 485.0f , -337.0f };
		Player->SetAnimationByDirection(EDIRECTION::DOWN);
	}
	else 
	{
		SpawnPosition = { HWinScale.X , -450.0f };
	}

	Player->Transform.SetLocalPosition(SpawnPosition);
}

void WitchHouse_Yard::CameraSetting()
{
	if (nullptr != GlobalValue::g_CameraControler)
	{
		if (GlobalValue::g_CameraControler != LevelCamera)
		{
			MsgBoxAssert("현재 카메라 매니저가 아닙니다.");
			return;
		}

		float4 HWinScale = GlobalValue::GetWindowScale().Half();
		HWinScale.Y *= -1.0f;

		GlobalValue::g_CameraControler->SetLocalPostion(HWinScale);
	}
}

void WitchHouse_Yard::ReleaseTexture()
{
	std::vector<GameEngineDirectory> Dirs = FileLoadFunction::GetAllDirInPath("Resources\\PlayContents\\WitchHouse_Yard");
	for (GameEngineDirectory& Dir : Dirs)
	{
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pFile : Files)
		{
			GameEngineTexture::Release(pFile.GetFileName());
		}
	}
}
