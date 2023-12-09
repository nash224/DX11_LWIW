#include "PreCompile.h"
#include "UI_Hub_QuickSlot.h"


UI_Hub_QuickSlot::UI_Hub_QuickSlot() 
{
}

UI_Hub_QuickSlot::~UI_Hub_QuickSlot() 
{
}


void UI_Hub_QuickSlot::Init()
{
	Transform.AddLocalPosition(float4(410.0f, -209.0f));

	const float FrameDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::HUB_Frame);
	const float ArrowDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::HUB_Indicator);
	const float IconDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::HUB_Icon);
	
	const float ArrowXPos = 25.0f;

	SlotRenderer = CreateComponent<GameEngineUIRenderer>();
	SlotRenderer->Transform.SetLocalPosition(float4(0.0f, 0.0f, FrameDepth));
	SlotRenderer->SetSprite("HUD_Potion_Slot.png");

	ArrowLeft = CreateComponent<GameEngineUIRenderer>();
	ArrowLeft->SetSprite("HUD_Arrow_Left.png");
	ArrowLeft->Transform.AddLocalPosition(float4(-ArrowXPos, 0.0f, ArrowDepth));

	ArrowRight = CreateComponent<GameEngineUIRenderer>();
	ArrowRight->SetSprite("HUD_Arrow_Left.png");
	ArrowRight->LeftFlip();
	ArrowRight->Transform.AddLocalPosition(float4(ArrowXPos, 0.0f, ArrowDepth));

	ItemRenderer = CreateComponent<GameEngineUIRenderer>();
	ItemRenderer->Transform.SetLocalPosition(float4(0.0f, 0.0f, IconDepth));
	ItemRenderer->Off();

	Off();
}