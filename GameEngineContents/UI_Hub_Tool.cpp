#include "PreCompile.h"
#include "UI_Hub_Tool.h"

#include "ContentsEvent.h"


ETOOLTYPE UI_Hub_Tool::m_CurrentTool = ETOOLTYPE::None;
UI_Hub_Tool::UI_Hub_Tool() 
{
	if (nullptr == GameEngineSound::FindSound("SFX_ToolSwap_01.wav"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Sound\\UI\\ToolChange");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pfile : Files)
		{
			GameEngineSound::SoundLoad(pfile.GetStringPath());
		}
	}
}

UI_Hub_Tool::~UI_Hub_Tool() 
{
}


void UI_Hub_Tool::Start()
{
	UI_Hub_Actor::Start();
}

void UI_Hub_Tool::Update(float _Delta)
{
	DetectToolChange();
	UpdateToolArrow(_Delta);
}

void UI_Hub_Tool::LevelStart(class GameEngineLevel* _NextLevel)
{
	ChangeToolImg(m_CurrentTool);
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void UI_Hub_Tool::Init()
{
	if (nullptr == GameEngineSprite::Find("Tool_Icon.png"))
	{
		GameEngineSprite::CreateCut("Tool_Icon.png", 3, 1);
	}

	m_CurrentTool = ETOOLTYPE::Gloves;

	Transform.AddLocalPosition({ -418.0f , -196.0f });


	m_Tool = CreateComponent<GameEngineUIRenderer>();
	m_Tool->Transform.SetLocalPosition(float4(0.0f, 0.0f, GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::HUB_Icon)));
	m_Tool->SetSprite("Tool_Icon.png", static_cast<int>(m_CurrentTool));

	m_LeftArrow = CreateComponent<GameEngineUIRenderer>();
	m_LeftArrow->SetSprite("HUD_Arrow_Left.png");
	m_LeftArrow->Transform.AddLocalPosition(float4(-28.0f, 0.0f, GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::UIArrow)));

	m_RightArrow = CreateComponent<GameEngineUIRenderer>();
	m_RightArrow->SetSprite("HUD_Arrow_Left.png");
	m_RightArrow->LeftFlip();
	m_RightArrow->Transform.AddLocalPosition(float4(26.0f, 0.0f, GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::UIArrow)));
}


/////////////////////////////////////////////////////////////////////////////////////

void UI_Hub_Tool::DetectToolChange()
{
	if (true == GameEngineInput::IsDown('Q', this))
	{
		PrevTool();
	}

	if (true == GameEngineInput::IsDown('W', this))
	{
		NextTool();
	}
}

void UI_Hub_Tool::NextTool()
{
	if (false == RemainToolCheck())
	{
		return;
	}

	int ToolValue = static_cast<int>(m_CurrentTool);

	while (true)
	{
		++ToolValue;
		
		if (ToolValue >= ContentsEvent::ToolData.size())
		{
			ToolValue = 0;
		}

		if (true == ContentsEvent::ToolData[ToolValue])
		{
			m_CurrentTool = static_cast<ETOOLTYPE>(ToolValue);
			break;
		}
	}

	ChangeToolImg();

	IsChangeTool = true;
}

void UI_Hub_Tool::PrevTool()
{
	if (false == RemainToolCheck())
	{
		return;
	}

	int ToolValue = static_cast<int>(m_CurrentTool);

	while (true)
	{
		--ToolValue;

		if (-1 == ToolValue)
		{
			ToolValue = static_cast<int>(ContentsEvent::ToolData.size()) - 1;
		}

		if (true == ContentsEvent::ToolData[ToolValue])
		{
			m_CurrentTool = static_cast<ETOOLTYPE>(ToolValue);
			break;
		}
	}

	ChangeToolImg();

	IsChangeTool = true;
}

bool UI_Hub_Tool::RemainToolCheck()
{
	int TrueValue = 0;

	for (size_t i = 0; i < ContentsEvent::ToolData.size(); i++)
	{
		if (true == ContentsEvent::ToolData[i])
		{
			++TrueValue;
		}

		if (TrueValue >= 2)
		{
			break;
		}

		if (i == ContentsEvent::ToolData.size() - 1)
		{
			return false;
		}
	}

	return true;
}

void UI_Hub_Tool::ChangeToolImg()
{
	if (m_CurrentToolRenderNumber == static_cast<int>(m_CurrentTool))
	{
		return;
	}

	if (nullptr == m_Tool)
	{
		MsgBoxAssert("존재하지 않은 렌더러를 생성하려 했습니다.");
		return;
	}

	m_Tool->SetSprite("Tool_Icon.png", static_cast<int>(m_CurrentTool));

	m_CurrentToolRenderNumber = static_cast<int>(m_CurrentTool);

	GlobalUtils::PlaySFX("SFX_ToolSwap_01.wav");
}


void UI_Hub_Tool::ChangeToolImg(ETOOLTYPE _Type)
{
	if (nullptr == m_Tool)
	{
		MsgBoxAssert("존재하지 않은 렌더러를 생성하려 했습니다.");
		return;
	}

	m_Tool->SetSprite("Tool_Icon.png", static_cast<int>(_Type));

	m_CurrentToolRenderNumber = static_cast<int>(_Type);
}


void UI_Hub_Tool::UpdateToolArrow(float _Delta)
{

}