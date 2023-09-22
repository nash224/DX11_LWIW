#include "PreCompile.h"
#include "BackDrop_MainMenu.h"

#include "GlobalUtils.h"

#include "Scenery.h"
#include "Prop.h"
#include "ChainProp.h"
#include "MainMenu_Trains.h"

BackDrop_MainMenu::BackDrop_MainMenu() 
{
}

BackDrop_MainMenu::~BackDrop_MainMenu() 
{
}


void BackDrop_MainMenu::Start()
{

}

void BackDrop_MainMenu::Update(float _Delta)
{
	
}

void BackDrop_MainMenu::Release()
{

}

void BackDrop_MainMenu::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void BackDrop_MainMenu::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void BackDrop_MainMenu::Init()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	CreateScenery(CurLevel);
	CreateProp(CurLevel);
	CreateTrain(CurLevel);
	CreateChainProp(CurLevel);

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("Title_Train_Sky.png");
	if (nullptr == Texture)
	{
		MsgBoxAssert("텍스처를 불러오지 못했습니다.");
		return;
	}

	m_BackScale = Texture->GetScale();
}


void BackDrop_MainMenu::CreateScenery(class GameEngineLevel* _CurLevel)
{

}

#pragma region Prop 생성

void BackDrop_MainMenu::CreateProp(class GameEngineLevel* _CurLevel)
{
	vecProps.reserve(30);

	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->CreateRenderer(ETITLERENDERORDER::Back_);
		Object->SetSprite("Title_Train_Sky.png");
		Object->SetPosition(float4::ZERO, PivotType::LeftTop);
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->CreateRenderer(ETITLERENDERORDER::Star);
		Object->CreateAutomatedAnimation("StarAni", "Title_train_star");
		Object->SetPosition(float4{ 20.0f , -100.0f }, PivotType::Left);
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->CreateRenderer(ETITLERENDERORDER::Water);
		Object->SetSprite("Title_Train_Water.png");
		Object->SetPosition(float4{ 0.0f , -398.0f }, PivotType::LeftTop);
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->CreateRenderer(ETITLERENDERORDER::Bridge_blur);
		Object->SetSprite("Title_Train_Bridge_Shadow.png");
		Object->SetPosition(float4{ 0.0f , -464.0f }, PivotType::LeftTop);
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->CreateRenderer(ETITLERENDERORDER::Train_blur);
		Object->SetSprite("Title_Train_TrainWater_blur.png");
		Object->SetPosition(float4{ 0.0f , -492.0f }, PivotType::LeftTop);
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->CreateRenderer(ETITLERENDERORDER::Train_Light_blur);
		Object->SetSprite("Title_Train_Light_Blur.png");
		Object->SetPosition(float4{ 26.0f , -500.0f }, PivotType::LeftTop);
		vecProps.push_back(Object);
	}

	

	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->CreateRenderer(ETITLERENDERORDER::Train_Light_blur);
		Object->SetSprite("Title_Train_WindowWater_blur.png");
		Object->SetPosition(float4{ 220.0f , -490.0f }, PivotType::LeftTop);
		vecProps.push_back(Object);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////


	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->CreateRenderer(ETITLERENDERORDER::Moon);
		Object->SetSprite("Title_Train_Moon.png");
		Object->SetPosition(float4{ 176.0f , -50.0f }, PivotType::LeftTop);
		vecProps.push_back(Object);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////


	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->CreateRenderer(ETITLERENDERORDER::TrainSmoke_Big);
		Object->SetPosition(float4{ 437.0f , -284.0f });
		Object->CreateAutomatedAnimation("Smoke_big", "trainsmoke_big.png", 0.1f);

		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->CreateRenderer(ETITLERENDERORDER::TrainSmoke_Mid);
		Object->SetPosition(float4{ 430.0f , -289.0f });
		Object->CreateAutomatedAnimation("Smoke_big", "trainsmoke_mid.png", 0.1f);

		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->CreateRenderer(ETITLERENDERORDER::TrainSmoke_Small);
		Object->SetPosition(float4{ 434.0f , -289.0f });
		Object->CreateAutomatedAnimation("Smoke_big", "trainsmoke_small.png", 0.1f);

		vecProps.push_back(Object);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->CreateRenderer(ETITLERENDERORDER::Shadow);
		Object->SetSprite("Background_Shadow-Title.png");
		Object->SetPosition(float4::ZERO, PivotType::LeftTop);
		Object->SetAutoSpriteSize(0.5f);
		vecProps.push_back(Object);
	}
}

#pragma endregion 

#pragma region 체인 소품 생성

void BackDrop_MainMenu::CreateTrain(class GameEngineLevel* _CurLevel)
{
	m_MainMenu_Train = _CurLevel->CreateActor<MainMenu_Trains>(EUPDATEORDER::Objects);
	if (nullptr == m_MainMenu_Train)
	{
		MsgBoxAssert("액터 생성을 실패하였습니다.");
		return;
	}

	m_MainMenu_Train->Init();
}

void BackDrop_MainMenu::CreateChainProp(class GameEngineLevel* _CurLevel)
{
	vecMainMenu_Chain.reserve(20);


	{
		std::shared_ptr<ChainProp> Object = _CurLevel->CreateActor<ChainProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->SetRenderOrder(ETITLERENDERORDER::Cloud_0);
		Object->SetSprite("Title_Train_Cloud_0.png");
		Object->SetSpawnPoint(300.0f);
		Object->SetSpeed(-20.0f);

		Object->CalculateAndSetRegenLocationInputFirstLocation(float4{ 700.0f , -70.0f});

		vecMainMenu_Chain.push_back(Object);
	}

	{
		std::shared_ptr<ChainProp> Object = _CurLevel->CreateActor<ChainProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->SetRenderOrder(ETITLERENDERORDER::Cloud_1);
		Object->SetSprite("Title_Train_Cloud_3.png");
		Object->SetSpawnPoint(200.0f);
		Object->SetSpeed(-27.0f);

		Object->CalculateAndSetRegenLocationInputFirstLocation(float4{ 500.0f , -110.0f });

		vecMainMenu_Chain.push_back(Object);
	}

	{
		std::shared_ptr<ChainProp> Object = _CurLevel->CreateActor<ChainProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->SetRenderOrder(ETITLERENDERORDER::Cloud_2);
		Object->SetSprite("Title_Train_Cloud_3.png");
		Object->SetSpawnPoint(100.0f);
		Object->SetSpeed(-30.0f);

		Object->CalculateAndSetRegenLocationInputFirstLocation(float4{ 400.0f , -170.0f });

		vecMainMenu_Chain.push_back(Object);
	}

	{
		std::shared_ptr<ChainProp> Object = _CurLevel->CreateActor<ChainProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->SetRenderOrder(ETITLERENDERORDER::Cloud_3);
		Object->SetSprite("Title_Train_Cloud_0.png");
		Object->SetSpawnPoint(130.0f);
		Object->SetSpeed(-40.0f);

		Object->CalculateAndSetRegenLocationInputFirstLocation(float4{ 360.0f , -225.0f });

		vecMainMenu_Chain.push_back(Object);
	}

	{
		std::shared_ptr<ChainProp> Object = _CurLevel->CreateActor<ChainProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->SetRenderOrder(ETITLERENDERORDER::Cloud_4);
		Object->SetSprite("Title_Train_Cloud_1.png");
		Object->SetSpawnPoint(100.0f);
		Object->SetSpeed(-42.0f);

		Object->CalculateAndSetRegenLocationInputFirstLocation(float4{ 770.0f , -260.0f });

		vecMainMenu_Chain.push_back(Object);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	
	{
		std::shared_ptr<ChainProp> Object = _CurLevel->CreateActor<ChainProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->SetRenderOrder(ETITLERENDERORDER::Props_0);
		Object->SetSprite("Title_Train_Mountain.png");
		Object->SetSpeed(CONST_MountainSpeed);

		Object->CalculateAndSetRegenLocationInputFirstLocation(float4{ 480.0f , -275.0f });
		Object->SetAutoSpawnPoint();

		vecMainMenu_Chain.push_back(Object);
	}

	{
		std::shared_ptr<ChainProp> Object = _CurLevel->CreateActor<ChainProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->SetRenderOrder(ETITLERENDERORDER::Mountain_blur);
		Object->SetSprite("Title_Train_MountainWater_blur.png");
		Object->SetSpeed(CONST_MountainSpeed);

		Object->CalculateAndSetRegenLocationInputFirstLocation(float4{ 480.0f , -451.0f });
		Object->SetAutoSpawnPoint();

		vecMainMenu_Chain.push_back(Object);
	}

	{
		std::shared_ptr<ChainProp> Object = _CurLevel->CreateActor<ChainProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->SetRenderOrder(ETITLERENDERORDER::Bridge_Down);
		Object->SetSprite("Title_Train_Bridge_Down.png");
		Object->SetSpeed(CONST_BridgeSpeed);

		Object->CalculateAndSetRegenLocationInputFirstLocation(float4{ 529.0f , -490.0f });
		Object->SetAutoSpawnPoint();

		vecMainMenu_Chain.push_back(Object);
	}

	{
		std::shared_ptr<ChainProp> Object = _CurLevel->CreateActor<ChainProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}
		
		Object->SetRenderOrder(ETITLERENDERORDER::Bridge);
		Object->SetSprite("Title_Train_Bridge.png");
		Object->SetSpeed(CONST_BridgeSpeed);

		Object->CalculateAndSetRegenLocationInputFirstLocation(float4{ 530.0f , -436.0f });
		Object->SetAutoSpawnPoint();

		vecMainMenu_Chain.push_back(Object);
	}

	{
		std::shared_ptr<ChainProp> Object = _CurLevel->CreateActor<ChainProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->SetRenderOrder(ETITLERENDERORDER::Water_blur);
		Object->SetSprite("Title_Train_WaterShine_blur.png");
		Object->SetSpeed(-400.0f);

		Object->CalculateAndSetRegenLocationInputFirstLocation(float4{ 544.0f , -483.0f });
		Object->SetAutoSpawnPoint();

		vecMainMenu_Chain.push_back(Object);
	}


	{
		std::shared_ptr<ChainProp> Object = _CurLevel->CreateActor<ChainProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->SetRenderOrder(ETITLERENDERORDER::Tree);
		Object->SetSprite("Title_Train_Tree_0.png");
		Object->SetSpeed(CONST_TreeSpeed);

		Object->SetFirstLocation(float4{ 300.0f , -410.0f });
		Object->SetRegenLocation(float4{ COSNT_TreeSpawnDistance , -410.0f });
		Object->SetAutoSpawnPoint();

		vecMainMenu_Chain.push_back(Object);
	}


	{
		std::shared_ptr<ChainProp> Object = _CurLevel->CreateActor<ChainProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->SetRenderOrder(ETITLERENDERORDER::Tree);
		Object->SetSprite("Title_Train_Tree_1.png");
		Object->SetSpeed(CONST_TreeSpeed);

		Object->SetFirstLocation(float4{ 900.0f , -418.0f });
		Object->SetRegenLocation(float4{ COSNT_TreeSpawnDistance , -418.0f });
		Object->SetAutoSpawnPoint();
		

		vecMainMenu_Chain.push_back(Object);
	}
}

#pragma endregion 



void BackDrop_MainMenu::ActorRelease()
{
	for (size_t i = 0; i < vecProps.size(); i++)
	{
		std::shared_ptr<Prop> Object = vecProps[i];
		if (nullptr == Object)
		{
			MsgBoxAssert("존재하지 않는 액터를 차조하려고 했습니다.");
			return;
		}

		Object->ActorRelease();
	}

	vecProps.clear();

	for (size_t i = 0; i < vecScenery.size(); i++)
	{
		std::shared_ptr<Scenery> Object = vecScenery[i];
		if (nullptr == Object)
		{
			MsgBoxAssert("존재하지 않는 액터를 차조하려고 했습니다.");
			return;
		}

		Object->ActorRelease();
	}

	vecScenery.clear();

	for (size_t i = 0; i < vecMainMenu_Chain.size(); i++)
	{
		std::shared_ptr<ChainProp> Object = vecMainMenu_Chain[i];
		if (nullptr == Object)
		{
			MsgBoxAssert("존재하지 않는 액터를 참조하려고 했습니다.");
			return;
		}

		Object->ActorRelease();
	}

	vecMainMenu_Chain.clear();

	if (nullptr != m_MainMenu_Train)
	{
		m_MainMenu_Train->ActorRelease();
		m_MainMenu_Train = nullptr;
	}

	Death();
}