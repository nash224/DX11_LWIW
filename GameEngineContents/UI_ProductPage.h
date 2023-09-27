#pragma once
#include "UI_DictionaryPage.h"

class ProduectPageParamter
{
public:
	std::string_view ProductName;


};


struct ProductPageComposition
{
public:
	std::shared_ptr<GameEngineSpriteRenderer> ProductTag;
	std::shared_ptr<GameEngineSpriteRenderer> Photo;
	std::shared_ptr<GameEngineSpriteRenderer> Illustration;
	std::shared_ptr<GameEngineSpriteRenderer> Frame;
	std::shared_ptr<GameEngineSpriteRenderer> Star;
	std::shared_ptr<GameEngineSpriteRenderer> Fire;
	std::shared_ptr<GameEngineSpriteRenderer> Ladle;
	std::shared_ptr<GameEngineSpriteRenderer> ItemSlot1;
	std::shared_ptr<GameEngineSpriteRenderer> ItemSlot2;
	std::shared_ptr<GameEngineSpriteRenderer> ItemSlot3;

};



// Ό³Έν :
class UI_ProductPage : public UI_DictionaryPage
{
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
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	ProductPageComposition m_ProductPageComposition;

};

