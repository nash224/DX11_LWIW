#include "PreCompile.h"
#include "WitchHouse_Yard.h"

#include "BackDrop_WitchHouse_Yard.h"
#include "CameraControler.h"
#include "Ellie.h"
#include "PortalObject.h"


WitchHouse_Yard::WitchHouse_Yard() 
{
}

WitchHouse_Yard::~WitchHouse_Yard() 
{
}


void WitchHouse_Yard::Start()
{
	PlayLevel::Start();

	SetName("WitchHouse_Yard");

	if (nullptr != m_LevelCameraControler)
	{
		m_LevelCameraControler->SetCameraMode(ECAMERAMODE::Fix);
	}
}

void WitchHouse_Yard::Update(float _Delta)
{
	PlayLevel::Update(_Delta);
}

void WitchHouse_Yard::LevelStart(class GameEngineLevel* _NextLevel)
{
	PlayLevel::LevelStart(_NextLevel);

	LoadTexture();
	LoadSprite();
	LoadActor();


	SetEllieLevelChangeLocation(_NextLevel);

	CameraSetting();
}

void WitchHouse_Yard::LevelEnd(class GameEngineLevel* _NextLevel)
{
	PlayLevel::LevelEnd(_NextLevel);

	ReleaseSprite();
	ReleaseTexture();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void WitchHouse_Yard::LoadTexture()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\PlayContents\\WitchHouse_Yard");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineFile File = Files[i];
		GameEngineTexture::Load(File.GetStringPath());
	}
}

void WitchHouse_Yard::LoadSprite()
{
	GameEngineSprite::CreateSingle("TestYardMap.png");
}


void WitchHouse_Yard::LoadActor()
{
	if (nullptr == m_BackDrop)
	{
		m_BackDrop = CreateActor<BackDrop_WitchHouse_Yard>(EUPDATEORDER::Objects);
	}

	if (nullptr == m_BackDrop)
	{
		MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
		return;
	}

	m_BackDrop->Init();
}


// ������ȯ�� �ٸ��� ������ġ�� �������ݴϴ�.
void WitchHouse_Yard::SetEllieLevelChangeLocation(class GameEngineLevel* _NextLevel)
{
	float4 SpawnPosition = float4::ZERO;

	float4 HWinScale = GlobalValue::GetWindowScale().Half();

	std::string NextLevelName = _NextLevel->GetName();
	if (NextLevelName == "Field_Center")
	{
		SpawnPosition = { HWinScale.X , -HWinScale.Half().Y };
	}

	if (nullptr == m_Ellie)
	{
		MsgBoxAssert("�ٸ��� �������� �ʾҽ��ϴ�.");
		return;
	}
	m_Ellie->SetSpawnLocalPosition(SpawnPosition);
}

void WitchHouse_Yard::CameraSetting()
{
	if (nullptr != GlobalValue::g_CameraControler)
	{
		if (GlobalValue::g_CameraControler != m_LevelCameraControler)
		{
			MsgBoxAssert("���� ī�޶� �Ŵ����� �ƴմϴ�.");
			return;
		}

		float4 HWinScale = GlobalValue::GetWindowScale().Half();
		HWinScale.Y *= -1.0f;

		GlobalValue::g_CameraControler->SetLocalPostion(HWinScale);
	}
}


void WitchHouse_Yard::LevelActorRelease()
{
	// ��� �����ϰ�
	if (nullptr != m_BackDrop)
	{
		m_BackDrop->ActorRelease();
	}
}

void WitchHouse_Yard::ReleaseSprite()
{
	GameEngineSprite::Release("TestYardMap.png");
}

void WitchHouse_Yard::ReleaseTexture()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\PlayContents\\WitchHouse_Yard");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineFile File = Files[i];
		GameEngineTexture::Release(File.GetFileName());
	}
}