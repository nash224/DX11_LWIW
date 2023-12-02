#pragma once

// Ό³Έν :
class ContentsActor : public GameEngineActor
{
public:
	// constrcuter destructer
	ContentsActor();
	~ContentsActor();

	// delete Function
	ContentsActor(const ContentsActor& _Other) = delete;
	ContentsActor(ContentsActor&& _Other) noexcept = delete;
	ContentsActor& operator=(const ContentsActor& _Other) = delete;
	ContentsActor& operator=(ContentsActor&& _Other) noexcept = delete;

	void ApplyDepth();

protected:
	void Start() override {}
	void Update(float _Delta) override {}
	void Release() override {}
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

	inline void ResetMoveVector()
	{
		m_MoveVector = float4::ZERO;
	}

	inline float4 GetMoveVector() const
	{
		return m_MoveVector;
	}

	inline void SetMoveVector(const float4& _Vector)
	{
		m_MoveVector = _Vector;
	}

	inline void AddMoveVector(const float4& _Vector)
	{
		m_MoveVector += _Vector;
	}

	inline void SetDepth(float _DepthBias)
	{
		PlusDepth = _DepthBias;
	}

	void ApplyMovement(float _Delta);
	void ApplyOnlyMovement(float _Delta);


	void StopSFX();
	void UpdateSoundVolumeByDistance();

private:
	float GetVolumeReductionByDistance() const;

protected:
	EDIRECTION Dir = EDIRECTION::LEFT;
	EDIRECTION RenderDir = EDIRECTION::CENTER;

	float4 m_MoveVector = float4::ZERO;
	float PlusDepth = 0.0f;

	GameEngineSoundPlayer SoundPlayer;

};