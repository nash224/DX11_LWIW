#include "PreCompile.h"
#include "SkyLerp.h"

#include "EffectEnum.h"
#include "SkyLightEffect.h"

#include "PlayLevel.h"

#include "TimeManager.h"
#include "CameraControler.h"


#define Sky_300 { 0.6f, 0.8f, 0.0f, 0.1f }
#define Sky_310 { 0.65f, 0.7f, 0.0f, 0.11f }
#define Sky_320 { 0.7f, 0.6f, 0.0f, 0.12f }
#define Sky_330 { 0.75f, 0.5f, 0.0f, 0.13f }
#define Sky_340 { 0.8f, 0.4f, 0.0f, 0.14f }
#define Sky_350 { 0.8f, 0.34f, 0.0f, 0.15f }
#define Sky_400 { 0.8f, 0.3f, 0.0f, 0.16f }
#define Sky_410 { 0.85f, 0.26f, 0.0f, 0.18f }
#define Sky_420 { 0.9f, 0.21f, 0.0f, 0.19f }
#define Sky_430 { 0.95f, 0.15f, 0.0f, 0.2f }
#define Sky_440 { 0.95f, 0.11f, 0.0f, 0.21f }
#define Sky_450 { 0.95f, 0.08f, 0.0f, 0.23f }
#define Sky_500 { 0.94f, 0.04f, 0.0f, 0.24f }
#define Sky_510 { 0.91f, 0.02f, 0.0f, 0.25f }
#define Sky_520 { 0.91f, 0.01f, 0.0f, 0.26f }
#define Sky_530 { 0.91f, 0.0f, 0.0f, 0.27f }
#define Sky_540 { 0.91f, 0.0f, 0.0f, 0.28f }
#define Sky_550 { 0.88f, 0.0f, 0.01f, 0.3f }
#define Sky_600 { 0.82f, 0.0f, 0.02f, 0.32f }
#define Sky_610 { 0.74f, 0.0f, 0.03f, 0.35f }
#define Sky_620 { 0.62f, 0.0f, 0.05f, 0.38f }
#define Sky_630 { 0.5f, 0.0f, 0.06f, 0.42f }
#define Sky_640 { 0.4f, 0.0f, 0.07f, 0.46f }
#define Sky_650 { 0.3f, 0.0f, 0.08f, 0.5f }
#define Sky_700 { 0.2f, 0.0f, 0.09f, 0.54f }
#define Sky_710 { 0.1f, 0.0f, 0.1f, 0.58f }
#define Sky_720 { 0.03f, 0.0f, 0.12f, 0.62f } 
#define Sky_730 { 0.02f, 0.0f, 0.15f, 0.66f }
#define Sky_740 { 0.0f, 0.0f, 0.18f, 0.7f }


SkyLerp::SkyLerp() 
{
}

SkyLerp::~SkyLerp() 
{
}

void SkyLerp::Start()
{
	SkyEffectPtr = GetLevel()->GetMainCamera()->GetCameraAllRenderTarget()->CreateEffect<SkyLightEffect>();

	Sun_Renderer = CreateComponent<GameEngineSpriteRenderer>();
	Sun_Renderer->SetSprite("SkyBox.png");
	Sun_Renderer->GetImageTransform().SetLocalScale(GlobalValue::GetWindowScale() + float4(30.0f, 30.0f));
	Sun_Renderer->GetColorData().MulColor.A = 0.0f;
	Sun_Renderer->RenderBaseInfoValue.Target0 = 0;
	Sun_Renderer->RenderBaseInfoValue.Target2 = 1;

	SetSkyData();

	TenMinuteTimeRatio = PlayLevel::GetTimeManager()->GetMinuteRatio();

	SunsetStartTimeRatio = GetTimeRatio((SunsetStartHour - PlayLevel::GetTimeManager()->GetStartHour()) * 6);
	ALightStartTimeRatio = GetTimeRatio((AlightStartHour - PlayLevel::GetTimeManager()->GetStartHour()) * 6);
	SunsetEndTimeRatio = GetTimeRatio(static_cast<int>(SkyData.size()) - 1) + SunsetStartTimeRatio;

	LerpSky(SkyData[0]);
}

void SkyLerp::Update(float _Delta)
{
	UpdateSkyLerp();
	FollowCamera();
}

void SkyLerp::Release()
{
	SkyEffectPtr = nullptr;
	Sun_Renderer = nullptr;
	SkyData.clear();
}

void SkyLerp::SetSkyData()
{
	SkyData.reserve(32);
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
}

// 하늘 고정색 지정
void SkyLerp::SetSkyColor()
{
	Sun_Renderer->GetColorData().MulColor = SkyColor;
}

void SkyLerp::SetDebugSkyColor(const float4& _Color)
{
	SkyColor = _Color;

	PauseSkyLerp = true;

	Sun_Renderer->GetColorData().MulColor = SkyColor;
	UpdateSkyLerp();
}

float SkyLerp::GetALightValue() const
{
	return ALight;
}


// 일몰 업데이트
void SkyLerp::UpdateSkyLerp()
{
	if (true == PauseSkyLerp)
	{
		return;
	}

	const float TimeRatio = PlayLevel::GetTimeManager()->GetTimeRatio();

	bool isOver300PM = (TimeRatio > SunsetStartTimeRatio);
	if (isOver300PM)
	{
		float SunSetRatio = (TimeRatio - SunsetStartTimeRatio) / (SunsetEndTimeRatio - SunsetStartTimeRatio);

		UpdateALightRatio(TimeRatio);

		SunSetRatio *= static_cast<float>(SkyData.size() - 1);
		float fRefNumber;

		SunSetRatio = std::modff(SunSetRatio, &fRefNumber);	// 정수부, 소수부 분리
		const int RefNumber = static_cast<int>(fRefNumber);
		const int MaxRefNumber = static_cast<int>(SkyData.size() - 1);

		bool isOver740PM = (RefNumber < MaxRefNumber);
		if (isOver740PM)
		{
			LerpSky(SkyData.at(RefNumber), SkyData.at(RefNumber + 1), SunSetRatio);
		}
		else
		{
			LerpSky(SkyData.at(MaxRefNumber));
		}
	}
	else
	{
		ALight = 0.0f;
		LerpSky(SkyData[0]);
	}
}

float SkyLerp::GetTimeRatio(int _MinuteCount) const
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
	float4 SkyPos = PlayLevel::GetCurLevel()->GetLevelCameraPtr()->GetCameraCurrentPostion();
	SkyPos.Z = DepthFunction::CalculateFixDepth(ERENDERDEPTH::SkyBox);

	Transform.SetLocalPosition(SkyPos);
}

void SkyLerp::UpdateALightRatio(const float _TimeRatio)
{
	if (_TimeRatio > ALightStartTimeRatio)
	{
		float ALightRatio = (_TimeRatio - ALightStartTimeRatio) / (SunsetEndTimeRatio - ALightStartTimeRatio);
		ALight = powf(ALightRatio, 2.0f);

		if (ALight >= 1.0f)
		{
			ALight = 1.0f;
		}
	}
	else
	{
		ALight = 0.0f;
	}
}