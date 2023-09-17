#include "PreCompile.h"
#include "Field_Center.h"


#include "CameraControler.h"
#include "BackDrop_CenterField.h"
#include "Ellie.h"


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

void Field_Center::LevelEnd(class GameEngineLevel* _NextLevel)
{
	PlayLevel::LevelEnd(_NextLevel);
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
	LoadGlobalUnit();
}

// �� �������� �ѹ� �����ϸ� �ι� �ٽ� ������ �ʽ��ϴ�. 
// ������ �����Ҷ����� �Բ� �����ϴ� �޸��Դϴ�.
void Field_Center::LoadGlobalUnit()
{
	if (true == LevelInitCheck)
	{
		return;
	}

	float4 HWinScale = GlobalValue::GetWindowScale().Half();
	HWinScale.Y *= -1.0f;

	m_BackDrop = CreateActor<BackDrop_CenterField>(EUPDATEORDER::Objects);
	if (nullptr == m_BackDrop)
	{
		MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
		return;
	}

	m_BackDrop->Init();


	m_Ellie = CreateActor<Ellie>(EUPDATEORDER::Player);
	if (nullptr == m_Ellie)
	{
		MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
		return;
	}

	m_Ellie->Init();
	m_Ellie->SetSpawnLocalPosition(HWinScale);


	if (nullptr == m_LevelCameraControler)
	{
		MsgBoxAssert("ī�޶� ��Ʈ�ѷ��� �������� �ʰ� ����Ϸ��� �߽��ϴ�.");
		return;
	}

	m_LevelCameraControler->SetBackDropScale(m_BackDrop->GetBackGroundScale());


	LevelInitCheck = true;
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