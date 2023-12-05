#include "PreCompile.h"
#include "Emoji.h"

#include "Ellie.h"

static constexpr float ExpressionTime = 2.0f;

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
	BaseRenderer = nullptr;
	EmotionRenderer = nullptr;
	Parent = nullptr;
}

void Emoji::RendererSetting(GameEngineActor* _Actor, const float4& _EmotionPos)
{
	EmotionPos = _EmotionPos;

	BaseRenderer = _Actor->CreateComponent<GameEngineUIRenderer>();
	BaseRenderer->SetSprite("Emoticon_Background.png");

	EmotionRenderer = _Actor->CreateComponent<GameEngineUIRenderer>();
}

void Emoji::ShowExpression(EMOJITYPE _Type)
{
	EmotionRenderer->SetSprite(GetFileName(_Type));
	State.ChangeState(EEMOJISTATE::Expression);
}


std::string Emoji::GetFileName(EMOJITYPE _Type)
{
	std::string FileName;
	switch (_Type)
	{
	case EMOJITYPE::Exclamation:
		FileName = "Exclamation.png";
		break;
	case EMOJITYPE::Question:
		FileName = "Question.png";
		break;
	default:
		break;
	}

	return FileName;
}

void Emoji::Update(float _Delta)
{
	State.Update(_Delta);
}

void Emoji::CalculateEmotionPos()
{
	if (nullptr == Parent)
	{
		MsgBoxAssert("부모를 지정하지 않고 기능을 사용하려 했습니다.");
		return;
	}

	const float4 CameraPos = PlayLevel::GetCurLevel()->GetMainCamera()->Transform.GetLocalPosition();
	float4 Pos = Parent->Transform.GetLocalPosition();
	float4 Vector = Pos - CameraPos;

	const float BaseDepth = DepthFunction::CalculateFixDepth(ERENDERDEPTH::Emoticon_Base);
	const float EmotionDepth = DepthFunction::CalculateFixDepth(ERENDERDEPTH::Emoticon_Emotion);

	Vector += EmotionPos;

	BaseRenderer->Transform.SetWorldPosition(float4(Vector.X, Vector.Y, BaseDepth));
	EmotionRenderer->Transform.SetWorldPosition(float4(Vector.X, Vector.Y, EmotionDepth));
}


void Emoji::StateSetting()
{
	CreateStateParameter ExpressionState;
	ExpressionState.Start = std::bind(&Emoji::StartExpression, this, std::placeholders::_1);
	ExpressionState.Stay = std::bind(&Emoji::UpdateExpression, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EEMOJISTATE::Expression, ExpressionState);

	CreateStateParameter NoneState;
	NoneState.Start = std::bind(&Emoji::StartNone, this, std::placeholders::_1);
	State.CreateState(EEMOJISTATE::None, NoneState);

	State.ChangeState(EEMOJISTATE::None);
}

void Emoji::StartExpression(GameEngineState* State)
{
	if (nullptr == BaseRenderer || nullptr == EmotionRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	BaseRenderer->On();
	EmotionRenderer->On();
}
void Emoji::StartNone(GameEngineState* State)
{
	if (nullptr == BaseRenderer || nullptr == EmotionRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	BaseRenderer->Off();
	EmotionRenderer->Off();
}

void Emoji::UpdateExpression(float _Delta, GameEngineState* State)
{
	if (State->GetStateTime() > ExpressionTime)
	{
		State->ChangeState(EEMOJISTATE::None);
		return;
	}

	CalculateEmotionPos();
}