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
	Off();
}


void UI_Conversation::RendererSetting()
{
	ResourceSetting();
	PortraitSetting();
	DialogueSetting();
}

void UI_Conversation::ResourceSetting()
{
	if (nullptr == GameEngineTexture::Find("Aurea_Expression.png"))
	{
		GameEngineSprite::CreateCut("Aurea_Expression.png", 2, 2);
		GameEngineSprite::CreateCut("Crow_Expression.png", 2, 1);
		GameEngineSprite::CreateCut("Dian_Expression.png", 3, 2);
		GameEngineSprite::CreateCut("Ellie_Basic.png", 4, 3);
		GameEngineSprite::CreateCut("Virgil_Basic.png", 3, 3);
	}
}

void UI_Conversation::PortraitSetting()
{
	static const int PortraitRenderOrder = 0;

	static constexpr const char* VirgilSpriteName = "Virgil_Basic.png";
	static constexpr const char* EllieSpriteName = "Ellie_Basic.png";
	static constexpr const char* OtherSpriteName = "Dian_Expression.png";

	static constexpr float ElliePortraitXPos = -330.0f;
	static constexpr float OtherPortraitXPos = 330.0f;

	const float4 WinScale = GlobalValue::GetWindowScale();

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

	const float ElliePortraitYPos = ElliePortraitScale.Half().Y - WinScale.Y;
	const float OtherPortraitYPos = OtherPortraitScale.Half().Y - WinScale.Y;	// NPC 스프라이트 크기가 같습니다.

	const float PortraitDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Conversation_Frame);

	const float4 ElliePortraitSpritePos = { ElliePortraitXPos, ElliePortraitYPos, PortraitDepth };
	const float4 OtherPortraitSpritePos = { OtherPortraitXPos, OtherPortraitYPos, PortraitDepth };



	Portrait.Ellie = CreateComponent<GameEngineUIRenderer>(PortraitRenderOrder);
	Portrait.Ellie->Transform.SetLocalPosition(ElliePortraitSpritePos);
	Portrait.Ellie->RightFlip();
	Portrait.Ellie->SetSprite(EllieSpriteName);
	Portrait.Ellie->Off();

	Portrait.Virgil = CreateComponent<GameEngineUIRenderer>(PortraitRenderOrder);
	Portrait.Virgil->Transform.SetLocalPosition(ElliePortraitSpritePos);
	Portrait.Virgil->RightFlip();
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

	Dialogue.Main_Font = CreateComponent<GameEngineUIRenderer>(DialogueRenderOrder);
	Dialogue.Main_Font->Transform.SetLocalPosition(float4(0.0f, Main_DialogueYPos, MessageDepth));
	Dialogue.Main_Font->Off();


	Dialogue.Virgil_Dialogue = CreateComponent<GameEngineUIRenderer>(DialogueRenderOrder);
	Dialogue.Virgil_Dialogue->Transform.SetLocalPosition(float4(0.0f, Main_DialogueYPos, FrameDepth));
	Dialogue.Virgil_Dialogue->SetSprite("Virgil_Dialogue_Cursor.png");
	Dialogue.Virgil_Dialogue->Off();

	Dialogue.Virgil_Cursor = CreateComponent<GameEngineUIRenderer>(DialogueRenderOrder);
	Dialogue.Virgil_Cursor->Transform.SetLocalPosition(float4(0.0f, Main_DialogueYPos, ArrowDepth));
	Dialogue.Virgil_Cursor->SetSprite("Dialogue_Cursor.png");
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

	Dialogue.Left_Tail->Off();
	Dialogue.Right_Tail->Off();
	Dialogue.Main_Dialogue->Off();
	Dialogue.Main_Cursor->Off();
	Dialogue.Main_Font->Off();

	Dialogue.Virgil_Cursor->Off();
	Dialogue.Virgil_Dialogue->Off();
	Dialogue.Virgil_Font->Off();

	Dialogue.Main_Message.clear();
	Dialogue.Virgil_Message.clear();
}


void UI_Conversation::StartConversation(std::string_view _NPCSpriteName)
{
	if (nullptr == Portrait.Other)
	{
		MsgBoxAssert("생성하지 않은 컨포넌트를 사용하려 했습니다.");
		return;
	}

	Portrait.Other->SetSprite(_NPCSpriteName);
}

void UI_Conversation::ShowConversation(const ConversationParameter& _Para)
{
	switch (_Para.Entity)
	{
	case ECONVERSATIONENTITY::NPC:
		Dialogue.Main_Message = _Para.Message;
		SetNPCExpression(_Para.FileIndex);
		break;
	case ECONVERSATIONENTITY::Ellie:
		Dialogue.Main_Message = _Para.Message;
		SetEllieExpression(_Para.FileIndex);
		break;
	case ECONVERSATIONENTITY::Virgil:
		Dialogue.Virgil_Message = _Para.Message;
		SetVirgilExpression(_Para.FileIndex);
		break;
	default:
		break;
	}



	_Para.FileIndex;
	_Para.FontName;
}

void UI_Conversation::EndConversation()
{
	Reset();
}


void UI_Conversation::SetEllieExpression(int _SpriteIndex)
{
	if (nullptr == Portrait.Ellie)
	{
		MsgBoxAssert("생성하지 않은 컴포넌트를 사용하려 했습니다.");
		return;
	}

	Portrait.Ellie->ChangeSpriteIndex(_SpriteIndex);
}

void UI_Conversation::SetNPCExpression(int _SpriteIndex)
{
	if (nullptr == Portrait.Other)
	{
		MsgBoxAssert("생성하지 않은 컴포넌트를 사용하려 했습니다.");
		return;
	}

	Portrait.Other->ChangeSpriteIndex(_SpriteIndex);
}

void UI_Conversation::SetVirgilExpression(int _SpriteIndex)
{

}


const unsigned int UI_Conversation::ReturnEllieIndexToVirgil()
{
	return 1;
}