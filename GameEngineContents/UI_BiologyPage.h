#pragma once
#include "UI_DictionaryPage.h"





// Ό³Έν :
class UI_BiologyPage : public UI_DictionaryPage
{
private:
	class NameTagInfo
	{
	public:
		std::shared_ptr<GameEngineSpriteRenderer> Base = nullptr;
		std::shared_ptr<GameEngineSpriteRenderer> MaterialName = nullptr;
	};

	class IllustrationInfo
	{
	public:
		std::shared_ptr<GameEngineSpriteRenderer> Photo = nullptr;
		std::shared_ptr<GameEngineSpriteRenderer> Illustration = nullptr;

	};

	class EcologicalInfo
	{
	public:
		std::shared_ptr<GameEngineSpriteRenderer> Font = nullptr;
		std::shared_ptr<GameEngineSpriteRenderer> Slot1 = nullptr;
		std::shared_ptr<GameEngineSpriteRenderer> Slot2 = nullptr;
		std::shared_ptr<GameEngineSpriteRenderer> Slot3 = nullptr;

	};

	class ItemSlot
	{
	public:
		std::shared_ptr<GameEngineSpriteRenderer> ItemSpace = nullptr;
		std::shared_ptr<GameEngineSpriteRenderer> ItemImg = nullptr;
		std::shared_ptr<GameEngineSpriteRenderer> ItemName = nullptr;

	};

	struct BiologyPageInfo
	{
	public:
		NameTagInfo NameTag;
		IllustrationInfo Illustration;
		EcologicalInfo Ecological;
		ItemSlot Item;

		std::shared_ptr<GameEngineSpriteRenderer> Frame = nullptr;
		std::shared_ptr<GameEngineSpriteRenderer> Tool = nullptr;

	};

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
	void Start() override {}
	void Update(float _Delta) override {}
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

private:
	std::string ReturnEcologyTypeFileName(EECOLOGYTYPE _Type);

private:
	BiologyPageInfo PageInfo;


};

