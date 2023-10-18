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
}

void MainMenu_Trains::Release()
{

}

void MainMenu_Trains::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void MainMenu_Trains::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();

	vecTrain.clear();
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
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	vecTrain.reserve(CONST_TrainCount);

	{
		std::shared_ptr<TrainPart> Object = CurLevel->CreateActor<TrainPart>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->CreateRenderer();
		Object->SetSprite("Title_Train_Train.png", "Title_Train_Window_0.png");

		float4 TrainPosition = { 462.0f , -334.0f, GlobalUtils::CalculateDepth(ETITLERENDERDEPTH::Trains) };
		float4 TrainLightPosition = { 470.0f , -354.0f , GlobalUtils::CalculateDepth(ETITLERENDERDEPTH::Trains_Light) };
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

		Object->CreateRenderer();
		Object->SetSprite("Title_Train_Train_1.png", "Title_Train_Window_1.png");

		float4 TrainPosition = { 350.0f , -334.0f, GlobalUtils::CalculateDepth(ETITLERENDERDEPTH::Trains) };
		float4 TrainLightPosition = { 356.0f , -354.0f , GlobalUtils::CalculateDepth(ETITLERENDERDEPTH::Trains_Light) };
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

		Object->CreateRenderer();
		Object->SetSprite("Title_Train_Train_2.png", "Title_Train_Window_2.png");
		float4 TrainPosition = { 240.0f , -334.0f, GlobalUtils::CalculateDepth(ETITLERENDERDEPTH::Trains) };
		float4 TrainLightPosition = { 244.0f , -354.0f , GlobalUtils::CalculateDepth(ETITLERENDERDEPTH::Trains_Light) };
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

		Object->CreateRenderer();
		Object->SetSprite("Title_Train_Train_3.png", "Title_Train_Light.png");
		float4 TrainPosition = { 16.0f , -334.0f, GlobalUtils::CalculateDepth(ETITLERENDERDEPTH::Trains) };
		float4 TrainLightPosition = { 56.0f , -360.0f, GlobalUtils::CalculateDepth(ETITLERENDERDEPTH::Trains_Light) };
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
		float4 TrainPosition = { 0.0f , -334.0f, GlobalUtils::CalculateDepth(ETITLERENDERDEPTH::Trains) };
		Object->SetLocalPosition(TrainPosition);
		vecTrain.push_back(Object);
	}
}

#pragma endregion 

/////////////////////////////////////////////////////////////////////////////////////


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
		MsgBoxAssert("기차를 불러오지 못했습니다.");
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
	if (nullptr == Train)
	{
		MsgBoxAssert("기차를 불러오지 못했습니다.");
		return;
	}

	Train->AddLocalPosition(CONST_RattleDownDistance);
}

void MainMenu_Trains::UpdateRattleDown(float _Delta)
{
	m_StateTime += _Delta;
	if (m_StateTime > m_RattleCycle)
	{
		m_StateTime -= m_RattleCycle;

		if (m_TrainState < CONST_TrainCount - 1)
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

		ChangeState(TrainState::RattleUp);
		return;
	}
}

#pragma endregion 
