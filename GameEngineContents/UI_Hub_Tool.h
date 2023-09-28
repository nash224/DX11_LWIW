#pragma once
#include "UI_Hub_Actor.h"

// Ό³Έν :
class UI_Hub_Tool : public UI_Hub_Actor
{
public:
	static ETOOLTYPE m_CurrentTool;

public:
	// constrcuter destructer
	UI_Hub_Tool();
	~UI_Hub_Tool();

	// delete Function
	UI_Hub_Tool(const UI_Hub_Tool& _Other) = delete;
	UI_Hub_Tool(UI_Hub_Tool&& _Other) noexcept = delete;
	UI_Hub_Tool& operator=(const UI_Hub_Tool& _Other) = delete;
	UI_Hub_Tool& operator=(UI_Hub_Tool&& _Other) noexcept = delete;

	void Init();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void NextTool();
	void PrevTool();
	void ChangeToolImg(ETOOLTYPE _Type);

private:
	void DetectToolChange();
	void UpdateToolArrow(float _Delta);


private:
	std::shared_ptr<GameEngineUIRenderer> m_Tool = nullptr;
	std::shared_ptr<GameEngineUIRenderer> m_LeftArrow = nullptr;
	std::shared_ptr<GameEngineUIRenderer> m_RightArrow = nullptr;


private:
	bool IsChangeTool = false;
	
};

