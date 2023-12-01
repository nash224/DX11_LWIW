#pragma once



// Ό³Έν :
class FireWorks : public GameEngineActor
{
private:
	enum class ECRACKERPOTIONSTATE
	{
		Light,
		Fire,
		FocusRayLight,
		Wait,
		PopCrackers,
		Done,
		None,
	};

	class RayLightState
	{
		friend class FireWorks;

	public:
		enum class EFIRELINESTATE
		{
			Ready,
			Ray,
			None,
		};

	public:
		void StateSetting();

		void StartReady(GameEngineState* _Parent);
		void UpdateReady(float _Delta, GameEngineState* _Parent);

		void StartRay(GameEngineState* _Parent);


	private:
		GameEngineState State;
		FireWorks* Parent = nullptr;


	};

	class CrackersInfo
	{
	public:
		std::shared_ptr<GameEngineSpriteRenderer> PopRenderer;
		float NextPopTime = 0.0f;

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
	void Fire();

	void SetLightColor(const float4& _Color);

	bool IsEndFireWork() const
	{
		return isFireWorkEnd;
	}

protected:
	void Start() override {}
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	void RendererSetting();
	void CrackersSetting();

	// State
	void StateSetting();

	// Start
	void StartLight(GameEngineState* _Parent);
	void StartFire(GameEngineState* _Parent);
	void StartFocusRayLight(GameEngineState* _Parent);
	void StartDone(GameEngineState* _Parent);

	// Update
	void UpdateLight(float _Delta, GameEngineState* _Parent);
	void UpdateFocusRayLight(float _Delta, GameEngineState* _Parent);
	void UpdateWait(float _Delta, GameEngineState* _Parent);
	void UpdatePopCrackers(float _Delta, GameEngineState* _Parent);

	void LightLerp(const float4& _ColorA, const float4& _ColorB, float _Time);

private:
	std::shared_ptr<GameEngineSpriteRenderer> PotionRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> LightRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> FxRenderer;

	std::vector<float4> LightData;
	float4 LightColor = float4::ZERO;
	float LightStateTime = 0.0f;
	int LightTransitionCount = 0;

	GameEngineState State;
	RayLightState RayLightStateInfo;


	float4 LimitCameraPos = float4::ZERO;
	static constexpr float TargetDistance = 2000.0f;

	std::vector<CrackersInfo> Crackers;
	int CurPopCount = 0;
	float PopRemainTime = 0.0f;

	bool isFireWorkEnd = false;

};

