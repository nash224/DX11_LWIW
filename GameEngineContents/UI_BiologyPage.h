#pragma once
#include "UI_DictionaryPage.h"

struct BiologyPageComposition
{
public:
	std::shared_ptr<GameEngineSpriteRenderer> NameTag = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Photo = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Frame = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Illustration = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Slot1 = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Slot2 = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Slot3 = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Tool = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> ItemSpace = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> ItemImg = nullptr;
};

// Ό³Έν :
class UI_BiologyPage : public UI_DictionaryPage
{
public:
	// constrcuter destructer
	UI_BiologyPage();
	~UI_BiologyPage();

	// delete Function
	UI_BiologyPage(const UI_BiologyPage & _Other) = delete;
	UI_BiologyPage(UI_BiologyPage && _Other) noexcept = delete;
	UI_BiologyPage& operator=(const UI_BiologyPage & _Other) = delete;
	UI_BiologyPage& operator=(UI_BiologyPage && _Other) noexcept = delete;

	void CreatePage(std::string_view _BiologyName, int& PageCount);


protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	std::string ReturnEcologyTypeFileName(EECOLOGYTYPE _Type);

private:
	BiologyPageComposition m_BiologyPageComposition;
};

