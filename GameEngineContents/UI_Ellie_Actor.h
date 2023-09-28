#pragma once

// Ό³Έν :
class UI_Ellie_Actor : public GameEngineActor
{
public:
	// constrcuter destructer
	UI_Ellie_Actor();
	~UI_Ellie_Actor();

	// delete Function
	UI_Ellie_Actor(const UI_Ellie_Actor& _Other) = delete;
	UI_Ellie_Actor(UI_Ellie_Actor&& _Other) noexcept = delete;
	UI_Ellie_Actor& operator=(const UI_Ellie_Actor& _Other) = delete;
	UI_Ellie_Actor& operator=(UI_Ellie_Actor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:


};

