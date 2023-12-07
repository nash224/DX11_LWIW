#pragma once
#include "PlayLevel.h"	
#include "UI_ButtonGuide.h"


class TestGUI : public GameEngineGUIWindow
{
	friend class TestLevel;

private:
	void Start() override {}
	void OnGUI(GameEngineLevel* _Level, float _Delta) override;

private:
	TestLevel* LevelPtr = nullptr;
	float4 LightColor = float4::ZERO;
	float Correction = 0.0f;
	float Inner = 0.0f;
	float Outter = 0.0f;
	float Size = 1.0f;

};



// Ό³Έν :
class TestLevel : public PlayLevel
{
	friend class TestGUI;

private:
	std::shared_ptr<class PixelManager> PixelManagerPtr = nullptr;
	std::shared_ptr<class TestGUI> TestGUIWindow = nullptr;

public:
	// constrcuter destructer
	TestLevel();
	~TestLevel();

	// delete Function
	TestLevel(const TestLevel& _Other) = delete;
	TestLevel(TestLevel&& _Other) noexcept = delete;
	TestLevel& operator=(const TestLevel& _Other) = delete;
	TestLevel& operator=(TestLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	void TestCode();
	void SetPixelMap();

private:
	std::shared_ptr<class TestPlayer> Player = nullptr;
	std::shared_ptr<class UIManager> UI = nullptr;
	std::shared_ptr<class SkyLerp> SkyLight;
	std::shared_ptr<class ALightActor> AlightPtr;
	std::shared_ptr<class Bush> bush = nullptr;

	std::shared_ptr<GameEngineActor> Map = nullptr;
	std::shared_ptr<class TestCircleGauge> ButtonGuide = nullptr;
	UI_ButtonGuide Guide;

};