#include "PreCompile.h"
#include "Field_Center.h"

#include <GameEngineCore/GameEngineCoreWindow.h>

#include "CameraControler.h"
#include "BackDrop_CenterField.h"
#include "Ellie.h"
#include "PortalObject.h"



Field_Center::Field_Center() 
{
}

Field_Center::~Field_Center() 
{
}


void Field_Center::Start()
{
	FieldLevel::Start();

	if (nullptr != LevelCamera)
	{
		LevelCamera->SetCameraMode(ECAMERAMODE::Play);
	}


	std::shared_ptr<GameEngineCoreWindow> Window = GameEngineGUI::FindGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow");
	if (nullptr != Window)
	{
		Window->AddDebugRenderTarget(2, "CenterRenderTarget", GetMainCamera()->GetCameraAllRenderTarget());
	}

	SetLocationName("중앙 필드");
}

void Field_Center::Update(float _Delta)
{
	FieldLevel::Update(_Delta);
}

void Field_Center::LevelStart(class GameEngineLevel* _NextLevel)
{
	FieldLevel::LevelStart(_NextLevel);

	LoadTexture();
	LoadActor();

	SetEllieLevelChangeLocation(_NextLevel);

	CameraSetting();
}

void Field_Center::LevelEnd(class GameEngineLevel* _NextLevel)
{
	FieldLevel::LevelEnd(_NextLevel);

	ReleaseTexture();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

#pragma region LoadAndInit
void Field_Center::LoadTexture()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\PlayContents\\FieldCenter");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineFile File = Files[i];
		GameEngineTexture::Load(File.GetStringPath());
	}
}


void Field_Center::LoadActor()
{
	if (nullptr == m_BackDrop)
	{
		m_BackDrop = CreateActor<BackDrop_CenterField>(EUPDATEORDER::Objects);
	}

	m_BackDrop->Init();

	if (nullptr != LevelCamera)
	{
		LevelCamera->SetBackDropScale(m_BackDrop->GetBackGroundScale());
	}
}

void Field_Center::SetEllieLevelChangeLocation(class GameEngineLevel* _NextLevel)
{
	float4 SpawnPosition = float4::ZERO;

	if (_NextLevel->GetName() == "WitchHouse_Yard")
	{
		SpawnPosition = { 1430.0f , -50.0f };
	}
	else
	{
		SpawnPosition = { 1430.0f , -50.0f };
	}

	if (nullptr != Player)
	{
		Player->Transform.SetLocalPosition(SpawnPosition);
	}
}



void Field_Center::CameraSetting()
{
	if (false == CameraControler::MainCameraControler.expired())
	{
		if (nullptr == Player)
		{
			MsgBoxAssert("플레이어가 존재하지 않습니다.");
			return;
		}

		CameraControler::MainCameraControler.lock()->SetFocusActor(Player.get());
		CameraControler::MainCameraControler.lock()->SetAutoInitialPosition(Player->Transform.GetWorldPosition());
	}
}

#pragma endregion

#pragma region ReleaseRes


void Field_Center::ReleaseTexture()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\PlayContents\\FieldCenter");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineFile File = Files[i];
		GameEngineTexture::Release(File.GetFileName());
	}
}

#pragma endregion