#include "PreCompile.h"
#include "WitchHouse.h"


#include "BackDrop_PlayLevel.h"

WitchHouse::WitchHouse() 
{
}

WitchHouse::~WitchHouse() 
{
}


void WitchHouse::Start()
{
}

void WitchHouse::Update(float _Delta)
{
}

void WitchHouse::Release()
{
	m_HouseVec.clear();
}

void WitchHouse::LevelStart(class GameEngineLevel* _NextLevel)
{
}

void WitchHouse::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void WitchHouse::Init()
{
	RendererSetting();
}

void WitchHouse::RendererSetting()
{
	m_HouseVec.resize(9);

	for (size_t i = 0; i < m_HouseVec.size(); i++)
	{
		std::shared_ptr<GameEngineSpriteRenderer> Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::NonAlphaBlend);
		if (nullptr == Renderer)
		{
			MsgBoxAssert("렌더러를 생성하지 못했습니다.");
			return;
		}

		if (nullptr == BackDrop_PlayLevel::MainBackDrop)
		{
			MsgBoxAssert("배경 매니저가 존재하지 않습니다.");
			return;
		}

		float RendererYPosition = -BackDrop_PlayLevel::MainBackDrop->GetBackGroundScale().Y + 40.0f - static_cast<float>(i);

		float ZOrder = BackDrop_PlayLevel::MainBackDrop->ZSort(RendererYPosition);
		float4 Position = { 0.0f , HouseRenderBias , ZOrder };

		Renderer->Transform.SetLocalPosition(Position);
		m_HouseVec[i] = Renderer;
	}

	m_HouseVec[0]->SetSprite("WitchHouse_Base.png");
	m_HouseVec[1]->SetSprite("WitchHouse_Roof.png");
	m_HouseVec[2]->SetSprite("WitchHouse_RepairedPart_0.png");
	m_HouseVec[3]->SetSprite("WitchHouse_RepairedPart_1.png");
	m_HouseVec[4]->SetSprite("WitchHouse_RepairedPart_2.png");
	m_HouseVec[5]->SetSprite("WitchHouse_BrokenPart_3.png");
	m_HouseVec[6]->SetSprite("WitchHouse_BrokenPart_4.png");
	m_HouseVec[7]->SetSprite("WitchHouse_RepairedPart_5.png");
	m_HouseVec[8]->SetSprite("WitchHouse_BrokenPart_6.png");
}