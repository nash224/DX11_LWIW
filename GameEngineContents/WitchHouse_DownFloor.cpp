#include "PreCompile.h"
#include "WitchHouse_DownFloor.h"

#include "CameraControler.h"
#include "Ellie.h"
#include "BackDrop_WitchHouse_DownFloor.h"
#include "PortalObject.h"


WitchHouse_DownFloor::WitchHouse_DownFloor()
{
}

WitchHouse_DownFloor::~WitchHouse_DownFloor()
{
}


void WitchHouse_DownFloor::Start()
{
	PlayLevel::Start();

	SetName(std::string("WitchHouse_DownFloor"));


	if (nullptr != m_LevelCameraControler)
	{
		m_LevelCameraControler->SetCameraMode(ECAMERAMODE::Fix);
	}
}

void WitchHouse_DownFloor::Update(float _Delta)
{
	PlayLevel::Update(_Delta);

	if (true == GameEngineInput::IsDown('T', this))
	{
		m_Ellie->Transform.SetLocalPosition(float4::ZERO);
	}
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

#pragma region LoadResource

void WitchHouse_DownFloor::LoadTexture()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\PlayContents\\WitchHouse_DownFloor");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile File = Files[i];
    			GameEngineTexture::Load(File.GetStringPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\PlayContents\\WitchHouse_DownFloor\\Down_Sprite");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}
	}
}

void WitchHouse_DownFloor::LoadActor()
{
	if (nullptr == m_BackDrop)
	{
		m_BackDrop = CreateActor<BackDrop_WitchHouse_DownFloor>(EUPDATEORDER::Objects);
	}

	if (nullptr == m_BackDrop)
	{
		MsgBoxAssert("액터가 존재하지 않습니다.");
		return;
	}

	m_BackDrop->Init();
}


#pragma endregion 

#pragma region Initial Setting

// 레벨전환시 앨리의 시작위치를 지정해줍니다.
void WitchHouse_DownFloor::SetEllieLevelChangeLocation(class GameEngineLevel* _NextLevel)
{
	if (nullptr == m_Ellie)
	{
		MsgBoxAssert("앨리를 생성하지 않았습니다.");
		return;
	}

	m_Ellie->Transform.SetLocalPosition({ 548.0f , -228.0f });
}

void WitchHouse_DownFloor::CameraSetting()
{
	if (nullptr != GlobalValue::g_CameraControler)
	{
		if (GlobalValue::g_CameraControler != m_LevelCameraControler)
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

#pragma region Update



#pragma endregion 

#pragma region Release

void WitchHouse_DownFloor::ReleaseTexture()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\PlayContents\\WitchHouse_DownFloor");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile pFile = Files[i];
			GameEngineTexture::Release(pFile.GetFileName());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\PlayContents\\WitchHouse_DownFloor\\Down_Sprite");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile pFile = Files[i];
			GameEngineTexture::Release(pFile.GetFileName());
		}
	}
}

#pragma endregion 