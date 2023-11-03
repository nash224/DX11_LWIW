#include "PreCompile.h"
#include "UI_Alert_Enter.h"


UI_Alert_Enter::UI_Alert_Enter() 
{
}

UI_Alert_Enter::~UI_Alert_Enter() 
{
}



void UI_Alert_Enter::Update(float _Delta)
{
	UI_Alert_Base::Update(_Delta);
}

void UI_Alert_Enter::Release()
{
	AlertData.ZoneName = nullptr;
	AlertData.Black = nullptr;
	AlertData.Font = nullptr;
}

void UI_Alert_Enter::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

float UI_Alert_Enter::AlertLevelEnter(GameEngineLevel* _Level, std::string_view _LevelName)
{
	const std::shared_ptr<UI_Alert_Enter>& Alert = _Level->CreateActor<UI_Alert_Enter>(EUPDATEORDER::Objects);
	Alert->Init(_LevelName);

	return 0.0f;
}

void UI_Alert_Enter::Init(std::string_view _LevelName)
{
	const float4& Position = float4(0.0f, 200.0f);
	Transform.SetLocalPosition(Position);

	RendererSetting(_LevelName);
	UI_Alert_Base::FSMSetting();
}

void UI_Alert_Enter::RendererSetting(std::string_view _LevelName)
{
	if (nullptr == GameEngineSprite::Find("ZoneName_Animation.png"))
	{
		GameEngineSprite::CreateCut("ZoneName_Animation.png", 7, 6);
	}

	const int RenderOrder = 0;

	const float ShadowDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Alert_Shadow);
	const float BaseDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Alert_Base);
	const float FontDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Alert_Font);

	const float4& fShadowDepth = float4(0.0f, 0.0f, ShadowDepth);
	const float4& fZoneNameDepth = float4(0.0f, 0.0f, BaseDepth);
	const float4& fFontDepth = float4(0.0f, 0.0f, FontDepth);


	{
		AlertData.Black = CreateComponent<GameEngineUIRenderer>(RenderOrder);
		AlertData.Black->Transform.SetLocalPosition(fShadowDepth);
		AlertData.Black->GetColorData().MulColor = float4::ZERO;
		AlertData.Black->SetSprite("Default_Particle.png");
		AlertData.Black->GetImageTransform().SetLocalScale(float4(300.0f, 200.0f));
	}

	{
		static constexpr const float ZoneName_Animation_Inter = 0.045f;

		AlertData.ZoneName = CreateComponent<GameEngineUIRenderer>(RenderOrder);
		AlertData.ZoneName->Transform.SetLocalPosition(fZoneNameDepth);
		AlertData.ZoneName->AutoSpriteSizeOn();
		AlertData.ZoneName->CreateAnimation("Alert", "ZoneName_Animation.png", ZoneName_Animation_Inter, 0, 36, false);
		AlertData.ZoneName->ChangeAnimation("Alert");
	}

	{
		const float4 InitialFontColor = float4(0.85f, 0.85f, 0.85f, 1.0f);
		static constexpr const float FontScale = 21.0f;

		AlertData.Font = CreateComponent<GameEngineUIRenderer>(RenderOrder);
		AlertData.Font->Transform.SetLocalPosition(fFontDepth);
		AlertData.Font->SetText(GlobalValue::Font_Sandoll, _LevelName.data(), FontScale, InitialFontColor, FW1_TEXT_FLAG::FW1_CENTER);
	}
}

void UI_Alert_Enter::StartFadeIn(GameEngineState* _Parent)
{
	if (nullptr == AlertData.Font)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	if (nullptr == AlertData.Black)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	ChangeFontAlpha(AlertData.Font, 0.0f);
	ChangeMulColor(AlertData.Black, 0.0f);
}


void UI_Alert_Enter::UpdateFadeIn(float _DeltaTime, GameEngineState* _Parent)
{
	float MulColorValue = _Parent->GetStateTime() / AlertData.Fade_Change_Time;

	ChangeFontAlpha(AlertData.Font, MulColorValue);
	ChangeMulColor(AlertData.Black, MulColorValue);

	if (_Parent->GetStateTime() > AlertData.Fade_Change_Time)
	{
		ChangeFontAlpha(AlertData.Font, 1.0f);
		ChangeMulColor(AlertData.Black, 1.0f);
		ChangeState(EENTERSTATE::Stay);
	}
}

void UI_Alert_Enter::UpdateStay(float _DeltaTime, GameEngineState* _Parent)
{
	static constexpr const float WaitTime = 1.6f;

	if (_Parent->GetStateTime() > WaitTime)
	{
		ChangeState(EENTERSTATE::FadeOut);
	}
}

void UI_Alert_Enter::UpdateFadeOut(float _DeltaTime, GameEngineState* _Parent)
{
	float MulColorValue = 1.0f - _Parent->GetStateTime() / AlertData.Fade_Change_Time;

	ChangeFontAlpha(AlertData.Font, MulColorValue);
	ChangeMulColor(AlertData.ZoneName, MulColorValue);
	ChangeMulColor(AlertData.Black, MulColorValue);

	if (_Parent->GetStateTime() > AlertData.Fade_Change_Time)
	{
		ChangeFontAlpha(AlertData.Font, 0.0f);
		ChangeMulColor(AlertData.ZoneName, 0.0f);
		ChangeMulColor(AlertData.Black, 0.0f);
		Death();
	}
}