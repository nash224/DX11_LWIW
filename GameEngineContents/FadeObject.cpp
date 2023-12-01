#include "PreCompile.h"
#include "FadeObject.h"

#include "CameraControler.h"

FadeObject::FadeObject()
{
}

FadeObject::~FadeObject()
{
}


void FadeObject::Update(float _Delta)
{
	UpdateFade(_Delta);
}

void FadeObject::Release()
{
	FadeRenderer = nullptr;
}

void FadeObject::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}

void FadeObject::CallFadeOut(std::string_view _NextLevelName, float _FadeOutDuration /*= 1.0f*/)
{
	FadeDuration = _FadeOutDuration;
	FadeType = CallFadeType::FadeOut;
	NextLevelName = _NextLevelName;
	Init();
}

void FadeObject::CallFadeIn(float _FadeOutDuration /*= 1.0f*/)
{
	FadeDuration = _FadeOutDuration;
	FadeType = CallFadeType::FadeIn;
	Init();
}



void FadeObject::Init()
{
	RendererSetting();
	PositionSetting();

	if (nullptr == FadeRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	if (CallFadeType::FadeOut == FadeType)
	{
		Alpha = 0.0f;
		FadeRenderer->GetColorData().MulColor.A = 0.0f;
	}
	else
	{
		Alpha = 1.0f;
	}
}

void FadeObject::RendererSetting()
{
	FadeRenderer = CreateComponent<GameEngineUIRenderer>(ERENDERORDER::Fade);
	FadeRenderer->GetImageTransform().SetLocalScale(GlobalValue::GetWindowScale());
	FadeRenderer->GetColorData().MulColor = float4(0.0f, 0.0f, 0.0f);
}


void FadeObject::PositionSetting()
{
	float FadeDepth = DepthFunction::CalculateFixDepth(ERENDERDEPTH::FadeObject);
	Transform.SetLocalPosition({ 0.0f, 0.0f, FadeDepth });
}

void FadeObject::UpdateFade(float _Delta)
{
	if (CallFadeType::FadeOut == FadeType)
	{
		Alpha += _Delta / FadeDuration;


		if (nullptr == FadeRenderer)
		{
			MsgBoxAssert("렌더러가 존재하지 않습니다.");
			return;
		}

		bool IsOver = false;
		if (Alpha > 1.0f)
		{
			Alpha = 1.0f;
			IsOver = true;
		}

		FadeRenderer->GetColorData().MulColor.A = Alpha;

		if (true == IsOver)
		{
			FadeType = CallFadeType::None;
			GameEngineCore::ChangeLevel(NextLevelName);
		}
	}

	if (CallFadeType::FadeIn == FadeType)
	{
		Alpha -= _Delta / FadeDuration;


		if (nullptr == FadeRenderer)
		{
			MsgBoxAssert("렌더러가 존재하지 않습니다.");
			return;
		}

		bool IsOver = false;
		if (Alpha <= 0.0f)
		{
			Alpha = 0.0f;
			Death();
			return;
		}

		FadeRenderer->GetColorData().MulColor.A = Alpha;

		Transform.GetLocalPosition();
	}
}