#pragma once
#include "UI_Hub_Actor.h"
#include "GaugeUIRenderer.h"

// Ό³Έν :
class UI_Hub_Broom : public UI_Hub_Actor
{
private:
	enum class EUIBROOMSTATE
	{
		HasNotBroom,
		UpdateFuel,
		None,
	};

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


protected:
	void Start() override {}
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

	void RendererSetting();
	void StateSetting();

	void StartHasNotBroom(GameEngineState* _Parent);

	void UpdateGauge(float _Delta, GameEngineState* _Parent);
	void UpdateHasNotBroom(float _Delta, GameEngineState* _Parent);

	void EndHasNotBroom(GameEngineState* _Parent);

private:
	float RenderingAccFuel = 0.0f;

	GameEngineState State;

	std::shared_ptr<GameEngineUIRenderer> FrameRenderer = nullptr;
	std::shared_ptr<GaugeUIRenderer> GaugeUI = nullptr;
	std::shared_ptr<GameEngineUIRenderer> IconRenderer = nullptr;

};

