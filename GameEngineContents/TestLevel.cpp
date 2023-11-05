#include "PreCompile.h"
#include "TestLevel.h"

#include "CameraControler.h"
#include "UIManager.h"

#include "Ellie.h"
#include "Bush.h"
#include "WitchFlower.h"
#include "MongSiri_Population.h"

#include "NormalProp.h"

TestLevel::TestLevel() 
{
}

TestLevel::~TestLevel() 
{
}


void TestLevel::Start()
{
	ContentsLevel::Start();

	float4 Position = GlobalValue::GetWindowScale().Half();
	Position.Y *= -1.0f;

	GetMainCamera()->Transform.SetLocalPosition(Position);
}

void TestLevel::Update(float _Delta)
{
	ContentsLevel::Update(_Delta); 
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
			witchflower->Transform.SetLocalPosition(float4(100.0f + (100.0f * i), -100.0f));
			witchflower->Init();
		}
	}
}

void TestLevel::LevelEnd(class GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelEnd(_NextLevel);

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