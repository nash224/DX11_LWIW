#pragma once
#include "UI_Hub_Actor.h"
#include "ContentsUIRenderer.h"

// Ό³Έν :
class UI_Hub_Broom : public UI_Hub_Actor
{
public:
	static float RenderingAccFuel;

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

	void UpdateGauge();

protected:
	void Start() override {}
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

private:
	std::shared_ptr<GameEngineUIRenderer> FrameRenderer = nullptr;
	std::shared_ptr<ContentsUIRenderer> GaugeRenderer = nullptr;
	std::shared_ptr<GameEngineUIRenderer> IconRenderer = nullptr;


};

