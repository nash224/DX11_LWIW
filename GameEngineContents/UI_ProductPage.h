#pragma once
#include "UI_DictionaryPage.h"



// Ό³Έν :
class UI_ProductPage : public UI_DictionaryPage
{
private:
	class PageFontStruct
	{
	public:
		std::shared_ptr<GameEngineUIRenderer> Tag;
		std::shared_ptr<GameEngineUIRenderer> Explanation;
		std::shared_ptr<GameEngineUIRenderer> Star;
		std::shared_ptr<GameEngineUIRenderer> Fire;
		std::shared_ptr<GameEngineUIRenderer> Stir;

	};

	class PageItemSlotStruct
	{
	public:
		std::shared_ptr<GameEngineUIRenderer> ItemSpace;
		std::shared_ptr<GameEngineUIRenderer> ItemSlot;
		std::shared_ptr<GameEngineUIRenderer> IngredientName;

	};

	struct ProductPageStruct
	{
	public:
		std::shared_ptr<GameEngineUIRenderer> ProductTag;
		std::shared_ptr<GameEngineUIRenderer> Photo;
		std::shared_ptr<GameEngineUIRenderer> Illustration;
		std::shared_ptr<GameEngineUIRenderer> Frame;
		std::shared_ptr<GameEngineUIRenderer> Star;
		std::shared_ptr<GameEngineUIRenderer> Fire;
		std::shared_ptr<GameEngineUIRenderer> Ladle;

		std::vector<PageItemSlotStruct> ItemSlots;
		PageFontStruct PageFont;

	};

public:
	// constrcuter destructer
	UI_ProductPage();
	~UI_ProductPage();

	// delete Function
	UI_ProductPage(const UI_ProductPage& _Other) = delete;
	UI_ProductPage(UI_ProductPage&& _Other) noexcept = delete;
	UI_ProductPage& operator=(const UI_ProductPage& _Other) = delete;
	UI_ProductPage& operator=(UI_ProductPage&& _Other) noexcept = delete;

	void CreatePage(std::string_view _ProduectName, int& PageCount);

protected:
	void Start() override {}
	void Update(float _Delta) override {}
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

	std::string GetStarString(EBREWING_DIFFICULTY _Number);
	std::string GetFireString(EBREWING_FIRE _Number);
	std::string GetLadleString(EBREWING_DIRECTION _Number);

private:
	ProductPageStruct Page;

};

