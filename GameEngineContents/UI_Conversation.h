#pragma once

// Ό³Έν :
class UI_Conversation : public GameEngineActor
{
public:
	// constrcuter destructer
	UI_Conversation();
	~UI_Conversation();

	// delete Function
	UI_Conversation(const UI_Conversation& _Other) = delete;
	UI_Conversation(UI_Conversation&& _Other) noexcept = delete;
	UI_Conversation& operator=(const UI_Conversation& _Other) = delete;
	UI_Conversation& operator=(UI_Conversation&& _Other) noexcept = delete;

protected:
	void Start() override {}
	void Update(float _Delta) override {}
	void Release() override {}
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

private:


};

