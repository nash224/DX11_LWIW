#include "PreCompile.h"
#include "BackDrop_MainMenu.h"

#include "ChainProp.h"
#include "LoopTextureActor.h"
#include "RendererActor.h"
#include "MainMenu_Trains.h"
#include "CometSpawner.h"

BackDrop_MainMenu::BackDrop_MainMenu() 
{
}

BackDrop_MainMenu::~BackDrop_MainMenu() 
{
}


void BackDrop_MainMenu::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}



void BackDrop_MainMenu::Init()
{
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

	PropSetting();
	CometSpawnerSetting();
	CreateTrain();
	CreateChainProp();
}


void BackDrop_MainMenu::PropSetting()
{
	{
		const float Depth = DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::Back_);
		std::shared_ptr<RendererActor> Object = GetLevel()->CreateActor<RendererActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(float4(0.0f, 0.0f, Depth));
		Object->Init();
		Object->m_Renderer->SetSprite("Title_Train_Sky.png");
		Object->m_Renderer->SetPivotType(PivotType::LeftTop);
	}

	{
		const float Depth = DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::Star);
		std::shared_ptr<RendererActor> Object = GetLevel()->CreateActor<RendererActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(float4(20.0f, -100.0f, Depth));
		Object->Init();
		Object->m_Renderer->CreateAnimation("StarAni", "Title_train_star");
		Object->m_Renderer->ChangeAnimation("StarAni");
		Object->m_Renderer->AutoSpriteSizeOn();
		Object->m_Renderer->SetPivotType(PivotType::Left);
	}

	{
		const float Depth = DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::Water);
		std::shared_ptr<RendererActor> Object = GetLevel()->CreateActor<RendererActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(float4(0.0f, -398.0f, Depth));
		Object->Init();
		Object->m_Renderer->SetSprite("Title_Train_Water.png");
		Object->m_Renderer->SetPivotType(PivotType::LeftTop);
	}

	{
		const float Depth = DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::Bridge_blur);
		std::shared_ptr<RendererActor> Object = GetLevel()->CreateActor<RendererActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(float4(0.0f, -464.0f, Depth));
		Object->Init();
		Object->m_Renderer->SetSprite("Title_Train_Bridge_Shadow.png");
		Object->m_Renderer->SetPivotType(PivotType::LeftTop);
	}

	{
		const float Depth = DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::Train_blur);
		std::shared_ptr<RendererActor> Object = GetLevel()->CreateActor<RendererActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(float4(0.0f, -492.0f, Depth));
		Object->Init();
		Object->m_Renderer->SetSprite("Title_Train_TrainWater_blur.png");
		Object->m_Renderer->SetPivotType(PivotType::LeftTop);
	}

	{
		const float Depth = DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::Train_Light_blur);
		std::shared_ptr<RendererActor> Object = GetLevel()->CreateActor<RendererActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(float4(26.0f, -500.0f, Depth));
		Object->Init();
		Object->m_Renderer->SetSprite("Title_Train_Light_Blur.png");
		Object->m_Renderer->SetPivotType(PivotType::LeftTop);
	}

	{
		const float Depth = DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::Train_Light_blur);
		std::shared_ptr<RendererActor> Object = GetLevel()->CreateActor<RendererActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(float4(220.0f, -490.0f, Depth));
		Object->Init();
		Object->m_Renderer->SetSprite("Title_Train_WindowWater_blur.png");
		Object->m_Renderer->SetPivotType(PivotType::LeftTop);
	}

	{
		const float Depth = DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::Moon);
		std::shared_ptr<RendererActor> Object = GetLevel()->CreateActor<RendererActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(float4(176.0f, -50.0f, Depth));
		Object->Init();
		Object->m_Renderer->SetSprite("Title_Train_Moon.png");
		Object->m_Renderer->SetPivotType(PivotType::LeftTop);
	}

	{
		const float Depth = DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::TrainSmoke_Big);
		std::shared_ptr<RendererActor> Object = GetLevel()->CreateActor<RendererActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(float4(437.0f, -284.0f, Depth));
		Object->Init();
		Object->m_Renderer->AutoSpriteSizeOn();
		Object->m_Renderer->CreateAnimation("Smoke", "trainsmoke_big.png", 0.14f);
		Object->m_Renderer->ChangeAnimation("Smoke");
	}

	{
		const float Depth = DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::TrainSmoke_Mid);
		std::shared_ptr<RendererActor> Object = GetLevel()->CreateActor<RendererActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(float4(430.0f, -289.0f, Depth));
		Object->Init();
		Object->m_Renderer->AutoSpriteSizeOn();
		Object->m_Renderer->CreateAnimation("Smoke", "trainsmoke_mid.png", 0.1f);
		Object->m_Renderer->ChangeAnimation("Smoke");
	}

	{
		const float Depth = DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::TrainSmoke_Small);
		std::shared_ptr<RendererActor> Object = GetLevel()->CreateActor<RendererActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(float4(434.0f, -289.0f, Depth));
		Object->Init();
		Object->m_Renderer->AutoSpriteSizeOn();
		Object->m_Renderer->CreateAnimation("Smoke", "trainsmoke_small.png", 0.06f);
		Object->m_Renderer->ChangeAnimation("Smoke");
	}


	{
		const float Depth = DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::Shadow);
		std::shared_ptr<RendererActor> Object = GetLevel()->CreateActor<RendererActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(float4(0.0f, 0.0f, Depth));
		Object->Init();
		Object->m_Renderer->SetSprite("Background_Shadow-Title.png");
		Object->m_Renderer->AutoSpriteSizeOn();
		Object->m_Renderer->SetAutoScaleRatio(0.5f);
		Object->m_Renderer->SetPivotType(PivotType::LeftTop);
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

void BackDrop_MainMenu::CometSpawnerSetting()
{
	GetLevel()->CreateActor<CometSpawner>(EUPDATEORDER::Objects);
}

void BackDrop_MainMenu::CreateTrain()
{
	std::shared_ptr<MainMenu_Trains> Trans = GetLevel()->CreateActor<MainMenu_Trains>(EUPDATEORDER::Objects);
	Trans->Init();
}

#pragma region 체인 소품 생성
void BackDrop_MainMenu::CreateChainProp()
{
	{
		std::shared_ptr<ChainProp> Object = GetLevel()->CreateActor<ChainProp>(EUPDATEORDER::Objects);

		Object->SetSprite("Title_Train_Cloud_0.png");
		Object->SetSpawnPoint(300.0f);
		Object->SetSpeed(-20.0f);
		Object->SetDepth(ETITLERENDERDEPTH::Cloud_0);

		Object->CalculateAndSetRegenLocation(float4{ 700.0f , -70.0f});
	}

	{
		std::shared_ptr<ChainProp> Object = GetLevel()->CreateActor<ChainProp>(EUPDATEORDER::Objects);

		Object->SetSprite("Title_Train_Cloud_3.png");
		Object->SetSpawnPoint(200.0f);
		Object->SetSpeed(-27.0f);
		Object->SetDepth(ETITLERENDERDEPTH::Cloud_1);
		Object->CalculateAndSetRegenLocation(float4{ 500.0f , -110.0f });
	}

	{
		std::shared_ptr<ChainProp> Object = GetLevel()->CreateActor<ChainProp>(EUPDATEORDER::Objects);

		Object->SetSprite("Title_Train_Cloud_3.png");
		Object->SetSpawnPoint(100.0f);
		Object->SetSpeed(-30.0f);
		Object->SetDepth(ETITLERENDERDEPTH::Cloud_2);
		Object->CalculateAndSetRegenLocation(float4{ 400.0f , -170.0f });
	}

	{
		std::shared_ptr<ChainProp> Object = GetLevel()->CreateActor<ChainProp>(EUPDATEORDER::Objects);

		Object->SetSprite("Title_Train_Cloud_0.png");
		Object->SetSpawnPoint(130.0f);
		Object->SetSpeed(-40.0f);
		Object->SetDepth(ETITLERENDERDEPTH::Cloud_3);
		Object->CalculateAndSetRegenLocation(float4{ 360.0f , -225.0f });
	}

	{
		std::shared_ptr<ChainProp> Object = GetLevel()->CreateActor<ChainProp>(EUPDATEORDER::Objects);

		Object->SetSprite("Title_Train_Cloud_1.png");
		Object->SetSpawnPoint(100.0f);
		Object->SetSpeed(-42.0f);
		Object->SetDepth(ETITLERENDERDEPTH::Cloud_4);
		Object->CalculateAndSetRegenLocation(float4{ 770.0f , -260.0f });
	}

	{
		std::shared_ptr<ChainProp> Object = GetLevel()->CreateActor<ChainProp>(EUPDATEORDER::Objects);

		Object->SetSprite("Title_Train_CloudBlur_1.png");
		Object->SetSpawnPoint(100.0f);
		Object->SetSpeed(-42.0f);
		Object->SetDepth(ETITLERENDERDEPTH::Cloud_blur_1);
		Object->CalculateAndSetRegenLocation(float4{ 770.0f , -460.0f });
	}

	{
		std::shared_ptr<ChainProp> Object = GetLevel()->CreateActor<ChainProp>(EUPDATEORDER::Objects);

		Object->SetSprite("Title_Train_CloudBlur_0.png");
		Object->SetSpawnPoint(130.0f);
		Object->SetSpeed(-40.0f);
		Object->SetDepth(ETITLERENDERDEPTH::Cloud_blur_2);
		Object->CalculateAndSetRegenLocation(float4{ 360.0f , -485.0f });
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	
	static constexpr float MountainSpeed = -60.0f;
	static constexpr float BridgeSpeed = -480.0f;
	static constexpr float TreeSpeed = -1200.0f;
	static constexpr float TreeSpawnDistance = 2400.0f;
	const float4& WinScale = GlobalValue::GetWindowScale();

	{
		const float Depth = DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::Props_0);
		std::shared_ptr<LoopTextureActor> Object = GetLevel()->CreateActor<LoopTextureActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(float4(WinScale.hX(), -275.0f, Depth));
		Object->Init();
		Object->Renderer->SetSprite("Title_Train_Mountain.png");
		Object->SetSpeed(MountainSpeed);
	}

	{
		const float Depth = DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::Mountain_blur);
		std::shared_ptr<LoopTextureActor> Object = GetLevel()->CreateActor<LoopTextureActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(float4(WinScale.hX(), -451.0f, Depth));
		Object->Init();
		Object->Renderer->SetMaterial("Texture2D_Overlay");
		Object->Renderer->SetSampler("EngineBaseWRAPSampler");
		Object->Renderer->SetSprite("Title_Train_MountainWater_blur.png");
		Object->SetSpeed(MountainSpeed);
	}

	{
		const float Depth = DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::Bridge_Down);
		std::shared_ptr<LoopTextureActor> Object = GetLevel()->CreateActor<LoopTextureActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(float4(530.0f, -500.0f, Depth));
		Object->Init();
		Object->Renderer->SetSprite("Title_Train_Bridge_Down.png");
		Object->SetSpeed(BridgeSpeed);
	}

	{
		const float Depth = DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::Bridge);
		std::shared_ptr<LoopTextureActor> Object = GetLevel()->CreateActor<LoopTextureActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(float4(530.0f, -436.0f, Depth));
		Object->Init();
		Object->Renderer->SetSprite("Title_Train_Bridge.png");
		Object->SetSpeed(BridgeSpeed);
	}

	{
		const float Depth = DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::Water_blur);
		std::shared_ptr<LoopTextureActor> Object = GetLevel()->CreateActor<LoopTextureActor>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(float4(544.0f, -483.0f, Depth));
		Object->Init();
		Object->Renderer->SetMaterial("Texture2D_Overlay");
		Object->Renderer->SetSampler("EngineBaseWRAPSampler");
		Object->Renderer->SetSprite("Title_Train_WaterShine_blur.png");
		Object->SetSpeed(-400.0f);
	}

	{
		std::shared_ptr<ChainProp> Object = GetLevel()->CreateActor<ChainProp>(EUPDATEORDER::Objects);

		Object->SetMaterial("Texture2D_Overlay");
		Object->SetSprite("cookie_1.png");
		Object->SetColor(float4(0.7f, 0.6f, 0.8f, 0.2f));
		Object->SetSpeed(-450.0f);
		Object->SetDepth(ETITLERENDERDEPTH::Light_);
		Object->CalculateAndSetRegenLocation(float4{ 544.0f , -483.0f });
		Object->SetAutoSpawnPoint();
	}


	{
		std::shared_ptr<ChainProp> Object = GetLevel()->CreateActor<ChainProp>(EUPDATEORDER::Objects);
		Object->SetSprite("Title_Train_Tree_0.png");
		Object->SetSpeed(TreeSpeed);
		Object->SetDepth(ETITLERENDERDEPTH::Tree);
		Object->SetFirstLocation(float4{ 300.0f , -410.0f });
		Object->SetRegenLocation(float4{ TreeSpawnDistance  , -410.0f });
		Object->SetAutoSpawnPoint();
	}


	{
		std::shared_ptr<ChainProp> Object = GetLevel()->CreateActor<ChainProp>(EUPDATEORDER::Objects);
		Object->SetSprite("Title_Train_Tree_1.png");
		Object->SetSpeed(TreeSpeed);
		Object->SetDepth(ETITLERENDERDEPTH::Tree);
		Object->SetFirstLocation(float4{ 900.0f , -418.0f });
		Object->SetRegenLocation(float4{ TreeSpawnDistance  , -418.0f });
		Object->SetAutoSpawnPoint();
	}

}

#pragma endregion 
