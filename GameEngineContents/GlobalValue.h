#pragma once



// Ό³Έν :
class Ellie;
class CameraControler;
class GlobalValue
{
public:
	static std::shared_ptr<CameraControler> g_CameraControler;
	static std::shared_ptr<Ellie> g_Ellie;

private:
	// constrcuter destructer
	GlobalValue() {}
	~GlobalValue() {}

	// delete Function
	GlobalValue(const GlobalValue& _Other) = delete;
	GlobalValue(GlobalValue&& _Other) noexcept = delete;
	GlobalValue& operator=(const GlobalValue& _Other) = delete;
	GlobalValue& operator=(GlobalValue&& _Other) noexcept = delete;

public:
	static void SetWindowScale(const float4& _Scale);
	static float4 GetWindowScale();

private:
	static float4 WindowScale;
};

