#pragma once

// Ό³Έν :
class BroomCollisionParticle : public GameEngineActor
{
public:
	// constrcuter destructer
	BroomCollisionParticle();
	~BroomCollisionParticle();

	// delete Function
	BroomCollisionParticle(const BroomCollisionParticle& _Other) = delete;
	BroomCollisionParticle(BroomCollisionParticle&& _Other) noexcept = delete;
	BroomCollisionParticle& operator=(const BroomCollisionParticle& _Other) = delete;
	BroomCollisionParticle& operator=(BroomCollisionParticle&& _Other) noexcept = delete;

	void Init(float _Size, float _Angle, float _Speed);

protected:
	void Start() override {}
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


private:
	std::shared_ptr<GameEngineSpriteRenderer> EffectRenderer;

	float Size = 0.0f;
	float4 Direction = float4::ZERO;
	float Speed = 0.0f;
	float MaxSpeed = 0.0f;
	float Alpha = 1.0f;

	const float ChangeTime = 0.4f;

};

