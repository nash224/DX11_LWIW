#include "PreCompile.h"
#include "BackDrop_WitchHouse_Yard.h"

#include "Prop.h"
#include "PortalObject.h"

BackDrop_WitchHouse_Yard::BackDrop_WitchHouse_Yard() 
{
}

BackDrop_WitchHouse_Yard::~BackDrop_WitchHouse_Yard() 
{
}


void BackDrop_WitchHouse_Yard::Start()
{
	BackDrop::Start();
}

void BackDrop_WitchHouse_Yard::Update(float _Delta)
{
	BackDrop::Update(_Delta);
}

void BackDrop_WitchHouse_Yard::LevelStart(class GameEngineLevel* _NextLevel)
{
	BackDrop::LevelStart(_NextLevel);
}

void BackDrop_WitchHouse_Yard::LevelEnd(class GameEngineLevel* _NextLevel)
{
	BackDrop::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void BackDrop_WitchHouse_Yard::Init()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	CreateProp(CurLevel);
	/*CreatePixelMap(CurLevel);*/
	CreatePortalActor(CurLevel);


	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("TestYardMap.png");
	if (nullptr == Texture)
	{
		MsgBoxAssert("존재하지 않는 텍스처입니다.");
		return;
	}

	m_BackScale = Texture->GetScale();
}

#pragma region CreateProp
void BackDrop_WitchHouse_Yard::CreateProp(GameEngineLevel* _Level)
{
	vecProps.reserve(30);

	std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
	if (nullptr == Object)
	{
		MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
		return;
	}

	Object->CreateRenderer(ERENDERORDER::Back_);
	Object->SetSprite("TestYardMap.png");
	Object->SetPosition(float4::ZERO, PivotType::LeftTop);
	vecProps.push_back(Object);
}

#pragma endregion 

#pragma region CreatePortal

void BackDrop_WitchHouse_Yard::CreatePortalActor(GameEngineLevel* _Level)
{
	{
		std::shared_ptr<PortalObject> Object = _Level->CreateActor<PortalObject>(EUPDATEORDER::Portal);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		float4 HWinScale = GlobalValue::GetWindowScale().Half();

		Object->CreatePortalCollision(ECOLLISION::Portal);
		Object->SetChangeLevelName("WitchHouse_UpFloor");
		Object->SetLevelChangeCallBack<BackDrop_WitchHouse_Yard>(this, &BackDrop_WitchHouse_Yard::ActorRelease);
		Object->SetLocalPosition({ HWinScale.X , -25.0f });
		Object->SetCollisionRange({ 200.0f , 50.0f });
		Object->SetCollisionType(ColType::AABBBOX2D);

		vecPortalObject.push_back(Object);
	}
}

#pragma endregion 

#pragma region Release

void BackDrop_WitchHouse_Yard::ActorRelease()
{
	BackDrop::ActorRelease();
}

#pragma endregion 