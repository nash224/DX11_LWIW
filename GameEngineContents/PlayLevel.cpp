#include "PreCompile.h"
#include "PlayLevel.h"

// GUI
#include <GameEngineCore/GameEngineCoreWindow.h>


// Manager
#include "CameraControler.h"
#include "UIManager.h"
#include "TimeManager.h"
#include "AlertManager.h"
#include "BGMManager.h"

// Actor
#include "Ellie.h"
#include "FadeObject.h"
#include "UI_Alert_Enter.h"

#include "SkyLightEffect.h"

std::weak_ptr<PlayLevel> PlayLevel::s_MainPlayLevel;
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

	if (nullptr == s_TimeManager)
	{
		s_TimeManager = std::make_unique<TimeManager>();
		s_TimeManager->Init();
	}

	if (nullptr == s_AlertManager)
	{
		s_AlertManager = std::make_unique<AlertManager>();
	}

	EffectSetting();
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
}

void PlayLevel::LevelStart(GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelStart(_NextLevel);

	s_MainPlayLevel = GetDynamic_Cast_This<PlayLevel>();

	PrevLevelName = _NextLevel->GetName();

	if (false == LevelInitCheck)
	{
		CreateEllie();
		CreateUIManager();
	}
	

	LevelInitCheck = true;

	{
		std::shared_ptr<FadeObject> Fade = CreateActor<FadeObject>(EUPDATEORDER::Fade);
		Fade->CallFadeIn(0.2f);
	}


	if (false == LocationKRName.empty())
	{
		s_AlertManager->RegisterAlert(AlertData(LocationKRName, EALERTTYPE::Enter));
	}
}

void PlayLevel::CreateUIManager()
{
	UI_Manager = CreateActor<UIManager>(EUPDATEORDER::UIMagnaer);
	UI_Manager->Init();
}

void PlayLevel::CreateEllie()
{
	Player = CreateActor<Ellie>(EUPDATEORDER::Player);
	Player->Init();
}

void PlayLevel::SetLocationName(std::string_view _KRName)
{
	LocationKRName = _KRName;
}

void PlayLevel::EffectSetting()
{
	{
		GetMainCamera()->GetCameraAllRenderTarget()->CreateEffect<SkyLightEffect>();
	}
}