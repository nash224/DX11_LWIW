#pragma once



// Ό³Έν :
class UI_Drop : public GameEngineActor
{
private:
	class ItemDropStruct
	{
	public:
		std::shared_ptr<GameEngineUIRenderer> SystemNotice_Base = nullptr;
		std::shared_ptr<GameEngineUIRenderer> Item_Img = nullptr;
		std::shared_ptr<GameEngineUIRenderer> ItemName = nullptr;
	};


private:
	enum class ENOTICECOLORSTATE
	{
		Appear,
		Stay,
		Disappear,
		None,
	};

	enum class ENOTICEPOSITIONSTATE
	{
		Awake,
		Stay,
		None,
	};


public:
	class UI_DropManager* ManagerPtr = nullptr;

public:
	// constrcuter destructer
	UI_Drop();
	~UI_Drop();

	// delete Function
	UI_Drop(const UI_Drop& _Other) = delete;
	UI_Drop(UI_Drop&& _Other) noexcept = delete;
	UI_Drop& operator=(const UI_Drop& _Other) = delete;
	UI_Drop& operator=(UI_Drop&& _Other) noexcept = delete;

	int UILine = 0;

	void Init(std::string_view _ItemName);

	void MoveUnderLine();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


private:
	void RendererSetting(std::string_view _ItemName);
	void AddColorData(float _AddValue);


	void StateSetting();
	void StartAwake(GameEngineState* _Parent);
	void UpdateAwake(float _Delta, GameEngineState* _Parent);

	void StartAppear(GameEngineState* _Parent);
	void UpdateAppear(float _Delta, GameEngineState* _Parent);

	void StartStay(GameEngineState* _Parent);
	void UpdateStay(float _Delta, GameEngineState* _Parent);

	void StartDisappear(GameEngineState* _Parent);
	void UpdateDisappear(float _Delta, GameEngineState* _Parent);


private:
	ItemDropStruct ItemDrop;
	GameEngineState PositionState;
	GameEngineState ColorState;

	bool IsFirst = true;
	bool isDisappear = false;
	float m_MulColor = 0.0f;
	float m_StateTime = 0.0f;
	float m_TargetPosition = 0.0f;

};

