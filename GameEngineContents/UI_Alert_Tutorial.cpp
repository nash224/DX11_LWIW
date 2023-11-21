#include "PreCompile.h"
#include "UI_Alert_Tutorial.h"

UI_Alert_Tutorial::UI_Alert_Tutorial() 
{
}

UI_Alert_Tutorial::~UI_Alert_Tutorial() 
{
}


void UI_Alert_Tutorial::Update(float _Delta)
{
	UI_Alert_Base::Update(_Delta);
}

void UI_Alert_Tutorial::Release()
{
	AlertInfo.Base = nullptr;
	AlertInfo.Img = nullptr;
	AlertInfo.Fade = nullptr;
	AlertInfo.TitleFont = nullptr;
	AlertInfo.ContentFont = nullptr;
}

void UI_Alert_Tutorial::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

float UI_Alert_Tutorial::AlertLevelEnter(GameEngineLevel* _Level, std::string_view _LevelName)
{
	const std::shared_ptr<UI_Alert_Tutorial>& Alert = _Level->CreateActor<UI_Alert_Tutorial>(EUPDATEORDER::Objects);
	Alert->Init(_LevelName);

	return 0.0f;
}

void UI_Alert_Tutorial::Init(std::string_view _LevelName)
{
	const float4& Position = float4(0.0f, 200.0f);
	Transform.SetLocalPosition(Position);

	RendererSetting(_LevelName);
	UI_Alert_Base::FSMSetting();
}

void UI_Alert_Tutorial::RendererSetting(std::string_view _LevelName)
{
	if (nullptr == GameEngineSprite::Find("ZoneName_Animation.png"))
	{
		GameEngineSprite::CreateCut("ZoneName_Animation.png", 7, 6);
	}

	const int RenderOrder = 0;

	const float BaseDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Alert_Base);
	const float ShadowDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Alert_Shadow);
	const float FontDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Alert_Font);
	const float ImgDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Alert_Img);

	const float4& fFadeDepth = float4(0.0f, 0.0f, ShadowDepth);
	const float4& fBaseDepth = float4(0.0f, 0.0f, BaseDepth);
	const float4& fImgDepth = float4(0.0f, 0.0f, FontDepth);
	const float4& fFontDepth = float4(0.0f, 0.0f, FontDepth);


	{
		AlertInfo.Base = CreateComponent<GameEngineUIRenderer>(RenderOrder);
		AlertInfo.Base->Transform.SetLocalPosition(fBaseDepth);
		AlertInfo.Base->SetSprite("Popup_Keyword_Base.png");
	}

	{
		AlertInfo.Fade = CreateComponent<GameEngineUIRenderer>(RenderOrder);
		AlertInfo.Fade->Transform.SetLocalPosition(fFadeDepth);
		AlertInfo.Fade->GetColorData().MulColor = FadeMulColor;
		AlertInfo.Fade->GetImageTransform().SetLocalScale(GlobalValue::GetWindowScale());
	}


	{
		static constexpr const float FontScale = 21.0f;

		/*float4 TitleFontPosition = float4( 3.0f,  ) + fFontDepth;*/

		AlertInfo.TitleFont = CreateComponent<GameEngineUIRenderer>(RenderOrder);
		AlertInfo.TitleFont->Transform.SetLocalPosition(fFontDepth);
		AlertInfo.TitleFont->SetText(GlobalValue::Font_Sandoll, _LevelName.data(), FontScale, InitialFontColor, FW1_TEXT_FLAG::FW1_CENTER);
	}

	{
		static constexpr const float FontScale = 21.0f;

		AlertInfo.ContentFont = CreateComponent<GameEngineUIRenderer>(RenderOrder);
		AlertInfo.ContentFont->Transform.SetLocalPosition(fFontDepth);
		AlertInfo.ContentFont->SetText(GlobalValue::Font_Sandoll, _LevelName.data(), FontScale, InitialFontColor, FW1_TEXT_FLAG::FW1_CENTER);
	}
}

void UI_Alert_Tutorial::StartFadeIn(GameEngineState* _Parent)
{
	if (nullptr == AlertInfo.Base)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	if (nullptr == AlertInfo.Fade)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	ChangeFontAlpha(AlertInfo.Base, 0.0f);
	ChangeMulColor(AlertInfo.Fade, 0.0f);
}


void UI_Alert_Tutorial::UpdateFadeIn(float _DeltaTime, GameEngineState* _Parent)
{
	float MulColorValue = _Parent->GetStateTime() / AlertInfo.Fade_Change_Time;

}

void UI_Alert_Tutorial::UpdateStay(float _DeltaTime, GameEngineState* _Parent)
{
	static constexpr const float WaitTime = 1.6f;

	if (_Parent->GetStateTime() > WaitTime)
	{
		ChangeState(EENTERSTATE::FadeOut);
	}
}

void UI_Alert_Tutorial::UpdateFadeOut(float _DeltaTime, GameEngineState* _Parent)
{
	float MulColorValue = 1.0f - _Parent->GetStateTime() / AlertInfo.Fade_Change_Time;

}