#pragma once

// Ό³Έν :
class UI_Ellie : public GameEngineActor
{
public:
	// constrcuter destructer
	UI_Ellie();
	~UI_Ellie();

	// delete Function
	UI_Ellie(const UI_Ellie& _Other) = delete;
	UI_Ellie(UI_Ellie&& _Other) noexcept = delete;
	UI_Ellie& operator=(const UI_Ellie& _Other) = delete;
	UI_Ellie& operator=(UI_Ellie&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:


};

