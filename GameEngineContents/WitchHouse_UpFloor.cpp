#include "PreCompile.h"
#include "WitchHouse_UpFloor.h"

#include "BackDrop_WitchHouse_UpFloor.h"
#include "BGMManager.h"
#include "CameraControler.h"
#include "Ellie.h"
#include "FadeObject.h"


WitchHouse_UpFloor::WitchHouse_UpFloor()
{
}

WitchHouse_UpFloor::~WitchHouse_UpFloor()
{
}


void WitchHouse_UpFloor::Start()
{
	PlayLevel::Start();

	Back = CreateActor<BackDrop_WitchHouse_UpFloor>(EUPDATEORDER::Back);

	if (nullptr != ContentsLevel::LevelCamera)
	{
		float4 SettingPos = GlobalValue::GetWindowScale().Half();
		SettingPos.Y *= -1.0f;

		ContentsLevel::LevelCamera->SetCameraMode(ECAMERAMODE::Fix);
		ContentsLevel::LevelCamera->SetLocalPostion(SettingPos);
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
	LoadTexture();
}

void WitchHouse_UpFloor::LevelEnd(class GameEngineLevel* _NextLevel)
{
	ReleaseTexture();
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