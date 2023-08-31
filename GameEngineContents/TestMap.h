#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class TestMap : public GameEngineActor
{
public:
	static TestMap* MainTestMap;

public:
	// constrcuter destructer
	TestMap();
	~TestMap();

	// delete Function
	TestMap(const TestMap& _Other) = delete;
	TestMap(TestMap&& _Other) noexcept = delete;
	TestMap& operator=(const TestMap& _Other) = delete;
	TestMap& operator=(TestMap&& _Other) noexcept = delete;

	GameEngineColor GetColor(float4 _Pos, GameEngineColor _DefaultColor = { 255, 255, 255, 255 });

protected:
	void Start() override;

private:

};

