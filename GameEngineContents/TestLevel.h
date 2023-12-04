#pragma once
#include "PlayLevel.h"	
#include "UI_ButtonGuide.h"

// Ό³Έν :
class TestLevel : public PlayLevel
{
public:
	std::shared_ptr<class PixelManager> PixelManagerPtr = nullptr;

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
	std::shared_ptr<class Bush> bush = nullptr;

	std::shared_ptr<GameEngineActor> Map = nullptr;
	std::shared_ptr<GameEngineActor> ButtonGuide = nullptr;
	UI_ButtonGuide Guide;

};