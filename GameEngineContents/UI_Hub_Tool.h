#pragma once
#include "UI_Hub_Actor.h"

// 설명 :
class UI_Hub_Tool : public UI_Hub_Actor
{
public:
	static ETOOLTYPE CurRenderToolType;

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
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

private:
	void NextTool();
	void PrevTool();

	bool RemainToolCheck();
	
	void ChangeToolImg();							// 이미지와 현재 변수가 다르면 변경
	void ChangeToolImg(ETOOLTYPE _Type);			// 같던 다르던 변경

private:
	void DetectToolChange();
	void UpdateToolArrow(float _Delta);


private:
	std::shared_ptr<GameEngineUIRenderer> Tool = nullptr;
	std::shared_ptr<GameEngineUIRenderer> LeftArrow = nullptr;
	std::shared_ptr<GameEngineUIRenderer> RightArrow = nullptr;


private:
	bool isChangeTool = false;

	int CurRenderToolNum = -1;
	
};

