#include "PreCompile.h"
#include "UI_Hub.h"

#include "UI_Hub_Stamina.h"
#include "UI_Hub_Tool.h"
#include "UI_Hub_QuickSlot.h"
#include "UI_Hub_Broom.h"
#include "UI_Hub_Calender.h"


UI_Hub::UI_Hub() 
{
}

UI_Hub::~UI_Hub() 
{
}


void UI_Hub::Init()
{
	IsHub = true;

	UITool = GetLevel()->CreateActor<UI_Hub_Tool>(EUPDATEORDER::UIComponent);
	UITool->Init();

	UIStamina = GetLevel()->CreateActor<UI_Hub_Stamina>(EUPDATEORDER::UIComponent);
	UIStamina->Init();

	UIQuickSlot = GetLevel()->CreateActor<UI_Hub_QuickSlot>(EUPDATEORDER::UIComponent);
	UIQuickSlot->Init();

	UIBroom = GetLevel()->CreateActor<UI_Hub_Broom>(EUPDATEORDER::UIComponent);
	UIBroom->Init();

	UICalender = GetLevel()->CreateActor<UI_Hub_Calender>(EUPDATEORDER::UIComponent);
	UICalender->Init();

	Reset();
}


/////////////////////////////////////////////////////////////////////////////////////

void UI_Hub::OpenInternal()
{
	if (nullptr != UITool)
	{
		UITool->On();
	}

	if (nullptr != UIStamina)
	{
		UIStamina->On();
	}

	if (nullptr != UIBroom)
	{
		UIBroom->On();
	}

	if (nullptr != UIQuickSlot)
	{
		UIQuickSlot->On();
	}

	if (nullptr != UICalender)
	{
		UICalender->On();
	}
}

void UI_Hub::CloseInternal()
{
	if (nullptr != UITool)
	{
		UITool->Off();
	}

	if (nullptr != UIStamina)
	{
		UIStamina->Off();
	}

	if (nullptr != UIQuickSlot)
	{
		UIQuickSlot->Off();
	}

	if (nullptr != UIBroom)
	{
		UIBroom->Off();
	}

	if (nullptr != UICalender)
	{
		UICalender->Off();
	}
}

void UI_Hub::Reset()
{
	if (nullptr != UITool)
	{
		UITool->On();
	}

	if (nullptr != UIStamina)
	{
		UIStamina->On();
	}

	if (nullptr != UIQuickSlot)
	{
		UIQuickSlot->On();
	}

	if (nullptr != UIBroom)
	{
		UIBroom->On();
	}

	if (nullptr != UICalender)
	{
		UICalender->On();
	}
}