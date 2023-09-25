#include "PreCompile.h"
#include "UI_Dictionary.h"


UI_Dictionary::UI_Dictionary() 
{
}

UI_Dictionary::~UI_Dictionary() 
{
}


void UI_Dictionary::Start()
{
	UI_ToggleActor::Start();
}

void UI_Dictionary::Update(float _Delta)
{
	UI_ToggleActor::Update(_Delta);

	UpdateDictionary();
}

void UI_Dictionary::LevelStart(class GameEngineLevel* _NextLevel)
{
	UI_ToggleActor::LevelStart(_NextLevel);
}

void UI_Dictionary::LevelEnd(class GameEngineLevel* _NextLevel)
{
	UI_ToggleActor::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
// �̴ϼ�

void UI_Dictionary::Init()
{
	// Base
	m_BaseRenderer = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDER::Base);
	if (nullptr == m_BaseRenderer)
	{
		MsgBoxAssert("Base�� �������� ���߽��ϴ�.");
		return;
	}

	m_BaseRenderer->SetSprite("Base.png");
}



/////////////////////////////////////////////////////////////////////////////////////
// 
// ������Ʈ

void UI_Dictionary::UpdateDictionary()
{
	if (false == OpenCheck)
	{
		if (true == GameEngineInput::IsDown('D'))
		{
			Close();
		}
	}

	OpenCheck = false;
}