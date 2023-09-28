#pragma once

// Ό³Έν :
class UI_Hub_Actor : public GameEngineActor
{
public:
	// constrcuter destructer
	UI_Hub_Actor();
	~UI_Hub_Actor();

	// delete Function
	UI_Hub_Actor(const UI_Hub_Actor& _Other) = delete;
	UI_Hub_Actor(UI_Hub_Actor&& _Other) noexcept = delete;
	UI_Hub_Actor& operator=(const UI_Hub_Actor& _Other) = delete;
	UI_Hub_Actor& operator=(UI_Hub_Actor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:


};

