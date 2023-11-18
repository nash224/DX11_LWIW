#pragma once

#define Light1 {0.0f, 0.0f, 0.0f, 0.0f} 
#define Light2 {0.25f, 0.28f, 0.156f, 1.0f} 
#define Light3 {0.1f, 0.25f, 0.17f, 0.58f} 
#define Light4 {0.68f, 1.0f, 0.56f, 1.0f} 
#define Light5 {0.31f, 0.29f, 0.56f, 0.67f} 


// Ό³Έν :
class FireWorks : public GameEngineActor
{
private:
	enum class ECRACKERPOTIONSTATE
	{
		Light,
		Fire,
		FireLine,
		None,
	};


public:
	// constrcuter destructer
	FireWorks();
	~FireWorks();

	// delete Function
	FireWorks(const FireWorks& _Other) = delete;
	FireWorks(FireWorks&& _Other) noexcept = delete;
	FireWorks& operator=(const FireWorks& _Other) = delete;
	FireWorks& operator=(FireWorks&& _Other) noexcept = delete;

	void Init();

	void SetLightColor(const float4& _Color);

protected:
	void Start() override {}
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	void RendererSetting();
	void StateSetting();

	void StartLight(GameEngineState* _Parent);
	void StartFire(GameEngineState* _Parent);
	void StartFireLine(GameEngineState* _Parent);

	void UpdateLight(float _Delta, GameEngineState* _Parent);

	void LightLerp(const float4& _ColorA, const float4& _ColorB, float _Time);

private:
	std::shared_ptr<GameEngineSpriteRenderer> PotionRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> LightRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> FxRenderer;

	std::vector<float4> LightData;
	float4 LightColor;

	float LightStateTime = 0.0f;
	static constexpr float ChangeLightTime = 0.25f;
	int ChangeCount = 0;

	GameEngineState State;

};

