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
	Transform.AddLocalPosition({ 410.0f , -209.0f });

	const float FrameDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::HUB_Frame);
	const float ArrowDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::HUB_Indicator);
	const float IconDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::HUB_Icon);
	
	const float ArrowXPos = 25.0f;

	m_Slot = CreateComponent<GameEngineUIRenderer>();
	m_Slot->Transform.SetLocalPosition(float4(0.0f, 0.0f, FrameDepth));
	m_Slot->SetSprite("HUD_Potion_Slot.png");

	m_ArrowLeft = CreateComponent<GameEngineUIRenderer>();
	m_ArrowLeft->SetSprite("HUD_Arrow_Left.png");
	m_ArrowLeft->Transform.AddLocalPosition(float4(-ArrowXPos, 0.0f, ArrowDepth));

	m_ArrowRight = CreateComponent<GameEngineUIRenderer>();
	m_ArrowRight->SetSprite("HUD_Arrow_Left.png");
	m_ArrowRight->LeftFlip();
	m_ArrowRight->Transform.AddLocalPosition(float4(ArrowXPos, 0.0f, ArrowDepth));

	m_Item = CreateComponent<GameEngineUIRenderer>();
	m_Item->Transform.SetLocalPosition(float4(0.0f, 0.0f, IconDepth));
	m_Item->Off();

	Off();
}