#include "PreCompile.h"
#include "PlayLevel.h"

// GUI
#include <GameEngineCore/GameEngineCoreWindow.h>


// Manager
#include "CameraControler.h"
#include "UIManager.h"
#include "TimeManager.h"
#include "AlertManager.h"

// Actor
#include "Ellie.h"
#include "FadeObject.h"
#include "UI_Alert_Enter.h"

#include "SkyLightEffect.h"

std::unique_ptr<TimeManager> PlayLevel::s_TimeManager;
std::unique_ptr<AlertManager> PlayLevel::s_AlertManager;
std::unique_ptr<PlayLevel::PlaySoundInfo> PlayLevel::MainPlaySound;
PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
	//if (nullptr != MainPlaySound)
	//{
	//	MainPlaySound.release();
	//	MainPlaySound = nullptr;
	//}
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

	if (nullptr == MainPlaySound)
	{
		MainPlaySound = std::make_unique<PlaySoundInfo>();
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

	if (false == LevelInitCheck)
	{
		CreateEllie();			// 敲饭捞绢 积己
		CreateUIManager();		// UI 积己
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

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelEnd(_NextLevel);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



// UI 概聪历 积己
void PlayLevel::CreateUIManager()
{
	m_UIManager = CreateActor<UIManager>(EUPDATEORDER::UIMagnaer);
	m_UIManager->Init();
}

// 敲饭捞绢 积己
void PlayLevel::CreateEllie()
{
	m_Ellie = CreateActor<Ellie>(EUPDATEORDER::Player);
	m_Ellie->Init();
}

void PlayLevel::SetLocationName(std::string_view _KRName)
{
	LocationKRName = _KRName;
}


void PlayLevel::PlaySoundInfo::PlayBGM(std::string_view _BGMName, std::string_view _BGM_SFXName /*= ""*/)
{
	if (nullptr == GameEngineSound::FindSound(_BGMName))
	{
		ResourceLoad();
	}

	if (BGMName == _BGMName.data())
	{
		return;
	}

	Stop();

	BGM = GameEngineSound::SoundPlay(_BGMName, 999);
	BGM.SetVolume(GlobalValue::GetSoundVolume() * BGMVolume);

	BGMName = _BGMName.data();

	if (false == _BGM_SFXName.empty())
	{
		BGM_SFX = GameEngineSound::SoundPlay(_BGM_SFXName, 999);
		BGM_SFX.SetVolume(GlobalValue::GetSoundVolume() * BGMVolume);
	}

	isPlayBGM = true;
}

bool PlayLevel::PlaySoundInfo::IsBGMPlay()
{
	return isPlayBGM;
}

void PlayLevel::PlaySoundInfo::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\Sound\\BGM\\Play");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (GameEngineFile pFile : Files)
	{
		GameEngineSound::SoundLoad(pFile.GetStringPath());
	}
}

void PlayLevel::PlaySoundInfo::Stop()
{
	BGM.Stop();
	BGM_SFX.Stop();
	isPlayBGM = false;
}

void PlayLevel::PlaySoundInfo::SetVolume(float _Value)
{
	if (_Value > Max_BGM_Volume)
	{
		BGMVolume = Max_BGM_Volume;
	}

	if (_Value < Min_BGM_Volume)
	{
		BGMVolume = Min_BGM_Volume;
	}

	BGMVolume = _Value;
}

void PlayLevel::EffectSetting()
{
	{
		GetMainCamera()->GetCameraAllRenderTarget()->CreateEffect<SkyLightEffect>();
	}
}