#include "PreCompile.h"
#include "SkyLerp.h"

#include "PlayLevel.h"

#include "TimeManager.h"

SkyLerp* SkyLerp::SkyManager = nullptr;
SkyLerp::SkyLerp() 
{
}

SkyLerp::~SkyLerp() 
{
}


void SkyLerp::Start()
{
	
}

void SkyLerp::Update(float _Delta)
{
	UpdateSkyLerp();
}

void SkyLerp::Release()
{
}

void SkyLerp::LevelStart(class GameEngineLevel* _NextLevel)
{
	SkyManager = this;
}

void SkyLerp::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////



void SkyLerp::Init()
{
	SkyManager = this;

	Transform.SetLocalPosition(float4(0.0f, 0.0f, GlobalUtils::CalculateFixDepth(ERENDERDEPTH::SkyBox)));


	Sun_Renderer = CreateComponent<GameEngineUIRenderer>();
	Sun_Renderer->SetSprite("SkyBox.png");
	Sun_Renderer->GetImageTransform().SetLocalScale(GlobalValue::GetWindowScale());
	Sun_Renderer->GetColorData().MulColor.A = 0.0f;


	SkyData.reserve(33);
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
	SkyData.push_back(Sky_530);
	SkyData.push_back(Sky_530);
	SkyData.push_back(Sky_540);
	SkyData.push_back(Sky_540);
	SkyData.push_back(Sky_550);
	SkyData.push_back(Sky_600);
	SkyData.push_back(Sky_610);
	SkyData.push_back(Sky_620);
	SkyData.push_back(Sky_630);
	SkyData.push_back(Sky_640);
	SkyData.push_back(Sky_650);
	SkyData.push_back(Sky_650);
	SkyData.push_back(Sky_700);
	SkyData.push_back(Sky_710);
	SkyData.push_back(Sky_720);
	SkyData.push_back(Sky_730);
	SkyData.push_back(Sky_740);

	
	
	
	TestCode();

	if (nullptr == PlayLevel::m_TimeManager)
	{
		MsgBoxAssert("타임 매니저가 존재하지 않습니다.");
		return;
	}


	MinuteRatio = PlayLevel::m_TimeManager->GetMinuteRatio();
	PlayLevel::m_TimeManager->SetTimeFlowRatio(5.0f);
	PlayLevel::m_TimeManager->SetTime(180.0f);

	LerpSky(SkyData[0]);

	
}


// 하늘 고정색 지정
void SkyLerp::SetSkyColor()
{
	PauseSkyLerp = true;

	Sun_Renderer->GetColorData().MulColor = SkyColor;
}

void SkyLerp::TestCode()
{
	/*PauseSkyLerp = true;*/

	static std::uint32_t Order = 0;
	std::shared_ptr<GameEngineUIRenderer> DarkFilter = CreateComponent<GameEngineUIRenderer>(Order);
	DarkFilter->SetSprite("SkyBox.png");
	DarkFilter->Transform.SetLocalPosition(float4(0.0f, 0.0f, GlobalUtils::CalculateFixDepth(-202)));
	DarkFilter->GetColorData().MulColor = float4(0.1f, 0.1f, 0.1f, 0.1f);
}

// 일몰 업데이트
void SkyLerp::UpdateSkyLerp()
{
	if (true == PauseSkyLerp)
	{
		return;
	}


	if (nullptr == PlayLevel::m_TimeManager)
	{
		MsgBoxAssert("시간 매니저가 존재하지 않습니다.");
		return;
	}

	float TimeRatio = PlayLevel::m_TimeManager->GetTimeRatio();
	if (TimeRatio > SUNSET_TIMERATIO)
	{
		float SunSetRatio = (TimeRatio - SUNSET_TIMERATIO) / MinuteRatio;				// 비율계산
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