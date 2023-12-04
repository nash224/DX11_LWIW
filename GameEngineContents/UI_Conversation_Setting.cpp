#include "PreCompile.h"
#include "UI_Conversation.h"



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

	const float DefaultPortrait_XGap = 340.0f;
	const float ElliePortraitXPos = -DefaultPortrait_XGap;
	const float OtherPortraitXPos = DefaultPortrait_XGap;

	const float4 HWinScale = GlobalValue::GetWindowScale().Half();

	const std::shared_ptr<GameEngineSprite> EllieSprite = GameEngineSprite::Find(EllieSpriteName);
	if (nullptr == EllieSprite)
	{
		MsgBoxAssert("존재하지 않는 스프라이트를 참조하려 했습니다.");
		return;
	}

	const std::shared_ptr<GameEngineSprite> OtherSprite = GameEngineSprite::Find(OtherSpriteName);
	if (nullptr == OtherSprite)
	{
		MsgBoxAssert("존재하지 않는 스프라이트를 참조하려 했습니다.");
		return;
	}

	const float4 ElliePortraitScale = EllieSprite->GetSpriteData(0).GetScale();
	const float4 OtherPortraitScale = OtherSprite->GetSpriteData(0).GetScale();

	const float ElliePortraitYPos = ElliePortraitScale.Half().Y - HWinScale.Y;
	const float OtherPortraitYPos = OtherPortraitScale.Half().Y - HWinScale.Y;	// NPC 스프라이트 크기가 같습니다.

	const float PortraitDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Conversation_Portrait);

	const float4 ElliePortraitSpritePos = { ElliePortraitXPos, ElliePortraitYPos, PortraitDepth };


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
	Portrait.Other->Transform.SetLocalPosition(float4(OtherPortraitXPos, OtherPortraitYPos, PortraitDepth));
	Portrait.Other->Off();
}

void UI_Conversation::DialogueSetting()
{
	const float FrameDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Conversation_Frame);
	const float TailDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Conversation_Tail);
	const float ArrowDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Conversation_Arrow);
	const float MessageDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Conversation_Message);

	const int DialogueRenderOrder = 0;
	const float MainDialogue_YPos = -185.0f;
	const float MainDialogueCursor_YPos = -238.0f;

	float4 MessagePos = MainDialogue_FirstLinePosition;
	MessagePos.Z = MessageDepth;

	Dialogue.Left_Tail = CreateComponent<GameEngineUIRenderer>();
	Dialogue.Left_Tail->Transform.SetLocalPosition(float4(0.0f, MainDialogue_YPos, TailDepth));
	Dialogue.Left_Tail->SetSprite("Dialogue_Left_Tail.png");
	Dialogue.Left_Tail->Off();

	Dialogue.Right_Tail = CreateComponent<GameEngineUIRenderer>();
	Dialogue.Right_Tail->Transform.SetLocalPosition(float4(0.0f, MainDialogue_YPos, TailDepth));
	Dialogue.Right_Tail->SetSprite("Dialogue_Right_Tail.png");
	Dialogue.Right_Tail->Off();

	Dialogue.MainBase = CreateComponent<GameEngineUIRenderer>();
	Dialogue.MainBase->Transform.SetLocalPosition(float4(0.0f, MainDialogue_YPos, FrameDepth));
	Dialogue.MainBase->SetSprite("Dialogue.png");
	Dialogue.MainBase->Off();

	Dialogue.Main_Cursor = CreateComponent<GameEngineUIRenderer>();
	Dialogue.Main_Cursor->Transform.SetLocalPosition(float4(0.0f, MainDialogueCursor_YPos, ArrowDepth));
	Dialogue.Main_Cursor->SetSprite("Dialogue_Cursor.png");
	Dialogue.Main_Cursor->Off();


	Dialogue.Main_Font = CreateComponent<GameEngineUIRenderer>();
	Dialogue.Main_Font->Transform.SetLocalPosition(MessagePos);
	Dialogue.Main_Font->Off();

	Dialogue.Virgil_DialogueBase = CreateComponent<GameEngineUIRenderer>(DialogueRenderOrder);
	Dialogue.Virgil_DialogueBase->Transform.SetLocalPosition(float4(-340.0f, 70.0f, FrameDepth));
	Dialogue.Virgil_DialogueBase->CreateAnimation("Saying", "Virgil_Dialogue_small.png", 0.2f);
	Dialogue.Virgil_DialogueBase->AutoSpriteSizeOn();
	Dialogue.Virgil_DialogueBase->ChangeAnimation("Saying");
	Dialogue.Virgil_DialogueBase->Off();

	Dialogue.Virgil_Cursor = CreateComponent<GameEngineUIRenderer>(DialogueRenderOrder);
	Dialogue.Virgil_Cursor->Transform.SetLocalPosition(float4(-280.0f, 26.0f, ArrowDepth));
	Dialogue.Virgil_Cursor->SetSprite("Virgil_Dialogue_Cursor.png");
	Dialogue.Virgil_Cursor->Off();

	Dialogue.Virgil_Font = CreateComponent<GameEngineUIRenderer>(DialogueRenderOrder);
	Dialogue.Virgil_Font->Transform.SetLocalPosition(float4(0.0f, MainDialogue_YPos, MessageDepth));
	Dialogue.Virgil_Font->Off();
}
