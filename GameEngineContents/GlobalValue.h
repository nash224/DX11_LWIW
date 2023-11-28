#pragma once


class CameraControler;
class GlobalValue
{
	friend class ContentsCore;
	friend class ContentsGUI;

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

	static float GetBGMVolume();
	static void SetBGMVolume(float _Volume);

	static float& GetSFXVolumePointer();
	static float& GetGlobalVolumePointer();
	static float& GetBGMVolumePointer();

private:
	static void SetWindowScale(const float4& _Scale);

public:
	static constexpr const char* Font_Cafe24 = "ī��24 �Ƴ׸��";
	static constexpr const char* Font_JejuHanlasan = "�����Ѷ��";
	static constexpr const char* Font_Sandoll = "Sandoll �︳ȣ��ü TTF Basic";
	static constexpr const char* Font_Liberation = "Liberation Sans";

private:
	static float4 WindowScale;
	static int RandomSeed;
	static float GlobalSoundVolume;
	static float SFXVolume;
	static float BGMVolume;

};

