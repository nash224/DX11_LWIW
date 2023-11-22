#include "PreCompile.h"
#include "WitchHouse_DownFloor.h"

#include "BackDrop_WitchHouse_DownFloor.h"
#include "BGMManager.h"
#include "CameraControler.h"

#include "Ellie.h"


WitchHouse_DownFloor::WitchHouse_DownFloor()
{
}

WitchHouse_DownFloor::~WitchHouse_DownFloor()
{
}


void WitchHouse_DownFloor::Start()
{
	PlayLevel::Start();

	if (nullptr != LevelCamera)
	{
		LevelCamera->SetCameraMode(ECAMERAMODE::Fix);
	}
}

void WitchHouse_DownFloor::Update(float _Delta)
{
	PlayLevel::Update(_Delta);

	AutoPlayBGM();
}

void WitchHouse_DownFloor::LevelStart(class GameEngineLevel* _NextLevel)
{
	PlayLevel::LevelStart(_NextLevel);

	LoadTexture();
	LoadActor();

	SetEllieLevelChangeLocation(_NextLevel);

	CameraSetting();
}

void WitchHouse_DownFloor::LevelEnd(class GameEngineLevel* _NextLevel)
{
	PlayLevel::LevelEnd(_NextLevel);

	ReleaseTexture();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


void WitchHouse_DownFloor::LoadTexture()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\PlayContents\\WitchHouse_DownFloor");
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

void WitchHouse_DownFloor::LoadActor()
{
	if (nullptr == Back)
	{
		Back = CreateActor<BackDrop_WitchHouse_DownFloor>(EUPDATEORDER::Objects);
	}

	Back->Init();
}


void WitchHouse_DownFloor::SetEllieLevelChangeLocation(class GameEngineLevel* _NextLevel)
{
	if (nullptr == Player)
	{
		MsgBoxAssert("앨리를 생성하지 않았습니다.");
		return;
	}

	Player->Transform.SetLocalPosition({ 548.0f , -228.0f });
}

void WitchHouse_DownFloor::CameraSetting()
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


void WitchHouse_DownFloor::ReleaseTexture()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\PlayContents\\WitchHouse_DownFloor");
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

void WitchHouse_DownFloor::AutoPlayBGM()
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