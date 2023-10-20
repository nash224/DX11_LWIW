#pragma once

#define SYSTEM_NOTICE_ITEM_FRIST_POSITION { -384.0f , -10.0f }
#define SYSTEM_NOTICE_ITEM_GAP 50.0f
#define SYSTEM_NOTICE_ITEM_MOVETIME 0.2f


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


class ItemDropRenderer
{
public:
	std::shared_ptr<GameEngineUIRenderer> SystemNotice_Base = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Item_Img = nullptr;
};


// Ό³Έν :
class UI_Drop : public GameEngineActor
{
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


	void Init(std::string_view _ItemName);

	void MoveUnderLine();

public:
	int m_Line = 0;

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

private:
	ItemDropRenderer m_ItemDropRenderer;
	GameEngineState PositionState;
	GameEngineState ColorState;

	bool IsFirst = true;
	float m_StateTime = 0.0f;
	float m_TargetPosition = 0.0f;

};

