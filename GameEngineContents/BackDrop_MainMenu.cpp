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
	BackDrop::Start();
}

void BackDrop_MainMenu::Update(float _Delta)
{
	BackDrop::Update(_Delta);
}

void BackDrop_MainMenu::Release()
{
	BackDrop::Release();
}

void BackDrop_MainMenu::LevelStart(class GameEngineLevel* _NextLevel)
{
	BackDrop::LevelStart(_NextLevel);
}

void BackDrop_MainMenu::LevelEnd(class GameEngineLevel* _NextLevel)
{
	BackDrop::LevelEnd(_NextLevel);

	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void BackDrop_MainMenu::Init()
{
	GameEngineLevel* CurLevel = GetLevel();

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


#pragma region Prop 생성

void BackDrop_MainMenu::CreateProp(class GameEngineLevel* _CurLevel)
{
	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		Object->CreateRenderer();
		Object->SetSprite("Title_Train_Sky.png");
		Object->SetRendererPivotType(PivotType::LeftTop);
		Object->SetPositionAndDepth(float4::ZERO, ETITLERENDERDEPTH::Back_);
	}

	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		Object->CreateRenderer();
		Object->CreateAndSetAnimation("StarAni", "Title_train_star");
		Object->SetRendererPivotType(PivotType::Left);
		Object->SetPositionAndDepth({ 20.0f , -100.0f }, ETITLERENDERDEPTH::Star);
	}

	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		Object->CreateRenderer();
		Object->SetSprite("Title_Train_Water.png");
		Object->SetRendererPivotType(PivotType::LeftTop);
		Object->SetPositionAndDepth({ 0.0f , -398.0f }, ETITLERENDERDEPTH::Water);
	}

	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		Object->CreateRenderer();
		Object->SetSprite("Title_Train_Bridge_Shadow.png");
		Object->SetRendererPivotType(PivotType::LeftTop);
		Object->SetPositionAndDepth({ 0.0f , -464.0f }, ETITLERENDERDEPTH::Bridge_blur);
	}

	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);

		Object->CreateRenderer();
		Object->SetSprite("Title_Train_TrainWater_blur.png");
		Object->SetRendererPivotType(PivotType::LeftTop);
		Object->SetPositionAndDepth({ 0.0f , -492.0f }, ETITLERENDERDEPTH::Train_blur);
	}

	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);

		Object->CreateRenderer();
		Object->SetSprite("Title_Train_Light_Blur.png");
		Object->SetRendererPivotType(PivotType::LeftTop);
		Object->SetPositionAndDepth({ 26.0f , -500.0f }, ETITLERENDERDEPTH::Train_Light_blur);
	}

	

	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);

		Object->CreateRenderer();
		Object->SetSprite("Title_Train_WindowWater_blur.png");
		Object->SetRendererPivotType(PivotType::LeftTop);
		Object->SetPositionAndDepth({ 220.0f , -490.0f }, ETITLERENDERDEPTH::Train_Light_blur);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////


	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		Object->CreateRenderer();
		Object->SetSprite("Title_Train_Moon.png");
		Object->SetRendererPivotType(PivotType::LeftTop);
		Object->SetPositionAndDepth({ 176.0f , -50.0f }, ETITLERENDERDEPTH::Moon);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////


	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		Object->CreateRenderer();
		Object->CreateAndSetAnimation("Smoke_big", "trainsmoke_big.png", 0.14f);
		Object->SetPositionAndDepth({ 437.0f , -284.0f }, ETITLERENDERDEPTH::TrainSmoke_Big);
	}

	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		Object->CreateRenderer();
		Object->CreateAndSetAnimation("Smoke_big", "trainsmoke_mid.png", 0.1f);
		Object->SetPositionAndDepth({ 430.0f , -289.0f }, ETITLERENDERDEPTH::TrainSmoke_Mid);
	}

	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		Object->CreateRenderer();
		Object->CreateAndSetAnimation("Smoke_big", "trainsmoke_small.png", 0.06f);
		Object->SetPositionAndDepth({ 434.0f , -289.0f }, ETITLERENDERDEPTH::TrainSmoke_Small);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		Object->CreateRenderer(0);
		Object->SetSprite("Background_Shadow-Title.png");
		Object->SetAutoSpriteSize(0.5f);
		Object->SetRendererPivotType(PivotType::LeftTop);
		Object->SetPositionAndDepth({ 0.0f , 0.0f }, ETITLERENDERDEPTH::Shadow);
	}
}

#pragma endregion 

// 기차
void BackDrop_MainMenu::CreateTrain(class GameEngineLevel* _CurLevel)
{
	std::shared_ptr<MainMenu_Trains> Trans = _CurLevel->CreateActor<MainMenu_Trains>(EUPDATEORDER::Objects);
	Trans->Init();
}

#pragma region 체인 소품 생성
void BackDrop_MainMenu::CreateChainProp(class GameEngineLevel* _CurLevel)
{
	{
		std::shared_ptr<ChainProp> Object = _CurLevel->CreateActor<ChainProp>(EUPDATEORDER::Objects);

		Object->SetSprite("Title_Train_Cloud_0.png");
		Object->SetSpawnPoint(300.0f);
		Object->SetSpeed(-20.0f);
		Object->SetDepth(ETITLERENDERDEPTH::Cloud_0);

		Object->CalculateAndSetRegenLocation(float4{ 700.0f , -70.0f});
	}

	{
		std::shared_ptr<ChainProp> Object = _CurLevel->CreateActor<ChainProp>(EUPDATEORDER::Objects);

		Object->SetSprite("Title_Train_Cloud_3.png");
		Object->SetSpawnPoint(200.0f);
		Object->SetSpeed(-27.0f);
		Object->SetDepth(ETITLERENDERDEPTH::Cloud_1);
		Object->CalculateAndSetRegenLocation(float4{ 500.0f , -110.0f });
	}

	{
		std::shared_ptr<ChainProp> Object = _CurLevel->CreateActor<ChainProp>(EUPDATEORDER::Objects);

		Object->SetSprite("Title_Train_Cloud_3.png");
		Object->SetSpawnPoint(100.0f);
		Object->SetSpeed(-30.0f);
		Object->SetDepth(ETITLERENDERDEPTH::Cloud_2);
		Object->CalculateAndSetRegenLocation(float4{ 400.0f , -170.0f });
	}

	{
		std::shared_ptr<ChainProp> Object = _CurLevel->CreateActor<ChainProp>(EUPDATEORDER::Objects);

		Object->SetSprite("Title_Train_Cloud_0.png");
		Object->SetSpawnPoint(130.0f);
		Object->SetSpeed(-40.0f);
		Object->SetDepth(ETITLERENDERDEPTH::Cloud_3);
		Object->CalculateAndSetRegenLocation(float4{ 360.0f , -225.0f });
	}

	{
		std::shared_ptr<ChainProp> Object = _CurLevel->CreateActor<ChainProp>(EUPDATEORDER::Objects);

		Object->SetSprite("Title_Train_Cloud_1.png");
		Object->SetSpawnPoint(100.0f);
		Object->SetSpeed(-42.0f);
		Object->SetDepth(ETITLERENDERDEPTH::Cloud_4);
		Object->CalculateAndSetRegenLocation(float4{ 770.0f , -260.0f });
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	
	{
		std::shared_ptr<ChainProp> Object = _CurLevel->CreateActor<ChainProp>(EUPDATEORDER::Objects);

		Object->SetSprite("Title_Train_Mountain.png");
		Object->SetSpeed(CONST_MountainSpeed);
		Object->SetDepth(ETITLERENDERDEPTH::Props_0);
		Object->CalculateAndSetRegenLocation(float4{ 480.0f , -275.0f });
		Object->SetAutoSpawnPoint();
	}

	{
		std::shared_ptr<ChainProp> Object = _CurLevel->CreateActor<ChainProp>(EUPDATEORDER::Objects);

		Object->SetSprite("Title_Train_MountainWater_blur.png");
		Object->SetSpeed(CONST_MountainSpeed);
		Object->SetDepth(ETITLERENDERDEPTH::Mountain_blur);
		Object->CalculateAndSetRegenLocation(float4{ 480.0f , -451.0f });
		Object->SetAutoSpawnPoint();
	}

	{
		std::shared_ptr<ChainProp> Object = _CurLevel->CreateActor<ChainProp>(EUPDATEORDER::Objects);

		Object->SetSprite("Title_Train_Bridge_Down.png");
		Object->SetSpeed(CONST_BridgeSpeed);
		Object->SetDepth(ETITLERENDERDEPTH::Bridge_Down);
		Object->CalculateAndSetRegenLocation(float4{ 529.0f , -490.0f });
		Object->SetAutoSpawnPoint();
	}

	{
		std::shared_ptr<ChainProp> Object = _CurLevel->CreateActor<ChainProp>(EUPDATEORDER::Objects);
		
		Object->SetSprite("Title_Train_Bridge.png");
		Object->SetSpeed(CONST_BridgeSpeed);
		Object->SetDepth(ETITLERENDERDEPTH::Bridge);
		Object->CalculateAndSetRegenLocation(float4{ 530.0f , -436.0f });
		Object->SetAutoSpawnPoint();
	}

	{
		std::shared_ptr<ChainProp> Object = _CurLevel->CreateActor<ChainProp>(EUPDATEORDER::Objects);

		Object->SetSprite("Title_Train_WaterShine_blur.png");
		Object->SetSpeed(-400.0f);
		Object->SetDepth(ETITLERENDERDEPTH::Water_blur);
		Object->CalculateAndSetRegenLocation(float4{ 544.0f , -483.0f });
		Object->SetAutoSpawnPoint();
	}


	{
		std::shared_ptr<ChainProp> Object = _CurLevel->CreateActor<ChainProp>(EUPDATEORDER::Objects);

		Object->SetSprite("Title_Train_Tree_0.png");
		Object->SetSpeed(CONST_TreeSpeed);
		Object->SetDepth(ETITLERENDERDEPTH::Tree);

		Object->SetFirstLocation(float4{ 300.0f , -410.0f });
		Object->SetRegenLocation(float4{ COSNT_TreeSpawnDistance , -410.0f });
		Object->SetAutoSpawnPoint();
	}


	{
		std::shared_ptr<ChainProp> Object = _CurLevel->CreateActor<ChainProp>(EUPDATEORDER::Objects);

		Object->SetSprite("Title_Train_Tree_1.png");
		Object->SetSpeed(CONST_TreeSpeed);
		Object->SetDepth(ETITLERENDERDEPTH::Tree);

		Object->SetFirstLocation(float4{ 900.0f , -418.0f });
		Object->SetRegenLocation(float4{ COSNT_TreeSpawnDistance , -418.0f });
		Object->SetAutoSpawnPoint();
	}
}

#pragma endregion 

