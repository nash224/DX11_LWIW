#pragma once



// Ό³Έν :
class Ellie;
class CameraControler;
class GlobalValue
{
public:
	static std::shared_ptr<CameraControler> g_CameraControler;

private:
	// constrcuter destructer
	GlobalValue() {}
	~GlobalValue() {}

	// delete Function
	GlobalValue(const GlobalValue& _Other) = delete;
	GlobalValue(GlobalValue&& _Other) noexcept = delete;
	GlobalValue& operator=(const GlobalValue& _Other) = delete;
	GlobalValue& operator=(GlobalValue&& _Other) noexcept = delete;

	static void Init();

public:
	static void SetWindowScale(const float4& _Scale);
	static float4 GetWindowScale();
	static float4 GetItemScale();
	static int GetSeedValue();

private:
	static float4 WindowScale;
	static float4 ItemScale;
	static int RandomSeed;
};

