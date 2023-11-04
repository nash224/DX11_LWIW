#include "PreCompile.h"
#include "UI_Hub.h"


#include "UI_Hub_Stamina.h"
#include "UI_Hub_Tool.h"
#include "UI_Hub_QuickSlot.h"
#include "UI_Hub_Broom.h"


UI_Hub::UI_Hub() 
{
}

UI_Hub::~UI_Hub() 
{
}


void UI_Hub::Start()
{
	UI_ToggleActor::Start();
}

void UI_Hub::Update(float _Delta)
{
	UI_ToggleActor::Update(_Delta);
}

void UI_Hub::LevelStart(class GameEngineLevel* _NextLevel)
{
	UI_ToggleActor::LevelStart(_NextLevel);
}

void UI_Hub::LevelEnd(class GameEngineLevel* _NextLevel)
{
	UI_ToggleActor::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void UI_Hub::Init()
{
	IsHub = true;

	m_Tool = GetLevel()->CreateActor<UI_Hub_Tool>(EUPDATEORDER::UIComponent);
	m_Tool->Init();


	m_Stamina = GetLevel()->CreateActor<UI_Hub_Stamina>(EUPDATEORDER::UIComponent);
	m_Stamina->Init();


	m_QuickSlot = GetLevel()->CreateActor<UI_Hub_QuickSlot>(EUPDATEORDER::UIComponent);
	m_QuickSlot->Init();


	m_Broom = GetLevel()->CreateActor<UI_Hub_Broom>(EUPDATEORDER::UIComponent);
	m_Broom->Init();

	Reset();
}


/////////////////////////////////////////////////////////////////////////////////////

void UI_Hub::OpenInternal()
{
	if (nullptr != m_Tool)
	{
		m_Tool->On();
	}

	if (nullptr != m_Stamina)
	{
		m_Stamina->On();
	}

	if (nullptr != m_Stamina)
	{
		m_Stamina->On();
	}

	if (nullptr != m_Broom)
	{
		m_Broom->On();
	}

	if (nullptr != m_QuickSlot)
	{
		m_QuickSlot->On();
	}
}

void UI_Hub::CloseInternal()
{
	if (nullptr != m_Tool)
	{
		m_Tool->Off();
	}

	if (nullptr != m_Stamina)
	{
		m_Stamina->Off();
	}

	if (nullptr != m_QuickSlot)
	{
		m_QuickSlot->Off();
	}

	if (nullptr != m_Broom)
	{
		m_Broom->Off();
	}

	if (nullptr != m_QuickSlot)
	{
		m_QuickSlot->Off();
	}
}

void UI_Hub::Reset()
{
	if (nullptr != m_Tool)
	{
		m_Tool->On();
	}

	if (nullptr != m_Stamina)
	{
		m_Stamina->On();
	}

	if (nullptr != m_QuickSlot)
	{
		m_QuickSlot->On();
	}

	if (nullptr != m_Broom)
	{
		m_Broom->On();
	}

	if (nullptr != m_QuickSlot)
	{
		m_QuickSlot->On();
	}
}