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

void WitchHouse::Update(float _Delta)
{
	UpdateHouseDebug();

	WindowALight.UpdateLightLerp();
	WindowRayALight.UpdateLightLerp();
}

void WitchHouse::Release()
{
	m_HouseVec.clear();
}
void WitchHouse::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void WitchHouse::Init()
{
	const float4& BackScale = BackDrop_PlayLevel::MainBackDrop->GetBackGroundScale();
	float HouseYPosition = -350.0f;
	float HouseZ = GlobalUtils::CalculateObjectDepth(BackScale.Y, HouseYPosition + 50.0f);
	const float4& HousePosition = float4(BackScale.hX(), YRenderCorrection + HouseYPosition, HouseZ);

	Transform.SetLocalPosition(HousePosition);

	RendererSetting();
}

void WitchHouse::RendererSetting()
{
	m_HouseVec.resize(9);

	for (size_t i = 0; i < m_HouseVec.size(); i++)
	{
		const std::shared_ptr<GameEngineSpriteRenderer>& Renderer = CreateComponent<GameEngineSpriteRenderer>();
		Renderer->Transform.SetLocalPosition(float4(0.0f, 0.0f, static_cast<float>(i) * -0.001f));
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


	WindowALight.LightRenderer = CreateComponent<GameEngineSpriteRenderer>();
	WindowALight.SetLightRendererSetting();
	WindowALight.LightRenderer->SetSprite("Light_9.png");


	WindowRayALight.LightRenderer = CreateComponent<GameEngineSpriteRenderer>();
	WindowRayALight.SetLightRendererSetting();
	WindowRayALight.LightRenderer->SetSprite("Light_8.png");
	WindowRayALight.LightRenderer->Transform.AddLocalPosition(float4(0.0f, 0.0f, -0.01f));
}


void WitchHouse::UpdateHouseDebug()
{
	if (false == IsRendererDebug && true == PlayLevel::PixelDebugMode)
	{
		for (std::weak_ptr<GameEngineSpriteRenderer> HouseRenderer : m_HouseVec)
		{
			if (true == HouseRenderer.expired())
			{
				return;
			}

			HouseRenderer.lock()->Off();
		}

		IsRendererDebug = true;
	}

	if (true == IsRendererDebug && false == PlayLevel::PixelDebugMode)
	{
		for (std::weak_ptr<GameEngineSpriteRenderer> HouseRenderer : m_HouseVec)
		{
			if (true == HouseRenderer.expired())
			{
				return;
			}
			
			HouseRenderer.lock()->On();
		}

		IsRendererDebug = false;
	}
}