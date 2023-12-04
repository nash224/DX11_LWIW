#include "PreCompile.h"
#include "Emoji.h"

#include "Ellie.h"

static constexpr float NoneState_TransitionTime = 2.0f;

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
	Base = nullptr;
	Emotion = nullptr;
	Parent = nullptr;
}

void Emoji::RendererSetting(GameEngineActor* _Actor, const float4& _EmotionPos)
{
	static constexpr int RenderOrder = 0;

	EmotionPos = _EmotionPos;

	Base = _Actor->CreateComponent<GameEngineUIRenderer>(RenderOrder);
	Base->SetSprite("Emoticon_Background.png");

	Emotion = _Actor->CreateComponent<GameEngineUIRenderer>(RenderOrder);
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
	if (nullptr == Base || nullptr == Emotion)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	Base->On();
	Emotion->On();
	Emotion->SetSprite("Exclamation.png");
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

void Emoji::StartQuestion(GameEngineState* State)
{
	if (nullptr == Emotion)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	Emotion->SetSprite("Question.png");
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

	const float4 ElliePos = PlayLevel::GetPlayLevelPtr()->GetPlayerPtr()->Transform.GetLocalPosition();
	const float4 MyPos = Parent->Transform.GetLocalPosition();
	const float4 Result = DirectX::XMVector2Length((MyPos - ElliePos).DirectXVector);
	return Result.X;
}

void Emoji::Update(float _Delta)
{
	State.Update(_Delta);
	const TransformData& TransData = PlayLevel::GetPlayLevelPtr()->GetMainCamera()->Transform.GetConstTransformDataRef();
	TransData.ViewMatrix;
	TransData.ProjectionMatrix;
}


void Emoji::CalculateWorldToScreen()
{
	if (nullptr == Parent)
	{
		MsgBoxAssert("부모를 지정하지 않고 기능을 사용하려 했습니다.");
		return;
	}

	const float4 CameraPos = PlayLevel::GetPlayLevelPtr()->GetMainCamera()->Transform.GetLocalPosition();
	float4 Pos = Parent->Transform.GetLocalPosition();
	float4 Vector = Pos - CameraPos;

	const float BaseDepth = DepthFunction::CalculateFixDepth(ERENDERDEPTH::Emoticon_Base);
	const float EmotionDepth = DepthFunction::CalculateFixDepth(ERENDERDEPTH::Emoticon_Emotion);

	Vector += EmotionPos;
	Vector.Z = BaseDepth;
	Base->Transform.SetWorldPosition(Vector);

	Vector.Z = EmotionDepth;
	Emotion->Transform.SetWorldPosition(Vector);
}