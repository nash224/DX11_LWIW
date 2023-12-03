#include "PreCompile.h"
#include "BackDrop_CenterField.h"

#include "ContentsEvent.h"
#include "FireWorksEvent.h"
#include "UI_Inventory.h"
#include "FadeObject.h"

#include "Aurea.h"
#include "BranchTree.h"
#include "Bush.h"
#include "FlowerBird.h"
#include "GroundRenderUnit.h"
#include "MongSiri_Population.h"
#include "NormalProp.h"
#include "SilverStarFlower.h"
#include "PumpkinTerrier.h"
#include "PortalObject.h"
#include "WitchFlower.h"


BackDrop_CenterField::BackDrop_CenterField() 
{
	BackDrop::BackScale = float4(1920.0f, 1280.0f);
}

BackDrop_CenterField::~BackDrop_CenterField() 
{
}

void BackDrop_CenterField::Start()
{
	BackDrop_Field::Start();
}

void BackDrop_CenterField::Update(float _Delta)
{
	BackDrop_Field::Update(_Delta);
}

void BackDrop_CenterField::LevelStart(class GameEngineLevel* _NextLevel)
{
	BackDrop_Field::LevelStart(_NextLevel);

	RenewMap();
	SpriteFileLoad();

	CheckFireWorksEvent();
}

void BackDrop_CenterField::LevelEnd(class GameEngineLevel* _NextLevel)
{
	BackDrop_Field::LevelEnd(_NextLevel);

	ReleaseSpriteFile();
}


void BackDrop_CenterField::RenewMap()
{
	SpriteFileLoad();

	BackDrop_PlayLevel::PixelVec.reserve(256);
	BackDrop_PlayLevel::PixelStaticEntityVec.reserve(32);

	NPCSetting();
	CreateMap();
	LoadSerBin();
	CreatePortalActor();

}

#pragma region SpriteFile

void BackDrop_CenterField::SpriteFileLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\PlayContents\\FieldCenter");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (GameEngineFile& pFile : Files)
	{
		GameEngineSprite::CreateSingle(pFile.GetFileName());
	}
}

void BackDrop_CenterField::ReleaseSpriteFile()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\PlayContents\\FieldCenter");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (GameEngineFile& pFile : Files)
	{
		GameEngineSprite::Release(pFile.GetFileName());
	}
}

#pragma endregion

#pragma region Map

void BackDrop_CenterField::CreateMap()
{
	{
		float4 MapPos = BackScale.Half();
		MapPos.Y *= -1.0f;
		MapPos.Z = DepthFunction::CalculateFixDepth(ERENDERDEPTH::Cliff);

		std::shared_ptr<NormalProp> CenterMap = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		CenterMap->Transform.SetLocalPosition(MapPos);
		CenterMap->Init();
		CenterMap->m_Renderer->SetSprite("CenterMap.png");
		CenterMap->SetPixelCollision("CenterMap_Pixel.png");
		PixelVec.push_back(CenterMap);
	}

	{
		float4 BasePosition = BackScale.Half();
		BasePosition.Y *= -1.0f;
		BasePosition.Z = DepthFunction::CalculateFixDepth(ERENDERDEPTH::Back_Paint);

		std::shared_ptr<RendererActor> BaseGorund = GetLevel()->CreateActor<RendererActor>(EUPDATEORDER::Objects);
		BaseGorund->Transform.SetLocalPosition(BasePosition);
		BaseGorund->Init();
		BaseGorund->m_Renderer->SetSprite("GroundBase.png");
		BaseGorund->m_Renderer->SetImageScale(BackScale);
	}
}


void BackDrop_CenterField::LoadSerBin()
{
	{
		GameEngineSerializer LoadBin;

		GameEngineFile File;
		File.MoveParentToExistsChild("Resources");
		File.MoveChild("Resources\\Data\\Field_Center\\Center_Prop\\CenterPropData.map");

		File.Open(FileOpenType::Read, FileDataType::Binary);
		File.DataAllRead(LoadBin);

		unsigned int ActorCount = 0;
		LoadBin >> ActorCount;

		for (unsigned int i = 0; i < ActorCount; i++)
		{
			const std::shared_ptr<NormalProp>& Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
			Object->DeSerializer(LoadBin);
			PixelVec.push_back(Object);
		}
	}


	{
		GameEngineSerializer LoadBin;

		GameEngineFile File;
		File.MoveParentToExistsChild("Resources");
		File.MoveChild("Resources\\Data\\Field_Center\\Center_Grass\\CenterGrassData.map");

		File.Open(FileOpenType::Read, FileDataType::Binary);
		File.DataAllRead(LoadBin);

		// 객체 수 읽어옴
		unsigned int ActorCount = 0;
		LoadBin >> ActorCount;

		for (unsigned int i = 0; i < ActorCount; i++)
		{
			std::shared_ptr<GroundRenderUnit> Object = GetLevel()->CreateActor<GroundRenderUnit>(EUPDATEORDER::Objects);
			Object->DeSerializer(LoadBin);
		}
	}
}

#pragma endregion


void BackDrop_CenterField::CreatePortalActor()
{
	{
		std::shared_ptr<PortalObject> Object = GetLevel()->CreateActor<PortalObject>(EUPDATEORDER::Portal);
		Object->CreatePortalCollision(ECOLLISION::Portal);
		Object->SetChangeLevelName("WitchHouse_Yard");
		Object->SetCollisionRange({ 100.0f , 50.0f });
		Object->SetLocalPosition({ 1432.0f , 0.0f });
		Object->SetCollisionType(ColType::AABBBOX2D);
	}
}

void BackDrop_CenterField::NPCSetting()
{
	const std::shared_ptr<ContentsEvent::QuestUnitBase>& Quest = ContentsEvent::FindQuest("Craft_Potion");
	if (nullptr == Quest)
	{
		MsgBoxAssert("생성되지 않은 퀘스트입니다.");
		return;
	}

	if (false == Quest->isQuestComplete())
	{
		return;
	}

	std::shared_ptr<Aurea> Npc_Aurea = GetLevel()->CreateActor<Aurea>(EUPDATEORDER::Entity);
	Npc_Aurea->Transform.SetLocalPosition(float4(940.0f, -235.0f));
	Npc_Aurea->Init();
}




void BackDrop_CenterField::CreateCreatureWhenDayChange()
{
	BackDrop_Field::CreateBush(float4(590.0f, -274.0f), EBUSHTYPE::BushBug);
	BackDrop_Field::CreateBush(float4(1244.0f, -1117.0f), EBUSHTYPE::BushApple);
	BackDrop_Field::CreateBush(float4(1374.0f, -723.0f), EBUSHTYPE::BushBug);
	BackDrop_Field::CreateBush(float4(1645.0f, -212.0f), EBUSHTYPE::BushApple);

	BackDrop_Field::CreateWitchFlower(float4(1652.0f, -165.0f));
	BackDrop_Field::CreateWitchFlower(float4(157.0f, -803.0f));
	BackDrop_Field::CreateWitchFlower(float4(614.0f, -406.0f));

	BackDrop_Field::CreateSilverStarFlower(float4(1248.0f, -170.0f));
	BackDrop_Field::CreateSilverStarFlower(float4(1150.0f, -1002.0f));
	BackDrop_Field::CreateSilverStarFlower(float4(1120.0f, -700.0f));
	BackDrop_Field::CreateSilverStarFlower(float4(1622.0f, -886.0f));

	BackDrop_Field::CreateBranchTree(float4(660.0f, -275.0f));
	BackDrop_Field::CreateBranchTree(float4(505.0f, -275.0f));
	BackDrop_Field::CreateBranchTree(float4(1350.0f, -1122.0f));
	BackDrop_Field::CreateBranchTree(float4(1630.0f, -856.0f));

	BackDrop_Field::CreateFlowerBird(float4(1323.0f, -265.0f));
	BackDrop_Field::CreateFlowerBird(float4(1440.0f, -313.0f));
	BackDrop_Field::CreateFlowerBird(float4(640.0f, -863.0f));
	BackDrop_Field::CreateFlowerBird(float4(775.0f, -908.0f));

	BackDrop_Field::CreateMongSiriPopulation(3, float4(1512.0f, -760.0f), float4(1458.0f, -828.0f));
	BackDrop_Field::CreateMongSiriPopulation(2, float4(173.0f, -705.0f), float4(280.0f, -767.0f));


	CreateItem("MapleHerb_Collect", float4(1100.0f, -760.0f));
	CreateItem("MapleHerb_Collect", float4(675.0f, -610.0f));
	CreateItem("MapleHerb_Collect", float4(310.0f, -260.0f));
}

void BackDrop_CenterField::DisappearDayCreature()
{
	LeavePopulation();
	LeaveFlowerBird();
}

void BackDrop_CenterField::AppearNightCreature()
{

}


void BackDrop_CenterField::ReleaseAllCreature()
{
	ReleaseEntity<Bush>();
	ReleaseEntity<WitchFlower>();
	ReleaseEntity<FlowerBird>();
	ReleaseEntity<SilverStarFlower>();
	ReleaseEntity<BranchTree>();

	ReleaseItemDrop();
	ReleaseMongSiriPopulation();

	PixelStaticEntityVec.clear();
}

void BackDrop_CenterField::CheckFireWorksEvent()
{
	if (true == UI_Inventory::IsItem("FirecrackerPotion"))
	{
		std::vector<std::shared_ptr<FadeObject>> FadeObjects = GetLevel()->GetObjectGroupConvert<FadeObject>(EUPDATEORDER::Fade);
		for (const std::shared_ptr<FadeObject>& Fade : FadeObjects)
		{
			Fade->Death();
		}

		ReleaseEntity<FlowerBird>();
		ReleaseMongSiriPopulation();
		ShowFireWorksEvent();
		return;
	}
}

void BackDrop_CenterField::ShowFireWorksEvent()
{
	std::shared_ptr<FireWorksEvent> Event = GetLevel()->CreateActor<FireWorksEvent>(EUPDATEORDER::Event);
	Event->Transform.SetLocalPosition(float4(734.0f, -918.0f));
	Event->Init();
}