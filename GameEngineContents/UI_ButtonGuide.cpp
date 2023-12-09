#include "PreCompile.h"
#include "UI_ButtonGuide.h"


UI_ButtonGuide::UI_ButtonGuide() 
{
}

UI_ButtonGuide::~UI_ButtonGuide() 
{
}

// 하단 고정된 위치에 버튼, 폰트가 쌍을 이뤄 있음
// 버튼을 중심으로 폰트는 버튼의 왼쪽에 와야함
// 한 쌍마다 사이가 동일함
// 

static constexpr float GuideFontSize = 14.0f;
static constexpr float RendererYPos = -240.0f;
static constexpr float DistanceBTW = 40.0f;

void UI_ButtonGuide::SetGuideInfo(GameEngineActor* _Actor, const std::vector<ButtonInfoParameter>& _Paras)
{
	Guides.resize(_Paras.size());

	for (int i = 0; i < Guides.size(); i++)
	{
		std::string ButtonSpriteName = ReturnButtonSpriteName(_Paras[i].Type);

		Guides[i].ButtonToTextSize = GetTotalSize(ButtonSpriteName, static_cast<int>(_Paras[i].Text.size()));
		Guides[i].ButtonType = _Paras[i].Type;

		std::shared_ptr<GameEngineUIRenderer> ButtonRenderer = _Actor->CreateComponent<GameEngineUIRenderer>();
		ButtonRenderer->SetSprite(ButtonSpriteName);
		ButtonRenderer->SetPivotType(PivotType::Left);
		ButtonRenderer->Off();
		Guides[i].ButtonRenderer = ButtonRenderer;

		std::shared_ptr<GameEngineUIRenderer> GuideRenderer = _Actor->CreateComponent<GameEngineUIRenderer>();
		GuideRenderer->SetText(GlobalValue::Font_Sandoll, _Paras[i].Text, 15.0f, float4::WHITE, FW1_TEXT_FLAG::FW1_RIGHT);
		GuideRenderer->Off();
		Guides[i].GuideRenderer = GuideRenderer;
	}

	float TotalSize = 0.0f;

	for (int i = 0; i < Guides.size(); i++)
	{
		TotalSize += Guides[i].ButtonToTextSize;
		if (i > 0)
		{
			TotalSize += DistanceBTW;
		}
	}

	const float Depth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Font);

	for (int i = 0; i < Guides.size(); i++)
	{
		float TotalFrontInfoSize = 0.0f;

		for (int j = 1; j <= i; j++)
		{
			TotalFrontInfoSize += Guides[j].ButtonToTextSize;
			TotalFrontInfoSize += DistanceBTW;
		}

		float XPos = -TotalSize * 0.5f + TotalFrontInfoSize;
		const float4 GuidePos = float4(XPos, RendererYPos, Depth);
		Guides[i].ButtonRenderer->Transform.SetWorldPosition(GuidePos);
		Guides[i].GuideRenderer->Transform.SetWorldPosition(GuidePos + float4(-8.0f, 6.0f));
	}
}

std::string UI_ButtonGuide::ReturnButtonSpriteName(EBUTTONTYPE _Type) const
{
	std::string ReturnName = "ButtonSet_Keyboard_";
	switch (_Type)
	{
	case EBUTTONTYPE::A:
		ReturnName += "A";
		break;
	case EBUTTONTYPE::C:
		ReturnName += "C";
		break;
	case EBUTTONTYPE::D:
		ReturnName += "D";
		break;
	case EBUTTONTYPE::S:
		ReturnName += "S";
		break;
	case EBUTTONTYPE::X:
		ReturnName += "X";
		break;
	case EBUTTONTYPE::Z:
		ReturnName += "Z";
		break;
	case EBUTTONTYPE::Z_PressHold:
		ReturnName += "Z_PressHold";
		break;
	case EBUTTONTYPE::QW:
		ReturnName += "QW";
		break;
	case EBUTTONTYPE::ER:
		ReturnName += "ER";
		break;
	case EBUTTONTYPE::Ctrl:
		ReturnName += "Ctrl";
		break;
	case EBUTTONTYPE::Shift:
		ReturnName += "Shift";
		break;
	case EBUTTONTYPE::Space:
		ReturnName += "Space";
		break;
	case EBUTTONTYPE::Tab:
		ReturnName += "Tab";
		break;
	case EBUTTONTYPE::Arrow_1:
		ReturnName += "Arrow_1";
		break;
	case EBUTTONTYPE::Arrow_Horizontal:
		ReturnName += "Arrow_Horizontal";
		break;
	case EBUTTONTYPE::Arrow_Vertical:
		ReturnName += "Arrow_Vertical";
		break;
	default:
		break;
	}

	ReturnName += ".png";
	return ReturnName;
}

float UI_ButtonGuide::GetTotalSize(std::string_view _FileName, int _StringSize) const
{
	std::weak_ptr<GameEngineTexture> Texture = GameEngineTexture::Find(_FileName);
	if (true == Texture.expired())
	{
		MsgBoxAssert("등록되지 않은 텍스처를 참조했습니다.");
		return 0.0f;
	}

	const float Font_Aspect_Ratio = 0.6f;
	const float TextToButtonGap = 4.0f;

	const float4 ButtonScale = Texture.lock()->GetScale();
	return ButtonScale.X + _StringSize * GuideFontSize * Font_Aspect_Ratio + TextToButtonGap;
}

void UI_ButtonGuide::On()
{
	for (int i = 0; i < Guides.size(); i++)
	{
		Guides[i].ButtonRenderer->On();
		Guides[i].GuideRenderer->On();
	}
}

void UI_ButtonGuide::Off()
{
	for (int i = 0; i < Guides.size(); i++)
	{
		Guides[i].ButtonRenderer->Off();
		Guides[i].GuideRenderer->Off();
	}
}

void UI_ButtonGuide::Release()
{
	Guides.clear();
}