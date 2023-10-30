#include "PreCompile.h"
#include "UI_Conversation.h"


UI_Conversation* UI_Conversation::MainConversationUI = nullptr;
UI_Conversation::UI_Conversation() 
{
}

UI_Conversation::~UI_Conversation() 
{
}

void UI_Conversation::LevelStart(class GameEngineLevel* _NextLevel)
{
	MainConversationUI = this;
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void UI_Conversation::Init()
{
	MainConversationUI = this;

	RendererSetting();
}


void UI_Conversation::RendererSetting()
{

}