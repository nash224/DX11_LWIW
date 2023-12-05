#pragma once

// Ό³Έν :
class SkyLerp : public GameEngineActor
{
public:
	// constrcuter destructer
	SkyLerp();
	~SkyLerp();

	// delete Function
	SkyLerp(const SkyLerp& _Other) = delete;
	SkyLerp(SkyLerp&& _Other) noexcept = delete;
	SkyLerp& operator=(const SkyLerp& _Other) = delete;
	SkyLerp& operator=(SkyLerp&& _Other) noexcept = delete;

	void SetSkyColor();
	void SetSkyColor(const float4& _Color);

	float GetALightValue() const;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

	virtual void SetSkyData();

	void UpdateSkyLerp();
	float GetTimeRatio(int _MinuteCount) const;
	void FollowCamera();
	void LerpSky(const float4& _ColorA, const float4& _ColorB, const float _Time);
	void LerpSky(const float4& _Color);

	void UpdateALightRatio(const float _TimeRatio);

public:
	float4 SkyColor = float4::ZERONULL;
	float4 ReflectionColor = float4::ZERONULL;

protected:
	std::vector<float4> SkyData;

private:
	std::shared_ptr<class SkyLightEffect> SkyEffectPtr;
	std::shared_ptr<GameEngineSpriteRenderer> Sun_Renderer = nullptr;

	bool PauseSkyLerp = false;
	static constexpr const int SunsetStartHour = 15;
	float SunsetStartTimeRatio = 0.0f;
	float SunsetEndTimeRatio = 0.0f;

	float TenMinuteTimeRatio = 0.0f;


	static constexpr const int AlightStartHour = 19;
	float ALightStartTimeRatio = 0.0f;
	float ALight = 0.0f;
};