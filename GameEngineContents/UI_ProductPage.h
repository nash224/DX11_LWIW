#pragma once
#include "UI_DictionaryPage.h"





struct ProductPageComposition
{
public:
	std::shared_ptr<GameEngineUIRenderer> ProductTag;
	std::shared_ptr<GameEngineUIRenderer> Photo;
	std::shared_ptr<GameEngineUIRenderer> Illustration;
	std::shared_ptr<GameEngineUIRenderer> Frame;
	std::shared_ptr<GameEngineUIRenderer> Star;
	std::shared_ptr<GameEngineUIRenderer> Fire;
	std::shared_ptr<GameEngineUIRenderer> Ladle;
	std::shared_ptr<GameEngineUIRenderer> ItemSlot1;
	std::shared_ptr<GameEngineUIRenderer> ItemSpace1;
	std::shared_ptr<GameEngineUIRenderer> ItemSlot2;
	std::shared_ptr<GameEngineUIRenderer> ItemSpace2;
	std::shared_ptr<GameEngineUIRenderer> ItemSlot3;
	std::shared_ptr<GameEngineUIRenderer> ItemSpace3;

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
	std::string ReturnIllustedBookFileName(EBREWINGOPTION _Option);
	int ReturnIllustedBookIndex(EBREWINGOPTION _Option);

private:
	ProductPageComposition m_ProductPageComposition;

	const float CONST_OptionGap = 100.0f;
	const float CONST_ItemSpaceGap = 74.0f;

};

