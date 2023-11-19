#pragma once



// 설명 :
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

	static float GetSoundVolume();
	static void SetSoundVolume(float _Volume);

	static float GetSFXVolume();
	static void SetSFXVolume(float _Volume);

public:
	static constexpr const char* Font_Cafe24 = "카페24 아네모네";
	static constexpr const char* Font_JejuHanlasan = "제주한라산";
	static constexpr const char* Font_Sandoll = "Sandoll 삼립호빵체 TTF Basic";
	static constexpr const char* Font_Liberation = "Liberation Sans";

private:
	static float4 WindowScale;
	static float4 ItemScale;
	static int RandomSeed;
	static float SoundVolume;
	static float SFXVolume;



};

