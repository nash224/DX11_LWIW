#pragma once

// Ό³Έν :
class BGMManager
{
private:
	enum class EBGMSTATE
	{
		Amplification,
		Play,
		Attenuation,
		Stop,
		None,
	};

public:
	// constrcuter destructer
	BGMManager();
	~BGMManager();

	// delete Function
	BGMManager(const BGMManager& _Other) = delete;
	BGMManager(BGMManager&& _Other) noexcept = delete;
	BGMManager& operator=(const BGMManager& _Other) = delete;
	BGMManager& operator=(BGMManager&& _Other) noexcept = delete;

	void Init();

	void PlayBGM(std::string_view _BGMName, std::string_view _BGM_SFXName = "");
	void NoneBGM();
	void StopBGM();
	bool IsBGMPlay() const;

protected:
	void Update(float _Delta);

	void ResourceLoad();
	void StateSetting();

	void StartAmplification(GameEngineState* _Parent);
	void UpdateAmplification(float _Delta, GameEngineState* _Parent);

	void UpdateAttenuation(float _Delta, GameEngineState* _Parent);

	void StartStop(GameEngineState* _Parent);

	void SetVolume();

private:
	GameEngineState State;


	GameEngineSoundPlayer BGM;
	GameEngineSoundPlayer BGM_SFX;
	std::string BGMName;
	std::string BGM_SFXName;

	float BGMVolume = 0.0f;
	bool isPlayBGM = false;


	static constexpr float AmplificationTime = 0.8f;

	static constexpr const float Max_BGM_Volume = 1.0f;
	static constexpr const float Min_BGM_Volume = 0.0f;

};

