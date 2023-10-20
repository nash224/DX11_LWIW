#include "PreCompile.h"
#include "Tunnel.h"

Tunnel::Tunnel() 
{
}

Tunnel::~Tunnel() 
{
}


void Tunnel::Start()
{

}

void Tunnel::Update(float _Delta)
{
	UpdateTunnel(_Delta);
}

void Tunnel::Release()
{
	m_Renderer = nullptr;
}

void Tunnel::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void Tunnel::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void Tunnel::Init()
{
	float4 WinScale = GlobalValue::GetWindowScale();

	Transform.SetLocalRotation({0.0f, 0.0f, 180.0f});
	float4 Position = { (WinScale.X + WinScale.hX()) * 2.0f, -WinScale.hY(), GlobalUtils::CalculateDepth(ERENDERDEPTH::FadeObject) };
	Transform.SetLocalPosition(Position);


	m_Renderer = CreateComponent<GameEngineSpriteRenderer>(EUPDATEORDER::Fade);
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_Renderer->SetSprite("Title_Train_Cover.png");
	m_Renderer->GetImageTransform().SetLocalScale({ WinScale.X * 2.0f , WinScale.Y });
}

void Tunnel::UpdateTunnel(float _Delta)
{
	float MovePosition = -TunnelSpeed* _Delta;
	Transform.AddLocalPosition({ MovePosition });

	float TunnelXPos = Transform.GetLocalPosition().X;
	if (TunnelXPos < 400.0f)
	{
		GameEngineCore::ChangeLevel("LoadingLevel");
	}
}