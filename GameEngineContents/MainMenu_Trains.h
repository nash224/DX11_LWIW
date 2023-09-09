#pragma once

enum class TrainState
{
	None,
	RattleUp,
	RattleDown,
	Wait,
};



// 설명 :
class MainMenu_Trains : public GameEngineActor
{
	friend class BackDrop_MainMenu;

public:
	// constrcuter destructer
	MainMenu_Trains();
	~MainMenu_Trains();

	// delete Function
	MainMenu_Trains(const MainMenu_Trains& _Other) = delete;
	MainMenu_Trains(MainMenu_Trains&& _Other) noexcept = delete;
	MainMenu_Trains& operator=(const MainMenu_Trains& _Other) = delete;
	MainMenu_Trains& operator=(MainMenu_Trains&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void Init();


public:
	void ActorRelease();

	void SetRattleCycle(float _Value);
private:
	void UpdateTrainFSM(float _Delta);
	void ChangeState(TrainState _State);


	void StartRattleUp();
	void UpdateRattleUp(float _Delta);

	void StartRattleDown();
	void UpdateRattleDown(float _Delta);


	void StartWait();
	void UpdateWait(float _Delta);


public:
	

private:
	const int CONST_TrainCount = 5;
	std::vector<std::shared_ptr<class TrainPart>> vecTrain;

private:
	int m_TrainState;					// 진행중인 객차
	float m_RattleCycle;				// 덜컹거림 주기

	TrainState m_State;					// 기차의 상태
	float m_StateTime;					// 상태시간


	const float4 CONST_RattleUpDistance = float4{ 0.0f , 2.0f };
	const float4 CONST_RattleDownDistance = float4{ 0.0f , -2.0f };
	const float CONST_RattleTime = 0.1f;								// 덜컹거림 시간
	const float CONST_WaitTime = 1.0f;


	


private:
	const float4 CONST_Train0Position = float4{ 462.0f , -334.0f };
	const float4 CONST_Train1Position = float4{ 350.0f , -334.0f };
	const float4 CONST_Train2Position = float4{ 240.0f , -334.0f };
	const float4 CONST_Train3Position = float4{ 16.0f , -334.0f };
	const float4 CONST_Train4Position = float4{ 0.0f , -334.0f };

	const float4 CONST_TrainLight0Position = float4{ 470.0f , -354.0f };
	const float4 CONST_TrainLight1Position = float4{ 356.0f , -354.0f };
	const float4 CONST_TrainLight2Position = float4{ 244.0f , -354.0f };
	const float4 CONST_TrainLight3Position = float4{ 56.0f , -360.0f };
};

