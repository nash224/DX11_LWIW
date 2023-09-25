#pragma once
#include "UI_ToggleActor.h"

struct DictionaryInfo
{
public:


};


// Ό³Έν :
class UI_Dictionary : public UI_ToggleActor
{
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
	void UpdateDictionary();


private:
	std::shared_ptr<GameEngineSpriteRenderer> m_BaseRenderer = nullptr;


};

