#pragma once

// Ό³Έν :
class UI_ToggleActor : public GameEngineActor
{
	friend class UIManager;

public:
	// constrcuter destructer
	UI_ToggleActor();
	~UI_ToggleActor();

	// delete Function
	UI_ToggleActor(const UI_ToggleActor& _Other) = delete;
	UI_ToggleActor(UI_ToggleActor&& _Other) noexcept = delete;
	UI_ToggleActor& operator=(const UI_ToggleActor& _Other) = delete;
	UI_ToggleActor& operator=(UI_ToggleActor&& _Other) noexcept = delete;

	void Open();
	void Close();


protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

protected:
	bool IsOpen = false;
	bool OpenCheck = false;

};

