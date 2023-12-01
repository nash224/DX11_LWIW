#include "PreCompile.h"
#include "BackDrop_WitchHouse_Yard.h"

#include "PlayLevel.h"
#include "TimeManager.h"
#include "UIManager.h"

#include "ContentsEvent.h"
#include "CrowEvent.h"
#include "InteractiveLetter.h"

#include "Dian.h"
#include "GroundRenderUnit.h"
#include "NormalProp.h"
#include "PortalObject.h"
#include "WitchHouse.h"



BackDrop_WitchHouse_Yard::BackDrop_WitchHouse_Yard() 
{
	BackScale = GlobalValue::GetWindowScale();
}

BackDrop_WitchHouse_Yard::~BackDrop_WitchHouse_Yard() 
{
}

void BackDrop_WitchHouse_Yard::LevelStart(class GameEngineLevel* _NextLevel)
{
	MainBackDrop = this;
	RenewMap();
}


void BackDrop_WitchHouse_Yard::LevelEnd(class GameEngineLevel* _NextLevel)
{
	ReleaseYardSprite();
}



void BackDrop_WitchHouse_Yard::RenewMap()
{
	MainBackDrop = this;

	LoadSprite();

	CreateBase();
	LoadSerBin();
	CreateHouse();
	CreateNormalProp();
	CreatePortalActor();
	EventSetting();
}

void BackDrop_WitchHouse_Yard::LoadSprite()
{
	if (nullptr == GameEngineSprite::Find("WitchHouse_Base.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\PlayContents\\WitchHouse_Yard\\YardSingle");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pFile : Files)
		{
			GameEngineSprite::CreateSingle(pFile.GetFileName());
		}
	}
}

#pragma region MapLoad

void BackDrop_WitchHouse_Yard::LoadSerBin()
{
	{
		GameEngineSerializer LoadBin;

		GameEngineFile File;
		File.MoveParentToExistsChild("Resources");
		File.MoveChild("Resources\\Data\\Yard\\Yard_Prop\\YardPropData.map");

		File.Open(FileOpenType::Read, FileDataType::Binary);
		File.DataAllRead(LoadBin);

		// 객체 수 읽어옴
		unsigned int ActorCount = 0;
		LoadBin >> ActorCount;

		for (unsigned int i = 0; i < ActorCount; i++)
		{
			std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>();
			Object->DeSerializer(LoadBin);
			PixelVec.push_back(Object);
		}
	}


	{
		GameEngineSerializer LoadBin;

		GameEngineFile File;
		File.MoveParentToExistsChild("Resources");
		File.MoveChild("Resources\\Data\\Yard\\Yard_Grass\\SaveYardGrassThis.map");

		File.Open(FileOpenType::Read, FileDataType::Binary);
		File.DataAllRead(LoadBin);

		// 객체 수 읽어옴
		unsigned int ActorCount = 0;
		LoadBin >> ActorCount;

		for (unsigned int i = 0; i < ActorCount; i++)
		{
			std::shared_ptr<GroundRenderUnit> Object = GetLevel()->CreateActor<GroundRenderUnit>();
			Object->DeSerializer(LoadBin);
		}
	}
}

void BackDrop_WitchHouse_Yard::CreateBase()
{
	{
		float4 CenterPosition = GlobalValue::GetWindowScale().Half();
		CenterPosition.Y *= -1.0f;
		CenterPosition.Z = DepthFunction::CalculateFixDepth(ERENDERDEPTH::Back_Paint);

		std::shared_ptr<GameEngineSpriteRenderer> Renderer = CreateComponent<GameEngineSpriteRenderer>();
		Renderer->Transform.SetLocalPosition(CenterPosition);
		Renderer->SetSprite("GroundBase.png");
		Renderer->SetImageScale(GlobalValue::GetWindowScale());
	}
}

#pragma endregion

#pragma region CreateProp

void BackDrop_WitchHouse_Yard::CreateNormalProp()
{
	{
		std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition({ 700.0f , -214.0f , DepthFunction::CalculateObjectDepth(BackScale.Y, -234.0f) });
		Object->Init();
		Object->m_Renderer->SetSprite("Yard_Pumpkins.png");
		Object->m_Renderer->Transform.SetLocalPosition(float4(0.0f, 10.0f));
	}

	{
		std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition({ 700.0f , -228.0f , DepthFunction::CalculateObjectDepth(BackScale.Y,-228.0f) });
		Object->Init();
		Object->m_Renderer->SetSprite("Yard_Stone_L_0.png");
		Object->SetPixelCollision("Yard_Stone_L_0_Pixel.png");
		PixelVec.push_back(Object);
	}

	{
		const float4& WinScale = GlobalValue::GetWindowScale();
		float4 Position = WinScale.Half();
		Position.Y *= -1.0f;

		std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(Position);
		Object->SetPixelCollision("Yard_Map_Pixel.png");
		PixelVec.push_back(Object);
	}
}

void BackDrop_WitchHouse_Yard::CreateHouse()
{
	std::shared_ptr<WitchHouse> Object = GetLevel()->CreateActor<WitchHouse>(EUPDATEORDER::Objects);
	Object->Init();

	{
		std::shared_ptr<NormalProp> PixelObject = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		PixelObject->Transform.SetLocalPosition(float4(BackScale.Half().X, -202.0f));
		PixelObject->SetPixelCollision("WitchHouse_Base_Pixel.png");
		PixelVec.push_back(PixelObject);
	}
}

#pragma endregion 

#pragma region CreatePortal

void BackDrop_WitchHouse_Yard::CreatePortalActor()
{
	float4 HWinScale = GlobalValue::GetWindowScale().Half();

	{
		std::shared_ptr<PortalObject> Object = GetLevel()->CreateActor<PortalObject>(EUPDATEORDER::Portal);
		Object->CreatePortalCollision(ECOLLISION::Portal);
		Object->SetChangeLevelName("WitchHouse_UpFloor");
		Object->SetLocalPosition({ 478.0f , -323.0f });
		Object->SetCollisionRange({ 60.0f , 4.0f });
		Object->SetCollisionType(ColType::AABBBOX2D);
	}


	{
		std::shared_ptr<PortalObject> Object = GetLevel()->CreateActor<PortalObject>(EUPDATEORDER::Portal);
		Object->CreatePortalCollision(ECOLLISION::Portal);
		Object->SetChangeLevelName("Field_Center");
		Object->SetLocalPosition({ HWinScale.X , -GlobalValue::GetWindowScale().Y });
		Object->SetCollisionRange({ 200.0f , 100.0f });
		Object->SetCollisionType(ColType::AABBBOX2D);
	}
}

#pragma endregion 

void BackDrop_WitchHouse_Yard::CreateDian()
{
	std::shared_ptr<Dian> Object = GetLevel()->CreateActor<Dian>(EUPDATEORDER::Entity);
	Object->Transform.SetLocalPosition({ 700.0f , -400.0f });
	Object->Init();
}



void BackDrop_WitchHouse_Yard::EventSetting()
{
	CheckLetterEvent();
	CheckDianSpawn();
	CheckCrowEvent();
}

void BackDrop_WitchHouse_Yard::CheckLetterEvent()
{
	std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("StartTraining");
	if (true == Quest.expired())
	{
		MsgBoxAssert("생성되지 않은 퀘스트입니다.");
		return;
	}

	if (false == Quest.lock()->IsQuestAccepted())
	{
		CreateLetter();
	}
}

void BackDrop_WitchHouse_Yard::CheckCrowEvent()
{
	const std::shared_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("Crow_Meet");
	if (nullptr == Quest)
	{
		MsgBoxAssert("생성되지 않은 퀘스트입니다.");
		return;
	}

	if (false == Quest->isQuestComplete())
	{
		if (Quest->CheckPrerequisiteQuest())
		{
			ShowCrowEvent();
			Quest->QuestComplete();
		}
	}
}

void BackDrop_WitchHouse_Yard::CheckDianSpawn()
{
	const std::shared_ptr<ContentsEvent::QuestUnitBase>& Quest = ContentsEvent::FindQuest("Crow_Meet");
	if (nullptr == Quest)
	{
		MsgBoxAssert("생성되지 않은 퀘스트입니다.");
		return;
	}

	if (true == Quest->isQuestComplete())
	{
		const std::shared_ptr<ContentsEvent::Crow_Meet>& CastedQuest = Quest->Get_DynamicCast_This<ContentsEvent::Crow_Meet>();
		if (nullptr == PlayLevel::s_TimeManager)
		{
			MsgBoxAssert("타임 매니저가 존재하지 않는데 참조하려 했습니다.");
			return;
		}

		const int CurDayCount = PlayLevel::s_TimeManager->GetDayCount();
		const int EventViewDayCount = CastedQuest->GetEventDay();
		if (EventViewDayCount < CurDayCount)
		{
			const int CurHour = PlayLevel::s_TimeManager->GetHour();
			if (CurHour < 19)
			{
				CreateDian();
			}
		}
	}
}



void BackDrop_WitchHouse_Yard::CreateLetter()
{
	std::weak_ptr<InteractiveLetter> Letter = GetLevel()->CreateActor<InteractiveLetter>(EUPDATEORDER::Entity); 
	Letter.lock()->Transform.SetLocalPosition(float4(262.0f, -144.0f));
	Letter.lock()->Init();
}

void BackDrop_WitchHouse_Yard::ShowCrowEvent()
{
	std::shared_ptr<CrowEvent> Event = GetLevel()->CreateActor<CrowEvent>(EUPDATEORDER::Event);
	Event->Init();
}


void BackDrop_WitchHouse_Yard::ReleaseYardSprite()
{
	if (nullptr != GameEngineSprite::Find("WitchHouse_Base.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\PlayContents\\WitchHouse_Yard\\YardSingle");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pFile : Files)
		{
			GameEngineSprite::Release(pFile.GetFileName());
		}
	}
}