#include "PreCompile.h"
#include "BGMManager.h"

BGMManager::BGMManager() 
{
	ResourceLoad();
}

BGMManager::~BGMManager() 
{
}


void BGMManager::Update(float _Delta)
{
	State.Update(_Delta);
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void BGMManager::Init()
{
	StateSetting();
}

void BGMManager::StateSetting()
{

}


void BGMManager::StartAmplification(GameEngineState* _Parent)
{
	BGM.Stop();
	BGM_SFX.Stop();

	BGM = GameEngineSound::SoundPlay(BGMName, 999);

	if (false == BGM_SFXName.empty())
	{
		BGM_SFX = GameEngineSound::SoundPlay(BGM_SFXName, 999);
	}

	isPlayBGM = true;
}

void BGMManager::UpdateAmplification(float _Delta, GameEngineState* _Parent)
{
	BGMVolume += _Delta / AmplificationTime;
	SetVolume();

	if (BGMVolume >= Max_BGM_Volume)
	{
		State.ChangeState(EBGMSTATE::Play);
	}
}

void BGMManager::UpdateAttenuation(float _Delta, GameEngineState* _Parent)
{
	static constexpr float ReadyTime = 2.0f;

	BGMVolume -= _Delta / AmplificationTime;
	SetVolume();

	if (BGMVolume <= 0.0f)
	{
		if (true == BGMName.empty())
		{
			State.ChangeState(EBGMSTATE::Stop);
		}
		else
		{
			if (_Parent->GetStateTime() > ReadyTime)
			{
				State.ChangeState(EBGMSTATE::Amplification);
			}
		}
	}
}


void BGMManager::StartStop(GameEngineState* _Parent)
{
	BGM.Stop();
	BGM_SFX.Stop();
	BGMName.clear();
	BGM_SFXName.clear();
	isPlayBGM = false;
}

void BGMManager::PlayBGM(std::string_view _BGMName, std::string_view _BGM_SFXName /*= ""*/)
{
	if (BGMName == _BGMName.data() || true == _BGMName.empty())
	{
		return;
	}

	if (false == _BGM_SFXName.empty())
	{
		BGM_SFXName = _BGM_SFXName;
	}

	if (true == BGMName.empty())
	{
		BGMName = _BGMName.data();
		State.ChangeState(EBGMSTATE::Amplification);
	}
	else
	{
		BGMName = _BGMName.data();
		State.ChangeState(EBGMSTATE::Attenuation);
	}
}

void BGMManager::NoneBGM()
{
	BGMName.clear();
	BGM_SFXName.clear();
	State.ChangeState(EBGMSTATE::Attenuation);
}

void BGMManager::StopBGM()
{
	State.ChangeState(EBGMSTATE::Stop);
}

bool BGMManager::IsBGMPlay() const
{
	return isPlayBGM;
}

void BGMManager::SetVolume()
{
	if (BGMVolume > Max_BGM_Volume)
	{
		BGMVolume = Max_BGM_Volume;
	}

	if (BGMVolume < Min_BGM_Volume)
	{
		BGMVolume = Min_BGM_Volume;
	}

	BGM.SetVolume(BGMVolume);
	BGM_SFX.SetVolume(BGMVolume);
}



void BGMManager::ResourceLoad()
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