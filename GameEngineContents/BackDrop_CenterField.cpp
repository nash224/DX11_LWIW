#include "PreCompile.h"
#include "BackDrop_CenterField.h"

#include "GroundRenderUnit.h"
#include "NormalProp.h"
#include "PortalObject.h"

#include "MongSiri_Population.h"
#include "Bush.h"
#include "WitchFlower.h"
#include "SilverStarFlower.h"
#include "FlowerBird.h"
#include "BranchTree.h"
#include "Aurea.h"
#include "PumpkinTerrier.h"


BackDrop_CenterField::BackDrop_CenterField() 
{
}

BackDrop_CenterField::~BackDrop_CenterField() 
{
}


void BackDrop_CenterField::LevelStart(class GameEngineLevel* _NextLevel)
{
	BackDrop_PlayLevel::LevelStart(_NextLevel);

	SpriteFileLoad();
}

void BackDrop_CenterField::LevelEnd(class GameEngineLevel* _NextLevel)
{
	BackDrop_PlayLevel::LevelEnd(_NextLevel);


	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\PlayContents\\FieldCenter");
	const std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (GameEngineFile pFile : Files)
	{
		GameEngineSprite::Release(pFile.GetFileName());
	}
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void BackDrop_CenterField::Init()
{
	MainBackDrop = this;

	SpriteFileLoad();

	PixelVec.reserve(256);

	CreateMap();
	LoadSerBin();
	CreatePortalActor();


	GameEngineLevel* CurLevel = GetLevel();
	CreateAurea(CurLevel);

	static bool IsCreatedCreature = false;
	if (false == IsCreatedCreature)
	{
		CreateCreature(CurLevel);

		IsCreatedCreature = true;
	}

}

void BackDrop_CenterField::SpriteFileLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\PlayContents\\FieldCenter");
	const std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (GameEngineFile pFile : Files)
	{
		GameEngineSprite::CreateSingle(pFile.GetFileName());
	}
}

void BackDrop_CenterField::CreateMap()
{
	const std::int32_t GroupZero = 0;

	const std::shared_ptr<GameEngineTexture> MapTexture = GameEngineTexture::Find("CenterMap.png");
	const float4 MapScale = MapTexture->GetScale();

	m_BackScale = MapScale;
	

	{
		float4 MapPos = MapScale.Half();
		MapPos.Y *= -1.0f;
		MapPos.Z = GlobalUtils::CalculateFixDepth(ERENDERDEPTH::Cliff);

		std::shared_ptr<NormalProp> CenterMap = GetLevel()->CreateActor<NormalProp>(GroupZero);
		CenterMap->Transform.SetLocalPosition(MapPos);
		CenterMap->Init();
		CenterMap->m_Renderer->SetSprite("CenterMap.png");
		CenterMap->SetPixelCollision("CenterMap_Pixel.png");
		PixelVec.push_back(CenterMap);
	}

	{
		float4 BasePosition = MapScale.Half();
		BasePosition.Y *= -1.0f;
		BasePosition.Z = GlobalUtils::CalculateFixDepth(ERENDERDEPTH::Back_Paint);

		std::shared_ptr<NormalProp> BaseGorund = GetLevel()->CreateActor<NormalProp>(GroupZero);
		BaseGorund->Transform.SetLocalPosition(BasePosition);
		BaseGorund->Init();
		BaseGorund->m_Renderer->SetSprite("GroundBase.png");
		BaseGorund->m_Renderer->SetImageScale(m_BackScale);
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

		for (size_t i = 0; i < ActorCount; i++)
		{
			const std::shared_ptr<NormalProp>& Object = GetLevel()->CreateActor<NormalProp>();
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

		// °´Ã¼ ¼ö ÀÐ¾î¿È
		unsigned int ActorCount = 0;
		LoadBin >> ActorCount;

		for (size_t i = 0; i < ActorCount; i++)
		{
			std::shared_ptr<GroundRenderUnit> Object = GetLevel()->CreateActor<GroundRenderUnit>();
			Object->DeSerializer(LoadBin);
		}
	}
}


void BackDrop_CenterField::CreateAurea(GameEngineLevel* _Level)
{
	std::shared_ptr<Aurea> Object = _Level->CreateActor<Aurea>(EUPDATEORDER::Entity);
	float4 Position = float4(700.0f, -300.0f);
	Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y);
	Object->Transform.SetLocalPosition(Position);
	Object->Init();
}


// ³¯ÀÌ ¹Ù²î¸é »ý¼ºµË´Ï´Ù.
void BackDrop_CenterField::CreateCreature(GameEngineLevel* _Level)
{
	CreateDayNightTimeCreature(_Level);
	CreateDayTimeCreature(_Level);
}

void BackDrop_CenterField::CreateDayNightTimeCreature(GameEngineLevel* _Level)
{
	CreateBush(_Level);
	CreateWitchFlower(_Level);
	CreateSilverStarFlower(_Level);
	CreateBranchTree(_Level);
	CreateFlowerBird(_Level);
	CreatePumpkinTerrier(_Level);
}


void BackDrop_CenterField::CreateDayTimeCreature(GameEngineLevel* _Level)
{
	/*CreateMongSiriPopulation(_Level);*/
}



void BackDrop_CenterField::CreateBush(GameEngineLevel* _Level)
{
	{
		std::shared_ptr<Bush> BushObject = _Level->CreateActor<Bush>(EUPDATEORDER::Entity);
		BushObject->Transform.SetLocalPosition({ 300.0f , -150.0f });
		BushObject->SetBushType(EBUSHTYPE::Bush);
		BushObject->Init();

		PixelStaticEntityVec.push_back(BushObject);
	}

	{
		std::shared_ptr<Bush> BushObject = _Level->CreateActor<Bush>(EUPDATEORDER::Entity);
		BushObject->Transform.SetLocalPosition({ 400.0f , -150.0f });
		BushObject->SetBushType(EBUSHTYPE::BushApple);
		BushObject->Init();

		PixelStaticEntityVec.push_back(BushObject);
	}

	{
		std::shared_ptr<Bush> BushObject = _Level->CreateActor<Bush>(EUPDATEORDER::Entity);
		BushObject->Transform.SetLocalPosition({ 500.0f , -150.0f });
		BushObject->SetBushType(EBUSHTYPE::BushBug);
		BushObject->Init();

		PixelStaticEntityVec.push_back(BushObject);
	}
}

void BackDrop_CenterField::CreateWitchFlower(GameEngineLevel* _Level)
{
	{
		std::shared_ptr<WitchFlower> Object = _Level->CreateActor<WitchFlower>(EUPDATEORDER::Entity);
		Object->Transform.SetLocalPosition({ 300.0f , -350.0f });
		Object->Init();
	}
}

void BackDrop_CenterField::CreateSilverStarFlower(GameEngineLevel* _Level)
{
	{
		std::shared_ptr<SilverStarFlower> Object = _Level->CreateActor<SilverStarFlower>(EUPDATEORDER::Entity);
		Object->Transform.SetLocalPosition({ 100.0f , -450.0f });
		Object->Init();
	}
}

void BackDrop_CenterField::CreateBranchTree(GameEngineLevel* _Level)
{
	{
		std::shared_ptr<BranchTree> Object = _Level->CreateActor<BranchTree>(EUPDATEORDER::Entity);
		Object->Transform.SetLocalPosition({ 500.0f , -550.0f });
		Object->Init();
	}
}


void BackDrop_CenterField::CreateMongSiriPopulation(GameEngineLevel* _Level)
{
	PopulationVec.reserve(3);

	{
		std::shared_ptr<MongSiri_Population> MongSiri1 = _Level->CreateActor<MongSiri_Population>(EUPDATEORDER::Objects);
		MongSiri1->Transform.SetLocalPosition({ 100.0f , -100.0f });
		MongSiri1->SetPopulationSpawnLocation({ 150.0f , -150.0f });
		MongSiri1->Init(3);
		PopulationVec.push_back(MongSiri1);
	}
}

void BackDrop_CenterField::CreateFlowerBird(GameEngineLevel* _Level)
{
	{
		std::shared_ptr<FlowerBird> Object = _Level->CreateActor<FlowerBird>(EUPDATEORDER::Entity);
		Object->Transform.SetLocalPosition({ 400.0f , -200.0f });
		Object->Init();
	}

	{
		std::shared_ptr<FlowerBird> Object = _Level->CreateActor<FlowerBird>(EUPDATEORDER::Entity);
		Object->Transform.SetLocalPosition({ 440.0f , -200.0f });
		Object->Init();
	}
}

void BackDrop_CenterField::CreatePumpkinTerrier(GameEngineLevel* _Level)
{
	{
		std::shared_ptr<PumpkinTerrier> Object = _Level->CreateActor<PumpkinTerrier>(EUPDATEORDER::Entity);
		Object->Transform.SetLocalPosition({ 360.0f , -400.0f });
		Object->Init();

	}
}


void BackDrop_CenterField::CreatePortalActor()
{
	{
		std::shared_ptr<PortalObject> Object = GetLevel()->CreateActor<PortalObject>(EUPDATEORDER::Portal);
		Object->CreatePortalCollision(ECOLLISION::Portal);
		Object->SetChangeLevelName("WitchHouse_Yard");
		Object->SetCollisionRange({ 100.0f , 400.0f });
		Object->SetLocalPosition({ 1200.0f , -200.0f });
		Object->SetCollisionType(ColType::AABBBOX2D);
	}
}



#pragma region Release


void BackDrop_CenterField::PopulationRelease()
{
	for (size_t i = 0; i < PopulationVec.size(); i++)
	{
		std::shared_ptr<MongSiri_Population> Population = PopulationVec[i];
		Population->ActorRelaese();
	}
}

#pragma endregion 