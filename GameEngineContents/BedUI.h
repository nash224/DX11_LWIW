#pragma once

// Ό³Έν :
class BedUI : public GameEngineActor
{
	friend class WitchHouseBed;

private:
	enum class EBEDUISTATE
	{
		Off,
		PopUp,
		Select,
		Disappear,
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
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


private:
	void RendererSetting();
	void StateSetting();



	void Open();
	void Close();

private:
	std::shared_ptr<GameEngineUIRenderer> BaseRenderer;
	std::shared_ptr<GameEngineUIRenderer> HedFontRenderer;
	std::vector<BedUISlot> SlotInfo;
	BedCursorInfo CursorInfo;

	GameEngineState State;

	static constexpr const float Tooltip_Gap = 12.0f;
	float4 TooltipScale = float4::ZERO;

};

