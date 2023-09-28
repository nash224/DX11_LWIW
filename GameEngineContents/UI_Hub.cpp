#include "PreCompile.h"
#include "UI_Hub.h"


#include "UI_Hub_Tool.h"


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
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	m_Tool = CurLevel->CreateActor<UI_Hub_Tool>(EUPDATEORDER::UIComponent);
	if (nullptr == m_Tool)
	{
		MsgBoxAssert("도구를 생성하지 못했습니다.");
		return;
	}

	m_Tool->Init();
}


/////////////////////////////////////////////////////////////////////////////////////

void UI_Hub::OpenChild()
{
	if (nullptr != m_Tool)
	{
		m_Tool->On();
	}
}

void UI_Hub::CloseChild()
{
	if (nullptr != m_Tool)
	{
		m_Tool->Off();
	}
}