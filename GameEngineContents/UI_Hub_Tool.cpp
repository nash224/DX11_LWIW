#include "PreCompile.h"
#include "UI_Hub_Tool.h"


ETOOLTYPE UI_Hub_Tool::m_CurrentTool = ETOOLTYPE::None;
UI_Hub_Tool::UI_Hub_Tool() 
{
}

UI_Hub_Tool::~UI_Hub_Tool() 
{
}


void UI_Hub_Tool::Start()
{

}

void UI_Hub_Tool::Update(float _Delta)
{
	DetectToolChange();
	UpdateToolArrow(_Delta);
}

void UI_Hub_Tool::LevelStart(class GameEngineLevel* _NextLevel)
{
	ChangeToolImg();
}

void UI_Hub_Tool::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void UI_Hub_Tool::Init()
{
	m_CurrentTool = ETOOLTYPE::Gloves;

	m_Tool = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::HUB_Icon);
	m_Tool->SetSprite("Tool_Icon.png", static_cast<int>(m_CurrentTool));

	m_LeftArrow = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::UIArrow);
	m_LeftArrow->SetSprite("HUD_Arrow_Left.png");
	m_LeftArrow->Transform.AddLocalPosition({ -28.0f , 0.0f });

	m_RightArrow = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::UIArrow);
	m_RightArrow->SetSprite("HUD_Arrow_Left.png");
	m_RightArrow->LeftFlip();
	m_RightArrow->Transform.AddLocalPosition({ 26.0f , 0.0f });

	Transform.AddLocalPosition({ -418.0f , -196.0f });
}


/////////////////////////////////////////////////////////////////////////////////////

void UI_Hub_Tool::DetectToolChange()
{
	if (true == GameEngineInput::IsDown('Q'))
	{
		PrevTool();
	}

	if (true == GameEngineInput::IsDown('W'))
	{
		NextTool();
	}
}

void UI_Hub_Tool::NextTool()
{
	int TrueValue = 0;

	// �����Ϳ� true�� 1���� �������� �ʴ´ٴ� ������ �������ݴϴ�.
	for (size_t i = 0; i < EventData::ToolData.size(); i++)
	{
		if (true == EventData::ToolData[i])
		{
			++TrueValue;
		}

		if (TrueValue >= 2)
		{
			break;
		}

		if (i == EventData::ToolData.size() - 1)
		{
			return;
		}
	}

	int ToolValue = static_cast<int>(m_CurrentTool);

	// ���� ���� ������ ������ ���ϰ� �մϴ�.
	while (true)
	{
		++ToolValue;

		ETOOLTYPE EToolValue = static_cast<ETOOLTYPE>(ToolValue);
		if (ETOOLTYPE::None == EToolValue)
		{
			ToolValue = 0;
		}

		if (true == EventData::ToolData[ToolValue])
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
	int TrueValue = 0;

	// �����Ϳ� true�� 1���� �������� �ʴ´ٴ� ������ �������ݴϴ�.
	for (size_t i = 0; i < EventData::ToolData.size(); i++)
	{
		if (true == EventData::ToolData[i])
		{
			++TrueValue;
		}

		if (TrueValue >= 2)
		{
			break;
		}

		if (i == EventData::ToolData.size() - 1)
		{
			return;
		}
	}

	int ToolValue = static_cast<int>(m_CurrentTool);

	while (true)
	{
		--ToolValue;

		if (-1 == ToolValue)
		{
			ToolValue = static_cast<int>(ETOOLTYPE::None) - 1;
		}

		if (true == EventData::ToolData[ToolValue])
		{
			m_CurrentTool = static_cast<ETOOLTYPE>(ToolValue);
			break;
		}
	}

	ChangeToolImg();

	IsChangeTool = true;
}

// ���� ���� �̹����� �ٸ��� �����մϴ�.

void UI_Hub_Tool::ChangeToolImg()
{
	if (m_CurrentToolRenderNumber == static_cast<int>(m_CurrentTool))
	{
		return;
	}

	if (nullptr == m_Tool)
	{
		MsgBoxAssert("�������� ���� �������� �����Ϸ� �߽��ϴ�.");
		return;
	}

	m_Tool->SetSprite("Tool_Icon.png", static_cast<int>(m_CurrentTool));

	m_CurrentToolRenderNumber = static_cast<int>(m_CurrentTool);
}

// ���� �̹����� �����մϴ�.
void UI_Hub_Tool::ChangeToolImg(ETOOLTYPE _Type)
{
	if (nullptr == m_Tool)
	{
		MsgBoxAssert("�������� ���� �������� �����Ϸ� �߽��ϴ�.");
		return;
	}

	m_Tool->SetSprite("Tool_Icon.png", static_cast<int>(_Type));

	m_CurrentToolRenderNumber = static_cast<int>(_Type);
}


void UI_Hub_Tool::UpdateToolArrow(float _Delta)
{

}