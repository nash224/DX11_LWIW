#include "PreCompile.h"
#include "FieldLevel.h"

#include <GameEngineCore/GameEngineRenderTarget.h>

#include "SkyLerp.h"
#include "SkyLightEffect.h"
#include "TimeManager.h"
#include "BGMManager.h"


FieldLevel::FieldLevel() 
{
	
}

FieldLevel::~FieldLevel() 
{
}


void FieldLevel::Start()
{
	PlayLevel::Start();

	Sky = CreateActor<SkyLerp>(EUPDATEORDER::Sky);
	Sky->Init();

	GetMainCamera()->GetCameraAllRenderTarget()->CreateEffect<SkyLightEffect>();
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


void FieldLevel::AutoPlayBGM()
{
	if (nullptr != MainPlaySound && nullptr != s_TimeManager)
	{
		int bgmType = MainPlaySound->GetPlayType();
		if (bgmType == static_cast<int>(EPLAYBGMTYPE::Event))
		{
			return;
		}

		if (true == s_TimeManager->IsDay() && static_cast<int>(EPLAYBGMTYPE::Day) != bgmType)
		{
			MainPlaySound->PlayBGM(EPLAYBGMTYPE::Day, "0424_Forest_Day.wav", "AMB_GF_Daytime_01.wav");
		}

		if (false == s_TimeManager->IsDay() && static_cast<int>(EPLAYBGMTYPE::Night) != bgmType)
		{
			MainPlaySound->PlayBGM(EPLAYBGMTYPE::Night, "0424_Forest_Night.wav", "AMB_GF_Nighttime_01.wav");
		}
	}
}