#include "PreCompile.h"
#include "WitchHouse_UpFloor.h"

#include "BackDrop_WitchHouse_UpFloor.h"
#include "BGMManager.h"
#include "CameraControler.h"

#include "Ellie.h"
#include "UpperLiftA.h"


WitchHouse_UpFloor::WitchHouse_UpFloor()
{
}

WitchHouse_UpFloor::~WitchHouse_UpFloor()
{
}


void WitchHouse_UpFloor::Start()
{
	PlayLevel::Start();

	if (nullptr != ContentsLevel::LevelCamera)
	{
		ContentsLevel::LevelCamera->SetCameraMode(ECAMERAMODE::Fix);
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

	SetEllieLevelChangeLocation(_NextLevel);
	CameraSetting();

	LoadTexture();
	FileLoadFunction::LoadTextureAndCreateSingleSpriteInPath("Resources\\PlayContents\\Lift");

	if (nullptr == Back)
	{
		Back = CreateActor<BackDrop_WitchHouse_UpFloor>(EUPDATEORDER::Objects);
	}
}

void WitchHouse_UpFloor::LevelEnd(class GameEngineLevel* _NextLevel)
{
	FileLoadFunction::ReleaseAllTextureAndSpriteInPath("Resources\\PlayContents\\Lift");
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


void WitchHouse_UpFloor::SetEllieLevelChangeLocation(class GameEngineLevel* _NextLevel)
{
	if (nullptr == PlayLevel::Player)
	{
		return;
	}

	float4 SpawnPosition = float4::ZERO;

	std::string NextLevelName = _NextLevel->GetName();
	if (NextLevelName == "WitchHouse_Yard")
	{
		PlayLevel::Player->SetAnimationByDirection(EDIRECTION::UP);
		SpawnPosition = { 465.0f , -353.0f };
	}
	else if (NextLevelName == "WitchHouse_DownFloor")
	{
		PlayLevel::Player->SetAnimationByDirection(EDIRECTION::DOWN);
		SpawnPosition = { 515.0f , -235.0f };
	}
	else if (NextLevelName == "DreamLevel")
	{
		PlayLevel::Player->SetAnimationByDirection(EDIRECTION::DOWN);
		SpawnPosition = { 440.0f , -271.0f };
	}
	else
	{
		SpawnPosition = Back->GetHouseLocation() + float4{ 128.0f , -310.0f };
	}
	
	PlayLevel::Player->Transform.SetLocalPosition(SpawnPosition);
}

void WitchHouse_UpFloor::CameraSetting()
{
	if (false == CameraControler::MainCameraControler.expired())
	{
		float4 SettingPos = GlobalValue::GetWindowScale().Half();
		SettingPos.Y *= -1.0f;

		CameraControler::MainCameraControler.lock()->SetLocalPostion(SettingPos);
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
	if (nullptr != ContentsLevel::MainPlaySound)
	{
		const int bgmType = MainPlaySound->GetPlayType();
		if (static_cast<int>(EPLAYBGMTYPE::House) != bgmType)
		{
			ContentsLevel::MainPlaySound->NoneBGM();
		}
	}
}