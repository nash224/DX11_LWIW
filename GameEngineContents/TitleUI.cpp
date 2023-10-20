#include "PreCompile.h"
#include "TitleUI.h"


#include "NormalProp.h"

TitleUI::TitleUI() 
{
}

TitleUI::~TitleUI() 
{
}


void TitleUI::Start()
{
}

void TitleUI::Update(float _Delta)
{
	UpdateUI();
}

void TitleUI::Release()
{
}

void TitleUI::LevelStart(class GameEngineLevel* _NextLevel)
{
}

void TitleUI::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void TitleUI::Init()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	ButtonSetting(CurLevel);
	StateSetting(CurLevel);
}


void TitleUI::ButtonSetting(GameEngineLevel* _Level)
{
	std::shared_ptr<NormalProp> ZButton = _Level->CreateActor<NormalProp>();
	if (nullptr == ZButton)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	ZButton->Transform.SetLocalPosition({100.0f, -480.0f, GlobalUtils::CalculateDepth(ETITLERENDERDEPTH::UI)});
	ZButton->Init();
	ZButton->m_Renderer->SetSprite("ButtonSet_Keyboard_Z_PressHold.png");


	std::shared_ptr<NormalProp> ArrowButton = _Level->CreateActor<NormalProp>();
	if (nullptr == ArrowButton)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	ArrowButton->Transform.SetLocalPosition({ 270.0f, -480.0f, GlobalUtils::CalculateDepth(ETITLERENDERDEPTH::UI) });
	ArrowButton->Init();
	ArrowButton->m_Renderer->SetSprite("ButtonSet_Keyboard_Arrow_Vertical.png");
}

void TitleUI::StateSetting(GameEngineLevel* _Level)
{
	//CreateStateParameter PressButtonState;
	//PressButtonState.Start = [=](GameEngineState* _Parent)
	//	{
	//		_Level->CreateActor<>
	//	};
}


/////////////////////////////////////////////////////////////////////////////////////

void TitleUI::UpdateUI()
{

}
