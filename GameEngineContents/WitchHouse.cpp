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
	HouseRenderers.clear();

	WindowALight.Release();
	WindowRayALight.Release();
}
void WitchHouse::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void WitchHouse::Init()
{
	static constexpr float YRender_Correction = 148.0f;


	const std::shared_ptr<BackDrop_PlayLevel>& BackDropPtr = PlayLevel::GetPlayLevelPtr()->GetBackDropPtr();
	if (nullptr == BackDropPtr)
	{
		MsgBoxAssert("배경 매니저가 존재하지 않습니다.");
		return;
	}

	const float4& BackScale = BackDropPtr->GetBackGroundScale();
	const float HouseYPosition = -350.0f;
	float HouseZ = DepthFunction::CalculateObjectDepth(BackScale.Y, HouseYPosition + 50.0f);
	const float4& HousePosition = float4(BackScale.hX(), YRender_Correction + HouseYPosition, HouseZ);

	Transform.SetLocalPosition(HousePosition);

	RendererSetting();
}

void WitchHouse::RendererSetting()
{
	HouseRenderers.resize(9);

	for (int i = 0; i < HouseRenderers.size(); i++)
	{
		const std::shared_ptr<GameEngineSpriteRenderer>& Renderer = CreateComponent<GameEngineSpriteRenderer>();
		Renderer->Transform.SetLocalPosition(float4(0.0f, 0.0f, static_cast<float>(i) * -0.001f));
		HouseRenderers[i] = Renderer;
	}

	HouseRenderers.at(0)->SetSprite("WitchHouse_Base.png");
	HouseRenderers.at(1)->SetSprite("WitchHouse_Roof.png");
	HouseRenderers.at(2)->SetSprite("WitchHouse_RepairedPart_0.png");
	HouseRenderers.at(3)->SetSprite("WitchHouse_RepairedPart_1.png");
	HouseRenderers.at(4)->SetSprite("WitchHouse_RepairedPart_2.png");
	HouseRenderers.at(5)->SetSprite("WitchHouse_BrokenPart_3.png");
	HouseRenderers.at(6)->SetSprite("WitchHouse_BrokenPart_4.png");
	HouseRenderers.at(7)->SetSprite("WitchHouse_RepairedPart_5.png");
	HouseRenderers.at(8)->SetSprite("WitchHouse_BrokenPart_6.png");

	WindowALight.Init(this, { float4::ONE , "Light_9.png" }); 
	WindowRayALight.Init(this, { float4::ONE, "Light_8.png" , float4::ZERO, float4(0.0f, 0.0f, -0.02f) });
}


void WitchHouse::UpdateHouseDebug()
{
	if (false == IsRendererDebug && true == PlayLevel::PixelDebugMode)
	{
		for (std::weak_ptr<GameEngineSpriteRenderer> HouseRenderer : HouseRenderers)
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
		for (std::weak_ptr<GameEngineSpriteRenderer> HouseRenderer : HouseRenderers)
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