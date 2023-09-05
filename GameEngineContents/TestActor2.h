#pragma once

// Ό³Έν :
class TestActor2 : public GameEngineActor
{
public:
	// constrcuter destructer
	TestActor2();
	~TestActor2();

	// delete Function
	TestActor2(const TestActor2& _Other) = delete;
	TestActor2(TestActor2&& _Other) noexcept = delete;
	TestActor2& operator=(const TestActor2& _Other) = delete;
	TestActor2& operator=(TestActor2&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:


};

