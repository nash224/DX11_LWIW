#include "PreCompile.h"
#include "SkyLerp.h"

#include "PlayLevel.h"

#include "TimeManager.h"
#include "CameraControler.h"

SkyLerp* SkyLerp::SkyManager = nullptr;
SkyLerp::SkyLerp() 
{
}

SkyLerp::~SkyLerp() 
{
}


void SkyLerp::Update(float _Delta)
{
	UpdateSkyLerp();
	FollowCamera();
}

void SkyLerp::Release()
{
	SkyManager = nullptr;
	Sun_Renderer = nullptr;
	SkyData.clear();
}

void SkyLerp::LevelStart(class GameEngineLevel* _NextLevel)
{
	SkyManager = this;
}


/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////



void SkyLerp::Init()
{
	SkyManager = this;

	static const std::uint32_t SkyOrder = 0;

	Sun_Renderer = CreateComponent<GameEngineSpriteRenderer>(SkyOrder);
	Sun_Renderer->SetSprite("SkyBox.png");
	Sun_Renderer->GetImageTransform().SetLocalScale(GlobalValue::GetWindowScale() + float4(30.0f, 30.0f));
	Sun_Renderer->GetColorData().MulColor.A = 0.0f;


	SkyData.reserve(29);
	SkyData.push_back(Sky_300);
	SkyData.push_back(Sky_310);
	SkyData.push_back(Sky_320);
	SkyData.push_back(Sky_330);
	SkyData.push_back(Sky_340);
	SkyData.push_back(Sky_350);
	SkyData.push_back(Sky_400);
	SkyData.push_back(Sky_410);
	SkyData.push_back(Sky_420);
	SkyData.push_back(Sky_430);
	SkyData.push_back(Sky_440);
	SkyData.push_back(Sky_450);
	SkyData.push_back(Sky_500);
	SkyData.push_back(Sky_510);
	SkyData.push_back(Sky_520);
	SkyData.push_back(Sky_530);
	SkyData.push_back(Sky_540);
	SkyData.push_back(Sky_550);
	SkyData.push_back(Sky_600);
	SkyData.push_back(Sky_610);
	SkyData.push_back(Sky_620);
	SkyData.push_back(Sky_630);
	SkyData.push_back(Sky_640);
	SkyData.push_back(Sky_650);
	SkyData.push_back(Sky_700);
	SkyData.push_back(Sky_710);
	SkyData.push_back(Sky_720);
	SkyData.push_back(Sky_730);
	SkyData.push_back(Sky_740);

	if (nullptr == PlayLevel::s_TimeManager)
	{
		MsgBoxAssert("타임 매니저가 존재하지 않습니다.");
		return;
	}

	TenMinuteTimeRatio = PlayLevel::s_TimeManager->GetMinuteRatio();
	PlayLevel::s_TimeManager->SetTime(13, 20);

	SunsetStartTimeRatio = CalculateTimeRatio((SunsetStartHour - PlayLevel::s_TimeManager->GetStartHour()) * 6);
	SunsetEndTimeRatio = CalculateTimeRatio(static_cast<int>(SkyData.size()) - 1) + SunsetStartTimeRatio;

	LerpSky(SkyData[0]);
}


// 하늘 고정색 지정
void SkyLerp::SetSkyColor()
{
	PauseSkyLerp = true;

	Sun_Renderer->GetColorData().MulColor = SkyColor;
}

// 일몰 업데이트
void SkyLerp::UpdateSkyLerp()
{
	if (true == PauseSkyLerp)
	{
		return;
	}


	if (nullptr == PlayLevel::s_TimeManager)
	{
		MsgBoxAssert("시간 매니저가 존재하지 않습니다.");
		return;
	}

	// 1 / 

	float TimeRatio = PlayLevel::s_TimeManager->GetTimeRatio();
	if (TimeRatio > SunsetStartTimeRatio)
	{
		float SunSetRatio = (TimeRatio - SunsetStartTimeRatio) / (SunsetEndTimeRatio - SunsetStartTimeRatio);
		SunSetRatio *= static_cast<float>(SkyData.size() - 1);
		float fRefNumber;

		SunSetRatio = std::modff(SunSetRatio, &fRefNumber);								// 정수부, 소수부 분리
		int RefNumber = static_cast<int>(fRefNumber);

		int MaxRefNumber = static_cast<int>(SkyData.size() - 1);
		if (RefNumber < MaxRefNumber)
		{
			LerpSky(SkyData[RefNumber], SkyData[static_cast<size_t>(RefNumber) + 1], SunSetRatio);			// 색 보간
		}
		else
		{
			LerpSky(SkyData[MaxRefNumber]);
		}
	}
	else
	{
		LerpSky(SkyData[0]);
	}
}

float SkyLerp::CalculateTimeRatio(int _MinuteCount)
{
	return static_cast<float>(_MinuteCount * TenMinuteTimeRatio);
}

void SkyLerp::LerpSky(const float4& _ColorA, const float4& _ColorB, const float _Time)
{
	SkyColor.R = std::lerp(_ColorA.R, _ColorB.R, _Time);
	SkyColor.G = std::lerp(_ColorA.G, _ColorB.G, _Time);
	SkyColor.B = std::lerp(_ColorA.B, _ColorB.B, _Time);
	SkyColor.A = std::lerp(_ColorA.A, _ColorB.A, _Time);

	LerpSky(SkyColor);
}

void SkyLerp::LerpSky(const float4& _Color)
{
	if (nullptr == Sun_Renderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	Sun_Renderer->GetColorData().MulColor = _Color;
}


void SkyLerp::FollowCamera() 
{
	if (nullptr == GlobalValue::g_CameraControler)
	{
		return;
	}

	const float4 CameraPos = GlobalValue::g_CameraControler->GetCameraCurrentPostion();
	float4 SkyPos = CameraPos;
	SkyPos.Z = GlobalUtils::CalculateFixDepth(ERENDERDEPTH::SkyBox);

	Transform.SetLocalPosition(SkyPos);
}