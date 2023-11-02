#pragma once

// Ό³Έν :
class UI_Alert_Tutorial : public GameEngineActor
{
public:
	// constrcuter destructer
	UI_Alert_Tutorial();
	~UI_Alert_Tutorial();

	// delete Function
	UI_Alert_Tutorial(const UI_Alert_Tutorial& _Other) = delete;
	UI_Alert_Tutorial(UI_Alert_Tutorial&& _Other) noexcept = delete;
	UI_Alert_Tutorial& operator=(const UI_Alert_Tutorial& _Other) = delete;
	UI_Alert_Tutorial& operator=(UI_Alert_Tutorial&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:


};

