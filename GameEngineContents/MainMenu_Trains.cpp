#include "PreCompile.h"
#include "MainMenu_Trains.h"

#include "TrainPart.h"


static constexpr int TrainMaxCount = 5;

MainMenu_Trains::MainMenu_Trains() 
{	
}
MainMenu_Trains::~MainMenu_Trains()
{
}


void MainMenu_Trains::Start()
{
	CurTrainNumber = 0;
	State = ETRAINSTATE::RattleUp;
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

void MainMenu_Trains::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}

void MainMenu_Trains::SetRattleCycle(float _Value)
{
	RattleCycle = _Value;
}


#pragma region 기차 생성

void MainMenu_Trains::Init()
{
	vecTrain.reserve(TrainMaxCount);

	const float TrainDepth = DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::Trains);
	const float LightDepth = DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::Trains_Light);

	{
		std::shared_ptr<TrainPart> Object = GetLevel()->CreateActor<TrainPart>(EUPDATEORDER::Objects);
		Object->Init();
		Object->SetTrainSprite("Title_Train_Train.png", "Title_Train_Window_0.png");

		const float4& TrainPosition = { 462.0f , -334.0f, TrainDepth };
		const float4& TrainLightPosition = { 470.0f , -354.0f , LightDepth };
		Object->SetLocalPosition(TrainPosition, TrainLightPosition);
		vecTrain.push_back(Object);
	}

	{
		const float4& TrainPosition = { 350.0f , -334.0f, TrainDepth };
		const float4& TrainLightPosition = { 356.0f , -354.0f , LightDepth };
		std::shared_ptr<TrainPart> Object = GetLevel()->CreateActor<TrainPart>(EUPDATEORDER::Objects);
		Object->Init();
		Object->SetTrainSprite("Title_Train_Train_1.png", "Title_Train_Window_1.png");
		Object->SetLocalPosition(TrainPosition, TrainLightPosition);
		vecTrain.push_back(Object);
	}

	{
		const float4& TrainPosition = { 240.0f , -334.0f, TrainDepth };
		const float4& TrainLightPosition = { 244.0f , -354.0f , LightDepth };
		std::shared_ptr<TrainPart> Object = GetLevel()->CreateActor<TrainPart>(EUPDATEORDER::Objects);
		Object->Init();
		Object->SetTrainSprite("Title_Train_Train_2.png", "Title_Train_Window_2.png");
		Object->SetLocalPosition(TrainPosition, TrainLightPosition);
		vecTrain.push_back(Object);
	}

	{
		const float4& TrainPosition = { 16.0f , -334.0f, TrainDepth };
		const float4& TrainLightPosition = { 56.0f , -360.0f, LightDepth };
		std::shared_ptr<TrainPart> Object = GetLevel()->CreateActor<TrainPart>(EUPDATEORDER::Objects);
		Object->Init();
		Object->SetTrainSprite("Title_Train_Train_3.png", "Title_Train_Light.png");
		Object->SetLocalPosition(TrainPosition, TrainLightPosition);
		vecTrain.push_back(Object);
	}

	{
		const float4& TrainPosition = { 0.0f , -334.0f, TrainDepth };
		std::shared_ptr<TrainPart> Object = GetLevel()->CreateActor<TrainPart>(EUPDATEORDER::Objects);
		Object->LastTrainInit();
		Object->SetTrainSprite("Title_Train_Train_4.png");
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
			static constexpr float SoundWaitTime = 1.0f;
			if (_Parent->GetStateTime() > SoundWaitTime)
			{
				TrainSoundState.ChangeState(ETRAINSOUNDSTATE::TurnDown);
			}
		};
	TrainSoundState.CreateState(ETRAINSOUNDSTATE::Onplay, OnplayState);


	CreateStateParameter TurnDownState;
	TurnDownState.Stay = [&](float _Delta, GameEngineState* _Parent)
		{
			static constexpr float Train_Sound_Turn_Down_Speed = 0.6f;

			float Volume = _Delta / Train_Sound_Turn_Down_Speed;
			TrainSoundPlayer.SetVolume(Volume * GlobalValue::GetSFXVolume());

			if (_Parent->GetStateTime() > Train_Sound_Turn_Down_Speed)
			{
				TrainSoundState.ChangeState(ETRAINSOUNDSTATE::None);
			}
		};
	TrainSoundState.CreateState(ETRAINSOUNDSTATE::TurnDown, TurnDownState);


	CreateStateParameter NoneState;
	TrainSoundState.CreateState(ETRAINSOUNDSTATE::None, NoneState);
}


#pragma region 기차 업데이트

void MainMenu_Trains::UpdateTrainFSM(float _Delta)
{
	switch (State)
	{
	case ETRAINSTATE::None:
	{
		MsgBoxAssert("행동을 지정해주지 않았습니다.");
		return;
	}
		break;
	case ETRAINSTATE::RattleUp:
		UpdateRattleUp(_Delta);
		break;
	case ETRAINSTATE::RattleDown:
		UpdateRattleDown(_Delta);
		break;
	case ETRAINSTATE::Wait:
		UpdateWait(_Delta);
		break;
	default:
		break;
	}


}

void MainMenu_Trains::ChangeState(ETRAINSTATE _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case ETRAINSTATE::None:
		{
			MsgBoxAssert("행동을 None 으로 지정해줄 수 없습니다.");
			return;
		}
			break;
		case ETRAINSTATE::RattleUp:
			StartRattleUp();
			break;
		case ETRAINSTATE::RattleDown:
			StartRattleDown();
			break;
		case ETRAINSTATE::Wait:
			StartWait();
			break;
		default:
			break;
		}

		State = _State;
	}
}



void MainMenu_Trains::StartRattleUp()
{
	std::shared_ptr<TrainPart> Train = vecTrain.at(CurTrainNumber);
	const float4& RattleUpDistance = float4{ 0.0f , 2.0f };
	Train->AddLocalPosition(RattleUpDistance);
}

void MainMenu_Trains::UpdateRattleUp(float _Delta)
{
	static constexpr float RattleTime = 0.1f;

	StateTime += _Delta;
	if (StateTime > RattleTime)
	{
		StateTime -= RattleTime;

		ChangeState(ETRAINSTATE::RattleDown);
		return;
	}
}



void MainMenu_Trains::StartRattleDown()
{
	std::shared_ptr<TrainPart> Train = vecTrain.at(CurTrainNumber);
	const float4& RattleDownDistance = float4{ 0.0f , -2.0f };
	Train->AddLocalPosition(RattleDownDistance);
}

void MainMenu_Trains::UpdateRattleDown(float _Delta)
{
	StateTime += _Delta;
	if (StateTime > RattleCycle)
	{
		StateTime -= RattleCycle;

		bool isNextTrain = (CurTrainNumber < TrainMaxCount - 1);
		if (isNextTrain)
		{
			CurTrainNumber++;
			ChangeState(ETRAINSTATE::RattleUp);
			return;
		}
		else
		{
			ChangeState(ETRAINSTATE::Wait);
			return;
		}
	}
}


void MainMenu_Trains::StartWait()
{
	CurTrainNumber = 0;
}

void MainMenu_Trains::UpdateWait(float _Delta)
{
	static constexpr float WaitTime = 1.0f;
	StateTime += _Delta;

	if (StateTime > WaitTime)
	{
		StateTime -= WaitTime;

		TrainSound();

		ChangeState(ETRAINSTATE::RattleUp);
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

