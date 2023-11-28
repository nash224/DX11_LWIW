#include "PreCompile.h"
#include "TestLevel.h"

#include <GameEngineCore/GameEngineCoreWindow.h>

#include "CameraControler.h"
#include "UIManager.h"
#include "SkyLerp.h"

#include "Ellie.h"
#include "Bush.h"
#include "WitchFlower.h"
#include "SilverStarFlower.h"
#include "MongSiri_Population.h"
#include "NormalProp.h"

#include "SkyLightEffect.h"
#include "PlayerEffect.h"
#include "OutLineEffect.h"

#include "TestCircleGauge.h"
#include "UI_ButtonGuide.h"
#include "UI_QuestUnit.h"
#include "UI_Hub_MainBoard.h"
#include "BaseLift.h"

#include "QuestData.h"



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

	std::shared_ptr<GameEngineCoreWindow> Window = GameEngineGUI::FindGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow");
	if (nullptr != Window)
	{
		Window->AddDebugRenderTarget(0, "TestRenderTarget", GetMainCamera()->GetCameraAllRenderTarget());
	}


	{
		/*GetMainCamera()->GetCameraAllRenderTarget()->CreateEffect<OutLineEffect>();*/
		/*GetMainCamera()->GetCameraAllRenderTarget()->CreateEffect<PlayerEffect>();*/
	}
}

void TestLevel::Update(float _Delta)
{
	PlayLevel::Update(_Delta);
}

void TestLevel::LevelStart(class GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelStart(_NextLevel);

	FileLoadFunction::LoadTextureAndCreateSingleSpriteInPath("Resources\\PlayContents\\Lift");

	CameraControler::MainCameraControler.lock()->SetCameraMode(ECAMERAMODE::Fix);

	const float4 WinScale = GlobalValue::GetWindowScale();

	{
		float4 Position = WinScale.Half();
		Position.Y *= -1.0f;
		Position.Z = DepthFunction::CalculateFixDepth(ERENDERDEPTH::Back_Paint);

		Map = CreateActor<GameEngineActor>(EUPDATEORDER::Objects);
		Map->Transform.SetLocalPosition(Position);



		std::weak_ptr<GameEngineSpriteRenderer> BaseRenderer = Map->CreateComponent<GameEngineSpriteRenderer>(0);
		BaseRenderer.lock()->SetSprite("GroundBase.png");
		BaseRenderer.lock()->GetImageTransform().SetLocalScale(WinScale);
	}

	float4 InitialPosition = WinScale.Half();
	InitialPosition.Y *= -1.0f;

	SkyLight = CreateActor<SkyLerp>(EUPDATEORDER::Sky);
	SkyLight->Init();

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
		std::shared_ptr<BaseLift> Lift = CreateActor<BaseLift>(EUPDATEORDER::UIMagnaer);
		Lift->Transform.SetLocalPosition(float4(540.0f, -480.0f));
		Lift->Init();
	}

	{
		bush = CreateActor<Bush>(EUPDATEORDER::Objects);
		bush->SetBushType(EBUSHTYPE::BushBug);
		bush->Transform.SetLocalPosition(float4(700.0f, -400.0f));
		bush->Init();
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

	{
		for (int i = 0; i < 3; i++)
		{
			const std::shared_ptr<SilverStarFlower>& SilverBellFlower = CreateActor<SilverStarFlower>(EUPDATEORDER::Objects);
			SilverBellFlower->Transform.SetLocalPosition(float4(100.0f + (100.0f * static_cast<float>(i)), -200.0f));
			SilverBellFlower->Init();
		}
	}

	if (false) 
	{
		//std::shared_ptr<UI_QuestUnit> QuestUnit = CreateActor<UI_QuestUnit>(EUPDATEORDER::UIComponent);
		// QuestUnit->Init("FindLetter");
	}

	if (false) 
	{
		std::shared_ptr<UI_Hub_MainBoard> MainBoard = CreateActor<UI_Hub_MainBoard>(EUPDATEORDER::UIComponent);
		MainBoard->Init();
	}

	{
		const std::shared_ptr<TestCircleGauge>& CircleGauge = CreateActor<TestCircleGauge>(EUPDATEORDER::Objects);
	}

	{
		std::vector<ButtonInfoParameter> Paras = 
		{
			{EBUTTONTYPE::A, "뽑기"},
			{EBUTTONTYPE::QW, "자기"},
			{EBUTTONTYPE::ER, "태우기"},
			{EBUTTONTYPE::Space, "달리기"},
		};

		ButtonGuide = CreateActor<TestCircleGauge>(EUPDATEORDER::Objects);
		Guide.SetGuideInfo(ButtonGuide.get(), Paras);
		Guide.On();
	}

	TestCode();
}

void TestLevel::LevelEnd(class GameEngineLevel* _NextLevel)
{
	FileLoadFunction::ReleaseAllTextureAndSpriteInPath("Resources\\PlayContents\\Lift");

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

	if (nullptr != bush)
	{
		bush->Death();
		bush = nullptr;
	}

	const std::vector<std::shared_ptr<SilverStarFlower>>& SBFGroup = GetObjectGroupConvert<SilverStarFlower>(EUPDATEORDER::Objects);
	for (std::weak_ptr<SilverStarFlower> SBF : SBFGroup)
	{
		SBF.lock()->Death();
	}

	const std::vector<std::shared_ptr<WitchFlower>>& WFGroup = GetObjectGroupConvert<WitchFlower>(EUPDATEORDER::Objects);
	for (std::weak_ptr<WitchFlower> WF : WFGroup)
	{
		WF.lock()->Death();
	}

	const std::vector<std::shared_ptr<MongSiri_Population>>& PopulationGroup = GetObjectGroupConvert<MongSiri_Population>(EUPDATEORDER::Objects);
	for (std::weak_ptr<MongSiri_Population> Population : PopulationGroup)
	{
		Population.lock()->ActorRelaese();
	}

	if (nullptr != UI)
	{
		UI->Death();
		UI = nullptr;
	}
}

void TestLevel::TestCode()
{
	std::shared_ptr<NormalProp> TestTree =  CreateActor<NormalProp>(EUPDATEORDER::Objects);
	TestTree->Transform.SetLocalPosition(float4(200.0f, -400.0f, DepthFunction::CalculateObjectDepth(GlobalValue::GetWindowScale().Y, -400.0f)));
	TestTree->Init();
	TestTree->m_Renderer->Transform.SetLocalPosition(float4(0.0f, 110.0f));
	TestTree->m_Renderer->SetSprite("Tree_2.png");
	TestTree->m_Renderer->RenderBaseInfoValue.Target1 = 1;
}