#pragma once

// Ό³Έν :
class UI_Alert_Quest : public GameEngineActor
{
public:
	// constrcuter destructer
	UI_Alert_Quest();
	~UI_Alert_Quest();

	// delete Function
	UI_Alert_Quest(const UI_Alert_Quest& _Other) = delete;
	UI_Alert_Quest(UI_Alert_Quest&& _Other) noexcept = delete;
	UI_Alert_Quest& operator=(const UI_Alert_Quest& _Other) = delete;
	UI_Alert_Quest& operator=(UI_Alert_Quest&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:


};

