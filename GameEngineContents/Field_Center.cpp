#include "PreCompile.h"
#include "Field_Center.h"


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
	PlayLevel::Start();

	if (nullptr != m_LevelCameraControler)
	{
		m_LevelCameraControler->SetCameraMode(ECAMERAMODE::Play);
	}

	SetName("Field_Center");
}

void Field_Center::Update(float _Delta)
{
	PlayLevel::Update(_Delta);
}

void Field_Center::LevelStart(class GameEngineLevel* _NextLevel)
{
	PlayLevel::LevelStart(_NextLevel);

	LoadTexture();
	LoadSprite();
	LoadActor();

	CameraSetting();
}

void Field_Center::LevelEnd(class GameEngineLevel* _NextLevel)
{
	PlayLevel::LevelEnd(_NextLevel);

	ReleaseSprite();
	ReleaseTexture();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


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

void Field_Center::LoadSprite()
{
	GameEngineSprite::CreateSingle("TestFieldMap.png");
	GameEngineSprite::CreateSingle("TestCenter_ColorMap.png");
}


void Field_Center::LoadActor()
{
	if (nullptr == m_BackDrop)
	{
		m_BackDrop = CreateActor<BackDrop_CenterField>(EUPDATEORDER::Objects);
	}

	if (nullptr == m_BackDrop)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_BackDrop->Init();


	if (nullptr == m_LevelCameraControler)
	{
		MsgBoxAssert("카메라 컨트롤러를 생성하지 않고 사용하려고 했습니다.");
		return;
	}

	// 배경 크기를 알려줘야 카메라 기능을 사용할 수 있습니다.
	m_LevelCameraControler->SetBackDropScale(m_BackDrop->GetBackGroundScale());
}





void Field_Center::CameraSetting()
{
	if (nullptr != GlobalValue::g_CameraControler)
	{
		if (GlobalValue::g_CameraControler != m_LevelCameraControler)
		{
			MsgBoxAssert("현재 카메라 매니저가 아닙니다.");
			return;
		}

		if (nullptr == m_Ellie)
		{
			MsgBoxAssert("플레이어가 존재하지 않습니다.");
			return;
		}

		GlobalValue::g_CameraControler->SetFocusActor(m_Ellie.get());
		GlobalValue::g_CameraControler->SetAutoInitialPosition(m_Ellie->Transform.GetWorldPosition());
	}
}


void Field_Center::LevelActorRelease()
{
	// 배경 정리하고
	if (nullptr != m_BackDrop)
	{
		m_BackDrop->ActorRelease();
	}
}

void Field_Center::ReleaseSprite()
{
	GameEngineSprite::Release("TestFieldMap.png");
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