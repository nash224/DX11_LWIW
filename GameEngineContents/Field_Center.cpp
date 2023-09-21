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

	UpdateLevelChange();
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
	LoadGlobalUnit();
	LoadPortalActor();


	m_BackDrop = CreateActor<BackDrop_CenterField>(EUPDATEORDER::Objects);
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

	m_LevelCameraControler->SetBackDropScale(m_BackDrop->GetBackGroundScale());
}


// 각 레벨에서 한번 실행하면 두번 다신 들어오지 않습니다. 
// 게임이 종료할때까지 함께 존재하는 메모리입니다.
void Field_Center::LoadGlobalUnit()
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
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_Ellie->Init();
	m_Ellie->SetSpawnLocalPosition(HWinScale);


	LevelInitCheck = true;
}



void Field_Center::LoadPortalActor()
{
	{
		std::shared_ptr<PortalObject> Object = CreateActor<PortalObject>(EUPDATEORDER::Portal);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		Object->CreatePortalCollision(ECOLLISION::Portal);
		Object->SetChangeLevelName("WitchHouse_Yard");
		Object->SetLevelChangeCallBack<Field_Center>(this, &Field_Center::LevelActorRelease);
		Object->SetCollisionRange({ 100.0f , 400.0f });
		Object->SetLocalPosition({ 1200.0f , -200.0f });
		Object->SetCollisionType(ColType::AABBBOX2D);

		vecPortalObject.push_back(Object);
	}
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




void Field_Center::UpdateLevelChange()
{
	UpdatePortalObject();
}

void Field_Center::UpdatePortalObject()
{
	/*for (size_t i = 0; i < vecPortalObject.size(); i++)
	{
		std::shared_ptr<PortalObject> Object = vecPortalObject[i];
		if (nullptr == Object)
		{
			MsgBoxAssert("지워진 포탈 오브젝트를 참조하려고 했습니다.");
			return;
		}

		if (true == Object->GetCollisionFlag())
		{
			LevelActorRelease();
		}
	}*/
}




void Field_Center::LevelActorRelease()
{
	// 배경 정리하고
	if (nullptr != m_BackDrop)
	{
		m_BackDrop->ActorRelease();
		m_BackDrop = nullptr;
	}


	// 포탈 정리하고
	for (size_t i = 0; i < vecPortalObject.size(); i++)
	{
		std::shared_ptr<PortalObject> Object = vecPortalObject[i];
		if (nullptr == Object)
		{
			MsgBoxAssert("도중에 지워진 객체가 존재합니다.");
			return;
		}

		Object->ActorRelease();
	}

	vecPortalObject.clear();
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