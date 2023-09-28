#include "PreCompile.h"
#include "UI_Ellie.h"


#include "UI_Ellie_Tool.h"


UI_Ellie::UI_Ellie() 
{
}

UI_Ellie::~UI_Ellie() 
{
}


void UI_Ellie::Start()
{
	UI_ToggleActor::Start();
}

void UI_Ellie::Update(float _Delta)
{
	UI_ToggleActor::Update(_Delta);
}

void UI_Ellie::LevelStart(class GameEngineLevel* _NextLevel)
{
	UI_ToggleActor::LevelStart(_NextLevel);
}

void UI_Ellie::LevelEnd(class GameEngineLevel* _NextLevel)
{
	UI_ToggleActor::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void UI_Ellie::Init()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	m_Tool = CurLevel->CreateActor<UI_Ellie_Tool>(EUPDATEORDER::UIComponent);
	if (nullptr == m_Tool)
	{
		MsgBoxAssert("도구를 생성하지 못했습니다.");
		return;
	}

	m_Tool->Init();
}


/////////////////////////////////////////////////////////////////////////////////////

void UI_Ellie::OpenChild()
{
	m_Tool->On();
}

void UI_Ellie::CloseChild()
{
	m_Tool->Off();
}