#pragma once

enum class TrainState
{
	None,
	RattleUp,
	RattleDown,
	Wait,
};



// ���� : Ÿ��Ʋ ���� �޴��� ������ ����ϰ� �ֽ��ϴ�. 
// �� ����ĭ�� ���Ʒ��� ������ ���ȰŸ��� �ǵ��߽��ϴ�.
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

	void SetRattleCycle(float _Value);
	void Init();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void UpdateTrainFSM(float _Delta);
	void ChangeState(TrainState _State);


	void StartRattleUp();
	void UpdateRattleUp(float _Delta);

	void StartRattleDown();
	void UpdateRattleDown(float _Delta);

	void StartWait();
	void UpdateWait(float _Delta);



private:
	std::vector<std::shared_ptr<class TrainPart>> vecTrain;

	const int CONST_TrainCount = 5;

private:
	int m_TrainState;					// �������� ����
	float m_RattleCycle;				// ���ȰŸ� �ֱ�

	TrainState m_State;					// ������ ����
	float m_StateTime;					// ���½ð�


	const float4 CONST_RattleUpDistance = float4{ 0.0f , 2.0f };
	const float4 CONST_RattleDownDistance = float4{ 0.0f , -2.0f };
	const float CONST_RattleTime = 0.1f;								// ���ȰŸ� �ð�
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

