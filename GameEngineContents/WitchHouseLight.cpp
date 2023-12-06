#include "PreCompile.h"
#include "WitchHouseLight.h"

#include "TimeManager.h"



static constexpr float MINALPHA = 0.2f;
static constexpr float MAXALPHA = 0.6f;

#define DAYLIGHTCOLOR {1.0f, 0.96f, 0.62f, 1.0f}
#define NIGHTLIGHTCOLOR {0.88f, 0.94f, 1.0f, 1.0f}

WitchHouseLight::WitchHouseLight() 
{
}

WitchHouseLight::~WitchHouseLight() 
{
}


void WitchHouseLight::Start()
{
	{
		CreateStateParameter DayState;
		DayState.Start = std::bind(&WitchHouseLight::StartDay, this, std::placeholders::_1);
		DayState.Stay = std::bind(&WitchHouseLight::UpdateDay, this, std::placeholders::_1, std::placeholders::_2);
		State.CreateState(EWLIGHTSTATE::Day, DayState);

		CreateStateParameter ChangeState;
		ChangeState.Stay = std::bind(&WitchHouseLight::UpdateChange, this, std::placeholders::_1, std::placeholders::_2);
		State.CreateState(EWLIGHTSTATE::Change, ChangeState);

		CreateStateParameter NightState;
		NightState.Stay = std::bind(&WitchHouseLight::UpdateNight, this, std::placeholders::_1, std::placeholders::_2);
		State.CreateState(EWLIGHTSTATE::Night, NightState);
	}


	{
		CreateStateParameter BrighterState;
		BrighterState.Stay = std::bind(&WitchHouseLight::UpdateBrighter, this, std::placeholders::_1, std::placeholders::_2);
		ChangeLightState.CreateState(EWLIGHT_CHANGESTATE::Brighter, BrighterState);

		CreateStateParameter DarkerState;
		DarkerState.Stay = std::bind(&WitchHouseLight::UpdateDarker, this, std::placeholders::_1, std::placeholders::_2);
		ChangeLightState.CreateState(EWLIGHT_CHANGESTATE::Darker, DarkerState);
	}

	{
		CreateStateParameter BrighterState;
		BrighterState.Start = std::bind(&WitchHouseLight::StartNightBrighter, this, std::placeholders::_1);
		BrighterState.Stay = std::bind(&WitchHouseLight::UpdateNightBrighter, this, std::placeholders::_1, std::placeholders::_2);
		NightState.CreateState(EWLIGHT_NIGHTSTATE::NightBrighter, BrighterState);

		CreateStateParameter DarkerState;
		DarkerState.Start = std::bind(&WitchHouseLight::StartNightDarker, this, std::placeholders::_1);
		DarkerState.Stay = std::bind(&WitchHouseLight::UpdateNightDarker, this, std::placeholders::_1, std::placeholders::_2);
		NightState.CreateState(EWLIGHT_NIGHTSTATE::NightDarker, DarkerState);
	}

	NightStartTime = PlayLevel::GetCurLevel()->GetTimeManager()->GetTime(18, 40);
}

void WitchHouseLight::Update(float _Delta)
{
	State.Update(_Delta);
}

void WitchHouseLight::Release()
{
	RendererActor::Release();
}

void WitchHouseLight::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}

void WitchHouseLight::Init(int _Order)
{
	m_Renderer = CreateComponent<GameEngineSpriteRenderer>(_Order);
	const float CurTime = PlayLevel::GetCurLevel()->GetTimeManager()->GetTime();
	if (CurTime > NightStartTime)
	{
		State.ChangeState(EWLIGHTSTATE::Night);
	}
	else
	{
		State.ChangeState(EWLIGHTSTATE::Day);
	}
}

#pragma region State

void WitchHouseLight::StartDay(GameEngineState* _Parent)
{
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	float4 Color = DAYLIGHTCOLOR;
	Color.A = MINALPHA;
	m_Renderer->GetColorData().MulColor = Color;
}


void WitchHouseLight::UpdateDay(float _Delta, GameEngineState* _Parent)
{
	const float CurTime = PlayLevel::GetCurLevel()->GetTimeManager()->GetTime();
	if (CurTime > NightStartTime)
	{
		State.ChangeState(EWLIGHTSTATE::Change);
		ChangeLightState.ChangeState(EWLIGHT_CHANGESTATE::Brighter);
		return;
	}
}

void WitchHouseLight::UpdateChange(float _Delta, GameEngineState* _Parent)
{
	ChangeLightState.Update(_Delta);
}

void WitchHouseLight::UpdateNight(float _Delta, GameEngineState* _Parent)
{
	NightState.Update(_Delta);
}

#pragma endregion

#pragma region ChangeLightState

void WitchHouseLight::UpdateBrighter(float _Delta, GameEngineState* _Parent)
{
	const float ChangeTime = 0.3f;
	const float CurTime = _Parent->GetStateTime();
	if (CurTime >= ChangeTime)
	{
		ChangeLightState.ChangeState(EWLIGHT_CHANGESTATE::Darker);
		return;
	}


	const float TimeRatio = CurTime / ChangeTime;

	float4 FromColor = DAYLIGHTCOLOR;
	FromColor.A = MINALPHA;
	float4 ToColor = NIGHTLIGHTCOLOR;
	ToColor.A = MAXALPHA;
	LerpLightColor(FromColor, ToColor, TimeRatio);
}

void WitchHouseLight::UpdateDarker(float _Delta, GameEngineState* _Parent)
{
	const float ChangeTime = 0.3f;
	const float CurTime = _Parent->GetStateTime();
	if (CurTime >= ChangeTime)
	{
		State.ChangeState(EWLIGHTSTATE::Night);
		NightState.ChangeState(EWLIGHT_NIGHTSTATE::NightBrighter);
		return;
	}

	const float TimeRatio = CurTime / ChangeTime;

	float4 FromColor = NIGHTLIGHTCOLOR;
	FromColor.A = MAXALPHA;
	float4 ToColor = NIGHTLIGHTCOLOR;
	ToColor.A = MINALPHA;
	LerpLightColor(FromColor, ToColor, TimeRatio);
}

#pragma endregion

#pragma region NightState

void WitchHouseLight::StartNightBrighter(GameEngineState* _Parent)
{
	const float Chance = RandomFunction::GetRandomfValue(0.6f, 1.2f);
	NightLerpTime = powf(Chance, 2.0f);
	NightWaitTime = RandomFunction::GetRandomfValue(0.08f, 0.3f) + NightLerpTime;
	NotUpdateColor = false;
}

void WitchHouseLight::StartNightDarker(GameEngineState* _Parent)
{
	const float Chance = RandomFunction::GetRandomfValue(0.6f, 1.2f);
	NightLerpTime = powf(Chance, 2.0f);
	NightWaitTime = RandomFunction::GetRandomfValue(0.08f, 0.3f) + NightLerpTime;
	NotUpdateColor = false;
}


void WitchHouseLight::UpdateNightBrighter(float _Delta, GameEngineState* _Parent)
{
	const float CurTime = _Parent->GetStateTime();
	if (CurTime > NightLerpTime)
	{
		NotUpdateColor = true;
	}
	if (CurTime > NightWaitTime)
	{
		NightState.ChangeState(EWLIGHT_NIGHTSTATE::NightDarker);
		return;
	}

	const float TimeRatio = CurTime / NightLerpTime;
	LerpLightAlpha(MINALPHA, MAXALPHA, TimeRatio);
}

void WitchHouseLight::UpdateNightDarker(float _Delta, GameEngineState* _Parent)
{
	const float CurTime = _Parent->GetStateTime();
	if (CurTime > NightLerpTime)
	{
		NotUpdateColor = true;
	}
	if (CurTime > NightWaitTime)
	{
		NightState.ChangeState(EWLIGHT_NIGHTSTATE::NightBrighter);
		return;
	}

	const float TimeRatio = CurTime / NightLerpTime;
	LerpLightAlpha(MAXALPHA, MINALPHA, TimeRatio);
}

#pragma endregion


void WitchHouseLight::LerpLightColor(const float4& _From, const float4& _To, float _LerpTime)
{
	float4 Color;
	Color.R = std::lerp(_From.R, _To.R, _LerpTime);
	Color.G = std::lerp(_From.G, _To.G, _LerpTime);
	Color.B = std::lerp(_From.B, _To.B, _LerpTime);
	Color.A = std::lerp(_From.A, _To.A, _LerpTime);
	Alpha = Color.A;

	if (nullptr != m_Renderer)
	{
		m_Renderer->GetColorData().MulColor = Color;
	}
}

void WitchHouseLight::LerpLightAlpha(float _From, float _To, float _LerpTime) const
{
	if (true == NotUpdateColor)
	{
		return;
	}

	const float AlphaValue = std::lerp(_From, _To, _LerpTime);
	if (nullptr != m_Renderer)
	{
		m_Renderer->GetColorData().MulColor.A = std::clamp(AlphaValue, 0.0f, 1.0f);
	}
}