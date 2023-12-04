#include "PreCompile.h"
#include "Field_Center.h"

#include <GameEngineCore/GameEngineCoreWindow.h>

#include "CameraControler.h"
#include "BackDrop_CenterField.h"
#include "Ellie.h"

Field_Center::Field_Center() 
{
	PlayLevel::LocationKRName = "초록숲 평원";
}

Field_Center::~Field_Center() 
{
}

void Field_Center::Start()
{
	FieldLevel::Start();

	Back = CreateActor<BackDrop_CenterField>(EUPDATEORDER::Back);

	if (nullptr != ContentsLevel::LevelCamera)
	{
		ContentsLevel::LevelCamera->SetCameraMode(ECAMERAMODE::Play);
		ContentsLevel::LevelCamera->SetBackDropScale(Back->GetBackGroundScale());
	}

	std::shared_ptr<GameEngineCoreWindow> Window = GameEngineGUI::FindGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow");
	if (nullptr != Window)
	{
		Window->AddDebugRenderTarget(2, "CenterRenderTarget", GetMainCamera()->GetCameraAllRenderTarget());
		Window->AddDebugRenderTarget(4, "CenterPixelTarget", GetCamera(static_cast<int>(ECAMERAORDER::MainPrev))->GetCameraAllRenderTarget());
	}
}

void Field_Center::Update(float _Delta)
{
	FieldLevel::Update(_Delta);
}

void Field_Center::LevelStart(class GameEngineLevel* _NextLevel)
{
	FieldLevel::LevelStart(_NextLevel);

	LoadTexture();

	SetPlayerPos(_NextLevel);
	CameraSetting();
}

void Field_Center::LevelEnd(class GameEngineLevel* _NextLevel)
{
	FieldLevel::LevelEnd(_NextLevel);

	ReleaseTexture();
}


void Field_Center::SetPlayerPos(class GameEngineLevel* _NextLevel) const
{
	if (nullptr == PlayLevel::Player)
	{
		MsgBoxAssert("레벨에 플레이어가 존재하지 않습니다.");
		return;
	}

	float4 SpawnPosition;

	if (_NextLevel->GetName() == "WitchHouse_Yard")
	{
		SpawnPosition = { 1430.0f , -50.0f };
		PlayLevel::Player->SetAnimationByDirection(EDIRECTION::DOWN);
	}
	else
	{
		SpawnPosition = { 1430.0f , -50.0f };
		PlayLevel::Player->SetAnimationByDirection(EDIRECTION::DOWN);
	}

	PlayLevel::Player->Transform.SetLocalPosition(SpawnPosition);
}

void Field_Center::CameraSetting()
{
	if (nullptr != ContentsLevel::LevelCamera)
	{
		if (nullptr == Player)
		{
			MsgBoxAssert("플레이어가 존재하지 않습니다.");
			return;
		}

		ContentsLevel::LevelCamera->SetFocusActor(PlayLevel::Player.get());
		ContentsLevel::LevelCamera->SetAutoInitialPosition(PlayLevel::Player->Transform.GetWorldPosition());
	}
}


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
