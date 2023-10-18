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

	std::string Name = "Field_Center";
	SetName(Name);
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

	SetEllieLevelChangeLocation(_NextLevel);

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
		MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
		return;
	}

	m_BackDrop->Init();

	if (nullptr == m_LevelCameraControler)
	{
		MsgBoxAssert("ī�޶� ��Ʈ�ѷ��� �������� �ʰ� ����Ϸ��� �߽��ϴ�.");
		return;
	}

	// ��� ũ�⸦ �˷���� ī�޶� ����� ����� �� �ֽ��ϴ�.
	m_LevelCameraControler->SetBackDropScale(m_BackDrop->GetBackGroundScale());
}

void Field_Center::SetEllieLevelChangeLocation(class GameEngineLevel* _NextLevel)
{
	float4 SpawnPosition = float4::ZERO;

	std::string NextLevelName = _NextLevel->GetName();
	if (NextLevelName == "WitchHouse_Yard")
	{
		SpawnPosition = { 200.0f , -200.0f };
	}

	if (nullptr == m_Ellie)
	{
		MsgBoxAssert("�ٸ��� �������� �ʾҽ��ϴ�.");
		return;
	}

	m_Ellie->SetSpawnLocalPosition(SpawnPosition);
}



void Field_Center::CameraSetting()
{
	if (nullptr != GlobalValue::g_CameraControler)
	{
		if (GlobalValue::g_CameraControler != m_LevelCameraControler)
		{
			MsgBoxAssert("���� ī�޶� �Ŵ����� �ƴմϴ�.");
			return;
		}

		if (nullptr == m_Ellie)
		{
			MsgBoxAssert("�÷��̾ �������� �ʽ��ϴ�.");
			return;
		}

		GlobalValue::g_CameraControler->SetFocusActor(m_Ellie.get());
		GlobalValue::g_CameraControler->SetAutoInitialPosition(m_Ellie->Transform.GetWorldPosition());
	}
}

#pragma endregion

#pragma region ReleaseRes

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

#pragma endregion