#include "PreCompile.h"
#include "TestLevel.h"


#include "CameraControler.h"

#include "Ellie.h"
#include "UIManager.h"

#include "Bush.h"
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

	Player = CreateActor<Ellie>(EUPDATEORDER::Player);
	Player->Transform.SetLocalPosition(InitialPosition);
	Player->Init();

	UI = CreateActor<UIManager>(EUPDATEORDER::UIMagnaer);
	UI->Init();

	m_bush = CreateActor<Bush>(EUPDATEORDER::Objects);
	m_bush->SetBushType(EBUSHTYPE::BushBug);
	m_bush->Transform.SetLocalPosition(InitialPosition);
	m_bush->Init();
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

	if (nullptr != UI)
	{
		UI->Death();
		UI = nullptr;
	}
}