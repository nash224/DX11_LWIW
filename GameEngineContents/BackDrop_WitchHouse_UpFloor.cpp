#include "PreCompile.h"
#include "BackDrop_WitchHouse_UpFloor.h"

#include "Prop.h"
#include "PortalObject.h"

#include "MongSiri_Population.h"

BackDrop_WitchHouse_UpFloor::BackDrop_WitchHouse_UpFloor() 
{
}

BackDrop_WitchHouse_UpFloor::~BackDrop_WitchHouse_UpFloor() 
{
}


void BackDrop_WitchHouse_UpFloor::Start()
{
	BackDrop::Start();
}

void BackDrop_WitchHouse_UpFloor::Update(float _Delta)
{
	BackDrop::Update(_Delta);
}

void BackDrop_WitchHouse_UpFloor::LevelStart(class GameEngineLevel* _NextLevel)
{
	BackDrop::LevelStart(_NextLevel);
}

void BackDrop_WitchHouse_UpFloor::LevelEnd(class GameEngineLevel* _NextLevel)
{
	BackDrop::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void BackDrop_WitchHouse_UpFloor::Init()
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
	LoadPortalActor(CurLevel);

	{
		std::shared_ptr<MongSiri_Population> Object = CurLevel->CreateActor<MongSiri_Population>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition({ 100.0f , -100.0f });
		Object->SetPopulationSpawnLocation({ 150.0f , -150.0f });
		Object->Init(3);
	}

	m_BackScale = GlobalValue::GetWindowScale();
}


#pragma region Prop

void BackDrop_WitchHouse_UpFloor::CreateProp(GameEngineLevel* _Level)
{
	vecProps.reserve(50);

	float4 RYWinScale = GlobalValue::GetWindowScale().Half();
	RYWinScale.Y *= -1.0f;

	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer(EWITCHHOUSEUPPERFLOOR::BackPaint);
		Object->SetSpriteRenderer({ "UpFloor_Back.png", RYWinScale });
		Object->SetRendererImageScale(GlobalValue::GetWindowScale());
		vecProps.push_back(Object);
	}


#pragma region HouseComposition

	// 
	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer(EWITCHHOUSEUPPERFLOOR::HouseComposition);
		Object->SetSpriteRenderer( "UpFloor_Circle.png", m_HouseLocation + float4{ 32.0f + 142.0f , -32.0f - 47.0f } );
		Object->SetRendererImageScale({ 64.0f , 64.0f });
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer(EWITCHHOUSEUPPERFLOOR::HouseComposition);
		Object->SetSpriteRenderer("UpFloor_Floor.png", m_HouseLocation + float4{ 126.0f , - 96.0f - 142.0f } );
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer(EWITCHHOUSEUPPERFLOOR::HouseComposition);
		Object->SetSpriteRenderer("UpFloor_WallPaper_1.png", m_HouseLocation + float4{ 32.0f + 142.0f , -64.0f - 14.0f });
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer(EWITCHHOUSEUPPERFLOOR::HouseComposition);
		Object->SetSpriteRenderer("UpFloor_WallPaper.png", m_HouseLocation + float4{ 112.0f + 14.0f , -64.0f - 46.0f });
		vecProps.push_back(Object);
	}


#pragma endregion 

#pragma region HouseShadow

	// HouseShadow
	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer(EWITCHHOUSEUPPERFLOOR::HouseShadow);
		Object->SetSpriteRenderer("UpFloor_Shadow.png", m_HouseLocation + float4{ 112.0f + 14.0f , -163.0f - 14.0f });
		vecProps.push_back(Object);
	}

#pragma endregion 

#pragma region FirstObjects


	// FirstObjects
	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer(EWITCHHOUSEUPPERFLOOR::FirstObjects);
		Object->SetSpriteRenderer("UpFloor_Carpet_0.png", m_HouseLocation + float4{ 60.0f + 64.0f , -25.0f - 280.0f });
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer(EWITCHHOUSEUPPERFLOOR::FirstObjects);
		Object->SetSpriteRenderer("UpFloor_Cabinet.png", m_HouseLocation + float4{ 12.0f + 214.0f , -75.0f - 88.0f });
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer(EWITCHHOUSEUPPERFLOOR::FirstObjects);
		Object->SetSpriteRenderer("UpFloor_Plant_L.png", m_HouseLocation + float4{ 29.0f + 179.0f , -39.0f - 234.0f });
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer(EWITCHHOUSEUPPERFLOOR::FirstObjects);
		Object->SetSpriteRenderer("UpFloor_window.png", m_HouseLocation + float4{ 25.0f + 150.0f , -25.0f - 51.0f });
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer(EWITCHHOUSEUPPERFLOOR::FirstObjects);
		Object->SetSpriteRenderer("UpFloor_bed.png", m_HouseLocation + float4{ 35.0f + 14.0f , -68.0f - 124.0f });
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer(EWITCHHOUSEUPPERFLOOR::FirstObjects);
		Object->SetSpriteRenderer("book_shelf_empty.png", m_HouseLocation + float4{ 30.0f + 74.0f , -12.0f - 94.0f });
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer(EWITCHHOUSEUPPERFLOOR::FirstObjects);
		Object->SetSpriteRenderer("UpFloor_Carpet_1.png", m_HouseLocation + float4{ 33.0f + 141.0f , -35.0f - 140.0f });
		vecProps.push_back(Object);
	}

#pragma endregion 

#pragma region SecondObjects

	// SecondObjects
	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer(EWITCHHOUSEUPPERFLOOR::SecondObjects);
		Object->SetSpriteRenderer("UpFloor_plants.png", m_HouseLocation + float4{ 34.0f + 140.0f , -23.0f - 28.0f });
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer(EWITCHHOUSEUPPERFLOOR::SecondObjects);
		Object->SetSpriteRenderer("UpFloor_drawer_under.png", m_HouseLocation + float4{ 27.0f + 6.0f , -33.0f - 252.0f });
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer(EWITCHHOUSEUPPERFLOOR::SecondObjects);
		Object->SetSpriteRenderer("UpFloor_Chair.png", m_HouseLocation + float4{ 16.0f + 159.0f , -17.0f - 128.0f });
		vecProps.push_back(Object);
	}

#pragma endregion 

#pragma region ThirdObjects
	// ThirdObjects
	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer(EWITCHHOUSEUPPERFLOOR::ThirdObjects);
		Object->SetSpriteRenderer("Chair_Shadow.png", m_HouseLocation + float4{ 33.0f + 141.0f , -7.0f - 142.0f });
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer(EWITCHHOUSEUPPERFLOOR::ThirdObjects);
		Object->SetSpriteRenderer("UpFloor_desk.png", m_HouseLocation + float4{ 34.0f + 140.0f , -15.0f - 112.0f });
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer(EWITCHHOUSEUPPERFLOOR::ThirdObjects);
		Object->SetSpriteRenderer("hanger.png", m_HouseLocation + float4{ 21.0f + 80.0f , -45.0f - 106.0f });
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer(EWITCHHOUSEUPPERFLOOR::ThirdObjects);
		Object->SetSpriteRenderer("PhotoFrame_0.png", m_HouseLocation + float4{ 13.0f + 1.0f , -18.0f - 241.0f });
		vecProps.push_back(Object);
	}


	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer(EWITCHHOUSEUPPERFLOOR::ThirdObjects);
		Object->SetSpriteRenderer("SaveProp.png", m_HouseLocation + float4{ 9.0f + 28.0f , -16.0f - 259.0f });
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer(EWITCHHOUSEUPPERFLOOR::ThirdObjects);
		Object->SetSpriteRenderer("UpFloor_Flower_0.png", m_HouseLocation + float4{ 16.0f + 98.0f , -22.0f - 62.0f });
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer(EWITCHHOUSEUPPERFLOOR::ThirdObjects);
		Object->SetSpriteRenderer("UpFloor_Flower_1.png", m_HouseLocation + float4{ 10.0f + 80.0f , -21.0f - 64.0f });
		vecProps.push_back(Object);
	}

#pragma endregion 

#pragma region ForthObjects

	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer(EWITCHHOUSEUPPERFLOOR::ForthObjects);
		Object->SetSpriteRenderer("UpFloor_bag.png", m_HouseLocation + float4{ 9.0f + 104.0f , -18.0f - 150.0f });
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer(EWITCHHOUSEUPPERFLOOR::ForthObjects);
		Object->SetSpriteRenderer("book_open.png", m_HouseLocation + float4{ 23.0f + 152.0f , -13.0f - 114.0f });
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer(EWITCHHOUSEUPPERFLOOR::ForthObjects);
		Object->SetSpriteRenderer("DreamCapture.png", m_HouseLocation + float4{ 13.0f + 19.0f , -23.0f - 93.0f });
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer(EWITCHHOUSEUPPERFLOOR::ForthObjects);
		Object->SetSpriteRenderer("UpFloor_PhotoFrame_1.png", m_HouseLocation + float4{ 12.0f + 46.0f , -9.0f - 110.0f });
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer(EWITCHHOUSEUPPERFLOOR::ForthObjects);
		Object->SetSpriteRenderer("UpFloor_PhotoFrame_2.png", m_HouseLocation + float4{ 8.0f + 50.0f , -10.0f - 88.0f });
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer(EWITCHHOUSEUPPERFLOOR::ForthObjects);
		Object->SetSpriteRenderer("hanger_light.png", m_HouseLocation + float4{ 10.0f + 88.0f , -8.0f - 118.0f });
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer(EWITCHHOUSEUPPERFLOOR::ForthObjects);
		Object->SetSpriteRenderer("book_shelf.png", m_HouseLocation + float4{ 30.0f + 28.0f , -17.0f - 58.0f });
		vecProps.push_back(Object);
	}


#pragma endregion 

#pragma region FifthObjects

	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer(EWITCHHOUSEUPPERFLOOR::FifthObjects);
		Object->SetSpriteRenderer("book_shelf.png", m_HouseLocation + float4{ 11.0f + 70.0f , -17.0f - 94.0f });
		vecProps.push_back(Object);
	}

#pragma endregion 

#pragma region HouseFrame

	// HouseFrame
	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->CreateRenderer(EWITCHHOUSEUPPERFLOOR::HouseFrame);
		Object->SetSpriteRenderer( "UpFloor_Frame.png", m_HouseLocation + float4{ 126.0f , -171.0f } );
		vecProps.push_back(Object);
	}

#pragma endregion 
}


#pragma endregion 

#pragma region PixelMap

void BackDrop_WitchHouse_UpFloor::CreatePixelMap(GameEngineLevel* _Level)
{
	std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
	if (nullptr == Object)
	{
		MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
		return;
	}

	Object->CreatePixelCollisionRenderer();
	Object->SetPixelSprite("UpFloor_PixelMap.png");
	Object->Transform.SetLocalPosition(m_HouseLocation + float4{ 128.0f , -100.0f - 142.0f });

	vecPixelProps.push_back(Object);
}


#pragma endregion 

#pragma region CreatePortal

void BackDrop_WitchHouse_UpFloor::LoadPortalActor(GameEngineLevel* _Level)
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
		Object->SetChangeLevelName("WitchHouse_DownFloor");
		Object->SetLevelChangeCallBack<BackDrop_WitchHouse_UpFloor>(this, &BackDrop_WitchHouse_UpFloor::ActorRelease);
		Object->SetCollisionRange({ 200.0f , 100.0f });
		Object->SetLocalPosition({ HWinScale.X , -50.0f });
		Object->SetCollisionType(ColType::AABBBOX2D);

		vecPortalObject.push_back(Object);
	}
}

#pragma endregion 

#pragma region Release


void BackDrop_WitchHouse_UpFloor::ActorRelease()
{
	BackDrop_PlayLevel::ActorRelease();
}

#pragma endregion 