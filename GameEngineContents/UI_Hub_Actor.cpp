#include "PreCompile.h"
#include "UI_Hub_Actor.h"

UI_Hub_Actor::UI_Hub_Actor() 
{
}

UI_Hub_Actor::~UI_Hub_Actor() 
{
}


void UI_Hub_Actor::Start()
{
	GameEngineInput::AddInputObject(this);
}