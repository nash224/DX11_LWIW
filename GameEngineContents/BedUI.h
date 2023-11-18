#pragma once

// Ό³Έν :
class BedUI : public GameEngineActor
{
	friend class WitchHouseBed;

private:
	enum class EBEDUISTATE
	{
		PopUp,
		Select,
		Disappear,
		GoDream,
		None,
	};

private:
	class BedCursorInfo
	{
	public:
		std::shared_ptr<GameEngineUIRenderer> CursorRenderer;

	};

	class BedUISlot
	{
	public:
		std::shared_ptr<GameEngineUIRenderer> FontRenderer;
		std::shared_ptr<GameEngineUIRenderer> TooltipRenderer;

	};

public:
	// constrcuter destructer
	BedUI();
	~BedUI();

	// delete Function
	BedUI(const BedUI& _Other) = delete;
	BedUI(BedUI&& _Other) noexcept = delete;
	BedUI& operator=(const BedUI& _Other) = delete;
	BedUI& operator=(BedUI&& _Other) noexcept = delete;

	void Init();

protected:
	void Start() override {}
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


private:
	void RendererSetting();
	void StateSetting();

	void StartPopUp(GameEngineState* _Parent);
	void StartGoDream(GameEngineState* _Parent);

	void UpdatePopUp(float _Delta, GameEngineState* _Parent);
	void UpdateSelect(float _Delta, GameEngineState* _Parent);
	void UpdateDisappear(float _Delta, GameEngineState* _Parent);


	void Open();
	void Close();
	void Reset();

	void SetScale(float _Size);
	void SetFontScale(float _Size);
	void UpdateCursor();
	void MoveCursor(int _Value);

	void SetCursorLocalPosition(bool _isLeft);

private:
	std::shared_ptr<GameEngineUIRenderer> BaseRenderer;
	std::shared_ptr<GameEngineUIRenderer> HedFontRenderer;
	std::vector<BedUISlot> SlotInfo;
	BedCursorInfo CursorInfo;

	GameEngineState State;

	static constexpr const float Tooltip_Gap = 12.0f;
	float4 TooltipScale = float4::ZERO;

	bool isGoDream = false;
	bool isLeftCursor = false;

	static constexpr float SlotYPos = -28.0f;
	static constexpr float PopUp_Time = 0.1f;
	static constexpr int Max_Slot_Count = 2;

	static constexpr float HeadFont_Size = 17.0f;
	static constexpr float SlotFont_Size = 14.0f;

};

