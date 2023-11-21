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
	static constexpr int RenderOrder = 0;

	const float FrameDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Frame);
	const float CutsceneDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Base);

	std::string FileName = GetCutsceneName(static_cast<EFRAMETYPE>(_Type));


	Frame = CreateComponent<GameEngineUIRenderer>(RenderOrder);
	Frame->Transform.SetLocalPosition(float4(0.0f, 0.0f, FrameDepth));
	Frame->SetSprite("Sample_UI_Cutscene_Frame.png");

	Cutscene = CreateComponent<GameEngineUIRenderer>(RenderOrder);
	Cutscene->Transform.SetLocalPosition(float4(0.0f, 0.0f, CutsceneDepth));
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
		MsgBoxAssert("�̻��� ���� ���Խ��ϴ�.");
		return std::string();
	}
		break;
	default:
		break;
	}

	return CutSceneName.data();
}