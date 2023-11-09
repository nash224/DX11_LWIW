#include "PreCompile.h"
#include "UI_Alert_Quest.h"

UI_Alert_Quest::UI_Alert_Quest() 
{
}

UI_Alert_Quest::~UI_Alert_Quest() 
{
}



void UI_Alert_Quest::Update(float _Delta)
{
	UI_Alert_Base::Update(_Delta);

	StampState.Update(_Delta);
}

void UI_Alert_Quest::Release()
{
	QuestInfo.Black = nullptr;
	QuestInfo.Font = nullptr;
	QuestInfo.QuestFrame = nullptr;
	QuestInfo.Stamp = nullptr;
	QuestInfo.UnderLine = nullptr;
}

void UI_Alert_Quest::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////




float UI_Alert_Quest::CallAlertQuest(GameEngineLevel* _Level, std::string_view _QuestName, EALERTTYPE _Type)
{
	const std::shared_ptr<UI_Alert_Quest>& Alert = _Level->CreateActor<UI_Alert_Quest>(EUPDATEORDER::Objects);

	switch (_Type)
	{
	case EALERTTYPE::Enter:
	case EALERTTYPE::Tutorial:
	case EALERTTYPE::None:
	{
		MsgBoxAssert("잘못된 값이 들어왔습니다.");
		return 0.0f;
	}
		break;
	case EALERTTYPE::QuestAccept:
		Alert->QuestAcceptInit(_QuestName);
		break;
	case EALERTTYPE::QuestClear:
		Alert->QuestClearInit(_QuestName);
		break;
	default:
		break;
	}

	return Fade_Change_Time * 2.0f + WaitTime;
}

void UI_Alert_Quest::SameInit(std::string_view _QuestName)
{
	const float4& Position = float4(0.0f, 140.0f);
	Transform.SetLocalPosition(Position);

	RendererSetting(_QuestName);
	UI_Alert_Base::FSMSetting();

	SoundSetting();
}

void UI_Alert_Quest::QuestAcceptInit(std::string_view _QuestName)
{
	SameInit(_QuestName);

	 GameEngineSoundPlayer SFX = GameEngineSound::SoundPlay("SFX_Quest_Start_01.wav");
	 SFX.SetVolume(GlobalValue::GetSFXVolume());
}

void UI_Alert_Quest::QuestClearInit(std::string_view _QuestName)
{
	SameInit(_QuestName);

	StampRendererSetting();
	FSMStampSetting();

	GameEngineSoundPlayer SFX = GameEngineSound::SoundPlay("SFX_Quest_Complete_01.wav");
	SFX.SetVolume(GlobalValue::GetSFXVolume());
}

void UI_Alert_Quest::RendererSetting(std::string_view _QuestName)
{
	if (nullptr == GameEngineSprite::Find("Quest_Notice_Bar_Animation.png"))
	{
		GameEngineSprite::CreateCut("Quest_Notice_Bar_Animation.png", 5, 5);
	}

	const int RenderOrder = 0;

	const float ShadowDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Alert_Shadow);
	const float BaseDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Alert_Base);
	const float FontDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Alert_Font);

	const float4& fShadowDepth = float4(0.0f, 0.0f, ShadowDepth);
	const float4& fQuestFrameDepth = float4(0.0f, 0.0f, BaseDepth);
	const float4& FontPosition = float4(0.0f, 2.0f, FontDepth);


	{
		QuestInfo.Black = CreateComponent<GameEngineUIRenderer>(RenderOrder);
		QuestInfo.Black->Transform.SetLocalPosition(fShadowDepth);
		QuestInfo.Black->SetSprite("Default_Particle.png");
		QuestInfo.Black->GetColorData().MulColor = float4::ZERO;
		QuestInfo.Black->GetImageTransform().SetLocalScale(float4(300.0f, 160.0f));
	}

	{
		static constexpr const float QuestFrame_Animation_Inter = 0.045f;

		QuestInfo.QuestFrame = CreateComponent<GameEngineUIRenderer>(RenderOrder);
		QuestInfo.QuestFrame->Transform.SetLocalPosition(fQuestFrameDepth);
		QuestInfo.QuestFrame->AutoSpriteSizeOn();
		QuestInfo.QuestFrame->CreateAnimation("Alert", "Quest_Notice_Bar_Animation.png", QuestFrame_Animation_Inter, 0, 22, false);
		QuestInfo.QuestFrame->ChangeAnimation("Alert");
	}

	{
		QuestInfo.UnderLine = CreateComponent<GameEngineUIRenderer>(RenderOrder);
		QuestInfo.UnderLine->Transform.SetLocalPosition(fQuestFrameDepth);
		QuestInfo.UnderLine->SetSprite("Quest_Notice_Bar.png");
	}

	{
		static constexpr const float FontScale = 21.0f;

		const float4 InitialFontColor = float4(0.85f, 0.85f, 0.85f, 1.0f);

		QuestInfo.Font = CreateComponent<GameEngineUIRenderer>(RenderOrder);
		QuestInfo.Font->Transform.SetLocalPosition(FontPosition);
		QuestInfo.Font->SetText(GlobalValue::Font_Sandoll, _QuestName.data(), FontScale, InitialFontColor, FW1_TEXT_FLAG::FW1_CENTER);
	}
}

void UI_Alert_Quest::StampRendererSetting()
{
	const int RenderOrder = 0;

	const float FrameDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Alert_Stamp);
	const float4& StampPosition = float4(110.0f, -30.0f, FrameDepth);

	QuestInfo.Stamp = CreateComponent<GameEngineUIRenderer>(RenderOrder);
	QuestInfo.Stamp->Transform.SetLocalPosition(StampPosition);
	QuestInfo.Stamp->SetSprite("Quest_Notice_Complete.png");
	QuestInfo.Stamp->AutoSpriteSizeOn();
	QuestInfo.Stamp->GetColorData().MulColor = float4(0.84f, 0.84f, 0.84f, 1.0f);
	QuestInfo.Stamp->Off();
}

void UI_Alert_Quest::SoundSetting()
{
	if (nullptr == GameEngineSound::FindSound("SFX_Quest_Start_01.wav"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Sound\\UI\\Quest");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pFile : Files)
		{
			GameEngineSound::SoundLoad(pFile.GetStringPath());
		}
	}
}

void UI_Alert_Quest::StartFadeIn(GameEngineState* _Parent)
{
	ChangeFontAlpha(QuestInfo.Font, 0.0f);
	ChangeMulColor(QuestInfo.Black, 0.0f);
	ChangeMulColor(QuestInfo.UnderLine, 0.0f);

	QuestInfo.UnderLine->SetAutoScaleRatio(float4(QuestInfo.UnderLine_Initial_X_Scale_Ratio, 1.0f));
}


void UI_Alert_Quest::UpdateFadeIn(float _DeltaTime, GameEngineState* _Parent)
{
	float SettingValue = _Parent->GetStateTime() / Fade_Change_Time;

	ChangeFontAlpha(QuestInfo.Font, SettingValue);
	ChangeMulColor(QuestInfo.Black, SettingValue);
	ChangeMulColor(QuestInfo.UnderLine, SettingValue);

	const float UnderLine_X_ScaleRatio = QuestInfo.UnderLine_Initial_X_Scale_Ratio + (1.0f - QuestInfo.UnderLine_Initial_X_Scale_Ratio) * SettingValue;
	const float4& ScaleRatio = float4(UnderLine_X_ScaleRatio, 1.0f);

	ChangeAutoScaleRatio(QuestInfo.UnderLine, ScaleRatio);

	if (_Parent->GetStateTime() > Fade_Change_Time)
	{
		ChangeFontAlpha(QuestInfo.Font, 1.0f);
		ChangeMulColor(QuestInfo.Black, 1.0f);

		ChangeAutoScaleRatio(QuestInfo.UnderLine, float4::ONE);

		ChangeState(EENTERSTATE::Stay);
		return;
	}
}

void UI_Alert_Quest::UpdateStay(float _DeltaTime, GameEngineState* _Parent)
{
	static constexpr const float StampTime = 0.2f;

	bool isStampDone = (_Parent->GetStateTime() > StampTime && false == QuestInfo.isStamped);
	if (isStampDone)
	{
		if (nullptr != QuestInfo.Stamp)
		{
			QuestInfo.isStamped = true;
			StampState.ChangeState(ESTAMPSTATE::Appear);
		}
	}

	if (_Parent->GetStateTime() > WaitTime)
	{
		ChangeState(EENTERSTATE::FadeOut);
		return;
	}
}

void UI_Alert_Quest::UpdateFadeOut(float _DeltaTime, GameEngineState* _Parent)
{
	float MulColorValue = 1.0f - _Parent->GetStateTime() / Fade_Change_Time;

	ChangeFontAlpha(QuestInfo.Font, MulColorValue);
	ChangeMulColor(QuestInfo.Black, MulColorValue);
	ChangeMulColor(QuestInfo.QuestFrame, MulColorValue);
	ChangeMulColor(QuestInfo.UnderLine, MulColorValue);

	if (nullptr != QuestInfo.Stamp)
	{
		ChangeMulColor(QuestInfo.Stamp, MulColorValue);
	}

	if (_Parent->GetStateTime() > Fade_Change_Time)
	{
		ChangeFontAlpha(QuestInfo.Font, 0.0f);
		ChangeMulColor(QuestInfo.QuestFrame, 0.0f);
		ChangeMulColor(QuestInfo.Black, 0.0f);
		ChangeMulColor(QuestInfo.UnderLine, 0.0f);

		if (nullptr != QuestInfo.Stamp)
		{
			ChangeMulColor(QuestInfo.Stamp, 0.0f);
		}

		Death();
	}
}

void UI_Alert_Quest::FSMStampSetting()
{
	CreateStateParameter AppearState;
	AppearState.Start = std::bind(&UI_Alert_Quest::StartAppear, this, std::placeholders::_1);
	AppearState.Stay = std::bind(&UI_Alert_Quest::UpdateAppear, this, std::placeholders::_1, std::placeholders::_2);
	StampState.CreateState(ESTAMPSTATE::Appear, AppearState);

	CreateStateParameter DoneState;
	DoneState.Stay = std::bind(&UI_Alert_Quest::UpdateDone, this, std::placeholders::_1, std::placeholders::_2);
	StampState.CreateState(ESTAMPSTATE::Done, DoneState);
}

void UI_Alert_Quest::StartAppear(GameEngineState* _Parent)
{
	ChangeAutoScaleRatio(QuestInfo.Stamp, QuestInfo.Stamp_Initial_Scale_Ratio_Size);
	ChangeMulColor(QuestInfo.Stamp, 0.0f);
	QuestInfo.Stamp->On();
}

void UI_Alert_Quest::UpdateAppear(float _DeltaTime, GameEngineState* _Parent)
{
	float SettingValue = _Parent->GetStateTime() / QuestInfo.Stamp_Change_FadeIn_Time;

	ChangeMulColor(QuestInfo.Stamp, SettingValue);

	const float MinusScaleRatio = (QuestInfo.Stamp_Initial_Scale_Ratio_Size.X - 1.0f) * SettingValue;
	const float StampScaleXRatio = QuestInfo.Stamp_Initial_Scale_Ratio_Size.X - MinusScaleRatio;
	const float4& StampScaleRatio = float4(StampScaleXRatio, StampScaleXRatio);

	ChangeAutoScaleRatio(QuestInfo.Stamp, StampScaleRatio);
	
	if (_Parent->GetStateTime() > QuestInfo.Stamp_Change_FadeIn_Time)
	{
		ChangeAutoScaleRatio(QuestInfo.Stamp, float4::ONE);
		StampState.ChangeState(ESTAMPSTATE::Done);
		return;
	}
}

void UI_Alert_Quest::UpdateDone(float _DeltaTime, GameEngineState* _Parent) 
{

}
