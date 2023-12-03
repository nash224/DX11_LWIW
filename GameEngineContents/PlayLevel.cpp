#include "PreCompile.h"
#include "PlayLevel.h"

// Manager
#include "UIManager.h"
#include "TimeManager.h"
#include "AlertManager.h"

// Actor
#include "Ellie.h"
#include "FadeObject.h"
#include "NormalProp.h"
#include "StaticEntity.h"


PlayLevel* PlayLevel::s_MainPlayLevel = nullptr;
std::unique_ptr<TimeManager> PlayLevel::s_TimeManager;
std::unique_ptr<AlertManager> PlayLevel::s_AlertManager;
PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{

}

void PlayLevel::Start()
{
	ContentsLevel::Start();

	s_MainPlayLevel = this;

	Player = CreateActor<Ellie>(EUPDATEORDER::Player);

	UIManagerPtr = CreateActor<UIManager>(EUPDATEORDER::UIMagnaer);
	UIManagerPtr->Init();

	if (nullptr == s_TimeManager)
	{
		s_TimeManager = std::make_unique<TimeManager>();
	}

	if (nullptr == s_AlertManager)
	{
		s_AlertManager = std::make_unique<AlertManager>();
	}
}

void PlayLevel::Update(float _Delta)
{
	ContentsLevel::Update(_Delta);

	if (nullptr != s_TimeManager)
	{
		s_TimeManager->Update(_Delta);
	}

	if (nullptr != s_AlertManager)
	{
		s_AlertManager->Update(_Delta);
	}

	ChangeDebugMode();
}

void PlayLevel::LevelStart(GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelStart(_NextLevel);

	s_MainPlayLevel = this;
	PrevLevelName = _NextLevel->GetName();

	{
		std::shared_ptr<FadeObject> Fade = CreateActor<FadeObject>(EUPDATEORDER::Fade);
		Fade->CallFadeIn(0.2f);
	}

	if (false == LocationKRName.empty())
	{
		s_AlertManager->RegisterAlert(AlertData(LocationKRName, EALERTTYPE::Enter));
	}
}


PlayLevel* PlayLevel::GetPlayLevelPtr()
{
	if (nullptr == s_MainPlayLevel)
	{
		MsgBoxAssert("메인 레벨 포인터가 존재하지 않습니다.");
		return nullptr;
	}

	return s_MainPlayLevel;
}

std::shared_ptr<class UIManager> PlayLevel::GetUIManagerPtr() const
{
	if (nullptr == UIManagerPtr)
	{
		MsgBoxAssert("UI매니저가 존재하지 않습니다.");
		return nullptr;
	}

	return UIManagerPtr;
}

std::shared_ptr<class Ellie> PlayLevel::GetPlayerPtr() const
{
	if (nullptr == Player)
	{
		MsgBoxAssert("UI매니저가 존재하지 않습니다.");
		return nullptr;
	}

	return Player;
}

std::shared_ptr<class BackDrop_PlayLevel> PlayLevel::GetBackDropPtr() const
{
	if (nullptr == Back)
	{
		return nullptr;
	}

	return Back;
}


void PlayLevel::ChangeDebugMode()
{
	if (true == GameEngineInput::IsDown(VK_F1, this))
	{
		IsDebug = !IsDebug;
	}

	if (true == GameEngineInput::IsDown(VK_F2, this))
	{
		PixelDebugMode = !PixelDebugMode;
		if (true == PixelDebugMode)
		{
			std::vector<std::shared_ptr<RendererActor>> RenderActors = GetObjectGroupConvert<RendererActor>(EUPDATEORDER::Objects);
			for (const std::shared_ptr<RendererActor>& Actor : RenderActors)
			{
				if (nullptr != Actor->m_Renderer)
				{
					Actor->m_Renderer->Off();
				}
			}

			std::vector<std::shared_ptr<NormalProp>> Props = GetObjectGroupConvert<NormalProp>(EUPDATEORDER::Objects);
			for (const std::shared_ptr<NormalProp>& Prop : Props)
			{
				if (true == Prop->GetPixelCheck())
				{
					Prop->m_DebugRenderer->On();
				}
			}

			std::vector<std::shared_ptr<StaticEntity>> Entitys = GetObjectGroupConvert<StaticEntity>(EUPDATEORDER::Entity);
			for (const std::shared_ptr<StaticEntity>& Entity : Entitys)
			{
				if (true == Entity->GetPixelCheck())
				{
					Entity->PixelRenderer->On();
					Entity->BodyRenderer->Off();
				}
			}
		}
		else
		{
			std::vector<std::shared_ptr<RendererActor>> RenderActors = GetObjectGroupConvert<RendererActor>(EUPDATEORDER::Objects);
			for (const std::shared_ptr<RendererActor>& Actor : RenderActors)
			{
				if (nullptr != Actor->m_Renderer)
				{
					Actor->m_Renderer->On();
				}
			}

			std::vector<std::shared_ptr<NormalProp>> Props = GetObjectGroupConvert<NormalProp>(EUPDATEORDER::Objects);
			for (const std::shared_ptr<NormalProp>& Prop : Props)
			{
				if (true == Prop->GetPixelCheck())
				{
					Prop->m_DebugRenderer->Off();
				}
			}

			std::vector<std::shared_ptr<StaticEntity>> Entitys = GetObjectGroupConvert<StaticEntity>(EUPDATEORDER::Entity);
			for (const std::shared_ptr<StaticEntity>& Entity : Entitys)
			{
				if (true == Entity->GetPixelCheck())
				{
					Entity->PixelRenderer->Off();
					Entity->BodyRenderer->On();
				}
			}
		}
	}
}