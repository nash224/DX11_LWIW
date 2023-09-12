#include "PreCompile.h"
#include "Field_Center.h"


#include "CameraControler.h"
#include "BackDrop_CenterField.h"


Field_Center::Field_Center() 
{
}

Field_Center::~Field_Center() 
{
}


void Field_Center::Start()
{
	ContentsLevel::Start();

	if (nullptr != m_LevelCameraControler)
	{
		m_LevelCameraControler->SetCameraMode(ECAMERAMODE::Play);
	}
}

void Field_Center::Update(float _Delta)
{
	ContentsLevel::Update(_Delta);
}

void Field_Center::LevelStart(class GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelStart(_NextLevel);

	LoadTexture();
	LoadSprite();
	LoadActor();
}

void Field_Center::LevelEnd(class GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelEnd(_NextLevel);
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
}


void Field_Center::LoadActor()
{
	m_BackDrop = CreateActor<BackDrop_CenterField>(EUPDATEORDER::Objects);
	if (nullptr == m_BackDrop)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_BackDrop->Init();
}


void Field_Center::ActorRelease()
{
	if (nullptr != m_BackDrop)
	{
		m_BackDrop->ActorRelease();
		m_BackDrop = nullptr;
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