#pragma once
#include "UI_Hub_Actor.h"

struct GaugeComposition
{
public:
	std::shared_ptr<GameEngineUIRenderer> Frame = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Gauge1 = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Gauge2 = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Indicator = nullptr;

};

// Ό³Έν :
class UI_Hub_Stamina : public UI_Hub_Actor
{
public:
	// constrcuter destructer
	UI_Hub_Stamina();
	~UI_Hub_Stamina();

	// delete Function
	UI_Hub_Stamina(const UI_Hub_Stamina& _Other) = delete;
	UI_Hub_Stamina(UI_Hub_Stamina&& _Other) noexcept = delete;
	UI_Hub_Stamina& operator=(const UI_Hub_Stamina& _Other) = delete;
	UI_Hub_Stamina& operator=(UI_Hub_Stamina&& _Other) noexcept = delete;

	void Init();

	static void AddGauge(int _Value);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	GaugeComposition m_GaugeComposition;

	const int MaxStamina = 100;
	int CurrentStamina = -1;
	int RecoverableStamina = -1;
};

