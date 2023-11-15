#include "PreCompile.h"
#include "BackDrop_WitchHouse_UpFloor.h"

#include "ContentsEvent.h"
#include "HouseDustEvent.h"

#include "Dust_HandBook.h"
#include "Dust_Bag.h"
#include "Dust_Elevator.h"

#include "PortalObject.h"
#include "RendererActor.h"
#include "NormalProp.h"

#include "UpperLift.h"
#include "WitchHouseBed.h"


BackDrop_WitchHouse_UpFloor::BackDrop_WitchHouse_UpFloor() 
{
	m_BackScale = GlobalValue::GetWindowScale();
}

BackDrop_WitchHouse_UpFloor::~BackDrop_WitchHouse_UpFloor() 
{
}

void BackDrop_WitchHouse_UpFloor::Start()
{
	DustEventSetting();
}

void BackDrop_WitchHouse_UpFloor::LevelStart(class GameEngineLevel* _NextLevel)
{
	MainBackDrop = this;
}

void BackDrop_WitchHouse_UpFloor::LevelEnd(class GameEngineLevel* _NextLevel)
{
	BackDrop_PlayLevel::LevelEnd(_NextLevel);

	ReleaseResources();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void BackDrop_WitchHouse_UpFloor::Init()
{
	MainBackDrop = this;

	LoadResources();

	GameEngineLevel* CurLevel = GetLevel();

	CreateProp(CurLevel);
	CreatePixelMap(CurLevel);
	LoadPortalActor(CurLevel);
	LiftSetting();
	BedSetting();
	
	//if (false == isInitDustEvent)
	//{
	//	isInitDustEvent = true;
	//}

	/*CheckHouseDustEvent();*/
}

#pragma region Resource

void BackDrop_WitchHouse_UpFloor::LoadResources()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\PlayContents\\WitchHouse_UpFloor\\HouseSingle");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (GameEngineFile& pFile : Files)
	{
		GameEngineSprite::CreateSingle(pFile.GetFileName());
	}
}

void BackDrop_WitchHouse_UpFloor::ReleaseResources()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\PlayContents\\WitchHouse_UpFloor\\HouseSingle");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (GameEngineFile& pFile : Files)
	{
		GameEngineSprite::Release(pFile.GetFileName());
	}
}

#pragma endregion

#pragma region HouseComposition
void BackDrop_WitchHouse_UpFloor::CreateProp(GameEngineLevel* _Level)
{
	float4 RYWinScale = GlobalValue::GetWindowScale().Half();
	RYWinScale.Y *= -1.0f;

	{
		const float4& Position = float4{ RYWinScale.X, RYWinScale.Y, GlobalUtils::CalculateFixDepth(EHOUSEDEPTH::BackPaint) };
		std::shared_ptr<RendererActor> Object = _Level->CreateActor<RendererActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_Back.png");
		Object->m_Renderer->GetImageTransform().SetLocalScale(float4(GlobalValue::GetWindowScale()));
	}

	{
		std::shared_ptr<RendererActor> Object = _Level->CreateActor<RendererActor>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 174.0f , -79.0f };
		Position.Z = GlobalUtils::CalculateFixDepth(EHOUSEDEPTH::BackWindow);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_Circle.png");
		Object->m_Renderer->GetImageTransform().SetLocalScale(float4(64.0f, 64.0f));
	}

	{
		std::shared_ptr<RendererActor> Object = _Level->CreateActor<RendererActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(HouseLocation  + float4{ 126.0f , -238.0f, GlobalUtils::CalculateFixDepth(EHOUSEDEPTH::HouseComposition) });
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_Floor.png");
	}

	{
		const float4& Position = HouseLocation  + float4{ 174.0f , -78.0f, GlobalUtils::CalculateFixDepth(EHOUSEDEPTH::HouseComposition) };

		std::shared_ptr<RendererActor> Object = _Level->CreateActor<RendererActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_WallPaper_1.png");
	}

	{
		std::shared_ptr<RendererActor> Object = _Level->CreateActor<RendererActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(HouseLocation  + float4{ 126.0f , -110.0f, GlobalUtils::CalculateFixDepth(EHOUSEDEPTH::HouseComposition) });
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_WallPaper.png");
	}



	{
		std::shared_ptr<RendererActor> Object = _Level->CreateActor<RendererActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(HouseLocation  + float4{ 126.0f , -177.0f, GlobalUtils::CalculateFixDepth(EHOUSEDEPTH::Shadow )});
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_Shadow.png");
	}

	{
		std::shared_ptr<RendererActor> Object = _Level->CreateActor<RendererActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(HouseLocation  + float4{ 124.0f , -305.0f, GlobalUtils::CalculateFixDepth(EHOUSEDEPTH::Rug) });
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_Carpet_0.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 228.0f , -163.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y - 70.0f );
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_Cabinet.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 208.0f , -263.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y -20.0f);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_Plant_L.png");
	}


	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 175.0f , -76.0f };
		Position.Z = GlobalUtils::CalculateFixDepth(EHOUSEDEPTH::Rug);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_window.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 49.0f , -192.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_bed.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 104.0f , -106.0f };
		Position.Z = GlobalUtils::CalculateFixDepth(EHOUSEDEPTH::Rug);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("book_shelf_empty.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 174.0f , -175.0f };
		Position.Z = GlobalUtils::CalculateFixDepth(EHOUSEDEPTH::Rug);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_Carpet_1.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 174.0f , -51.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_plants.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 33.0f , -285.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_drawer_under.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 175.0f , -145.0f };
		Position.Z = GlobalUtils::CalculateFixDepth(EHOUSEDEPTH::Chair);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_Chair.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 174.0f , -149.0f };
		Position.Z = GlobalUtils::CalculateFixDepth(EHOUSEDEPTH::Shadow);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("Chair_Shadow.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 174.0f , -127.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_desk.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 101.0f , -151.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("hanger.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 14.0f , -259.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("PhotoFrame_0.png");
	}


	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 27.0f , -275.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y - 14.0f);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("SaveProp.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 117.0f , -84.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_Flower_0.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 90.0f , -85.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_Flower_1.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 113.0f , -168.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_bag.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 175.0f , -127.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("book_open.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 32.0f , -116.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DreamCapture.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 58.0f , -119.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_PhotoFrame_1.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 58.0f , -98.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_PhotoFrame_2.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 98.0f , -126.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("hanger_light.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 58.0f , -75.0f };
		Position.Z = GlobalUtils::CalculateFixDepth(EHOUSEDEPTH::Rug);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("book_shelf.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 126.0f , -171.0f };
		Position.Z = GlobalUtils::CalculateFixDepth(EHOUSEDEPTH::FRAME);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_Frame.png");
	}
}

#pragma endregion 

#pragma region PixelMap

void BackDrop_WitchHouse_UpFloor::CreatePixelMap(GameEngineLevel* _Level)
{
	PixelVec.reserve(3);

	std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
	float4 Position = HouseLocation  + float4{ 128.0f , -242.0f };
	Position.Z = GlobalUtils::CalculateFixDepth(EHOUSEDEPTH::FRAME);
	Object->Transform.SetLocalPosition(Position);
	Object->SetPixelCollision("UpFloor_PixelMap.png");
	PixelVec.push_back(Object);
}


#pragma endregion 

void BackDrop_WitchHouse_UpFloor::LoadPortalActor(GameEngineLevel* _Level)
{
	float4 HWinScale = GlobalValue::GetWindowScale().Half();

	{
		std::shared_ptr<PortalObject> Object = _Level->CreateActor<PortalObject>(EUPDATEORDER::Portal);
		Object->CreatePortalCollision(ECOLLISION::Portal);
		Object->SetChangeLevelName("WitchHouse_Yard");
		Object->SetCollisionRange({ 60.0f , 10.0f });
		Object->SetLocalPosition(HouseLocation  + float4{ 126.0f , -336.0f });
		Object->SetCollisionType(ColType::AABBBOX2D);
	}
}

void BackDrop_WitchHouse_UpFloor::LiftSetting()
{
	{
		const float4& LiftPosition = HouseLocation  + float4{ 174.0f , -184.0f };

		std::weak_ptr<UpperLift> Object = GetLevel()->CreateActor<UpperLift>(EUPDATEORDER::Entity);
		Object.lock()->Transform.SetLocalPosition(LiftPosition);
		Object.lock()->Init();
	}
}

void BackDrop_WitchHouse_UpFloor::BedSetting()
{
	{
		const float4& LiftPosition = HouseLocation  + float4{ 49.0f , -192.0f };

		std::weak_ptr<WitchHouseBed> Object = GetLevel()->CreateActor<WitchHouseBed>(EUPDATEORDER::Entity);
		Object.lock()->Transform.SetLocalPosition(LiftPosition);
	}
}



void BackDrop_WitchHouse_UpFloor::DustEventSetting()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\PlayContents\\WitchHouse_UpFloor\\HouseDust");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (GameEngineFile& pFile : Files)
	{
		GameEngineSprite::CreateSingle(pFile.GetFileName());
	}

	{
		const float4& DustPosition = float4(370.0f, -320.0f);
		std::weak_ptr<Dust_HandBook> DustHandBook = GetLevel()->CreateActor<Dust_HandBook>(EUPDATEORDER::Entity);
		DustHandBook.lock()->Transform.SetLocalPosition(DustPosition);
		DustHandBook.lock()->Init("WitchHouse_Dust_10.png");
		DustHandBook.lock()->AddDepth(-2.0f);
	}

	{
		const float4& DustPosition = float4(445.0f, -241.0f);
		std::weak_ptr<Dust_Bag> DustHandBook = GetLevel()->CreateActor<Dust_Bag>(EUPDATEORDER::Entity);
		DustHandBook.lock()->Transform.SetLocalPosition(DustPosition);
		DustHandBook.lock()->Init("WitchHouse_Dust_11.png");
		DustHandBook.lock()->AddDepth(-1.0f);
	}

	{
		const float4& DustPosition = float4(510.0f, -240.0f);
		std::weak_ptr<Dust_Elevator> DustElevator = GetLevel()->CreateActor<Dust_Elevator>(EUPDATEORDER::Entity);
		DustElevator.lock()->Transform.SetLocalPosition(DustPosition);
		DustElevator.lock()->Init("paper.png", true);
	}
}

void BackDrop_WitchHouse_UpFloor::CheckHouseDustEvent()
{
	std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("House_Dust");
	if (true == Quest.expired())
	{
		MsgBoxAssert("생성되지 않은 퀘스트입니다.");
		return;
	}

	if (Quest.lock()->CheckPrerequisiteQuest())
	{
		ShowHouseDustEvent();
		Quest.lock()->QuestComplete();
	}
}

void BackDrop_WitchHouse_UpFloor::ShowHouseDustEvent()
{
	std::weak_ptr<HouseDustEvent> HouseDust = GetLevel()->CreateActor<HouseDustEvent>(EUPDATEORDER::Entity);
	HouseDust.lock()->Init();
}