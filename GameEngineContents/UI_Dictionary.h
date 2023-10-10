#pragma once
#include "UI_ToggleActor.h"

constexpr float CategoryGap = 14.0f;


struct CategoryRenderer
{
public:
	std::shared_ptr<GameEngineSpriteRenderer> Creature = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Plant = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Potion = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Candy = nullptr;

};


// 설명 :
class UI_DictionaryPage;
class UI_Dictionary : public UI_ToggleActor
{
private:
	static int g_CurrentLeftPage;
	static EDICTIONARYCATEGORY g_CurrentCategory;

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
	// 생성
	void CreateBase();
	void CreateCategory();
	void CreatePage(EDICTIONARYCATEGORY _Type, std::string_view Name);


private:
	// Open, Close
	void OpenChild() override;
	void CloseChild() override;

	void OpenNextPage(EDICTIONARYCATEGORY _Type);
	void CloseCurrentPage(EDICTIONARYCATEGORY _Type);

private:
	// Update
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
	void ChangeCategoryMark();


private:
	std::shared_ptr<GameEngineUIRenderer> m_BaseRenderer = nullptr;
	CategoryRenderer m_CategoryRenderer;
	std::vector<std::shared_ptr<class UI_BiologyPage>> vecCreaturePage;
	std::vector<std::shared_ptr<class UI_BiologyPage>> vecPlantPage;
	std::vector<std::shared_ptr<class UI_ProductPage>> vecPotionPage;
	std::vector<std::shared_ptr<class UI_ProductPage>> vecCandyPage;

private:
	bool IsTurnedPage = false;



	int m_CreaturePageCount = 0;
	int m_PlantPageCount = 0;
	int m_PotionPageCount = 0;
	int m_CandyPageCount = 0;
};

