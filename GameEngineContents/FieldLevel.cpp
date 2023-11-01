#include "PreCompile.h"
#include "FieldLevel.h"

#include "SkyLerp.h"
#include "TimeManager.h"


FieldLevel::FieldLevel() 
{
}

FieldLevel::~FieldLevel() 
{
}


void FieldLevel::Start()
{
	PlayLevel::Start();

	m_SkyLerp = CreateActor<SkyLerp>(EUPDATEORDER::Sky);
	m_SkyLerp->Init();
}

void FieldLevel::Update(float _Delta)
{
	PlayLevel::Update(_Delta);

	AutoPlayBGM();
}

void FieldLevel::LevelStart(class GameEngineLevel* _NextLevel)
{
	PlayLevel::LevelStart(_NextLevel);
}

void FieldLevel::LevelEnd(class GameEngineLevel* _NextLevel)
{
	PlayLevel::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void FieldLevel::AutoPlayBGM()
{
	if (nullptr != s_TimeManager)
	{
		if (true == s_TimeManager->IsDay() && EBGMTYPE::Day != BGMType)
		{
			MainPlaySound.PlayBGM("0424_Forest_Day.wav", "AMB_GF_Daytime_01.wav");
			BGMType = EBGMTYPE::Day;
		}

		if (false == s_TimeManager->IsDay() && EBGMTYPE::Night != BGMType)
		{
			MainPlaySound.PlayBGM("0424_Forest_Night.wav", "AMB_GF_Nighttime_01.wav");
			BGMType = EBGMTYPE::Night;
		}
	}
}