#include "PreCompile.h"
#include "BackDrop_WitchHouse_DownFloor.h"


#include "Prop.h"
#include "PortalObject.h"

#include "AlchemyPot.h"
#include "Extractor.h"
#include "Roaster.h"


BackDrop_WitchHouse_DownFloor::BackDrop_WitchHouse_DownFloor() 
{
}

BackDrop_WitchHouse_DownFloor::~BackDrop_WitchHouse_DownFloor() 
{
}


void BackDrop_WitchHouse_DownFloor::Start()
{
	BackDrop::Start();
}

void BackDrop_WitchHouse_DownFloor::Update(float _Delta)
{
	BackDrop::Update(_Delta);
}

void BackDrop_WitchHouse_DownFloor::LevelStart(class GameEngineLevel* _NextLevel)
{
	BackDrop::LevelStart(_NextLevel);
}

void BackDrop_WitchHouse_DownFloor::LevelEnd(class GameEngineLevel* _NextLevel)
{
	BackDrop::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void BackDrop_WitchHouse_DownFloor::Init()
{
	BackDrop_PlayLevel::Init();

	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	CreateProp(CurLevel);
	CreatePixelMap(CurLevel);
	CreateStaticActor(CurLevel);
	CreatePortalActor(CurLevel);

	m_BackScale = GlobalValue::GetWindowScale();
}


#pragma endregion 

#pragma region CreateProp

void BackDrop_WitchHouse_DownFloor::CreateProp(GameEngineLevel* _Level)
{
	vecProps.reserve(30);

#pragma region BackPaint

	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer();
		Object->SetSprite("DownFloor_Back.png");
		Object->SetRendererPivotType(PivotType::LeftTop);
		Object->SetRendererImageScale(GlobalValue::GetWindowScale());
		Object->SetPositionAndDepth(float4::ZERO, EHOUSEDEPTH::BackPaint);
		vecProps.push_back(Object);
	}

#pragma endregion

#pragma region HouseComposition

	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer();
		Object->SetSprite("DownFloor_Floor.png");
		Object->SetPositionAndDepth(m_DownFloorWholePosition + float4{ 337.0f + 12.0f , -181.0f - 134.0f }, EHOUSEDEPTH::HouseComposition);
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer();
		Object->SetSprite("DownFloor_Wall.png");
		Object->SetPositionAndDepth(m_DownFloorWholePosition + float4{ 336.0f + 14.0f , -177.0f - 14.0f }, EHOUSEDEPTH::HouseComposition);
		vecProps.push_back(Object);
	}

#pragma endregion 

#pragma region Frame

	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer();
		Object->SetSprite("DownFloor_Frame.png");
		Object->SetPositionAndDepth(m_DownFloorWholePosition + float4{ 350.0f , -255.0f }, EHOUSEDEPTH::FRAME);
		vecProps.push_back(Object);
	}

#pragma endregion 
}


#pragma endregion 

#pragma region CreatePixelMap


void BackDrop_WitchHouse_DownFloor::CreatePixelMap(GameEngineLevel* _Level)
{
	std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
	if (nullptr == Object)
	{
		MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
		return;
	}

	Object->CreatePixelCollisionRenderer();
	Object->SetPixelSprite("DownFloor_PixelMap.png");
	Object->Transform.SetLocalPosition(m_DownFloorWholePosition + float4{ 350.0f , -206.0f - 100.0f });

	vecPixelProps.push_back(Object);
}


#pragma endregion 

#pragma region CreateStaticActor

void BackDrop_WitchHouse_DownFloor::CreateStaticActor(GameEngineLevel* _Level)
{
	{
		std::shared_ptr<AlchemyPot> Object = _Level->CreateActor<AlchemyPot>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateAndSetCollision(ECOLLISION::Entity, { 100.0f , 100.0f }, float4::ZERO, ColType::SPHERE2D );
		Object->SetInteractionType(EINTERACTION_TYPE::Far);
		Object->SetInteractionButtonType(EINTERACTION_BUTTONTYPE::Gear);
		Object->Transform.SetLocalPosition(m_DownFloorWholePosition + float4{ 57.0f + 352.0f , -53.0f - 246.0f });

		vecStaticEntity.push_back(Object);
	}

	{
		std::shared_ptr<Roaster> Object = _Level->CreateActor<Roaster>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateAndSetCollision(ECOLLISION::Entity, { 150.0f , 150.0f }, float4::ZERO, ColType::SPHERE2D);
		Object->SetInteractionType(EINTERACTION_TYPE::Far);
		Object->SetInteractionButtonType(EINTERACTION_BUTTONTYPE::Gear);
		Object->Transform.SetLocalPosition(m_DownFloorWholePosition + float4{ 47.0f + 183.0f , -47.0f - 313.0f });

		vecStaticEntity.push_back(Object);
	}

	{
		std::shared_ptr<Extractor> Object = _Level->CreateActor<Extractor>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateAndSetCollision(ECOLLISION::Entity, { 150.0f , 150.0f }, float4::ZERO, ColType::SPHERE2D);
		Object->SetInteractionType(EINTERACTION_TYPE::Far);
		Object->SetInteractionButtonType(EINTERACTION_BUTTONTYPE::Gear);
		Object->Transform.SetLocalPosition(m_DownFloorWholePosition + float4{ 39.0f + 267.0f , -46.0f - 99.0f });

		vecStaticEntity.push_back(Object);
	}
}


#pragma endregion 

#pragma region CreatePortal

void BackDrop_WitchHouse_DownFloor::CreatePortalActor(GameEngineLevel* _Level)
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
		Object->SetLevelChangeCallBack<BackDrop_WitchHouse_DownFloor>(this, &BackDrop_WitchHouse_DownFloor::ActorRelease);
		Object->SetCollisionRange({ 64.0f , 22.0f });
		Object->SetLocalPosition({ 548.0f , -172.0f });
		Object->SetCollisionType(ColType::AABBBOX2D);

		vecPortalObject.push_back(Object);
	}
}



#pragma endregion 

#pragma region Release

void BackDrop_WitchHouse_DownFloor::ActorRelease()
{
	BackDrop_PlayLevel::ActorRelease();
}

#pragma endregion 