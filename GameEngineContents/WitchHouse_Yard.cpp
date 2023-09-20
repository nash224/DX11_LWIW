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

	if (nullptr != m_LevelCameraControler)
	{
		m_LevelCameraControler->SetCameraMode(ECAMERAMODE::Play);
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

	CameraSetting();
}

void WitchHouse_Yard::LevelEnd(class GameEngineLevel* _NextLevel)
{
	PlayLevel::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void WitchHouse_Yard::LoadTexture()
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

void WitchHouse_Yard::LoadSprite()
{
	GameEngineSprite::CreateSingle("TestFieldMap.png");
	GameEngineSprite::CreateSingle("TestCenter_ColorMap.png");
}


void WitchHouse_Yard::LoadActor()
{
	LoadGlobalUnit();
	LoadPortalActor();


	m_BackDrop = CreateActor<BackDrop_WitchHouse_Yard>(EUPDATEORDER::Objects);
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

	m_LevelCameraControler->SetBackDropScale(m_BackDrop->GetBackGroundScale());
}


// �� �������� �ѹ� �����ϸ� �ι� �ٽ� ������ �ʽ��ϴ�. 
// ������ �����Ҷ����� �Բ� �����ϴ� �޸��Դϴ�.
void WitchHouse_Yard::LoadGlobalUnit()
{
	if (true == LevelInitCheck)
	{
		return;
	}

	float4 HWinScale = GlobalValue::GetWindowScale().Half();
	HWinScale.Y *= -1.0f;


	m_Ellie = CreateActor<Ellie>(EUPDATEORDER::Player);
	if (nullptr == m_Ellie)
	{
		MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
		return;
	}

	m_Ellie->Init();
	m_Ellie->SetSpawnLocalPosition(HWinScale);


	LevelInitCheck = true;
}



void WitchHouse_Yard::LoadPortalActor()
{
	/*{
		std::shared_ptr<PortalObject> Object = CreateActor<PortalObject>(EUPDATEORDER::Portal);
		if (nullptr == Object)
		{
			MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
			return;
		}

		Object->CreatePortalCollision(ECOLLISION::Portal);
		Object->SetChangeLevelName("WitchHouse_Yard");
		Object->SetLevelChangeCallBack<WitchHouse_Yard>(this, &WitchHouse_Yard::LevelActorRelease);
		Object->SetCollisionRange({ 100.0f , 400.0f });
		Object->SetLocalPosition({ 1200.0f , -200.0f });
		Object->SetCollisionType(ColType::AABBBOX2D);

		vecPortalObject.push_back(Object);
	}*/
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

		if (nullptr == m_Ellie)
		{
			MsgBoxAssert("�÷��̾ �������� �ʽ��ϴ�.");
			return;
		}

		GlobalValue::g_CameraControler->SetFocusActor(m_Ellie.get());
		GlobalValue::g_CameraControler->SetAutoInitialPosition(m_Ellie->Transform.GetWorldPosition());
	}
}




void WitchHouse_Yard::UpdateLevelChange()
{
	UpdatePortalObject();
}

void WitchHouse_Yard::UpdatePortalObject()
{
	/*for (size_t i = 0; i < vecPortalObject.size(); i++)
	{
		std::shared_ptr<PortalObject> Object = vecPortalObject[i];
		if (nullptr == Object)
		{
			MsgBoxAssert("������ ��Ż ������Ʈ�� �����Ϸ��� �߽��ϴ�.");
			return;
		}

		if (true == Object->GetCollisionFlag())
		{
			LevelActorRelease();
		}
	}*/
}




void WitchHouse_Yard::LevelActorRelease()
{
	// ��� �����ϰ�
	if (nullptr != m_BackDrop)
	{
		m_BackDrop->ActorRelease();
		m_BackDrop = nullptr;
	}


	// ��Ż �����ϰ�
	for (size_t i = 0; i < vecPortalObject.size(); i++)
	{
		std::shared_ptr<PortalObject> Object = vecPortalObject[i];
		if (nullptr == Object)
		{
			MsgBoxAssert("���߿� ������ ��ü�� �����մϴ�.");
			return;
		}

		Object->ActorRelease();
	}

	vecPortalObject.clear();
}

void WitchHouse_Yard::ReleaseSprite()
{
	GameEngineSprite::Release("TestFieldMap.png");
}

void WitchHouse_Yard::ReleaseTexture()
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