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
	LoadGlobalUnit();
	LoadPortalActor();


	if (nullptr == m_BackDrop)
	{
		m_BackDrop = CreateActor<BackDrop_WitchHouse_Yard>(EUPDATEORDER::Objects);
	}

	if (nullptr == m_BackDrop)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_BackDrop->Init();
}


// 각 레벨에서 한번 실행하면 두번 다신 들어오지 않습니다. 
// 게임이 종료할때까지 함께 존재하는 메모리입니다.
void WitchHouse_Yard::LoadGlobalUnit()
{
	if (true == LevelInitCheck)
	{
		return;
	}

	m_Ellie = CreateActor<Ellie>(EUPDATEORDER::Player);
	if (nullptr == m_Ellie)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_Ellie->Init();

	LevelInitCheck = true;
}



void WitchHouse_Yard::LoadPortalActor()
{
	{
		std::shared_ptr<PortalObject> Object = CreateActor<PortalObject>(EUPDATEORDER::Portal);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		float4 HWinScale = GlobalValue::GetWindowScale().Half();

		Object->CreatePortalCollision(ECOLLISION::Portal);
		Object->SetChangeLevelName("WitchHouse_UpFloor");
		Object->SetLevelChangeCallBack<WitchHouse_Yard>(this, &WitchHouse_Yard::LevelActorRelease);
		Object->SetLocalPosition({ HWinScale.X , -25.0f });
		Object->SetCollisionRange({ 200.0f , 50.0f });
		Object->SetCollisionType(ColType::AABBBOX2D);

		vecPortalObject.push_back(Object);
	}
}




// 레벨전환시 앨리의 시작위치를 지정해줍니다.
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
		MsgBoxAssert("앨리를 생성하지 않았습니다.");
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
			MsgBoxAssert("현재 카메라 매니저가 아닙니다.");
			return;
		}

		float4 HWinScale = GlobalValue::GetWindowScale().Half();
		HWinScale.Y *= -1.0f;

		GlobalValue::g_CameraControler->SetLocalPostion(HWinScale);
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
			MsgBoxAssert("지워진 포탈 오브젝트를 참조하려고 했습니다.");
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
	// 배경 정리하고
	if (nullptr != m_BackDrop)
	{
		m_BackDrop->ActorRelease();
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