#pragma once
#include "UI_Ellie_Actor.h"

// Ό³Έν :
class UI_Ellie_Tool : public UI_Ellie_Actor
{
public:
	static ETOOLTYPE m_CurrentTool;

public:
	// constrcuter destructer
	UI_Ellie_Tool();
	~UI_Ellie_Tool();

	// delete Function
	UI_Ellie_Tool(const UI_Ellie_Tool& _Other) = delete;
	UI_Ellie_Tool(UI_Ellie_Tool&& _Other) noexcept = delete;
	UI_Ellie_Tool& operator=(const UI_Ellie_Tool& _Other) = delete;
	UI_Ellie_Tool& operator=(UI_Ellie_Tool&& _Other) noexcept = delete;

	void Init();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<GameEngineUIRenderer> m_Tool = nullptr;
	std::shared_ptr<GameEngineUIRenderer> m_LeftArrow = nullptr;
	std::shared_ptr<GameEngineUIRenderer> m_RightArrow = nullptr;


private:
	
};

