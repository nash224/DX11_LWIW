#pragma once
#include "UI_ToggleActor.h"


// Ό³Έν :
class UI_DictionaryPage;
class UI_Dictionary : public UI_ToggleActor
{
private:
	static EDICTIONARYCATEGORY m_CurrentCategory;

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

	void NextPage();
	void PrevPage();

	void PrevCategory();
	void NextCategory();


protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void CreatePage(EDICTIONARYCATEGORY _Type, std::string_view Name);

	void OpenChild() override;
	void CloseChild() override;

private:
	void UpdateDictionary();
	bool CheckOpenDictionary();
	bool CheckMoveCategory();
	bool CheckTurningPage();


private:
	std::shared_ptr<GameEngineSpriteRenderer> m_BaseRenderer = nullptr;
	std::vector<std::shared_ptr<class UI_BiologyPage>> vecCreaturePage;
	std::vector<std::shared_ptr<class UI_BiologyPage>> vecPlantPage;

private:
	bool IsTurnedPage = false;
	int m_CurrentPage = 0;



	int m_CreaturePageCount = 0;
	int m_PlantPageCount = 0;
};

