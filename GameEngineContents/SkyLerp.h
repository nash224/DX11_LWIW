#pragma once



#define Sky_300 { 0.6f, 0.8f, 0.0f, 0.03f }
#define Sky_310 { 0.65f, 0.75f, 0.0f, 0.04f }
#define Sky_320 { 0.7f, 0.7f, 0.0f, 0.05f }
#define Sky_330 { 0.75f, 0.65f, 0.0f, 0.07f }
#define Sky_340 { 0.8f, 0.6f, 0.0f, 0.08f }
#define Sky_350 { 0.8f, 0.55f, 0.0f, 0.10f }
#define Sky_400 { 0.8f, 0.5f, 0.0f, 0.11f }
#define Sky_410 { 0.85f, 0.45f, 0.0f, 0.11f }
#define Sky_420 { 0.9f, 0.4f, 0.0f, 0.12f }
#define Sky_430 { 0.95f, 0.35f, 0.0f, 0.13f }
#define Sky_440 { 0.95f, 0.25f, 0.0f, 0.14f }
#define Sky_450 { 0.95f, 0.15f, 0.0f, 0.14f }
#define Sky_500 { 0.9f, 0.05f, 0.0f, 0.16f }
#define Sky_510 { 0.85f, 0.0f, 0.0f, 0.18f }
#define Sky_520 { 0.8f, 0.0f, 0.0f, 0.2f }
#define Sky_530 { 0.75f, 0.0f, 0.0f, 0.2f }
#define Sky_540 { 0.7f, 0.0f, 0.0f, 0.23f }
#define Sky_550 { 0.6f, 0.0f, 0.01f, 0.25f }
#define Sky_600 { 0.47f, 0.0f, 0.02f, 0.29f }
#define Sky_610 { 0.35f, 0.0f, 0.03f, 0.33f }
#define Sky_620 { 0.21f, 0.0f, 0.05f, 0.37f }
#define Sky_630 { 0.17f, 0.0f, 0.06f, 0.42f }
#define Sky_640 { 0.11f, 0.0f, 0.07f, 0.47f }
#define Sky_650 { 0.07f, 0.0f, 0.08f, 0.51f }
#define Sky_700 { 0.04f, 0.0f, 0.09f, 0.55f }
#define Sky_710 { 0.03f, 0.0f, 0.1f, 0.59f }
#define Sky_720 { 0.01f, 0.0f, 0.11f, 0.62f } 
#define Sky_730 { 0.0f, 0.0f, 0.12f, 0.66f }
#define Sky_740 { 0.0f, 0.0f, 0.14f, 0.7f }

#define START_SUNSET_TIMERATIO 0.4f
#define NIGHT_TIMERATIO 0.666667f


// Ό³Έν :
class SkyLerp : public GameEngineActor
{
public:
	static SkyLerp* SkyManager;

public:
	// constrcuter destructer
	SkyLerp();
	~SkyLerp();

	// delete Function
	SkyLerp(const SkyLerp& _Other) = delete;
	SkyLerp(SkyLerp&& _Other) noexcept = delete;
	SkyLerp& operator=(const SkyLerp& _Other) = delete;
	SkyLerp& operator=(SkyLerp&& _Other) noexcept = delete;

	void Init();

	void SetSkyColor();

	float4 SkyColor = float4::ZERONULL;
	

protected:
	void Start() override {}
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}


	void UpdateSkyLerp();
	float CalculateTimeRatio(int _MinuteCount);
	void FollowCamera();
	void LerpSky(const float4& _ColorA, const float4& _ColorB, const float _Time);
	void LerpSky(const float4& _Color);

private:
	std::vector<float4> SkyData;
	std::shared_ptr<GameEngineSpriteRenderer> Sun_Renderer = nullptr;

	bool PauseSkyLerp = false;
	static constexpr const int SunsetStartHour = 15;
	float SunsetStartTimeRatio = 0.0f;
	float SunsetEndTimeRatio = 0.0f;

	float TenMinuteTimeRatio = 0.0f;

};