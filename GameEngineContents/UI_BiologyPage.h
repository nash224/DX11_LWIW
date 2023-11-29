#pragma once
#include "UI_DictionaryPage.h"





// Ό³Έν :
class UI_BiologyPage : public UI_DictionaryPage
{
private:
	class EcologicalStruct
	{
	public:
		std::shared_ptr<GameEngineUIRenderer> Font = nullptr;
		std::shared_ptr<GameEngineUIRenderer> Slot1 = nullptr;
		std::shared_ptr<GameEngineUIRenderer> Slot2 = nullptr;
		std::shared_ptr<GameEngineUIRenderer> Slot3 = nullptr;

	};

	class ItemSlot
	{
	public:
		std::shared_ptr<GameEngineUIRenderer> ItemSpace = nullptr;
		std::shared_ptr<GameEngineUIRenderer> ItemImg = nullptr;
		std::shared_ptr<GameEngineUIRenderer> ItemName = nullptr;

	};

	struct BiologyDESCStruct
	{
	public:
		std::shared_ptr<GameEngineUIRenderer> Mark = nullptr;
		std::shared_ptr<GameEngineUIRenderer> Content = nullptr;

	};

	struct BiologyPageStruct
	{
	public:
		EcologicalStruct Ecological;
		ItemSlot Item;
		std::vector<BiologyDESCStruct> DESCArray;

		std::shared_ptr<GameEngineUIRenderer> Base = nullptr;
		std::shared_ptr<GameEngineUIRenderer> MaterialName = nullptr;
		std::shared_ptr<GameEngineUIRenderer> Photo = nullptr;
		std::shared_ptr<GameEngineUIRenderer> Illustration = nullptr;
		std::shared_ptr<GameEngineUIRenderer> Frame = nullptr;
		std::shared_ptr<GameEngineUIRenderer> Tool = nullptr;

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
	BiologyPageStruct PageInfo;


};

