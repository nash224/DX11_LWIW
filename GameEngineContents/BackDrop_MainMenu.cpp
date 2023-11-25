#include "PreCompile.h"
#include "BackDrop_MainMenu.h"

#include "Prop.h"
#include "ChainProp.h"
#include "LoopTextureActor.h"
#include "RendererActor.h"
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

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("Title_Train_Sky.png");
	if (nullptr == Texture)
	{
		MsgBoxAssert("텍스처를 불러오지 못했습니다.");
		return;
	}

	m_BackScale = Texture->GetScale();



	if (nullptr == GameEngineSound::FindSound("BGM_MainTheme.wav"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Sound\\MainMenu");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile pFile : Files)
		{
			GameEngineSound::SoundLoad(pFile.GetStringPath());
		}
	}

	CreateProp(CurLevel);
	CreateTrain(CurLevel);
	CreateChainProp(CurLevel);
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

	{
		const float4& Position = float4(300.0f, 100.0f, DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::Logo));

		std::shared_ptr<GameEngineUIRenderer> _Logo = CreateComponent<GameEngineUIRenderer>();
		_Logo->SetSprite("Logo.png");
		_Logo->Transform.SetLocalPosition(Position);
		_Logo->AutoSpriteSizeOn();
		_Logo->SetAutoScaleRatio(0.5f);
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

	
	static constexpr float MountainSpeed = -60.0f;
	static constexpr float BridgeSpeed = -480.0f;
	static constexpr float TreeSpeed = -1200.0f;
	static constexpr float TreeSpawnDistance = 2400.0f;
	const float4& WinScale = GlobalValue::GetWindowScale();

	{
		const float Depth = DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::Props_0);
		std::shared_ptr<LoopTextureActor> Object = _CurLevel->CreateActor<LoopTextureActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(float4(WinScale.hX(), -275.0f, Depth));
		Object->Init();
		Object->Renderer->SetSprite("Title_Train_Mountain.png");
		Object->SetSpeed(MountainSpeed);
	}

	{
		const float Depth = DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::Mountain_blur);
		std::shared_ptr<LoopTextureActor> Object = _CurLevel->CreateActor<LoopTextureActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(float4(WinScale.hX(), -451.0f, Depth));
		Object->Init();
		Object->Renderer->SetMaterial("Texture2D_Overlay");
		Object->Renderer->SetSampler("EngineBaseWRAPSampler");
		Object->Renderer->SetSprite("Title_Train_MountainWater_blur.png");
		Object->SetSpeed(MountainSpeed);
	}

	{
		const float Depth = DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::Bridge_Down);
		std::shared_ptr<LoopTextureActor> Object = _CurLevel->CreateActor<LoopTextureActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(float4(530.0f, -500.0f, Depth));
		Object->Init();
		Object->Renderer->SetSprite("Title_Train_Bridge_Down.png");
		Object->SetSpeed(BridgeSpeed);
	}

	{
		const float Depth = DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::Bridge);
		std::shared_ptr<LoopTextureActor> Object = _CurLevel->CreateActor<LoopTextureActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(float4(530.0f, -436.0f, Depth));
		Object->Init();
		Object->Renderer->SetSprite("Title_Train_Bridge.png");
		Object->SetSpeed(BridgeSpeed);
	}

	{
		const float Depth = DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::Water_blur);
		std::shared_ptr<LoopTextureActor> Object = _CurLevel->CreateActor<LoopTextureActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(float4(544.0f, -483.0f, Depth));
		Object->Init();
		Object->Renderer->SetMaterial("Texture2D_Overlay");
		Object->Renderer->SetSampler("EngineBaseWRAPSampler");
		Object->Renderer->SetSprite("Title_Train_WaterShine_blur.png");
		Object->SetSpeed(-400.0f);
	}

	{
		std::shared_ptr<ChainProp> Object = _CurLevel->CreateActor<ChainProp>(EUPDATEORDER::Objects);

		Object->SetMaterial("Texture2D_Overlay");
		Object->SetSprite("cookie_1.png");
		Object->SetColor(float4(0.7f, 0.6f, 0.8f, 0.2f));
		Object->SetSpeed(-450.0f);
		Object->SetDepth(ETITLERENDERDEPTH::Light_);
		Object->CalculateAndSetRegenLocation(float4{ 544.0f , -483.0f });
		Object->SetAutoSpawnPoint();
	}


	{
		std::shared_ptr<ChainProp> Object = _CurLevel->CreateActor<ChainProp>(EUPDATEORDER::Objects);
		Object->SetSprite("Title_Train_Tree_0.png");
		Object->SetSpeed(TreeSpeed);
		Object->SetDepth(ETITLERENDERDEPTH::Tree);
		Object->SetFirstLocation(float4{ 300.0f , -410.0f });
		Object->SetRegenLocation(float4{ TreeSpawnDistance  , -410.0f });
		Object->SetAutoSpawnPoint();
	}


	{
		std::shared_ptr<ChainProp> Object = _CurLevel->CreateActor<ChainProp>(EUPDATEORDER::Objects);
		Object->SetSprite("Title_Train_Tree_1.png");
		Object->SetSpeed(TreeSpeed);
		Object->SetDepth(ETITLERENDERDEPTH::Tree);
		Object->SetFirstLocation(float4{ 900.0f , -418.0f });
		Object->SetRegenLocation(float4{ TreeSpawnDistance  , -418.0f });
		Object->SetAutoSpawnPoint();
	}

}

#pragma endregion 
