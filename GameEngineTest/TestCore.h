#pragma once

// Ό³Έν :
class TestCore : public GameEngineObject
{
public:
	static std::string GetWindowTitle()
	{
		return "TestWindow";
	}

	static float4 GetStartWindowSize()
	{
		return { 960, 540 };
	}

	static float4 GetStartWindowPos()
	{
		return { 50, 50 };
	}

	// constrcuter destructer
	TestCore();
	~TestCore();

	// delete Function
	TestCore(const TestCore& _Other) = delete;
	TestCore(TestCore&& _Other) noexcept = delete;
	TestCore& operator=(const TestCore& _Other) = delete;
	TestCore& operator=(TestCore&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;


private:



};

