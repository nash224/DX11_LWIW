#pragma once
#include "UI_Hub_Actor.h"

// Ό³Έν :
class UI_Hub_Broom : public UI_Hub_Actor
{
public:
	static float BroomFuelTank;

public:
	// constrcuter destructer
	UI_Hub_Broom();
	~UI_Hub_Broom();

	// delete Function
	UI_Hub_Broom(const UI_Hub_Broom& _Other) = delete;
	UI_Hub_Broom(UI_Hub_Broom&& _Other) noexcept = delete;
	UI_Hub_Broom& operator=(const UI_Hub_Broom& _Other) = delete;
	UI_Hub_Broom& operator=(UI_Hub_Broom&& _Other) noexcept = delete;

	void Init();

	static void AddBroomGauge(const float _Value);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<GameEngineUIRenderer> m_Frame = nullptr;
	std::shared_ptr<GameEngineUIRenderer> m_Gauge = nullptr;
	std::shared_ptr<GameEngineUIRenderer> m_Icon = nullptr;


};

