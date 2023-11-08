#include "PreCompile.h"
#include "TestLevel.h"

#include "CameraControler.h"
#include "UIManager.h"
#include "SkyLerp.h"

#include "Ellie.h"
#include "Bush.h"
#include "WitchFlower.h"
#include "MongSiri_Population.h"
#include "NormalProp.h"


#include "PlayerEffect.h"
#include "VirgilHat.h"



TestLevel::TestLevel() 
{
}

TestLevel::~TestLevel() 
{
}


void TestLevel::Start()
{
	PlayLevel::Start();

	float4 Position = GlobalValue::GetWindowScale().Half();
	Position.Y *= -1.0f;

	GetMainCamera()->Transform.SetLocalPosition(Position);


	{
		/*GetMainCamera()->GetCameraAllRenderTarget()->CreateEffect<PlayerEffect>();*/
		GetMainCamera()->GetCameraAllRenderTarget()->CreateEffect<VirgilHat>();
	}
}

void TestLevel::Update(float _Delta)
{
	PlayLevel::Update(_Delta);
}

void TestLevel::LevelStart(class GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelStart(_NextLevel);

	GlobalValue::g_CameraControler->SetCameraMode(ECAMERAMODE::Fix);

	const float4 WinScale = GlobalValue::GetWindowScale();

	{
		float4 Position = WinScale.Half();
		Position.Y *= -1.0f;
		Position.Z = GlobalUtils::CalculateFixDepth(ERENDERDEPTH::Back_Paint);

		Map = CreateActor<GameEngineActor>(EUPDATEORDER::Objects);
		Map->Transform.SetLocalPosition(Position);



		std::weak_ptr<GameEngineSpriteRenderer> BaseRenderer = Map->CreateComponent<GameEngineSpriteRenderer>(0);
		BaseRenderer.lock()->SetSprite("GroundBase.png");
		BaseRenderer.lock()->GetImageTransform().SetLocalScale(WinScale);
	}

	float4 InitialPosition = WinScale.Half();
	InitialPosition.Y *= -1.0f;

	m_SkyLerp = CreateActor<SkyLerp>(EUPDATEORDER::Sky);
	m_SkyLerp->Init();

	{
		Player = CreateActor<Ellie>(EUPDATEORDER::Player);
		Player->Transform.SetLocalPosition(InitialPosition);
		Player->Init();
	}

	{
		UI = CreateActor<UIManager>(EUPDATEORDER::UIMagnaer);
		UI->Init();
	}

	{
		m_bush = CreateActor<Bush>(EUPDATEORDER::Objects);
		m_bush->SetBushType(EBUSHTYPE::BushBug);
		m_bush->Transform.SetLocalPosition(InitialPosition);
		m_bush->Init();
	}


	{
		std::shared_ptr<MongSiri_Population> MongSiri1 = CreateActor<MongSiri_Population>(EUPDATEORDER::Objects);
		MongSiri1->Transform.SetLocalPosition({ 300.0f , -400.0f });
		MongSiri1->SetPopulationSpawnLocation({ 400.0f , -400.0f });
		MongSiri1->Init(3);
	}

	{
		for (int i = 0; i < 5; i++)
		{
			const std::shared_ptr<WitchFlower>& witchflower = CreateActor<WitchFlower>(EUPDATEORDER::Objects);
			witchflower->Transform.SetLocalPosition(float4(100.0f + (100.0f * static_cast<float>(i)), -100.0f));
			witchflower->Init();
		}
	}

	TestCode();
}

void TestLevel::LevelEnd(class GameEngineLevel* _NextLevel)
{
	if (nullptr != Map)
	{
		Map->Death();
		Map = nullptr;
	}

	if (nullptr != Player)
	{
		Player->Death();
		Player = nullptr;
	}

	if (nullptr != m_bush)
	{
		m_bush->Death();
		m_bush = nullptr;
	}

	std::vector<std::shared_ptr<WitchFlower>> WFGroup = GetObjectGroupConvert<WitchFlower>(0);
	for (std::weak_ptr<WitchFlower> WF : WFGroup)
	{
		WF.lock()->Death();
	}

	if (nullptr != UI)
	{
		UI->Death();
		UI = nullptr;
	}
}

void TestLevel::TestCode()
{
	std::shared_ptr<RendererActor> TestMap =  CreateActor<RendererActor>(EUPDATEORDER::Objects);
	TestMap->Transform.SetLocalPosition(float4(200.0f, -400.0f, GlobalUtils::CalculateObjectDepth(GlobalValue::GetWindowScale().Y, -400.0f)));

	std::shared_ptr<GameEngineSpriteRenderer> Tree = TestMap->CreateComponent<GameEngineSpriteRenderer>();
	Tree->Transform.SetLocalPosition(float4(0.0f, 110.0f));
	Tree->SetSprite("Tree_2.png");
	Tree->RenderBaseInfoValue.Target2 = 1;
}