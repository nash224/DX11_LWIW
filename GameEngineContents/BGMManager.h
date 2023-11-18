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

	template<typename BgmType>
	void PlayBGM(BgmType _PlayType, std::string_view _BGMName, std::string_view _BGM_SFXName = "")
	{
		PlayBGM(static_cast<int>(_PlayType), _BGMName, _BGM_SFXName);
	}

	void PlayBGM(int _PlayType, std::string_view _BGMName, std::string_view _BGM_SFXName);
	void NoneBGM();
	void AbsoluteNoneBGM();
	void DoneAbsoluteNoneBGM();

	void StopBGM();
	bool IsBGMPlay() const;

	int GetPlayType() const
	{
		return PlayType;
	}

	void Update(float _Delta);

protected:

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
	bool isDoneBGM = false;

	int PlayType = -1;

	static constexpr float AmplificationTime = 0.8f;

	static constexpr const float Max_BGM_Volume = 1.0f;
	static constexpr const float Min_BGM_Volume = 0.0f;

};

