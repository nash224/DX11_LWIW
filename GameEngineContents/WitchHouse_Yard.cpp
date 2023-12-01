#include "PreCompile.h"
#include "WitchHouse_Yard.h"

#include "CameraControler.h"

#include "BackDrop_WitchHouse_Yard.h"
#include "Ellie.h"

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
		ContentsLevel::LevelCamera->SetCameraMode(ECAMERAMODE::Fix);
	}
}

void WitchHouse_Yard::Update(float _Delta)
{
	FieldLevel::Update(_Delta);
}

void WitchHouse_Yard::LevelStart(class GameEngineLevel* _NextLevel)
{
	FieldLevel::LevelStart(_NextLevel);

	LoadTexture();

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

void WitchHouse_Yard::SetElliePosToEnter(class GameEngineLevel* _NextLevel)
{
	if (nullptr == PlayLevel::Player)
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
		PlayLevel::Player->SetAnimationByDirection(EDIRECTION::UP);
	}
	else if (_NextLevel->GetName() == "WitchHouse_UpFloor")
	{
		SpawnPosition = { 485.0f , -337.0f };
		PlayLevel::Player->SetAnimationByDirection(EDIRECTION::DOWN);
	}
	else 
	{
		SpawnPosition = { HWinScale.X , -450.0f };
	}

	PlayLevel::Player->Transform.SetLocalPosition(SpawnPosition);
}

void WitchHouse_Yard::CameraSetting()
{
	if (nullptr != ContentsLevel::LevelCamera)
	{
		float4 SettingPos = GlobalValue::GetWindowScale().Half();
		SettingPos.Y *= -1.0f;

		ContentsLevel::LevelCamera->SetLocalPostion(SettingPos);
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
