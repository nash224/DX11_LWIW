#include "PreCompile.h"
#include "UI_Alert_Quest.h"

UI_Alert_Quest::UI_Alert_Quest() 
{
}

UI_Alert_Quest::~UI_Alert_Quest() 
{
}


void UI_Alert_Quest::Start()
{
}

void UI_Alert_Quest::Update(float _Delta)
{
}

void UI_Alert_Quest::Release()
{
}

void UI_Alert_Quest::LevelStart(class GameEngineLevel* _NextLevel)
{
}

void UI_Alert_Quest::LevelEnd(class GameEngineLevel* _NextLevel)
{
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////




float UI_Alert_Quest::AlertLevelEnter(GameEngineLevel* _Level, std::string_view _LevelName)
{
	const std::shared_ptr<UI_Alert_Quest>& Alert = _Level->CreateActor<UI_Alert_Quest>(EUPDATEORDER::Objects);
	Alert->Init(_LevelName);

	return 0.0f;
}


void UI_Alert_Quest::Init(std::string_view _LevelName)
{
	const float4& Position = float4(0.0f, 200.0f);
	Transform.SetLocalPosition(Position);

	RendererSetting(_LevelName);
	UI_Alert_Base::FSMSetting();
}

void UI_Alert_Quest::RendererSetting(std::string_view _LevelName)
{
	if (nullptr == GameEngineSprite::Find("QuestFrame_Animation.png"))
	{
		GameEngineSprite::CreateCut("QuestFrame_Animation.png", 7, 6);
	}

	const int RenderOrder = 0;

	const float ShadowDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Alert_Shadow);
	const float BaseDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Alert_Base);
	const float FontDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Alert_Font);

	const float4& fShadowDepth = float4(0.0f, 0.0f, ShadowDepth);
	const float4& fQuestFrameDepth = float4(0.0f, 0.0f, BaseDepth);
	const float4& fFontDepth = float4(0.0f, 0.0f, FontDepth);


	{
		QuestInfo.Black = CreateComponent<GameEngineUIRenderer>(RenderOrder);
		QuestInfo.Black->Transform.SetLocalPosition(fShadowDepth);
		QuestInfo.Black->GetColorData().MulColor = float4::ZERO;
		QuestInfo.Black->SetSprite("Default_Particle.png");
		QuestInfo.Black->GetImageTransform().SetLocalScale(float4(300.0f, 200.0f));
	}

	{
		static constexpr const float QuestFrame_Animation_Inter = 0.045f;

		QuestInfo.QuestFrame = CreateComponent<GameEngineUIRenderer>(RenderOrder);
		QuestInfo.QuestFrame->Transform.SetLocalPosition(fQuestFrameDepth);
		QuestInfo.QuestFrame->AutoSpriteSizeOn();
		QuestInfo.QuestFrame->CreateAnimation("Alert", "QuestFrame_Animation.png", QuestFrame_Animation_Inter, 0, 36, false);
		QuestInfo.QuestFrame->ChangeAnimation("Alert");
	}

	{
		const float4 InitialFontColor = float4(0.85f, 0.85f, 0.85f, 1.0f);
		static constexpr const float FontScale = 21.0f;

		QuestInfo.Font = CreateComponent<GameEngineUIRenderer>(RenderOrder);
		QuestInfo.Font->Transform.SetLocalPosition(fFontDepth);
		QuestInfo.Font->SetText(GlobalValue::Font_Sandoll, _LevelName.data(), FontScale, InitialFontColor, FW1_TEXT_FLAG::FW1_CENTER);
	}
}

void UI_Alert_Quest::StartFadeIn(GameEngineState* _Parent)
{
	if (nullptr == QuestInfo.Font)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	if (nullptr == QuestInfo.Black)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	ChangeFontAlpha(QuestInfo.Font, 0.0f);
	ChangeMulColor(QuestInfo.Black, 0.0f);
}


void UI_Alert_Quest::UpdateFadeIn(float _DeltaTime, GameEngineState* _Parent)
{
	float MulColorValue = _Parent->GetStateTime() / QuestInfo.Fade_Change_Time;

	ChangeFontAlpha(QuestInfo.Font, MulColorValue);
	ChangeMulColor(QuestInfo.Black, MulColorValue);

	if (_Parent->GetStateTime() > QuestInfo.Fade_Change_Time)
	{
		ChangeFontAlpha(QuestInfo.Font, 1.0f);
		ChangeMulColor(QuestInfo.Black, 1.0f);
		ChangeState(EENTERSTATE::Stay);
	}
}

void UI_Alert_Quest::UpdateStay(float _DeltaTime, GameEngineState* _Parent)
{
	static constexpr const float WaitTime = 1.6f;

	if (_Parent->GetStateTime() > WaitTime)
	{
		ChangeState(EENTERSTATE::FadeOut);
	}
}

void UI_Alert_Quest::UpdateFadeOut(float _DeltaTime, GameEngineState* _Parent)
{
	float MulColorValue = 1.0f - _Parent->GetStateTime() / QuestInfo.Fade_Change_Time;

	ChangeFontAlpha(QuestInfo.Font, MulColorValue);
	ChangeMulColor(QuestInfo.QuestFrame, MulColorValue);
	ChangeMulColor(QuestInfo.Black, MulColorValue);

	if (_Parent->GetStateTime() > QuestInfo.Fade_Change_Time)
	{
		ChangeFontAlpha(QuestInfo.Font, 0.0f);
		ChangeMulColor(QuestInfo.QuestFrame, 0.0f);
		ChangeMulColor(QuestInfo.Black, 0.0f);
		Death();
	}
}