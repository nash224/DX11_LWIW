#pragma once


class CameraControler;
class GlobalValue
{
	friend class ContentsCore;

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
	static float4 GetWindowScale();
	static int GetSeedValue();

	static float GetSoundVolume();
	static void SetSoundVolume(float _Volume);

	static float GetSFXVolume();
	static void SetSFXVolume(float _Volume);

private:
	static void SetWindowScale(const float4& _Scale);

public:
	static constexpr const char* Font_Cafe24 = "카페24 아네모네";
	static constexpr const char* Font_JejuHanlasan = "제주한라산";
	static constexpr const char* Font_Sandoll = "Sandoll 삼립호빵체 TTF Basic";
	static constexpr const char* Font_Liberation = "Liberation Sans";

private:
	static float4 WindowScale;
	static int RandomSeed;
	static float GlobalSoundVolume;
	static float SFXVolume;

};

