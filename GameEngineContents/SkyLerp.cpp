#include "PreCompile.h"
#include "SkyLerp.h"

#include "EffectEnum.h"

#include "PlayLevel.h"

#include "TimeManager.h"
#include "CameraControler.h"

SkyLerp* SkyLerp::MainSkyManager = nullptr;
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
	MainSkyManager = nullptr;
	Sun_Renderer = nullptr;
	SkyData.clear();
}

void SkyLerp::LevelStart(class GameEngineLevel* _NextLevel)
{
	MainSkyManager = this;
}


/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////



void SkyLerp::Init()
{
	MainSkyManager = this;

	static const std::uint32_t SkyOrder = 0;

	Sun_Renderer = CreateComponent<GameEngineSpriteRenderer>(SkyOrder);
	Sun_Renderer->SetSprite("SkyBox.png");
	Sun_Renderer->GetImageTransform().SetLocalScale(GlobalValue::GetWindowScale() + float4(30.0f, 30.0f));
	Sun_Renderer->GetColorData().MulColor.A = 0.0f;
	Sun_Renderer->RenderBaseInfoValue.Target0 = 0;
	Sun_Renderer->RenderBaseInfoValue.Target2 = 1;


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

	if (nullptr == PlayLevel::s_TimeManager)
	{
		MsgBoxAssert("�ð��Ŵ��� ���̴� ����� �� ���� ����Դϴ�.");
		return;
	}

	TenMinuteTimeRatio = PlayLevel::s_TimeManager->GetMinuteRatio();
	/*PlayLevel::s_TimeManager->SetTime(13, 20);*/

	SunsetStartTimeRatio = CalculateTimeRatio((SunsetStartHour - PlayLevel::s_TimeManager->GetStartHour()) * 6);
	SunsetEndTimeRatio = CalculateTimeRatio(static_cast<int>(SkyData.size()) - 1) + SunsetStartTimeRatio;

	ALightStartTimeRatio = CalculateTimeRatio((AlightStartHour - PlayLevel::s_TimeManager->GetStartHour()) * 6);

	LerpSky(SkyData[0]);
}


// �ϴ� ������ ����
void SkyLerp::SetSkyColor()
{
	PauseSkyLerp = true;

	Sun_Renderer->GetColorData().MulColor = SkyColor;
}


float SkyLerp::GetALightValue() const
{
	return ALight;
}


// �ϸ� ������Ʈ
void SkyLerp::UpdateSkyLerp()
{
	if (true == PauseSkyLerp)
	{
		return;
	}

	if (nullptr == PlayLevel::s_TimeManager)
	{
		MsgBoxAssert("�ð��Ŵ��� ���̴� ����� �� ���� ����Դϴ�.");
		return;
	}

	const float TimeRatio = PlayLevel::s_TimeManager->GetTimeRatio();

	bool isOver300PM = (TimeRatio > SunsetStartTimeRatio);
	if (isOver300PM)
	{
		float SunSetRatio = (TimeRatio - SunsetStartTimeRatio) / (SunsetEndTimeRatio - SunsetStartTimeRatio);

		UpdateALightRatio(TimeRatio);

		SunSetRatio *= static_cast<float>(SkyData.size() - 1);
		float fRefNumber;

		SunSetRatio = std::modff(SunSetRatio, &fRefNumber);								// ������, �Ҽ��� �и�
		int RefNumber = static_cast<int>(fRefNumber);

		const int MaxRefNumber = static_cast<int>(SkyData.size() - 1);

		bool isOver740PM = (RefNumber < MaxRefNumber);
		if (isOver740PM)
		{
			LerpSky(SkyData[RefNumber], SkyData[static_cast<size_t>(RefNumber) + 1], SunSetRatio);
		}
		else
		{
			LerpSky(SkyData[MaxRefNumber]);
		}
	}
	else
	{
		ALight = 0.0f;
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
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	Sun_Renderer->GetColorData().MulColor = _Color;
}


void SkyLerp::FollowCamera() 
{
	if (false == CameraControler::MainCameraControler.expired())
	{
		const float4& CameraPos = CameraControler::MainCameraControler.lock()->GetCameraCurrentPostion();
		float4 SkyPos = CameraPos;
		SkyPos.Z = DepthFunction::CalculateFixDepth(ERENDERDEPTH::SkyBox);

		Transform.SetLocalPosition(SkyPos);
	}
}

void SkyLerp::UpdateALightRatio(const float _TimeRatio)
{
	if (_TimeRatio > ALightStartTimeRatio)
	{
		float ALightValue = (_TimeRatio - ALightStartTimeRatio) / (SunsetEndTimeRatio - ALightStartTimeRatio);
		ALight = powf(ALightValue, 2.0f);

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