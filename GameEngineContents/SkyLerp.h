#pragma once



#define Sky_300 { 0.6f, 0.8f, 0.0f, 0.06f }
#define Sky_310 { 0.65f, 0.75f, 0.0f, 0.07f }
#define Sky_320 { 0.7f, 0.7f, 0.0f, 0.08f }
#define Sky_330 { 0.75f, 0.65f, 0.0f, 0.09f }
#define Sky_340 { 0.8f, 0.6f, 0.0f, 0.1f }
#define Sky_350 { 0.8f, 0.55f, 0.0f, 0.11f }
#define Sky_400 { 0.8f, 0.5f, 0.0f, 0.13f }
#define Sky_410 { 0.85f, 0.45f, 0.0f, 0.14f }
#define Sky_420 { 0.9f, 0.4f, 0.0f, 0.16f }
#define Sky_430 { 0.95f, 0.35f, 0.0f, 0.17f }
#define Sky_440 { 0.95f, 0.25f, 0.0f, 0.18f }
#define Sky_450 { 0.95f, 0.15f, 0.0f, 0.19f }
#define Sky_500 { 0.9f, 0.05f, 0.0f, 0.2f }
#define Sky_510 { 0.85f, 0.0f, 0.0f, 0.23f }
#define Sky_520 { 0.8f, 0.0f, 0.0f, 0.26f }
#define Sky_530 { 0.75f, 0.0f, 0.0f, 0.3f }
#define Sky_540 { 0.7f, 0.0f, 0.0f, 0.33f }
#define Sky_550 { 0.65f, 0.0f, 0.0f, 0.35f }
#define Sky_600 { 0.55f, 0.0f, 0.0f, 0.37f }
#define Sky_610 { 0.45f, 0.0f, 0.0f, 0.39f }
#define Sky_620 { 0.39f, 0.0f, 0.0f, 0.41f }
#define Sky_630 { 0.33f, 0.0f, 0.01f, 0.43f }
#define Sky_640 { 0.29f, 0.0f, 0.02f, 0.47f }
#define Sky_650 { 0.21f, 0.0f, 0.04f, 0.5f }
#define Sky_700 { 0.14f, 0.0f, 0.06f, 0.54f }
#define Sky_710 { 0.07f, 0.0f, 0.08f, 0.58f }
#define Sky_720 { 0.03f, 0.0f, 0.1f, 0.63f }
#define Sky_730 { 0.01f, 0.0f, 0.12f, 0.69f }
#define Sky_740 { 0.0f, 0.0f, 0.14f, 0.74f }

#define SUNSET_TIMERATIO 0.4f
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
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


	void UpdateSkyLerp();
	void LerpSky(const float4& _ColorA, const float4& _ColorB, const float _Time);
	void LerpSky(const float4& _Color);

private:
	std::vector<float4> SkyData;
	std::shared_ptr<GameEngineUIRenderer> Sun_Renderer = nullptr;

	bool PauseSkyLerp = false;
	float MinuteRatio = 0.0f;

};