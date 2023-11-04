#include "PreCompile.h"
#include "UI_ToggleActor.h"

UI_ToggleActor::UI_ToggleActor() 
{
}

UI_ToggleActor::~UI_ToggleActor() 
{
}


void UI_ToggleActor::Start()
{
	GameEngineInput::AddInputObject(this);
}

void UI_ToggleActor::Update(float _Delta)
{
	if (false == IsHub && true == IsOpen)
	{
		if (true == GameEngineInput::IsDown(VK_ESCAPE, this))
		{
			Close();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////




void UI_ToggleActor::Open()
{
	OpenInternal();
	On();
	IsOpen = true;
	OpenCheck = true;
}


void UI_ToggleActor::Close()
{
 	CloseInternal();
	Off();
	IsOpen = false;
}