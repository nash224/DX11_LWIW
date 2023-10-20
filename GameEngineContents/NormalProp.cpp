#include "PreCompile.h"
#include "NormalProp.h"

NormalProp::NormalProp() 
{
}

NormalProp::~NormalProp() 
{
}


void NormalProp::Start()
{

}

void NormalProp::Update(float _Delta)
{
	UpdateDebug();

}

void NormalProp::Release()
{
	m_Renderer = nullptr;
	m_DebugRenderer = nullptr;
}

void NormalProp::LevelStart(class GameEngineLevel* _NextLevel)
{
}

void NormalProp::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void NormalProp::Init(int _Order)
{
	m_Renderer = CreateComponent<GameEngineSpriteRenderer>(_Order);
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	
}