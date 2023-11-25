#pragma once

enum class ETRAINSTATE
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

private:
	enum class ETRAINSOUNDSTATE
	{
		Onplay,
		TurnDown,
		None,
	};

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
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


	void SoundStateSetting();

private:
	void UpdateTrainFSM(float _Delta);
	void ChangeState(ETRAINSTATE _State);


	void StartRattleUp();
	void UpdateRattleUp(float _Delta);

	void StartRattleDown();
	void UpdateRattleDown(float _Delta);

	void StartWait();
	void UpdateWait(float _Delta);

	void TrainSound();

private:
	std::vector<std::shared_ptr<class TrainPart>> vecTrain;
	GameEngineSoundPlayer TrainSoundPlayer;
	GameEngineState TrainSoundState;

	ETRAINSTATE State = ETRAINSTATE::None;
	float StateTime = 0.0f;
	float TrainSoundTime = 0.0f;
	float RattleCycle = 0.3f;

	int CurTrainNumber = 0;

};

