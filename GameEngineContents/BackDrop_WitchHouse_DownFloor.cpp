#include "PreCompile.h"
#include "BackDrop_WitchHouse_DownFloor.h"

#include "NormalProp.h"
#include "RendererActor.h"

#include "AlchemyPot.h"
#include "Extractor.h"
#include "Roaster.h"
#include "LowerLift.h"
#include "BaseLift.h"

#include "Dust_Pot.h"
#include "Dust_Extractor.h"

#include "ContentsEvent.h"
#include "WorkplaceFindEvent.h"


BackDrop_WitchHouse_DownFloor::BackDrop_WitchHouse_DownFloor() 
{
	BackDrop_PlayLevel::m_BackScale = GlobalValue::GetWindowScale();
}

BackDrop_WitchHouse_DownFloor::~BackDrop_WitchHouse_DownFloor() 
{
}

void BackDrop_WitchHouse_DownFloor::Start()
{
	DustEventSetting();
	
	BackDrop_PlayLevel::CreateItem("MapleHerb_Water", float4(670.0f , -260.0f), 1);
	BackDrop_PlayLevel::CreateItem("Mongsiri_Water", float4(450.0f, -250.0f), 1);
	BackDrop_PlayLevel::CreateItem("Mongsiri_Water", float4(670.0f, -430.0f), 1);
	BackDrop_PlayLevel::CreateItem("WitchFlower_Water", float4(450.0f, -430.0f), 1);
}

void BackDrop_WitchHouse_DownFloor::LevelStart(class GameEngineLevel* _NextLevel)
{
	BackDrop_PlayLevel::MainBackDrop = this;
}

void BackDrop_WitchHouse_DownFloor::LevelEnd(class GameEngineLevel* _NextLevel)
{
	BackDrop_PlayLevel::LevelEnd(_NextLevel);


	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\PlayContents\\WitchHouse_DownFloor\\DownSingle");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineFile pFile = Files[i];
		GameEngineSprite::Release(pFile.GetFileName());
	}
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void BackDrop_WitchHouse_DownFloor::Init()
{
	BackDrop_PlayLevel::MainBackDrop = this;


	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\PlayContents\\WitchHouse_DownFloor\\DownSingle");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (GameEngineFile& pFile: Files)
	{
		GameEngineSprite::CreateSingle(pFile.GetFileName());
	}

	CreateProp();
	CreatePixelMap();
	CreateStaticActor();

	CheckFindWorkPlaceEvent();
}


#pragma endregion 

#pragma region CreateProp

void BackDrop_WitchHouse_DownFloor::CreateProp()
{
	{
		float Depth = DepthFunction::CalculateFixDepth(EHOUSEDEPTH::BackPaint);

		const float4& HWinScale = GlobalValue::GetWindowScale().Half();
		const float4& Position = float4(HWinScale.X, HWinScale.Y * -1.0f, Depth);

		std::shared_ptr<RendererActor> Object = GetLevel()->CreateActor<RendererActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Back.png");
		Object->m_Renderer->GetImageTransform().SetLocalScale(GlobalValue::GetWindowScale());
	}


	{
		const float4& Position = HousePoint + float4( 349.0f , -315.0f );
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Floor.png", Position, static_cast<int>(EHOUSEDEPTH::HouseComposition));
	}

	{
		const float4& Position = HousePoint + float4(350.0f, -191.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Wall.png", Position, static_cast<int>(EHOUSEDEPTH::Wall));
	}

	{
		const float4& Position = HousePoint + float4(617.0f, -349.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Desk.png", Position, static_cast<int>(EHOUSEDEPTH::Object), false);
	}

	{
		const float4& Position = HousePoint + float4(254.0f , -469.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Candle.png", Position, static_cast<int>(EHOUSEDEPTH::Object), false, -15.0f);
	}

	{
		const float4& Position = HousePoint + float4(45.0f, -134.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Candle.png", Position, static_cast<int>(EHOUSEDEPTH::Object), false, -20.0f);
	}

	{
		const float4& Position = HousePoint + float4(198.0f, -63.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_PhotoFrame_5.png", Position, static_cast<int>(EHOUSEDEPTH::Object), false);
	}

	{
		const float4& Position = HousePoint + float4(177.0f, -37.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_PhotoFrame_2.png", Position, static_cast<int>(EHOUSEDEPTH::Object), false);
	}

	{
		const float4& Position = HousePoint + float4(157.0f, -65.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Paper_2.png", Position, static_cast<int>(EHOUSEDEPTH::Object), false);
	}

	{
		const float4& Position = HousePoint + float4(221.0f, -38.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Paper_2.png", Position, static_cast<int>(EHOUSEDEPTH::Object), false);
	}

	{
		const float4& Position = HousePoint + float4(120.0f, -52.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Paper_1.png", Position, static_cast<int>(EHOUSEDEPTH::Object), false);
	}

	{
		const float4& Position = HousePoint + float4(73.0f, -41.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Paper_1.png", Position, static_cast<int>(EHOUSEDEPTH::Object), false);
	}

	{
		const float4& Position = HousePoint + float4(616.0f, -272.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Paper_1.png", Position, static_cast<int>(EHOUSEDEPTH::Object), false);
	}

	{
		const float4& Position = HousePoint + float4(399.0f, -159.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "Ev_Enter_1.png", Position, static_cast<int>(EHOUSEDEPTH::Rug));
	}

	{
		const float4& Position = HousePoint + float4(398.0f, -164.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "Ev_Enter_2.png", Position, static_cast<int>(EHOUSEDEPTH::Rug));
	}

	{
		const float4& Position = HousePoint + float4(201.0f, -167.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Chair_0.png", Position, static_cast<int>(EHOUSEDEPTH::Object), false);
	}

	{
		const float4& Position = HousePoint + float4(48.0f, -147.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Chair_0.png", Position, static_cast<int>(EHOUSEDEPTH::Object), false);
	}

	{
		const float4& Position = HousePoint + float4(205.0f, -197.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Chair_1.png", Position, static_cast<int>(EHOUSEDEPTH::Object), false);
	}

	{
		const float4& Position = HousePoint + float4(168.0f, -268.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "Prop_DownFloor_Potion_1.png", Position, static_cast<int>(EHOUSEDEPTH::Object), false);
	}

	{
		const float4& Position = HousePoint + float4(92.0f, -247.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "ToolBox.png", Position, static_cast<int>(EHOUSEDEPTH::Object), false);
	}

	{
		const float4& Position = HousePoint + float4(143.0f, -260.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "Prop_DownFloor_Potion_0.png", Position, static_cast<int>(EHOUSEDEPTH::Object), false);
	}

	{
		const float4& Position = HousePoint + float4(408.0f, -394.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "PotBook.png", Position, static_cast<int>(EHOUSEDEPTH::Object), false);
	}

	{
		const float4& Position = HousePoint + float4(223.0f, -474.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Books_0.png", Position, static_cast<int>(EHOUSEDEPTH::Object), false);
	}

	{
		const float4& Position = HousePoint + float4(451.0f, -186.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Books_6.png", Position, static_cast<int>(EHOUSEDEPTH::Object), false, -12.0f);
	}

	{
		const float4& Position = HousePoint + float4(229.0f, -141.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Handrail_2.png", Position, static_cast<int>(EHOUSEDEPTH::Object), false, 30.0f);
	}

	{
		const float4& Position = HousePoint + float4(215.0f, -331.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Handrail_1.png", Position, static_cast<int>(EHOUSEDEPTH::Object), false, -30.0f);
	}

	{
		const float4& Position = HousePoint + float4(75.0f, -269.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Handrail_0.png", Position, static_cast<int>(EHOUSEDEPTH::Object), false, -20.0f);
	}

	{
		const float4& Position = HousePoint + float4(455.0f, -195.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Chair_1.png", Position, static_cast<int>(EHOUSEDEPTH::Object), false);
	}

	{
		const float4& Position = HousePoint + float4(26.0f, -203.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Cabinet.png", Position, static_cast<int>(EHOUSEDEPTH::Object), false);
	}

	{
		const float4& Position = HousePoint + float4(521.0f, -132.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Cabinet_0.png", Position, static_cast<int>(EHOUSEDEPTH::Object), false);
	}

	{
		const float4& Position = HousePoint + float4(113.0f, -127.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Locker.png", Position, static_cast<int>(EHOUSEDEPTH::Object), false);
	}

	{
		const float4& Position = HousePoint + float4(189.0f, -119.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Locker_1.png", Position, static_cast<int>(EHOUSEDEPTH::Object), false);
	}

	{
		const float4& Position = HousePoint + float4(254.0f, -481.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Books_3.png", Position, static_cast<int>(EHOUSEDEPTH::Object), false);
	}

	{
		const float4& Position = HousePoint + float4(191.0f, -476.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Books_7.png", Position, static_cast<int>(EHOUSEDEPTH::Object), false);
	}

	{
		const float4& Position = HousePoint + float4(67.0f, -197.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Books_2.png", Position, static_cast<int>(EHOUSEDEPTH::UnderBook));
	}

	{
		const float4& Position = HousePoint + float4(641.0f, -485.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Drawer_1.png", Position, static_cast<int>(EHOUSEDEPTH::Object), false , -20.0f);
	}

	{
		const float4& Position = HousePoint + float4(544.0f, -476.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Drawer_0.png", Position, static_cast<int>(EHOUSEDEPTH::Object), false , -20.0f);
	}

	{
		const float4& Position = HousePoint + float4(130.0f, -179.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Carpet.png", Position, static_cast<int>(EHOUSEDEPTH::Rug));
	}

	{
		const float4& Position = HousePoint + float4(580.0f, -184.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Books_5.png", Position, static_cast<int>(EHOUSEDEPTH::Object), false);
	}

	{
		const float4& Position = HousePoint + float4(409.0f, -325.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "WitchHouse_PotBase_MagicCircle_2.png", Position, static_cast<int>(EHOUSEDEPTH::Sign));
	}

	{
		const float4& Position = HousePoint + float4(409.0f, -325.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "WitchHouse_PotBase_MagicCircle_1.png", Position, static_cast<int>(EHOUSEDEPTH::Sign));
	}

	{
		const float4& Position = HousePoint + float4(409.0f, -325.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "PotBase_MagicCircle_0.png", Position, static_cast<int>(EHOUSEDEPTH::Sign));
	}

	{
		const float4& Position = HousePoint + float4(68.0f, -205.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Books_Shadow_2.png", Position, static_cast<int>(EHOUSEDEPTH::Shadow));
	}

	{
		const float4& Position = HousePoint + float4(205.0f, -211.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Chair_Shadow.png", Position, static_cast<int>(EHOUSEDEPTH::Shadow));
	}

	{
		const float4& Position = HousePoint + float4(455.0f, -209.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Chair_Shadow.png", Position, static_cast<int>(EHOUSEDEPTH::Shadow));
	}

	{
		const float4& Position = HousePoint + float4(130.0f, -181.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Chair_Shadow.png", Position, static_cast<int>(EHOUSEDEPTH::Shadow));
	}

	{
		const float4& Position = HousePoint + float4(617.0f, -397.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Desk_Shadow.png", Position, static_cast<int>(EHOUSEDEPTH::Shadow));
	}

	{
		const float4& Position = HousePoint + float4(48.0f, -161.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Chair_Shadow.png", Position, static_cast<int>(EHOUSEDEPTH::Shadow));
	}

	{
		const float4& Position = HousePoint + float4(224.0f, -490.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Books_Shadow_0.png", Position, static_cast<int>(EHOUSEDEPTH::Shadow));
	}

	{
		const float4& Position = HousePoint + float4(409.0f, -325.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "PotBase.png", Position, static_cast<int>(EHOUSEDEPTH::Rug));
	}

	{
		const float4& Position = HousePoint + float4(350.0f, -255.0f);
		CreateRenderActor(static_cast<int>(EUPDATEORDER::Objects), "DownFloor_Frame.png", Position, static_cast<int>(EHOUSEDEPTH::FRAME));
	}
}

#pragma endregion 

#pragma region CreatePixelMap


void BackDrop_WitchHouse_DownFloor::CreatePixelMap()
{
	{
		float4 Position = HousePoint  + float4{ 350.0f , -306.0f };
		Position.Z = DepthFunction::CalculateFixDepth(EHOUSEDEPTH::FRAME);
		
		std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(Position);
		Object->SetPixelCollision("DownFloor_PixelMap.png");
		BackDrop_PlayLevel::PixelVec.push_back(Object);
	}
}


#pragma endregion 

void BackDrop_WitchHouse_DownFloor::CreateStaticActor()
{
	{
		float4 Position = float4(HousePoint  + float4(409.0f, -299.0f));
		Position.Z = DepthFunction::CalculateObjectDepth(m_BackScale.Y,Position.Y);

		std::shared_ptr<AlchemyPot> Object = GetLevel()->CreateActor<AlchemyPot>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();

		BackDrop_PlayLevel::PixelStaticEntityVec.push_back(Object);
	}

	{
		float4 Position = float4(HousePoint  + float4(296.0f, -186.0f));
		Position.Z = DepthFunction::CalculateObjectDepth(m_BackScale.Y,Position.Y);

		std::shared_ptr<Extractor> Object = GetLevel()->CreateActor<Extractor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(Position);
		
		BackDrop_PlayLevel::PixelStaticEntityVec.push_back(Object);
	}

	{
		std::shared_ptr<LowerLift> Object = GetLevel()->CreateActor<LowerLift>(EUPDATEORDER::Entity);
		Object->Transform.SetLocalPosition(float4(548.0f, -172.0f));
	}
}



void BackDrop_WitchHouse_DownFloor::CreateRenderActor(
	int _UpdateOrder, 
	std::string_view _SpriteName,
	const float4& _Position,
	int _DepthType, 
	bool _isFixDepth /*= true*/,
	float _DepthCorrection/*= 0.0f*/)
{
	float Depth = 0.0f;
	if (true == _isFixDepth)
	{
		Depth = DepthFunction::CalculateFixDepth(_DepthType);
	}
	else
	{
		Depth = DepthFunction::CalculateObjectDepth(m_BackScale.Y, _Position.Y + _DepthCorrection);
	}

	const float4 Position = float4(_Position.X, _Position.Y, Depth);

	std::shared_ptr<RendererActor> Object = GetLevel()->CreateActor<RendererActor>(_UpdateOrder);
	Object->Transform.SetLocalPosition(Position);
	Object->Init();
	Object->m_Renderer->SetSprite(_SpriteName);
}

void BackDrop_WitchHouse_DownFloor::DustEventSetting()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\PlayContents\\WitchHouse_DownFloor\\DownDust");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pFile : Files)
		{
			GameEngineSprite::CreateSingle(pFile.GetFileName());
		}
	}

	{
		const float4& DustPosition = float4(560.0f, -330.0f);
		std::weak_ptr<Dust_Pot> DustHandBook = GetLevel()->CreateActor<Dust_Pot>(EUPDATEORDER::Entity);
		DustHandBook.lock()->Transform.SetLocalPosition(DustPosition);
		DustHandBook.lock()->Init("WitchHouse_Dust_5.png");
		DustHandBook.lock()->AddDepth(-2.0f);
	}

	{
		const float4& DustPosition = float4(446.0f, -180.0f);
		std::weak_ptr<Dust_Extractor> DustHandBook = GetLevel()->CreateActor<Dust_Extractor>(EUPDATEORDER::Entity);
		DustHandBook.lock()->Transform.SetLocalPosition(DustPosition);
		DustHandBook.lock()->Init("WitchHouse_Dust_3.png");
		DustHandBook.lock()->AddDepth(-1.0f);
	}
}

void BackDrop_WitchHouse_DownFloor::CheckFindWorkPlaceEvent()
{
	std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("FindWorkPlace");
	if (true == Quest.expired())
	{
		MsgBoxAssert("생성되지 않은 퀘스트입니다.");
		return;
	}

	if (false == Quest.lock()->isQuestComplete())
	{
		ShowFindWorkPlaceEvent();
		Quest.lock()->QuestComplete();
	}
}

void BackDrop_WitchHouse_DownFloor::ShowFindWorkPlaceEvent()
{
	std::weak_ptr<WorkplaceFindEvent> Event = GetLevel()->CreateActor<WorkplaceFindEvent>(EUPDATEORDER::Entity);
	Event.lock()->Init();
}