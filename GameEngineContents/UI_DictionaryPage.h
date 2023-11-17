#pragma once

// Ό³Έν :
class UI_DictionaryPage : public GameEngineActor
{
public:
	// constrcuter destructer
	UI_DictionaryPage();
	~UI_DictionaryPage();

	// delete Function
	UI_DictionaryPage(const UI_DictionaryPage& _Other) = delete;
	UI_DictionaryPage(UI_DictionaryPage&& _Other) noexcept = delete;
	UI_DictionaryPage& operator=(const UI_DictionaryPage& _Other) = delete;
	UI_DictionaryPage& operator=(UI_DictionaryPage&& _Other) noexcept = delete;

protected:
	void Start() override {}
	void Update(float _Delta) override {}
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

private:

};

