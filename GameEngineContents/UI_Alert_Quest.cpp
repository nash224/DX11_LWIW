#include "PreCompile.h"
#include "UI_Alert_Quest.h"

#include "AlertManager.h"

UI_Alert_Quest::UI_Alert_Quest() 
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

	AlertManager::isAlerting = false;
}

void UI_Alert_Quest::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


void UI_Alert_Quest::CallAlertQuest(GameEngineLevel* _Level, std::string_view _QuestName, EALERTTYPE _Type)
{
	const std::shared_ptr<UI_Alert_Quest>& Alert = _Level->CreateActor<UI_Alert_Quest>(EUPDATEORDER::Objects);

	switch (_Type)
	{
	case EALERTTYPE::Enter:
	case EALERTTYPE::Tutorial:
	case EALERTTYPE::None:
	{
		MsgBoxAssert("잘못된 값이 들어왔습니다.");
		return;
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
}

void UI_Alert_Quest::SameInit(std::string_view _QuestName)
{
	Transform.SetLocalPosition(float4(0.0f, 140.0f));

	RendererSetting(_QuestName);
	UI_Alert_Base::FSMSetting();
}

void UI_Alert_Quest::QuestAcceptInit(std::string_view _QuestName)
{
	SameInit(_QuestName);

	
	SFXFunction::PlaySFX("SFX_Quest_Start_01.wav");
}

void UI_Alert_Quest::QuestClearInit(std::string_view _QuestName)
{
	SameInit(_QuestName);

	StampRendererSetting();
	FSMStampSetting();

	SFXFunction::PlaySFX("SFX_Quest_Complete_01.wav");
}

void UI_Alert_Quest::RendererSetting(std::string_view _QuestName)
{
	if (nullptr == GameEngineSprite::Find("Quest_Notice_Bar_Animation.png"))
	{
		GameEngineSprite::CreateCut("Quest_Notice_Bar_Animation.png", 5, 5);
	}

	const float ShadowDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Alert_Shadow);
	const float BaseDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Alert_Base);
	const float FontDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Alert_Font);


	{
		QuestInfo.Black = CreateComponent<GameEngineUIRenderer>();
		QuestInfo.Black->Transform.SetLocalPosition(float4(0.0f, 0.0f, ShadowDepth));
		QuestInfo.Black->SetSprite("Default_Particle.png");
		QuestInfo.Black->GetColorData().MulColor = float4::ZERO;
		QuestInfo.Black->GetImageTransform().SetLocalScale(float4(300.0f, 160.0f));
	}

	{
		QuestInfo.QuestFrame = CreateComponent<GameEngineUIRenderer>();
		QuestInfo.QuestFrame->Transform.SetLocalPosition(float4(0.0f, 0.0f, BaseDepth));
		QuestInfo.QuestFrame->AutoSpriteSizeOn();
		QuestInfo.QuestFrame->CreateAnimation("Alert", "Quest_Notice_Bar_Animation.png", 0.045f, 0, 22, false);
		QuestInfo.QuestFrame->ChangeAnimation("Alert");
	}

	{
		QuestInfo.UnderLine = CreateComponent<GameEngineUIRenderer>();
		QuestInfo.UnderLine->Transform.SetLocalPosition(float4(0.0f, 0.0f, BaseDepth));
		QuestInfo.UnderLine->SetSprite("Quest_Notice_Bar.png");
	}

	{
		QuestInfo.Font = CreateComponent<GameEngineUIRenderer>();
		QuestInfo.Font->Transform.SetLocalPosition(float4(0.0f, 2.0f, FontDepth));
		QuestInfo.Font->SetText(GlobalValue::Font_Sandoll, _QuestName.data(), 21.0f, float4(0.85f, 0.85f, 0.85f, 1.0f), FW1_TEXT_FLAG::FW1_CENTER);
	}

	{
		QuestInfo.HeadFont = CreateComponent<GameEngineUIRenderer>();
		QuestInfo.HeadFont->Transform.SetLocalPosition(float4(0.0f, 30.0f, FontDepth));
		QuestInfo.HeadFont->SetText(GlobalValue::Font_Sandoll, "메인", 16.0f, float4(0.75f, 0.2f, 0.1f, 1.0f), FW1_TEXT_FLAG::FW1_CENTER);
	}
}

void UI_Alert_Quest::StampRendererSetting()
{
	const float FrameDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Alert_Stamp);

	QuestInfo.Stamp = CreateComponent<GameEngineUIRenderer>();
	QuestInfo.Stamp->Transform.SetLocalPosition(float4(110.0f, -30.0f, FrameDepth));
	QuestInfo.Stamp->SetSprite("Quest_Notice_Complete.png");
	QuestInfo.Stamp->AutoSpriteSizeOn();
	QuestInfo.Stamp->GetColorData().MulColor = float4(0.84f, 0.84f, 0.84f, 1.0f);
	QuestInfo.Stamp->Off();
}

void UI_Alert_Quest::StartFadeIn(GameEngineState* _Parent)
{
	ChangeFontAlpha(QuestInfo.Font, 0.0f);
	ChangeFontAlpha(QuestInfo.HeadFont, 0.0f);
	ChangeMulColor(QuestInfo.Black, 0.0f);
	ChangeMulColor(QuestInfo.UnderLine, 0.0f);

	QuestInfo.UnderLine->SetAutoScaleRatio(float4(QuestInfo.UnderLine_Initial_X_Scale_Ratio, 1.0f));
}


void UI_Alert_Quest::UpdateFadeIn(float _DeltaTime, GameEngineState* _Parent)
{
	float SettingValue = _Parent->GetStateTime() / Fade_Change_Time;

	ChangeFontAlpha(QuestInfo.Font, SettingValue);
	ChangeFontAlpha(QuestInfo.HeadFont, SettingValue);
	ChangeMulColor(QuestInfo.Black, SettingValue);
	ChangeMulColor(QuestInfo.UnderLine, SettingValue);

	const float UnderLine_X_ScaleRatio = QuestInfo.UnderLine_Initial_X_Scale_Ratio + (1.0f - QuestInfo.UnderLine_Initial_X_Scale_Ratio) * SettingValue;

	ChangeAutoScaleRatio(QuestInfo.UnderLine, float4(UnderLine_X_ScaleRatio, 1.0f));

	if (_Parent->GetStateTime() > Fade_Change_Time)
	{
		ChangeFontAlpha(QuestInfo.Font, 1.0f);
		ChangeFontAlpha(QuestInfo.HeadFont, 1.0f);
		ChangeMulColor(QuestInfo.Black, 1.0f);

		ChangeAutoScaleRatio(QuestInfo.UnderLine, float4::ONE);

		ChangeState(EENTERSTATE::Stay);
		return;
	}
}

void UI_Alert_Quest::UpdateStay(float _DeltaTime, GameEngineState* _Parent)
{
	const float StampTime = 0.2f;

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
	ChangeFontAlpha(QuestInfo.HeadFont, MulColorValue);
	ChangeMulColor(QuestInfo.Black, MulColorValue);
	ChangeMulColor(QuestInfo.QuestFrame, MulColorValue);
	ChangeMulColor(QuestInfo.UnderLine, MulColorValue);

	if (nullptr != QuestInfo.Stamp)
	{
		ChangeMulColor(QuestInfo.Stamp, MulColorValue);
	}

	const float FadeOutTime = 0.8f;

	if (_Parent->GetStateTime() > FadeOutTime)
	{
		ChangeFontAlpha(QuestInfo.Font, 0.0f);
		ChangeFontAlpha(QuestInfo.HeadFont, 0.0f);
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

	ChangeAutoScaleRatio(QuestInfo.Stamp, float4(StampScaleXRatio, StampScaleXRatio));
	
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
