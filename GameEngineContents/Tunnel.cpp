#include "PreCompile.h"
#include "Tunnel.h"

Tunnel::Tunnel() 
{
}

Tunnel::~Tunnel() 
{
}


void Tunnel::Update(float _Delta)
{
	TunnelState.Update(_Delta);
}

void Tunnel::Release()
{
	m_Renderer = nullptr;
}

void Tunnel::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void Tunnel::Init(std::string_view _NextLevelName)
{
	NextLevelName = _NextLevelName;

	// Actor Transfomr Setting
	float4 WinScale = GlobalValue::GetWindowScale();
	float4 Position = { WinScale.X * 2.0f, 0.0f, GlobalUtils::CalculateFixDepth(ERENDERDEPTH::FadeObject) };
	Transform.SetLocalRotation({0.0f, 0.0f, 180.0f});
	Transform.SetLocalPosition(Position);

	// Renderer Setting
	m_Renderer = CreateComponent<GameEngineUIRenderer>();
	m_Renderer->SetSprite("Title_Train_Cover.png");
	m_Renderer->UpFlip();
	m_Renderer->GetImageTransform().SetLocalScale({ WinScale.X * 2.0f , WinScale.Y });


	StateSetting();

	TunnelState.ChangeState(ETUNNELSTATE::EnterTunnel);
}

void Tunnel::StateSetting()
{
	CreateStateParameter EnterState;
	EnterState.Start = std::bind(&Tunnel::StartEnterTunnel, this, std::placeholders::_1);
	EnterState.Stay = std::bind(&Tunnel::UpdateEnterTunnel, this, std::placeholders::_1, std::placeholders::_2);
	TunnelState.CreateState(ETUNNELSTATE::EnterTunnel, EnterState);


	CreateStateParameter WaitState;
	WaitState.Stay = std::bind(&Tunnel::UpdateWait, this, std::placeholders::_1, std::placeholders::_2);
	TunnelState.CreateState(ETUNNELSTATE::Wait, WaitState);
}

void Tunnel::StartEnterTunnel(GameEngineState* _Parent)
{
	GameEngineSoundPlayer WhistleSoundPlayer = GameEngineSound::SoundPlay("SFX_TrainWhistle_01.wav");
	WhistleSoundPlayer.SetVolume(GlobalValue::GetSFXVolume());
}

void Tunnel::UpdateEnterTunnel(float _Delta, GameEngineState* _Parent)
{
	float MovePosition = -TunnelSpeed * _Delta;
	Transform.AddLocalPosition({ MovePosition });

	float TunnelXPos = Transform.GetLocalPosition().X;
	if (TunnelXPos < 0.0f)
	{
		TunnelState.ChangeState(ETUNNELSTATE::Wait);
	}
}

void Tunnel::UpdateWait(float _Delta, GameEngineState* _Parent)
{
	static constexpr const float WaitDoneTime = 2.5f;
	
	if (_Parent->GetStateTime() > WaitDoneTime)
	{
		GameEngineCore::ChangeLevel(NextLevelName);
	}
}