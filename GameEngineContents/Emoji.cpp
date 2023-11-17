#include "PreCompile.h"
#include "Emoji.h"

#include "Ellie.h"

Emoji::Emoji() 
{
	if (nullptr == GameEngineSprite::Find("Emoticon_Background.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\PlayContents\\PlayResourecs\\UI\\UI_Sprite\\UI_Emoticon");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pFile : Files)
		{
			GameEngineSprite::CreateSingle(pFile.GetStringPath());
		}
	}
}

Emoji::~Emoji() 
{
}


void Emoji::Init(GameEngineActor* _Actor, const float4& _EmotionPos /*= float4::ZERO*/)
{
	Parent = _Actor;
	RendererSetting(_Actor, _EmotionPos);
	StateSetting();
}

void Emoji::Release()
{
	// 안전?
	Base = nullptr;
	Emotion = nullptr;
	Parent = nullptr;
}

void Emoji::RendererSetting(GameEngineActor* _Actor, const float4& _EmotionPos)
{
	static constexpr int RenderOrder = 0;

	const float BaseDepth = GlobalUtils::CalculateFixDepth(ERENDERDEPTH::Emoticon_Base);
	const float EmotionDepth = GlobalUtils::CalculateFixDepth(ERENDERDEPTH::Emoticon_Emotion);

	const float4& BasePosition = float4(_EmotionPos.X, _EmotionPos.Y, BaseDepth);
	const float4& EmotionPosition = float4(_EmotionPos.X, _EmotionPos.Y, EmotionDepth);

	Base = _Actor->CreateComponent<GameEngineSpriteRenderer>(RenderOrder);
	Base->Transform.SetLocalPosition(BasePosition);
	Base->SetSprite("Emoticon_Background.png");

	Emotion = _Actor->CreateComponent<GameEngineSpriteRenderer>(RenderOrder);
	Emotion->Transform.SetLocalPosition(EmotionPosition);
}

void Emoji::SetRecognitionRange(float _Range)
{
	RecognitionRange = _Range;
}

void Emoji::UseOnlyExclamation()
{
	isUseOnlyExclamation = true;
}

void Emoji::StateSetting()
{
	CreateStateParameter ExclamationState;
	ExclamationState.Start = std::bind(&Emoji::StartExclamation, this, std::placeholders::_1);
	ExclamationState.Stay = std::bind(&Emoji::UpdateExclamation, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EEMOJISTATE::Exclamation, ExclamationState);

	CreateStateParameter QuestionState;
	QuestionState.Start = std::bind(&Emoji::StartQuestion, this, std::placeholders::_1);
	QuestionState.Stay = std::bind(&Emoji::UpdateQuestion, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EEMOJISTATE::Question, QuestionState);

	CreateStateParameter NoneState;
	NoneState.Start = std::bind(&Emoji::StartNone, this, std::placeholders::_1);
	State.CreateState(EEMOJISTATE::None, NoneState);

	State.ChangeState(EEMOJISTATE::None);
}



void Emoji::StartExclamation(GameEngineState* State)
{
	if (nullptr == Base || nullptr == Emotion || nullptr == Parent)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	Base->On();
	Emotion->On();
	Emotion->SetSprite("Exclamation.png");
}

void Emoji::UpdateExclamation(float _Delta, GameEngineState* State)
{
	if (false == isUseOnlyExclamation)
	{
		if (GetDistanceToEllie() > RecognitionRange)
		{
			State->ChangeState(EEMOJISTATE::Question);
			return;
		}
	}


	if (State->GetStateTime() > NoneState_TransitionTime)
	{
		State->ChangeState(EEMOJISTATE::None);
		return;
	}
}


void Emoji::StartQuestion(GameEngineState* State)
{
	if (nullptr == Emotion)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	Emotion->SetSprite("Question.png");
}

void Emoji::UpdateQuestion(float _Delta, GameEngineState* State)
{
	if (GetDistanceToEllie() < RecognitionRange)
	{
		State->ChangeState(EEMOJISTATE::Exclamation);
		return;
	}

	if (State->GetStateTime() > NoneState_TransitionTime)
	{
		State->ChangeState(EEMOJISTATE::None);
		return;
	}
}


void Emoji::StartNone(GameEngineState* State)
{
	if (nullptr == Base || nullptr == Emotion)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	Base->Off();
	Emotion->Off();
}

void Emoji::ShowExclamation()
{
	State.ChangeState(EEMOJISTATE::Exclamation);
}

float Emoji::GetDistanceToEllie()
{
	if (nullptr == Parent)
	{
		MsgBoxAssert("부모를 지정해주지 않았습니다.");
		return 0.0f;
	}

	if (nullptr == Ellie::MainEllie)
	{
		return 0.0f;
	}
	
	const float4& ElliePos = Ellie::MainEllie->Transform.GetLocalPosition();
	const float4& MyPos = Parent->Transform.GetLocalPosition();
	const float4& Result = DirectX::XMVector2Length((MyPos - ElliePos).DirectXVector);
	return Result.X;
}

void Emoji::Update(float _Delta)
{
	State.Update(_Delta);
}