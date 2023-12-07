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

#include "ContentsSpriteRenderer.h"

#include "PixelManager.h"
#include "TestPlayer.h"
#include "ALightActor.h"



void TestGUI::OnGUI(GameEngineLevel* _Level, float _Delta)
{
	if (nullptr != LevelPtr)
	{
		if (nullptr != LevelPtr->AlightPtr)
		{
			ImGui::SeparatorText("LightDebug");
			if (ImGui::ColorEdit4("Color", &LightColor.R))
			{
				LevelPtr->AlightPtr->SetColor(LightColor);
			}
			if (ImGui::SliderFloat("Correction", &Correction, 0.0f, 1.0f, "%.2f"))
			{
				LevelPtr->AlightPtr->SetAlphaCorrection(Correction);
			}
			if (ImGui::SliderFloat("Inner", &Inner, 0.0f, 1.0f, "%.2f"))
			{
				LevelPtr->AlightPtr->SetInner(Inner);
			}
			if (ImGui::SliderFloat("Outter", &Outter, 0.0f, 1.0f, "%.2f"))
			{
				LevelPtr->AlightPtr->SetOutter(Outter);
			}
			if (ImGui::SliderFloat("Size", &Size, 0.0f, 2.0f, "%.2f"))
			{
				LevelPtr->AlightPtr->Transform.SetLocalScale(float4(Size, Size, 1.0f));
				LevelPtr->AlightPtr->SetOutter(Size);
			}
		}
	}
}



TestLevel::TestLevel() 
{
	if (nullptr != LevelCamera)
	{
		float4 Position = GlobalValue::GetWindowScale().Half();
		Position.Y *= -1.0f;
		LevelCamera->SetCameraPos(Position);
		LevelCamera->SetCameraMode(ECAMERAMODE::Fix);
	}
}

TestLevel::~TestLevel() 
{
}


void TestLevel::Start()
{
	GameEngineInput::AddInputObject(this);

	GetMainCamera()->GetCameraAllRenderTarget()->CreateEffect<OutLineEffect>();

	const std::shared_ptr<GameEngineCoreWindow>& Window = GameEngineGUI::FindGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow");
	if (nullptr != Window)
	{
		Window->AddDebugRenderTarget(0, "TestRenderTarget", GetMainCamera()->GetCameraAllRenderTarget());
		Window->AddDebugRenderTarget(3, "TestPixelRenderTarget", GetCamera(static_cast<int>(ECAMERAORDER::MainPrev))->GetCameraAllRenderTarget());
	}

	if (true)
	{
		SkyLight = CreateActor<SkyLerp>(EUPDATEORDER::Sky);
	}

	TestGUIWindow = GameEngineGUI::CreateGUIWindow<TestGUI>("TestGUI");
	TestGUIWindow->LevelPtr = this;
	TestGUIWindow->Off();
}

void TestLevel::Update(float _Delta)
{
	PlayLevel::Update(_Delta);

	if (nullptr != TestGUIWindow && true == GameEngineInput::IsDown(VK_F8, this))
	{
		if (true == TestGUIWindow->IsUpdate())
		{
			TestGUIWindow->Off();
		}
		else
		{
			TestGUIWindow->On();
		}
	}
}

void TestLevel::LevelStart(class GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelStart(_NextLevel);

	const float4 WinScale = GlobalValue::GetWindowScale();

	{
		float4 Position = WinScale.Half();
		Position.Y *= -1.0f;
		Position.Z = DepthFunction::CalculateFixDepth(ERENDERDEPTH::Back_Paint);
		Map = CreateActor<GameEngineActor>(EUPDATEORDER::Objects);
		Map->Transform.SetLocalPosition(Position);

		std::shared_ptr<GameEngineSpriteRenderer> BaseRenderer = Map->CreateComponent<GameEngineSpriteRenderer>(0);
		BaseRenderer->SetSprite("GroundBase.png");
		BaseRenderer->GetImageTransform().SetLocalScale(WinScale);
	}

	if (false)
	{
		PixelManagerPtr = CreateActor<PixelManager>(EUPDATEORDER::Back);
	}

	{
		float4 InitialPosition = WinScale.Half();
		InitialPosition.Y *= -1.0f;
		Player = CreateActor<TestPlayer>(EUPDATEORDER::Player);
		Player->Transform.SetLocalPosition(InitialPosition);
	}


	TestCode();

	if (false)
	{
		SetPixelMap();
	}
}

void TestLevel::LevelEnd(class GameEngineLevel* _NextLevel)
{
	if (nullptr != TestGUIWindow)
	{
		TestGUIWindow->Off();
	}

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

	if (nullptr != PixelManagerPtr)
	{
		PixelManagerPtr->Death();
		PixelManagerPtr = nullptr;
	}

	if (nullptr != bush)
	{
		bush->Death();
		bush = nullptr;
	}

	if (nullptr != ButtonGuide)
	{
		ButtonGuide->Death();
		ButtonGuide = nullptr;
	}

	std::vector<std::shared_ptr<SilverStarFlower>> SBFGroup = GetObjectGroupConvert<SilverStarFlower>(EUPDATEORDER::Objects);
	for (const std::shared_ptr<SilverStarFlower>& SBF : SBFGroup)
	{
		SBF->Death();
	}

	std::vector<std::shared_ptr<WitchFlower>> WFGroup = GetObjectGroupConvert<WitchFlower>(EUPDATEORDER::Objects);
	for (const std::shared_ptr<WitchFlower>& WF : WFGroup)
	{
		WF->Death();
	}

	std::vector<std::shared_ptr<MongSiri_Population>> PopulationGroup = GetObjectGroupConvert<MongSiri_Population>(EUPDATEORDER::Objects);
	for (const std::shared_ptr<MongSiri_Population>& Population : PopulationGroup)
	{
		Population->ActorRelaese();
	}

	if (nullptr != UI)
	{
		UI->Death();
		UI = nullptr;
	}
}

void TestLevel::TestCode()
{
	if (true)
	{

		{
			UI = CreateActor<UIManager>(EUPDATEORDER::UIMagnaer);
			UI->Init();
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
			std::shared_ptr<UI_Hub_MainBoard> MainBoard = CreateActor<UI_Hub_MainBoard>(EUPDATEORDER::UIMagnaer);
			MainBoard->Init();
		}

		if (true)
		{
			std::vector<ButtonInfoParameter> Paras =
			{
				{EBUTTONTYPE::A, "뽑기"},
				{EBUTTONTYPE::QW, "자기"},
				{EBUTTONTYPE::ER, "태우기"},
				{EBUTTONTYPE::Space, "달리기"},
			};

			ButtonGuide = CreateActor<TestCircleGauge>(EUPDATEORDER::Objects);
			ButtonGuide->GaugeRenderer->Transform.SetLocalPosition(float4(200.0f, -100.0f));
			Guide.SetGuideInfo(ButtonGuide.get(), Paras);
			Guide.On();
		}

		if (false)
		{
			std::shared_ptr<NormalProp> TestTree =  CreateActor<NormalProp>(EUPDATEORDER::Objects);
			TestTree->Transform.SetLocalPosition(float4(200.0f, -400.0f, DepthFunction::CalculateObjectDepth(GlobalValue::GetWindowScale().Y, -400.0f)));
			TestTree->Init();
			TestTree->m_Renderer->Transform.SetLocalPosition(float4(0.0f, 110.0f));
			TestTree->m_Renderer->SetSprite("Tree_2.png");
			TestTree->m_Renderer->RenderBaseInfoValue.Target1 = 1;
		}

		if (false)
		{
			std::shared_ptr<RendererActor> TestCamera =  CreateActor<RendererActor>(EUPDATEORDER::Objects);
			TestCamera->Transform.SetLocalPosition(float4(200.0f, -400.0f, DepthFunction::CalculateObjectDepth(GlobalValue::GetWindowScale().Y, -400.0f)));
			TestCamera->Init();
			TestCamera->m_Renderer->SetViewCameraSelect(static_cast<int>(ECAMERAORDER::MainPrev));
			TestCamera->m_Renderer->Transform.SetLocalPosition(float4(0.0f, 110.0f));
			TestCamera->m_Renderer->SetSprite("Tree_1.png");
			TestCamera->m_Renderer->RenderBaseInfoValue.Target1 = 1;
			TestCamera->m_Renderer->RenderBaseInfoValue.Target0 = 0;

			// GetCamera(static_cast<int>(ECAMERAORDER::MainPrev))->GetCameraAllRenderTarget()->GetTexture(1)->GetColor();
		}
	}

	if (false)
	{
		std::shared_ptr<RendererActor> LightTest = CreateActor<RendererActor>();
		LightTest->Transform.SetLocalPosition(float4(480.0f, -270.0f));
		std::shared_ptr<ContentsSpriteRenderer> LightRenderer = LightTest->CreateComponent<ContentsSpriteRenderer>();
		LightRenderer->SetMaterial("ContentsLight2DTexture");
		LightRenderer->SetSprite("Circle.png");
		LightRenderer->GetTransparentInfo().iTransparent = 1;
		LightRenderer->GetTransparentInfo().Inner = 0.2f;
		LightRenderer->GetTransparentInfo().Outter = 1.0f;
	}

	if (true)
	{
		std::shared_ptr<ALightActor> LightTest = CreateActor<ALightActor>(EUPDATEORDER::Objects);
		LightTest->Transform.SetLocalPosition(float4(480.0f, -270.0f));
		LightTest->Init();
		LightTest->SetImageScale(float4(100.0f, 100.0f));
		LightTest->SetColor(float4(0.8f, 0.7f, 0.2f));
		LightTest->SetAlphaCorrection(0.4f);
		LightTest->SetInner(0.2f);

		AlightPtr = LightTest;
	}
}


void TestLevel::SetPixelMap()
{
	std::shared_ptr<NormalProp> MapPixel = CreateActor<NormalProp>(EUPDATEORDER::Objects);
	MapPixel->Transform.SetLocalPosition(float4(300.0f, -200.0f));
	MapPixel->SetPixelCollision("Bench_2_Pixel.png");
	MapPixel->m_DebugRenderer->SetViewCameraSelect(static_cast<int>(ECAMERAORDER::MainPrev));
	MapPixel->m_DebugRenderer->RenderBaseInfoValue.Target0 = 0;
	MapPixel->m_DebugRenderer->RenderBaseInfoValue.Target1 = 1;
	MapPixel->m_DebugRenderer->On();

	MapPixel = CreateActor<NormalProp>(EUPDATEORDER::Objects);
	MapPixel->Transform.SetLocalPosition(float4(100.0f, -100.0f));
	MapPixel->SetPixelCollision("FlowerPot_pixel.png");
	MapPixel->m_DebugRenderer->SetViewCameraSelect(static_cast<int>(ECAMERAORDER::MainPrev));
	MapPixel->m_DebugRenderer->RenderBaseInfoValue.Target0 = 0;
	MapPixel->m_DebugRenderer->RenderBaseInfoValue.Target1 = 1;
	MapPixel->m_DebugRenderer->On();

	MapPixel = CreateActor<NormalProp>(EUPDATEORDER::Objects);
	MapPixel->Transform.SetLocalPosition(float4(700.0f, -400.0f));
	MapPixel->SetPixelCollision("Tree_Pixel.png");
	MapPixel->m_DebugRenderer->SetViewCameraSelect(static_cast<int>(ECAMERAORDER::MainPrev));
	MapPixel->m_DebugRenderer->RenderBaseInfoValue.Target0 = 0;
	MapPixel->m_DebugRenderer->RenderBaseInfoValue.Target1 = 1;
	MapPixel->m_DebugRenderer->On();

	MapPixel = CreateActor<NormalProp>(EUPDATEORDER::Objects);
	MapPixel->Transform.SetLocalPosition(float4(600.0f, -300.0f));
	MapPixel->SetPixelCollision("Tree_Pixel.png");
	MapPixel->m_DebugRenderer->SetViewCameraSelect(static_cast<int>(ECAMERAORDER::MainPrev));
	MapPixel->m_DebugRenderer->RenderBaseInfoValue.Target0 = 0;
	MapPixel->m_DebugRenderer->RenderBaseInfoValue.Target1 = 1;
	MapPixel->m_DebugRenderer->On();

	if (bool isTestOn = false)
	{
		MapPixel = CreateActor<NormalProp>(EUPDATEORDER::Objects);
		MapPixel->Transform.SetLocalPosition(float4(480.0f, -270.0f));
		MapPixel->SetPixelCollision("Tree_Pixel.png");
		MapPixel->m_DebugRenderer->GetImageTransform().SetLocalScale(float4(300.0f, 300.0f));
		MapPixel->m_DebugRenderer->SetViewCameraSelect(static_cast<int>(ECAMERAORDER::MainPrev));
		MapPixel->m_DebugRenderer->RenderBaseInfoValue.Target0 = 0;
		MapPixel->m_DebugRenderer->RenderBaseInfoValue.Target1 = 1;
		MapPixel->m_DebugRenderer->On();
	}
}