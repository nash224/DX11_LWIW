#pragma once



// Ό³Έν :
class CameraControler;
class GlobalValue
{
public:
	static std::shared_ptr<CameraControler> g_CameraControler;

protected:

private:
	// constrcuter destructer
	GlobalValue() {}
	~GlobalValue() {}

	// delete Function
	GlobalValue(const GlobalValue& _Other) = delete;
	GlobalValue(GlobalValue&& _Other) noexcept = delete;
	GlobalValue& operator=(const GlobalValue& _Other) = delete;
	GlobalValue& operator=(GlobalValue&& _Other) noexcept = delete;

private:

public:
	static void SetWindowScale(const float4& _Scale);
	static float4 GetWindowScale();

public:

private:
	static float4 WindowScale;
};

