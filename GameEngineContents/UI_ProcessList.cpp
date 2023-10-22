#include "PreCompile.h"
#include "UI_ProcessList.h"

#include "UI_ProcessListUnit.h"

#include "IngredientData.h"

UI_ProcessList::UI_ProcessList() 
{
}

UI_ProcessList::~UI_ProcessList() 
{
}



void UI_ProcessList::Start() 
{

}

void UI_ProcessList::Update(float _Delta) 
{

}

void UI_ProcessList::Release() 
{

}

void UI_ProcessList::LevelEnd(class GameEngineLevel* _NextLevel) 
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////



void UI_ProcessList::Init()
{
	RendererSetting();

	CreateProcessSlot("Mongsiri_Water");
	

	// 등록하면
	// Init
}

void UI_ProcessList::RendererSetting()
{
	m_Base = CreateComponent<GameEngineUIRenderer>();
	m_Base->Transform.SetLocalPosition(float4(0.0f, 0.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Base)));
	m_Base->SetSprite("Process_Base.png");



	Off();
}


void UI_ProcessList::CreateProcessSlot(std::string_view _ProcessName)
{
	if (nullptr == IngredientData::Find(_ProcessName))
	{
		MsgBoxAssert("가공하는 재료의 정보가 존재하지 않습니다.");
		return;
	}

	std::shared_ptr<UI_ProcessListUnit > Unit = GetLevel()->CreateActor<UI_ProcessListUnit>(EUPDATEORDER::UIComponent);
	Unit->Init(_ProcessName, 2);
	SlotVec.push_back(Unit);
}