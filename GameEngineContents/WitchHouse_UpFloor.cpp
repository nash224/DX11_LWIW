#include "PreCompile.h"
#include "WitchHouse_UpFloor.h"

#include "BackDrop_WitchHouse_UpFloor.h"
#include "BGMManager.h"
#include "CameraControler.h"

#include "Ellie.h"


WitchHouse_UpFloor::WitchHouse_UpFloor()
{
}

WitchHouse_UpFloor::~WitchHouse_UpFloor()
{
}


void WitchHouse_UpFloor::Start()
{
	PlayLevel::Start();
	LevelType = ELEVELTYPE::House;

	if (nullptr != LevelCamera)
	{
		LevelCamera->SetCameraMode(ECAMERAMODE::Fix);
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

	LoadTexture();
	LoadActor();


	SetEllieLevelChangeLocation(_NextLevel);

	CameraSetting();
}

void WitchHouse_UpFloor::LevelEnd(class GameEngineLevel* _NextLevel)
{
	ReleaseTexture();
}


#pragma region LoadRes
void WitchHouse_UpFloor::LoadTexture()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\PlayContents\\WitchHouse_UpFloor");
	std::vector<GameEngineDirectory> Dirs = Dir.GetAllDirectory();
	for (GameEngineDirectory& Dircetory : Dirs)
	{
		std::vector<GameEngineFile> Files = Dircetory.GetAllFile();
		for (GameEngineFile& pFile : Files)
		{
			GameEngineTexture::Load(pFile.GetStringPath());
		}
	}
}



void WitchHouse_UpFloor::LoadActor()
{
	if (nullptr == m_BackDrop)
	{
		m_BackDrop = CreateActor<BackDrop_WitchHouse_UpFloor>(EUPDATEORDER::Objects);
	}
}


void WitchHouse_UpFloor::SetEllieLevelChangeLocation(class GameEngineLevel* _NextLevel)
{
	if (nullptr == Player)
	{
		return;
	}

	float4 SpawnPosition = float4::ZERO;

	std::string NextLevelName = _NextLevel->GetName();
	if (NextLevelName == "WitchHouse_Yard")
	{
		Player->SetAnimationByDirection(EDIRECTION::UP);
		SpawnPosition = { 465.0f , -353.0f };
	}
	else if (NextLevelName == "WitchHouse_DownFloor")
	{
		Player->SetAnimationByDirection(EDIRECTION::DOWN);
		SpawnPosition = { 515.0f , -235.0f };
	}
	else if (NextLevelName == "DreamLevel")
	{
		Player->SetAnimationByDirection(EDIRECTION::DOWN);
		SpawnPosition = { 440.0f , -271.0f };
	}
	else
	{
		SpawnPosition = m_BackDrop->GetHouseLocation() + float4{ 128.0f , -310.0f };
	}
	
	Player->Transform.SetLocalPosition(SpawnPosition);
}

void WitchHouse_UpFloor::CameraSetting()
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

#pragma endregion 

void WitchHouse_UpFloor::ReleaseTexture()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\PlayContents\\WitchHouse_UpFloor");
	std::vector<GameEngineDirectory> Dirs = Dir.GetAllDirectory();
	for (GameEngineDirectory& Dircetory : Dirs)
	{
		std::vector<GameEngineFile> Files = Dircetory.GetAllFile();
		for (GameEngineFile& pFile : Files)
		{
			GameEngineTexture::Release(pFile.GetFileName());
		}
	}
}

void WitchHouse_UpFloor::AutoPlayBGM()
{
	if (nullptr != MainPlaySound)
	{
		const int bgmType = MainPlaySound->GetPlayType();
		if (static_cast<int>(EPLAYBGMTYPE::House) != bgmType)
		{
			MainPlaySound->NoneBGM();
		}
	}
}