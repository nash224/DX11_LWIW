#pragma once
#include "UI_DictionaryPage.h"




class AnimalPageParameter
{
public:
	std::string_view Name;
};

// Ό³Έν :
class UI_AnimalPage : public UI_DictionaryPage
{
public:
	// constrcuter destructer
	UI_AnimalPage();
	~UI_AnimalPage();

	// delete Function
	UI_AnimalPage(const UI_AnimalPage& _Other) = delete;
	UI_AnimalPage(UI_AnimalPage&& _Other) noexcept = delete;
	UI_AnimalPage& operator=(const UI_AnimalPage& _Other) = delete;
	UI_AnimalPage& operator=(UI_AnimalPage&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:


};

