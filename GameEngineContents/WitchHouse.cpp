#include "PreCompile.h"
#include "WitchHouse.h"


#include "BackDrop_PlayLevel.h"
#include "PlayLevel.h"

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
	UpdateHouseDebug();
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
	float HouseYPosition = -350.0f;
	float HouseZ = BackDrop_PlayLevel::MainBackDrop->ZSort(HouseYPosition + 50.0f);
	Transform.SetLocalPosition({ BackDrop_PlayLevel::MainBackDrop->GetBackGroundScale().Half().X, HouseYPosition, HouseZ});

	RendererSetting();
}

void WitchHouse::RendererSetting()
{
	m_HouseVec.resize(9);

	for (size_t i = 0; i < m_HouseVec.size(); i++)
	{
		std::shared_ptr<GameEngineSpriteRenderer> Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::NonAlphaBlend);
		Renderer->Transform.SetLocalPosition(float4(0.0f, HouseRenderBias, static_cast<float>(i) * -0.001f));
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


void WitchHouse::UpdateHouseDebug()
{
	if (false == IsRendererDebug && true == PlayLevel::PixelDebugMode)
	{
		for (size_t i = 0; i < m_HouseVec.size(); i++)
		{
			if (nullptr == m_HouseVec[i])
			{
				MsgBoxAssert("존재하지 않는 렌더러를 참조하려 했습니다.");
				return;
			}

			m_HouseVec[i]->Off();
		}

		IsRendererDebug = true;
	}

	if (true == IsRendererDebug && false == PlayLevel::PixelDebugMode)
	{
		for (size_t i = 0; i < m_HouseVec.size(); i++)
		{
			if (nullptr == m_HouseVec[i])
			{
				MsgBoxAssert("존재하지 않는 렌더러를 참조하려 했습니다.");
				return;
			}

			m_HouseVec[i]->On();
		}

		IsRendererDebug = false;
	}
	
}