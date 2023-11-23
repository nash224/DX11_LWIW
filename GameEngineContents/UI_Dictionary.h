#pragma once
#include "UI_ToggleActor.h"
#include "UI_ButtonGuide.h"

struct CategoryStruct
{
public:
	std::shared_ptr<GameEngineSpriteRenderer> Creature = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Plant = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Potion = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Candy = nullptr;

};


// Ό³Έν :
class UI_DictionaryPage;
class UI_Dictionary : public UI_ToggleActor
{
private:
	static int s_CurrentLeftPage;
	static EDICTIONARYCATEGORY s_CurrentCategory;

public:
	// constrcuter destructer
	UI_Dictionary();
	~UI_Dictionary();

	// delete Function
	UI_Dictionary(const UI_Dictionary& _Other) = delete;
	UI_Dictionary(UI_Dictionary&& _Other) noexcept = delete;
	UI_Dictionary& operator=(const UI_Dictionary& _Other) = delete;
	UI_Dictionary& operator=(UI_Dictionary&& _Other) noexcept = delete;

	
	void Init();


protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void CreateBase();
	void CreateCategory();
	void CreatePage(EDICTIONARYCATEGORY _Type, std::string_view Name);

	// Open, Close Child
	void OpenInternal() override;
	void CloseInternal() override;

	void OpenNextPage(EDICTIONARYCATEGORY _Type);
	void CloseCurrentPage(EDICTIONARYCATEGORY _Type);


	void OnLevelStart();
	bool OnLevelStartCheck = false;

	void UpdateDictionary();
	bool CheckOpenDictionary();
	bool CheckMoveCategory();
	bool CheckTurningPage();

	void NextPage();
	void PrevPage();

	void PrevCategory();
	void NextCategory();


	void OffCategoryMark();
	void OffAllCategoryMark();
	void ChangeCategoryMark();


private:
	std::shared_ptr<GameEngineUIRenderer> BookBase = nullptr;
	CategoryStruct Category;
	std::vector<std::shared_ptr<class UI_BiologyPage>> CreaturePages;
	std::vector<std::shared_ptr<class UI_BiologyPage>> PlantPages;
	std::vector<std::shared_ptr<class UI_ProductPage>> PotionPages;
	std::vector<std::shared_ptr<class UI_ProductPage>> CandyPages;

	UI_ButtonGuide UIGuide;

	bool IsTurnedPage = false;

	int CreaturePageCount = 0;
	int PlantPageCount = 0;
	int PotionPageCount = 0;
	int CandyPageCount = 0;
};

