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

void BackDrop_WitchHouse_Yard::Start()
{
	BackDrop_PlayLevel::Start();
}


void BackDrop_WitchHouse_Yard::LevelStart(class GameEngineLevel* _NextLevel)
{
	std::vector<GameEngineDirectory> Dirs = FileLoadFunction::GetAllDirInPath("Resources\\PlayContents\\WitchHouse_Yard");
	for (GameEngineDirectory& Dir : Dirs)
	{
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pFile : Files)
		{
			GameEngineTexture::Load(pFile.GetStringPath());
		}
	}

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

	RenewMap();
}


void BackDrop_WitchHouse_Yard::LevelEnd(class GameEngineLevel* _NextLevel)
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

	std::vector<GameEngineDirectory> Dirs = FileLoadFunction::GetAllDirInPath("Resources\\PlayContents\\WitchHouse_Yard");
	for (GameEngineDirectory& Dir : Dirs)
	{
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pFile : Files)
		{
			GameEngineTexture::Release(pFile.GetFileName());
		}
	}
}



void BackDrop_WitchHouse_Yard::RenewMap()
{
	CreateBase();
	LoadSerBin();
	CreateHouse();
	CreateNormalProp();
	CreatePortalActor();
	EventSetting();
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
			std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
			Object->DeSerializer(LoadBin);
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
			std::shared_ptr<GroundRenderUnit> Object = GetLevel()->CreateActor<GroundRenderUnit>(EUPDATEORDER::Objects);
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
		Object->Renderer->SetSprite("Yard_Pumpkins.png");
		Object->Renderer->Transform.SetLocalPosition(float4(0.0f, 10.0f));
	}

	{
		std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition({ 700.0f , -228.0f , DepthFunction::CalculateObjectDepth(BackScale.Y,-228.0f) });
		Object->Init();
		Object->Renderer->SetSprite("Yard_Stone_L_0.png");
		Object->SetPixelCollision("Yard_Stone_L_0_Pixel.png");
	}

	{
		float4 Position = GlobalValue::GetWindowScale().Half();
		Position.Y *= -1.0f;

		std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(Position);
		Object->SetPixelCollision("Yard_Map_Pixel.png");
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
	}
}

#pragma endregion 

#pragma region CreatePortal

void BackDrop_WitchHouse_Yard::CreatePortalActor()
{
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
		Object->SetLocalPosition({ GlobalValue::GetWindowScale().Half().X , -GlobalValue::GetWindowScale().Y });
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
	const std::shared_ptr<ContentsEvent::QuestUnitBase>& Quest = ContentsEvent::FindQuest("StartTraining");
	if (nullptr == Quest)
	{
		MsgBoxAssert("생성되지 않은 퀘스트입니다.");
		return;
	}

	if (false == Quest->IsQuestAccepted())
	{
		CreateLetter();
	}
}

void BackDrop_WitchHouse_Yard::CheckCrowEvent()
{
	const std::shared_ptr<ContentsEvent::QuestUnitBase>& Quest = ContentsEvent::FindQuest("Crow_Meet");
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
		if (nullptr == PlayLevel::GetTimeManager())
		{
			MsgBoxAssert("타임 매니저가 존재하지 않는데 참조하려 했습니다.");
			return;
		}

		const int CurDayCount = PlayLevel::GetTimeManager()->GetDayCount();
		const int EventViewDayCount = CastedQuest->GetEventDay();
		if (EventViewDayCount < CurDayCount)
		{
			const int CurHour = PlayLevel::GetTimeManager()->GetHour();
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