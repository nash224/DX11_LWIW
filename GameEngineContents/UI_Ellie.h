#pragma once
#include "UI_ToggleActor.h"


// Ό³Έν :
class UI_Ellie : public UI_ToggleActor
{
public:
	// constrcuter destructer
	UI_Ellie();
	~UI_Ellie();

	// delete Function
	UI_Ellie(const UI_Ellie& _Other) = delete;
	UI_Ellie(UI_Ellie&& _Other) noexcept = delete;
	UI_Ellie& operator=(const UI_Ellie& _Other) = delete;
	UI_Ellie& operator=(UI_Ellie&& _Other) noexcept = delete;

	void Init();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void OpenChild() override;
	void CloseChild() override;


private:
	std::shared_ptr<class UI_Ellie_Tool> m_Tool = nullptr;
};

