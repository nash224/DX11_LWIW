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

#include "UpperLiftA.h"
#include "WitchHouseBed.h"
#include "WitchHouseLight.h"


BackDrop_WitchHouse_UpFloor::BackDrop_WitchHouse_UpFloor() 
{
	BackScale = GlobalValue::GetWindowScale();
}

BackDrop_WitchHouse_UpFloor::~BackDrop_WitchHouse_UpFloor() 
{
}

void BackDrop_WitchHouse_UpFloor::Start()
{
	BackDrop_PlayLevel::Start();
	DustEventSetting();
}


void BackDrop_WitchHouse_UpFloor::LevelStart(class GameEngineLevel* _NextLevel)
{
	BackDrop_PlayLevel::LevelStart(_NextLevel);

	RenewMap();
}

void BackDrop_WitchHouse_UpFloor::LevelEnd(class GameEngineLevel* _NextLevel)
{
	ReleaseResources();
}


void BackDrop_WitchHouse_UpFloor::RenewMap()
{
	LoadResources();

	CreateProp();
	HouseLightSetting();
	CreatePixelMap();
	LoadPortalActor();
	LiftSetting();
	BedSetting();

	CheckHouseDustEvent();
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
void BackDrop_WitchHouse_UpFloor::CreateProp()
{
	float4 RYWinScale = GlobalValue::GetWindowScale().Half();
	RYWinScale.Y *= -1.0f;

	{
		const float4& Position = float4{ RYWinScale.X, RYWinScale.Y, DepthFunction::CalculateFixDepth(EHOUSEDEPTH::BackPaint) };
		std::shared_ptr<RendererActor> Object = GetLevel()->CreateActor<RendererActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_Back.png");
		Object->m_Renderer->GetImageTransform().SetLocalScale(float4(GlobalValue::GetWindowScale()));
	}

	{
		std::shared_ptr<RendererActor> Object = GetLevel()->CreateActor<RendererActor>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 174.0f , -79.0f };
		Position.Z = DepthFunction::CalculateFixDepth(EHOUSEDEPTH::BackWindow);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_Circle.png");
		Object->m_Renderer->GetImageTransform().SetLocalScale(float4(64.0f, 64.0f));
	}

	{
		std::shared_ptr<RendererActor> Object = GetLevel()->CreateActor<RendererActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(HouseLocation  + float4{ 126.0f , -238.0f, DepthFunction::CalculateFixDepth(EHOUSEDEPTH::HouseComposition) });
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_Floor.png");
	}

	{
		const float4& Position = HouseLocation  + float4{ 174.0f , -78.0f, DepthFunction::CalculateFixDepth(EHOUSEDEPTH::HouseComposition) };

		std::shared_ptr<RendererActor> Object = GetLevel()->CreateActor<RendererActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_WallPaper_1.png");
	}

	{
		std::shared_ptr<RendererActor> Object = GetLevel()->CreateActor<RendererActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(HouseLocation  + float4{ 126.0f , -110.0f, DepthFunction::CalculateFixDepth(EHOUSEDEPTH::HouseComposition) });
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_WallPaper.png");
	}



	{
		std::shared_ptr<RendererActor> Object = GetLevel()->CreateActor<RendererActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(HouseLocation  + float4{ 126.0f , -177.0f, DepthFunction::CalculateFixDepth(EHOUSEDEPTH::Shadow )});
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_Shadow.png");
	}

	{
		std::shared_ptr<RendererActor> Object = GetLevel()->CreateActor<RendererActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(HouseLocation  + float4{ 124.0f , -305.0f, DepthFunction::CalculateFixDepth(EHOUSEDEPTH::Rug) });
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_Carpet_0.png");
	}

	{
		std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 228.0f , -163.0f };
		Position.Z = DepthFunction::CalculateObjectDepth(BackScale.Y, Position.Y - 70.0f );
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_Cabinet.png");
	}

	{
		std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 175.0f , -76.0f };
		Position.Z = DepthFunction::CalculateFixDepth(EHOUSEDEPTH::Rug);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_window.png");
	}

	{
		std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 49.0f , -192.0f };
		Position.Z = DepthFunction::CalculateObjectDepth(BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_bed.png");
	}

	{
		std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 104.0f , -106.0f };
		Position.Z = DepthFunction::CalculateFixDepth(EHOUSEDEPTH::Rug);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("book_shelf_empty.png");
	}

	{
		std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 174.0f , -175.0f };
		Position.Z = DepthFunction::CalculateFixDepth(EHOUSEDEPTH::Rug);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_Carpet_1.png");
	}

	{
		std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 174.0f , -51.0f };
		Position.Z = DepthFunction::CalculateObjectDepth(BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_plants.png");
	}

	{
		std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 33.0f , -285.0f };
		Position.Z = DepthFunction::CalculateObjectDepth(BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_drawer_under.png");
	}

	{
		std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 175.0f , -145.0f };
		Position.Z = DepthFunction::CalculateFixDepth(EHOUSEDEPTH::Chair);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_Chair.png");
	}

	{
		std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 174.0f , -149.0f };
		Position.Z = DepthFunction::CalculateFixDepth(EHOUSEDEPTH::Shadow);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("Chair_Shadow.png");
	}

	{
		std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 174.0f , -127.0f };
		Position.Z = DepthFunction::CalculateObjectDepth(BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_desk.png");
	}

	{
		std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 101.0f , -151.0f };
		Position.Z = DepthFunction::CalculateObjectDepth(BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("hanger.png");
	}

	{
		std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 14.0f , -259.0f };
		Position.Z = DepthFunction::CalculateObjectDepth(BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("PhotoFrame_0.png");
	}


	{
		std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 27.0f , -275.0f };
		Position.Z = DepthFunction::CalculateObjectDepth(BackScale.Y, Position.Y - 14.0f);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("SaveProp.png");
	}

	{
		std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 117.0f , -84.0f };
		Position.Z = DepthFunction::CalculateObjectDepth(BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_Flower_0.png");
	}

	{
		std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 90.0f , -85.0f };
		Position.Z = DepthFunction::CalculateObjectDepth(BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_Flower_1.png");
	}

	{
		std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 113.0f , -168.0f };
		Position.Z = DepthFunction::CalculateObjectDepth(BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_bag.png");
	}

	{
		std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 175.0f , -127.0f };
		Position.Z = DepthFunction::CalculateObjectDepth(BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("book_open.png");
	}

	{
		std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 32.0f , -116.0f };
		Position.Z = DepthFunction::CalculateObjectDepth(BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DreamCapture.png");
	}

	{
		std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 58.0f , -119.0f };
		Position.Z = DepthFunction::CalculateObjectDepth(BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_PhotoFrame_1.png");
	}

	{
		std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 58.0f , -98.0f };
		Position.Z = DepthFunction::CalculateObjectDepth(BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_PhotoFrame_2.png");
	}

	{
		std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 98.0f , -126.0f };
		Position.Z = DepthFunction::CalculateObjectDepth(BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("hanger_light.png");
	}

	{
		std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = HouseLocation  + float4{ 58.0f , -75.0f };
		Position.Z = DepthFunction::CalculateFixDepth(EHOUSEDEPTH::Rug);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("book_shelf.png");
	}

	{
		float4 Position = GlobalValue::GetWindowScale().Half();
		Position.Y *= -1.0f;
		const std::shared_ptr<RendererActor>& Ceil 
			= BackDrop_PlayLevel::CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "UpFloor_Frame.png", Position, static_cast<int>(EHOUSEDEPTH::FRAME));
		Ceil->m_Renderer->SetViewCameraSelect(static_cast<int>(ECAMERAORDER::MainNext));
	}
}

#pragma endregion 

void BackDrop_WitchHouse_UpFloor::HouseLightSetting()
{
	{
		std::shared_ptr<WitchHouseLight> Light = GetLevel()->CreateActor<WitchHouseLight>(EUPDATEORDER::Objects);
		Light->Transform.SetLocalPosition(float4(516.0f, -165.0f, -2000.0f));
		Light->Transform.SetLocalScale(float4(0.25f, 0.25f, 1.0f));
		Light->Init("EllieHouse_Light_2.png");
	}

	{
		std::shared_ptr<WitchHouseLight> Light = GetLevel()->CreateActor<WitchHouseLight>(EUPDATEORDER::Objects);
		Light->Transform.SetLocalPosition(float4(374.0f, -304.0f, -2000.0f));
		Light->Transform.SetLocalScale(float4(0.25f, 0.25f, 1.0f));
		Light->Init("EllieHouse_Light_0.png");
	}

	{
		std::shared_ptr<WitchHouseLight> Light = GetLevel()->CreateActor<WitchHouseLight>(EUPDATEORDER::Objects);
		Light->Transform.SetLocalPosition(float4(514.0f, -264.0f, -2000.0f));
		Light->Transform.SetLocalScale(float4(0.25f, 0.25f, 1.0f));
		Light->Init("EllieHouse_Light_1.png");
	}
}


void BackDrop_WitchHouse_UpFloor::CreatePixelMap()
{
	std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
	float4 Position = HouseLocation  + float4{ 128.0f , -242.0f };
	Object->Transform.SetLocalPosition(Position);
	Object->SetPixelCollision("UpFloor_PixelMap.png");
}


void BackDrop_WitchHouse_UpFloor::LoadPortalActor()
{
	std::shared_ptr<PortalObject> Object = GetLevel()->CreateActor<PortalObject>(EUPDATEORDER::Portal);
	Object->CreatePortalCollision(ECOLLISION::Portal);
	Object->SetChangeLevelName("WitchHouse_Yard");
	Object->SetCollisionRange({ 60.0f , 10.0f });
	Object->SetLocalPosition(HouseLocation  + float4{ 126.0f , -336.0f });
	Object->SetCollisionType(ColType::AABBBOX2D);
}

void BackDrop_WitchHouse_UpFloor::LiftSetting()
{
	std::shared_ptr<UpperLiftA> Lift = GetLevel()->CreateActor<UpperLiftA>(EUPDATEORDER::Entity);
	Lift->Transform.SetLocalPosition(float4(513.0f, -242.0f));
	Lift->Init();
	
	if (PlayLevel::GetCurLevel()->GetPrevLevelName() == "WitchHouse_DownFloor")
	{
		Lift->LiftToArrive();
	}
}

void BackDrop_WitchHouse_UpFloor::BedSetting()
{
	std::shared_ptr<WitchHouseBed> Object = GetLevel()->CreateActor<WitchHouseBed>(EUPDATEORDER::Entity);
	Object->Transform.SetLocalPosition(HouseLocation + float4{ 49.0f , -192.0f });
}



void BackDrop_WitchHouse_UpFloor::DustEventSetting()
{
	FileLoadFunction::LoadTextureAndCreateSingleSpriteInPath("Resources\\PlayContents\\WitchHouse_UpFloor\\HouseDust");

	{
		std::shared_ptr<Dust_HandBook> DustHandBook = GetLevel()->CreateActor<Dust_HandBook>(EUPDATEORDER::Entity);
		DustHandBook->Transform.SetLocalPosition(float4(370.0f, -320.0f));
		DustHandBook->Init("WitchHouse_Dust_10.png");
		DustHandBook->AddDepth(-2.0f);
	}

	{
		std::shared_ptr<Dust_Bag> DustHandBook = GetLevel()->CreateActor<Dust_Bag>(EUPDATEORDER::Entity);
		DustHandBook->Transform.SetLocalPosition(float4(445.0f, -241.0f));
		DustHandBook->Init("WitchHouse_Dust_11.png");
		DustHandBook->AddDepth(-1.0f);
	}

	{
		std::shared_ptr<Dust_Elevator> DustElevator = GetLevel()->CreateActor<Dust_Elevator>(EUPDATEORDER::Entity);
		DustElevator->Transform.SetLocalPosition(float4(510.0f, -240.0f));
		DustElevator->Init("paper.png", true);
	}
}

void BackDrop_WitchHouse_UpFloor::CheckHouseDustEvent()
{
	const std::shared_ptr<ContentsEvent::QuestUnitBase>& Quest = ContentsEvent::FindQuest("House_Dust");
	if (nullptr == Quest)
	{
		MsgBoxAssert("생성되지 않은 퀘스트입니다.");
		return;
	}

	if (true == Quest->CheckPrerequisiteQuest())
	{
		ShowHouseDustEvent();
		Quest->QuestComplete();
	}
}

void BackDrop_WitchHouse_UpFloor::ShowHouseDustEvent()
{
	std::shared_ptr<HouseDustEvent> HouseDust = GetLevel()->CreateActor<HouseDustEvent>(EUPDATEORDER::Entity);
	HouseDust->Init();
}