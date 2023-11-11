#include "PreCompile.h"
#include "UI_Frame.h"

UI_Frame::UI_Frame() 
{
}

UI_Frame::~UI_Frame() 
{
}

void UI_Frame::Release()
{
	Frame = nullptr;
	Cutscene = nullptr;
}

void UI_Frame::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void UI_Frame::Init(int _Type)
{
	RendererSetting(_Type);
}

void UI_Frame::RendererSetting(int _Type)
{
	static constexpr const int RenderOrder = 0;

	const float FrameDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Frame);
	const float CutsceneDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Base);

	float4 FramePosition = float4(0.0f, 0.0f, FrameDepth);
	float4 CutscenePosition = float4(0.0f, 0.0f, CutsceneDepth);

	std::string FileName = GetCutsceneName(static_cast<EFRAMETYPE>(_Type));


	Frame = CreateComponent<GameEngineUIRenderer>(RenderOrder);
	Frame->Transform.SetLocalPosition(FramePosition);
	Frame->SetSprite("Sample_UI_Cutscene_Frame.png");

	Cutscene = CreateComponent<GameEngineUIRenderer>(RenderOrder);
	Cutscene->Transform.SetLocalPosition(CutscenePosition);
	Cutscene->SetSprite(FileName);
}

std::string UI_Frame::GetCutsceneName(EFRAMETYPE _Type)
{
	std::string_view CutSceneName;

	switch (_Type)
	{
	case EFRAMETYPE::Mail:
		CutSceneName = "Cutscene_Mail.png";
		break;
	case EFRAMETYPE::BroomStick:
		CutSceneName = "Cutscene_BasicWitchBroomStick.png";
		break;
	case EFRAMETYPE::None:
	{
		MsgBoxAssert("이상한 값이 들어왔습니다.");
		return std::string();
	}
		break;
	default:
		break;
	}

	return CutSceneName.data();
}