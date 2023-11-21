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

	const float PortraitDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Conversation_Portrait);

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

	float4 MessagePos = Dialogue.Main_Dialogue_1th_Line_Position;

	const float FrameDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Conversation_Frame);
	const float TailDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Conversation_Tail);
	const float ArrowDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Conversation_Arrow);
	const float MessageDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Conversation_Message);

	MessagePos.Z = MessageDepth;


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
	Dialogue.Main_Font->Transform.SetLocalPosition(MessagePos);
	Dialogue.Main_Font->Off();


	float4 Virgil_Dialogue_Position = Dialogue.Virgil_Dialogue_Position;
	Virgil_Dialogue_Position.Z = FrameDepth;

	float4 Virgil_Dialogue_Cursor_Position = float4(-280.0f, 26.0f);
	Virgil_Dialogue_Cursor_Position.Z = ArrowDepth;

	Dialogue.Virgil_Dialogue = CreateComponent<GameEngineUIRenderer>(DialogueRenderOrder);
	Dialogue.Virgil_Dialogue->Transform.SetLocalPosition(Virgil_Dialogue_Position);
	Dialogue.Virgil_Dialogue->CreateAnimation("Saying", "Virgil_Dialogue_small.png", Dialogue.Virgil_Dialogue_Animation_Inter);
	Dialogue.Virgil_Dialogue->AutoSpriteSizeOn();
	Dialogue.Virgil_Dialogue->ChangeAnimation("Saying");
	Dialogue.Virgil_Dialogue->Off();

	Dialogue.Virgil_Cursor = CreateComponent<GameEngineUIRenderer>(DialogueRenderOrder);
	Dialogue.Virgil_Cursor->Transform.SetLocalPosition(Virgil_Dialogue_Cursor_Position);
	Dialogue.Virgil_Cursor->SetSprite("Virgil_Dialogue_Cursor.png");
	Dialogue.Virgil_Cursor->Off();

	Dialogue.Virgil_Font = CreateComponent<GameEngineUIRenderer>(DialogueRenderOrder);
	Dialogue.Virgil_Font->Transform.SetLocalPosition(float4(0.0f, Main_DialogueYPos, MessageDepth));
	Dialogue.Virgil_Font->Off();
}
