#include "PreCompile.h"
#include "UI_Alert_Enter.h"

#include "AlertManager.h"

UI_Alert_Enter::UI_Alert_Enter() 
{
}

UI_Alert_Enter::~UI_Alert_Enter() 
{
}


static constexpr float Fade_Change_Time = 1.0f;

void UI_Alert_Enter::Update(float _Delta)
{
	UI_Alert_Base::Update(_Delta);
}

void UI_Alert_Enter::Release()
{
	AlertInfo.ZoneFrame = nullptr;
	AlertInfo.Black = nullptr;
	AlertInfo.Font = nullptr;

	AlertManager::isAlerting = false;
}

void UI_Alert_Enter::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


void UI_Alert_Enter::AlertLevelEnter(GameEngineLevel* _Level, std::string_view _LevelName)
{
	const std::shared_ptr<UI_Alert_Enter>& Alert = _Level->CreateActor<UI_Alert_Enter>(EUPDATEORDER::Objects);
	Alert->Init(_LevelName);
}

void UI_Alert_Enter::Init(std::string_view _LevelName)
{
	Transform.SetLocalPosition(float4(0.0f, 200.0f));

	RendererSetting(_LevelName);
	UI_Alert_Base::FSMSetting();
}

void UI_Alert_Enter::RendererSetting(std::string_view _LevelName)
{
	if (nullptr == GameEngineSprite::Find("ZoneName_Animation.png"))
	{
		GameEngineSprite::CreateCut("ZoneName_Animation.png", 7, 6);
	}

	const float ShadowDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Alert_Shadow);
	const float BaseDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Alert_Base);
	const float FontDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Alert_Font);


	{
		AlertInfo.Black = CreateComponent<GameEngineUIRenderer>();
		AlertInfo.Black->Transform.SetLocalPosition(float4(0.0f, 0.0f, ShadowDepth));
		AlertInfo.Black->GetColorData().MulColor = float4::ZERO;
		AlertInfo.Black->SetSprite("Default_Particle.png");
		AlertInfo.Black->GetImageTransform().SetLocalScale(float4(300.0f, 200.0f));
	}

	{
		AlertInfo.ZoneFrame = CreateComponent<GameEngineUIRenderer>();
		AlertInfo.ZoneFrame->Transform.SetLocalPosition(float4(0.0f, 0.0f, BaseDepth));
		AlertInfo.ZoneFrame->AutoSpriteSizeOn();
		AlertInfo.ZoneFrame->CreateAnimation("Alert", "ZoneName_Animation.png", 0.045f, 0, 36, false);
		AlertInfo.ZoneFrame->ChangeAnimation("Alert");
	}

	{
		AlertInfo.Font = CreateComponent<GameEngineUIRenderer>();
		AlertInfo.Font->Transform.SetLocalPosition(float4(0.0f, 0.0f, FontDepth));
		AlertInfo.Font->SetText(GlobalValue::Font_Sandoll, _LevelName.data(), 21.0f, InitialFontColor, FW1_TEXT_FLAG::FW1_CENTER);
	}
}

void UI_Alert_Enter::StartFadeIn(GameEngineState* _Parent)
{
	if (nullptr == AlertInfo.Font || nullptr == AlertInfo.Black)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	ChangeFontAlpha(AlertInfo.Font, 0.0f);
	ChangeMulColor(AlertInfo.Black, 0.0f);
}


void UI_Alert_Enter::UpdateFadeIn(float _DeltaTime, GameEngineState* _Parent)
{
	float MulColorValue = _Parent->GetStateTime() / Fade_Change_Time;

	ChangeFontAlpha(AlertInfo.Font, MulColorValue);
	ChangeMulColor(AlertInfo.Black, MulColorValue);

	if (_Parent->GetStateTime() > Fade_Change_Time)
	{
		ChangeFontAlpha(AlertInfo.Font, 1.0f);
		ChangeMulColor(AlertInfo.Black, 1.0f);
		ChangeState(EENTERSTATE::Stay);
	}
}

void UI_Alert_Enter::UpdateStay(float _DeltaTime, GameEngineState* _Parent)
{
	const float WaitTime = 1.6f;
	if (_Parent->GetStateTime() > WaitTime)
	{
		ChangeState(EENTERSTATE::FadeOut);
	}
}

void UI_Alert_Enter::UpdateFadeOut(float _DeltaTime, GameEngineState* _Parent)
{
	float MulColorValue = 1.0f - _Parent->GetStateTime() / Fade_Change_Time;

	ChangeFontAlpha(AlertInfo.Font, MulColorValue);
	ChangeMulColor(AlertInfo.ZoneFrame, MulColorValue);
	ChangeMulColor(AlertInfo.Black, MulColorValue);

	if (_Parent->GetStateTime() > Fade_Change_Time)
	{
		ChangeFontAlpha(AlertInfo.Font, 0.0f);
		ChangeMulColor(AlertInfo.ZoneFrame, 0.0f);
		ChangeMulColor(AlertInfo.Black, 0.0f);
		Death();
	}
}