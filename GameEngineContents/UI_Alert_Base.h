#pragma once

// Ό³Έν :
class UI_Alert_Base : public GameEngineActor
{
protected:
	enum class EENTERSTATE
	{
		FadeIn,
		Stay,
		FadeOut,
	};

public:
	// constrcuter destructer
	UI_Alert_Base();
	~UI_Alert_Base();

	// delete Function
	UI_Alert_Base(const UI_Alert_Base& _Other) = delete;
	UI_Alert_Base(UI_Alert_Base&& _Other) noexcept = delete;
	UI_Alert_Base& operator=(const UI_Alert_Base& _Other) = delete;
	UI_Alert_Base& operator=(UI_Alert_Base&& _Other) noexcept = delete;

protected:
	void Start() override {}
	void Update(float _Delta) override;
	void Release() override {}
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

	void FSMSetting();
	void ChangeState(EENTERSTATE _State);

	void ChangeFontAlpha(std::weak_ptr<GameEngineUIRenderer> _Font, float _ColorRatio);
	void ChangeMulColor(std::weak_ptr<GameEngineUIRenderer> _Member, float _ColorRatio);

	virtual void StartFadeIn(GameEngineState* _Parent) {}

	virtual void UpdateFadeIn(float _DeltaTime, GameEngineState* _Parent) {}
	virtual void UpdateStay(float _DeltaTime, GameEngineState* _Parent) {}
	virtual void UpdateFadeOut(float _DeltaTime, GameEngineState* _Parent) {}

	

private:
	GameEngineState State;

};

