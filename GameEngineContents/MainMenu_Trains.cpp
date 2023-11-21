#include "PreCompile.h"
#include "MainMenu_Trains.h"

#include "TrainPart.h"

MainMenu_Trains::MainMenu_Trains() 
	:
	m_State(TrainState::None),
	m_TrainState(0),
	m_StateTime(0.0f),
	m_RattleCycle(0.3f)
{	
}
MainMenu_Trains::~MainMenu_Trains()
{
}


void MainMenu_Trains::Start()
{
	m_TrainState = 0;
	m_State = TrainState::RattleUp;
}

void MainMenu_Trains::Update(float _Delta)
{
	UpdateTrainFSM(_Delta);
	TrainSoundState.Update(_Delta);
}

void MainMenu_Trains::Release()
{
	vecTrain.clear();
	TrainSoundPlayer.Stop();
}

void MainMenu_Trains::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void MainMenu_Trains::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////


void MainMenu_Trains::SetRattleCycle(float _Value)
{
	m_RattleCycle = _Value;
}

/////////////////////////////////////////////////////////////////////////////////////


#pragma region 기차 생성

void MainMenu_Trains::Init()
{
	GameEngineLevel* CurLevel = GetLevel();


	vecTrain.reserve(TrainCount);

	{
		std::shared_ptr<TrainPart> Object = CurLevel->CreateActor<TrainPart>(EUPDATEORDER::Objects);
		Object->CreateRenderer();
		Object->SetSprite("Title_Train_Train.png", "Title_Train_Window_0.png");

		float4 TrainPosition = { 462.0f , -334.0f, DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::Trains) };
		float4 TrainLightPosition = { 470.0f , -354.0f , DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::Trains_Light) };
		Object->SetLocalPosition(TrainPosition, TrainLightPosition);
		vecTrain.push_back(Object);
	}

	{
		std::shared_ptr<TrainPart> Object = CurLevel->CreateActor<TrainPart>(EUPDATEORDER::Objects);
		Object->CreateRenderer();
		Object->SetSprite("Title_Train_Train_1.png", "Title_Train_Window_1.png");

		float4 TrainPosition = { 350.0f , -334.0f, DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::Trains) };
		float4 TrainLightPosition = { 356.0f , -354.0f , DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::Trains_Light) };
		Object->SetLocalPosition(TrainPosition, TrainLightPosition);
		vecTrain.push_back(Object);
	}

	{
		std::shared_ptr<TrainPart> Object = CurLevel->CreateActor<TrainPart>(EUPDATEORDER::Objects);
		Object->CreateRenderer();
		Object->SetSprite("Title_Train_Train_2.png", "Title_Train_Window_2.png");
		float4 TrainPosition = { 240.0f , -334.0f, DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::Trains) };
		float4 TrainLightPosition = { 244.0f , -354.0f , DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::Trains_Light) };
		Object->SetLocalPosition(TrainPosition, TrainLightPosition);
		vecTrain.push_back(Object);
	}

	{
		std::shared_ptr<TrainPart> Object = CurLevel->CreateActor<TrainPart>(EUPDATEORDER::Objects);
		Object->CreateRenderer();
		Object->SetSprite("Title_Train_Train_3.png", "Title_Train_Light.png");
		float4 TrainPosition = { 16.0f , -334.0f, DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::Trains) };
		float4 TrainLightPosition = { 56.0f , -360.0f, DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::Trains_Light) };
		Object->SetLocalPosition(TrainPosition, TrainLightPosition);
		vecTrain.push_back(Object);
	}

	{
		std::shared_ptr<TrainPart> Object = CurLevel->CreateActor<TrainPart>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->CreateLastTrainRenderer();
		Object->SetSprite("Title_Train_Train_4.png");
		float4 TrainPosition = { 0.0f , -334.0f, DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::Trains) };
		Object->SetLocalPosition(TrainPosition);
		vecTrain.push_back(Object);
	}

	SoundStateSetting();
}

#pragma endregion 

/////////////////////////////////////////////////////////////////////////////////////

void MainMenu_Trains::SoundStateSetting()
{
	CreateStateParameter OnplayState;
	OnplayState.Stay = [&](float _Delta, GameEngineState* _Parent)
		{
			static constexpr const float SoundWaitTime = 1.0f;
			if (_Parent->GetStateTime() > SoundWaitTime)
			{
				TrainSoundState.ChangeState(ETRAINSOUNDSTATE::TurnDown);
			}
		};
	TrainSoundState.CreateState(ETRAINSOUNDSTATE::Onplay, OnplayState);


	CreateStateParameter TurnDownState;
	TurnDownState.Stay = [&](float _Delta, GameEngineState* _Parent)
		{
			static constexpr const float Train_Sound_Turn_Down_Speed = 0.6f;

			float Volume = _Delta / Train_Sound_Turn_Down_Speed;
			TrainSoundPlayer.SetVolume(Volume * GlobalValue::GetSFXVolume());

			if (_Parent->GetStateTime() > Train_Sound_Turn_Down_Speed)
			{
				TrainSoundState.ChangeState(ETRAINSOUNDSTATE::None);
			}
		};
	TrainSoundState.CreateState(ETRAINSOUNDSTATE::TurnDown, TurnDownState);


	CreateStateParameter NoneState;
	NoneState.Start = [&](GameEngineState* _Parent)
		{

		};
	TrainSoundState.CreateState(ETRAINSOUNDSTATE::None, NoneState);
}


#pragma region 기차 업데이트

void MainMenu_Trains::UpdateTrainFSM(float _Delta)
{
	switch (m_State)
	{
	case TrainState::None:
	{
		MsgBoxAssert("행동을 지정해주지 않았습니다.");
		return;
	}
		break;
	case TrainState::RattleUp:
		UpdateRattleUp(_Delta);
		break;
	case TrainState::RattleDown:
		UpdateRattleDown(_Delta);
		break;
	case TrainState::Wait:
		UpdateWait(_Delta);
		break;
	default:
		break;
	}


}

void MainMenu_Trains::ChangeState(TrainState _State)
{
	if (_State != m_State)
	{
		switch (_State)
		{
		case TrainState::None:
		{
			MsgBoxAssert("행동을 None 으로 지정해줄 수 없습니다.");
			return;
		}
			break;
		case TrainState::RattleUp:
			StartRattleUp();
			break;
		case TrainState::RattleDown:
			StartRattleDown();
			break;
		case TrainState::Wait:
			StartWait();
			break;
		default:
			break;
		}

		m_State = _State;
	}
}



void MainMenu_Trains::StartRattleUp()
{
	std::shared_ptr<TrainPart> Train = vecTrain[m_TrainState];
	if (nullptr == Train)
	{
		MsgBoxAssert("기차가 존재하지 않습니다.");
		return;
	}

	Train->AddLocalPosition(CONST_RattleUpDistance);
}

void MainMenu_Trains::UpdateRattleUp(float _Delta)
{
	m_StateTime += _Delta;
	if (m_StateTime > CONST_RattleTime)
	{
		m_StateTime -= CONST_RattleTime;

		ChangeState(TrainState::RattleDown);
		return;
	}
}



void MainMenu_Trains::StartRattleDown()
{
	std::shared_ptr<TrainPart> Train = vecTrain[m_TrainState];
	Train->AddLocalPosition(CONST_RattleDownDistance);
}

void MainMenu_Trains::UpdateRattleDown(float _Delta)
{
	m_StateTime += _Delta;
	if (m_StateTime > m_RattleCycle)
	{
		m_StateTime -= m_RattleCycle;

		bool isNextTrain = (m_TrainState < TrainCount - 1);
		if (isNextTrain)
		{
			m_TrainState++;
			ChangeState(TrainState::RattleUp);
			return;
		}
		else
		{
			ChangeState(TrainState::Wait);
			return;
		}
	}
}


void MainMenu_Trains::StartWait()
{
	m_TrainState = 0;
}

void MainMenu_Trains::UpdateWait(float _Delta)
{
	m_StateTime += _Delta;

	if (m_StateTime > CONST_WaitTime)
	{
		m_StateTime -= CONST_WaitTime;

		TrainSound();

		ChangeState(TrainState::RattleUp);
		return;
	}
}

#pragma endregion 

void MainMenu_Trains::TrainSound()
{
	TrainSoundPlayer = GameEngineSound::SoundPlay("TD_000.wav");
	TrainSoundPlayer.SetVolume(GlobalValue::GetSFXVolume());
	TrainSoundState.ChangeState(ETRAINSOUNDSTATE::Onplay);
}

