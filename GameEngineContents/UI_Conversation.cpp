#include "PreCompile.h"
#include "UI_Conversation.h"


UI_Conversation* UI_Conversation::MainConversationUI = nullptr;
UI_Conversation::UI_Conversation()
{
}

UI_Conversation::~UI_Conversation()
{
}


void UI_Conversation::Update(float _Delta)
{

}

void UI_Conversation::Release()
{
	Portrait.Ellie = nullptr;
	Portrait.Other = nullptr;
	Portrait.Virgil = nullptr;

	Dialogue.Left_Tail = nullptr;
	Dialogue.Right_Tail = nullptr;
	Dialogue.Main_Dialogue = nullptr;
	Dialogue.Main_Cursor = nullptr;
	Dialogue.Main_Font = nullptr;

	Dialogue.Virgil_Cursor = nullptr;
	Dialogue.Virgil_Dialogue = nullptr;
	Dialogue.Virgil_Font = nullptr;
}

void UI_Conversation::LevelStart(class GameEngineLevel* _NextLevel)
{
	MainConversationUI = this;
}




/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void UI_Conversation::Init()
{
	MainConversationUI = this;

	RendererSetting();
}


void UI_Conversation::RendererSetting()
{
	ResourceSetting();
	PortraitSetting();
	DialogueSetting();
}

void UI_Conversation::ResourceSetting()
{
	if (nullptr == GameEngineSprite::Find("Aurea_Expression.png"))
	{
		GameEngineSprite::CreateCut("Aurea_Expression.png", 2, 2);
		GameEngineSprite::CreateCut("Crow_Expression.png", 2, 1);
		GameEngineSprite::CreateCut("Dian_Expression.png", 3, 2);
		GameEngineSprite::CreateCut("Ellie_Basic.png", 4, 3);
		GameEngineSprite::CreateCut("Virgil_Basic.png", 3, 3);
		GameEngineSprite::CreateCut("Virgil_Dialogue_small.png", 3, 1);
		GameEngineSprite::CreateCut("Virgil_Dialogue_Large.png", 3, 1);
	}
}

void UI_Conversation::PortraitSetting()
{
	static const int PortraitRenderOrder = 0;

	static constexpr const char* VirgilSpriteName = "Virgil_Basic.png";
	static constexpr const char* EllieSpriteName = "Ellie_Basic.png";
	static constexpr const char* OtherSpriteName = "Dian_Expression.png";

	static constexpr float ElliePortraitXPos = -Portrait.Portrait_Default_X_Gap;
	static constexpr float OtherPortraitXPos = Portrait.Portrait_Default_X_Gap;

	const float4 HWinScale = GlobalValue::GetWindowScale().Half();

	const std::shared_ptr<GameEngineSprite> EllieSprite = GameEngineSprite::Find(EllieSpriteName);
	if (nullptr == EllieSprite)
	{
		MsgBoxAssert("존재하지 않는 스프라이트를 참조하려 했습니다.");
		return;
	}

	const float4 ElliePortraitScale = EllieSprite->GetSpriteData(0).GetScale();

	const std::shared_ptr<GameEngineSprite> OtherSprite = GameEngineSprite::Find(OtherSpriteName);
	if (nullptr == OtherSprite)
	{
		MsgBoxAssert("존재하지 않는 스프라이트를 참조하려 했습니다.");
		return;
	}

	const float4 OtherPortraitScale = OtherSprite->GetSpriteData(0).GetScale();

	const float ElliePortraitYPos = ElliePortraitScale.Half().Y - HWinScale.Y;
	const float OtherPortraitYPos = OtherPortraitScale.Half().Y - HWinScale.Y;	// NPC 스프라이트 크기가 같습니다.

	const float PortraitDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Conversation_Portrait);

	const float4 ElliePortraitSpritePos = { ElliePortraitXPos, ElliePortraitYPos, PortraitDepth };
	const float4 OtherPortraitSpritePos = { OtherPortraitXPos, OtherPortraitYPos, PortraitDepth };



	Portrait.Ellie = CreateComponent<GameEngineUIRenderer>(PortraitRenderOrder);
	Portrait.Ellie->Transform.SetLocalPosition(ElliePortraitSpritePos);
	Portrait.Ellie->LeftFlip();
	Portrait.Ellie->SetSprite(EllieSpriteName);
	Portrait.Ellie->Off();

	Portrait.Virgil = CreateComponent<GameEngineUIRenderer>(PortraitRenderOrder);
	Portrait.Virgil->Transform.SetLocalPosition(ElliePortraitSpritePos);
	Portrait.Virgil->LeftFlip();
	Portrait.Virgil->SetSprite(VirgilSpriteName);
	Portrait.Virgil->Off();

	Portrait.Other = CreateComponent<GameEngineUIRenderer>(PortraitRenderOrder);
	Portrait.Other->Transform.SetLocalPosition(OtherPortraitSpritePos);
	Portrait.Other->Off();
}

void UI_Conversation::DialogueSetting()
{
	static const int DialogueRenderOrder = 0;
	static constexpr const float Main_DialogueYPos = -185.0f;
	static constexpr const float Main_Dialogue_Cursor_YPos = -238.0f;

	const float4 MessagePos = float4(-164.0f, -167.0f);

	const float FrameDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Conversation_Frame);
	const float TailDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Conversation_Tail);
	const float ArrowDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Conversation_Arrow);
	const float MessageDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Conversation_Message);


	Dialogue.Left_Tail = CreateComponent<GameEngineUIRenderer>(DialogueRenderOrder);
	Dialogue.Left_Tail->Transform.SetLocalPosition(float4(0.0f, Main_DialogueYPos, TailDepth));
	Dialogue.Left_Tail->SetSprite("Dialogue_Left_Tail.png");
	Dialogue.Left_Tail->Off();

	Dialogue.Right_Tail = CreateComponent<GameEngineUIRenderer>(DialogueRenderOrder);
	Dialogue.Right_Tail->Transform.SetLocalPosition(float4(0.0f, Main_DialogueYPos, TailDepth));
	Dialogue.Right_Tail->SetSprite("Dialogue_Right_Tail.png");
	Dialogue.Right_Tail->Off();

	Dialogue.Main_Dialogue = CreateComponent<GameEngineUIRenderer>(DialogueRenderOrder);
	Dialogue.Main_Dialogue->Transform.SetLocalPosition(float4(0.0f, Main_DialogueYPos, FrameDepth));
	Dialogue.Main_Dialogue->SetSprite("Dialogue.png");
	Dialogue.Main_Dialogue->Off();

	Dialogue.Main_Cursor = CreateComponent<GameEngineUIRenderer>(DialogueRenderOrder);
	Dialogue.Main_Cursor->Transform.SetLocalPosition(float4(0.0f, Main_Dialogue_Cursor_YPos, ArrowDepth));
	Dialogue.Main_Cursor->SetSprite("Dialogue_Cursor.png");
	Dialogue.Main_Cursor->Off();

	Dialogue.Main_Font = CreateComponent<GameEngineSpriteRenderer>(DialogueRenderOrder);
	Dialogue.Main_Font->Transform.SetLocalPosition(float4(0.0f, Main_DialogueYPos, MessageDepth));
	Dialogue.Main_Font->Off();


	float4 Virgil_Dialogue_Position = Dialogue.Virgil_Dialogue_Position;
	Virgil_Dialogue_Position.Z = FrameDepth;

	Dialogue.Virgil_Dialogue = CreateComponent<GameEngineUIRenderer>(DialogueRenderOrder);
	Dialogue.Virgil_Dialogue->Transform.SetLocalPosition(Virgil_Dialogue_Position);
	Dialogue.Virgil_Dialogue->CreateAnimation("Saying", "Virgil_Dialogue_small.png", Dialogue.Virgil_Dialogue_Animation_Inter);
	Dialogue.Virgil_Dialogue->AutoSpriteSizeOn();
	Dialogue.Virgil_Dialogue->ChangeAnimation("Saying");
	Dialogue.Virgil_Dialogue->Off();

	Dialogue.Virgil_Cursor = CreateComponent<GameEngineUIRenderer>(DialogueRenderOrder);
	Dialogue.Virgil_Cursor->Transform.SetLocalPosition(float4(0.0f, Main_DialogueYPos, ArrowDepth));
	Dialogue.Virgil_Cursor->SetSprite("Virgil_Dialogue_Cursor.png");
	Dialogue.Virgil_Cursor->Off();

	Dialogue.Virgil_Font = CreateComponent<GameEngineUIRenderer>(DialogueRenderOrder);
	Dialogue.Virgil_Font->Transform.SetLocalPosition(float4(0.0f, Main_DialogueYPos, MessageDepth));
	Dialogue.Virgil_Font->Off();
}


void UI_Conversation::Reset()
{
	Portrait.Ellie->Off();
	Portrait.Other->Off();
	Portrait.Virgil->Off();

	const int Virgil_Default_Index = ReturnVirgilIndexToEllie(Portrait.Ellie_Portrait_Default_Index);

	Portrait.Ellie->ChangeCurSprite(Portrait.Ellie_Portrait_Default_Index);
	Portrait.Virgil->ChangeCurSprite(Virgil_Default_Index);

	Dialogue.Left_Tail->Off();
	Dialogue.Right_Tail->Off();
	Dialogue.Main_Dialogue->Off();
	Dialogue.Main_Cursor->Off();
	Dialogue.Main_Font->Off();

	ResetVirgil();

	Dialogue.Main_Message.clear();
	Dialogue.Virgil_Message.clear();
}

void UI_Conversation::ResetVirgil()
{
	Dialogue.Virgil_Dialogue->Off();
	Dialogue.Virgil_Cursor->Off();
	Dialogue.Virgil_Font->Off();
}


void UI_Conversation::StartConversation(std::string_view _NPCSpriteName)
{
	if (nullptr == Portrait.Other)
	{
		MsgBoxAssert("생성하지 않은 컨포넌트를 사용하려 했습니다.");
		return;
	}

	if (nullptr == Portrait.Ellie)
	{
		MsgBoxAssert("생성하지 않은 컨포넌트를 사용하려 했습니다.");
		return;
	}

	if (nullptr == Portrait.Virgil)
	{
		MsgBoxAssert("생성하지 않은 컨포넌트를 사용하려 했습니다.");
		return;
	}

	if (nullptr == Dialogue.Main_Dialogue)
	{
		MsgBoxAssert("생성하지 않은 컨포넌트를 사용하려 했습니다.");
		return;
	}

	Portrait.Other->On();
	Portrait.Ellie->On();
	Portrait.Virgil->On();


	const int Virgil_Default_Index = ReturnVirgilIndexToEllie(Portrait.Ellie_Portrait_Default_Index);
	Portrait.VirgilIndex = Virgil_Default_Index;

	Portrait.Ellie->ChangeCurSprite(Portrait.Ellie_Portrait_Default_Index);
	Portrait.Virgil->ChangeCurSprite(Virgil_Default_Index);
	Portrait.Other->SetSprite(_NPCSpriteName);

	Dialogue.Main_Dialogue->On();
}

void UI_Conversation::ShowConversation(const ConversationParameter& _Para)
{
	bool VirgilNotConverse = (ECONVERSATIONENTITY::Virgil != _Para.Entity);
	if (true == isJustVirgilTalked && VirgilNotConverse)
	{
		LoseSpeechControlVirgil();
		isJustVirgilTalked = false;
	}

	switch (_Para.Entity)
	{
	case ECONVERSATIONENTITY::NPC:
		SetNPCExpression(_Para.FileIndex);
		Dialogue.Main_Message = _Para.Message;
		SetMainMessage(_Para.FontName);
		SetRightTail();
		break;
	case ECONVERSATIONENTITY::Ellie:
		SetEllieExpression(_Para.FileIndex);
		Dialogue.Main_Message = _Para.Message;
		SetMainMessage(_Para.FontName);
		SetLeftTail();
		break;
	case ECONVERSATIONENTITY::Virgil:
		SetVirgilExpression(_Para.FileIndex);
		Dialogue.Virgil_Message = _Para.Message;
		SetVirgilMessage(_Para.FontName);
		break;
	default:
		break;
	}
}

void UI_Conversation::EndConversation()
{
	Reset();
}


void UI_Conversation::SetEllieExpression(unsigned int _SpriteIndex)
{
	SetAllExpressionBlack();
	Portrait.Ellie->GetColorData().MulColor = Portrait.SayingColor;
	Portrait.Virgil->GetColorData().MulColor = Portrait.SayingColor;


	const std::uint32_t Virgil_Sprite_Index = ReturnVirgilIndexToEllie(_SpriteIndex);

	Portrait.Ellie->ChangeCurSprite(_SpriteIndex);
	Portrait.Virgil->ChangeCurSprite(Virgil_Sprite_Index);

	Portrait.VirgilIndex = Virgil_Sprite_Index;
}

void UI_Conversation::SetNPCExpression(unsigned int _SpriteIndex)
{
	SetAllExpressionBlack();

	Portrait.Other->GetColorData().MulColor = Portrait.SayingColor;

	Portrait.Other->ChangeCurSprite(_SpriteIndex);
}

void UI_Conversation::SetVirgilExpression(unsigned int _SpriteIndex)
{
	SetAllExpressionBlack();

	Portrait.Ellie->GetColorData().MulColor = Portrait.SayingColor;
	Portrait.Virgil->GetColorData().MulColor = Portrait.SayingColor;
	

	if (false == isJustVirgilTalked)
	{
		const int Virgil_Saying_Index = Portrait.VirgilIndex - 1;
		Portrait.Virgil->ChangeCurSprite(Virgil_Saying_Index);
	}

	isJustVirgilTalked = true;
}

void UI_Conversation::SetAllExpressionBlack()
{
	if (nullptr == Portrait.Virgil)
	{
		MsgBoxAssert("생성하지 않은 컴포넌트를 사용하려 했습니다.");
		return;
	}

	if (nullptr == Portrait.Other)
	{
		MsgBoxAssert("생성하지 않은 컴포넌트를 사용하려 했습니다.");
		return;
	}

	if (nullptr == Portrait.Ellie)
	{
		MsgBoxAssert("생성하지 않은 컴포넌트를 사용하려 했습니다.");
		return;
	}

	Portrait.Virgil->GetColorData().MulColor = Portrait.UnsaidColor;
	Portrait.Other->GetColorData().MulColor = Portrait.UnsaidColor;
	Portrait.Ellie->GetColorData().MulColor = Portrait.UnsaidColor;
}


void UI_Conversation::SetMainMessage(std::string_view _FontName)
{
	if (nullptr == Dialogue.Main_Font)
	{
		MsgBoxAssert("FontRenderer가 없습니다.");
		return;
	}

	Dialogue.Main_Font->SetText(_FontName.data(), Dialogue.Main_Message.data(), Dialogue.FontSize, Dialogue.DefaultColor);
	Dialogue.Main_Font->On();
}

void UI_Conversation::SetVirgilMessage(std::string_view _FontName)
{
	if (nullptr == Dialogue.Virgil_Font)
	{
		MsgBoxAssert("FontRenderer가 없습니다.");
		return;
	}

	Dialogue.Virgil_Cursor->On();
	Dialogue.Virgil_Dialogue->On();

	Dialogue.Virgil_Font->SetText(_FontName.data(), Dialogue.Virgil_Message.data(), Dialogue.FontSize, Dialogue.DefaultColor);
	Dialogue.Virgil_Font->On();
}

const unsigned int UI_Conversation::ReturnVirgilIndexToEllie(unsigned int _Index)
{
	switch (_Index)
	{
	case 0:
	{
		MsgBoxAssert("스프라이트에 앨리가 존재하지 않습니다.");
		return 0;
	}
		break;
	case 1:
	case 5:
	case 10:
		return 2;
	default:
		break;
	}

	return 6;
}


void UI_Conversation::LoseSpeechControlVirgil()
{
	if (nullptr == Portrait.Virgil)
	{
		MsgBoxAssert("생성하지 않은 컴포넌트를 사용하려 했습니다.");
		return;
	}

	Portrait.Virgil->ChangeCurSprite(Portrait.VirgilIndex);

	ResetVirgil();
}


void UI_Conversation::SetRightTail()
{
	ResetAllTail();

	Dialogue.Right_Tail->On();
}

void UI_Conversation::SetLeftTail()
{
	ResetAllTail();

	Dialogue.Left_Tail->On();
}

void UI_Conversation::ResetAllTail()
{
	if (nullptr == Dialogue.Left_Tail)
	{
		MsgBoxAssert("생성하지 않은 컴포넌트를 사용하려 했습니다.");
		return;
	}

	if (nullptr == Dialogue.Right_Tail)
	{
		MsgBoxAssert("생성하지 않은 컴포넌트를 사용하려 했습니다.");
		return;
	}

	Dialogue.Left_Tail->Off();
	Dialogue.Right_Tail->Off();
}