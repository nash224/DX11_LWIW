#pragma once


constexpr float BroomFxLiveTime = 0.6f;


// Ό³Έν :
class Ellie_Ride_Particle : public GameEngineActor
{
public:
	// constrcuter destructer
	Ellie_Ride_Particle();
	~Ellie_Ride_Particle();

	// delete Function
	Ellie_Ride_Particle(const Ellie_Ride_Particle& _Other) = delete;
	Ellie_Ride_Particle(Ellie_Ride_Particle&& _Other) noexcept = delete;
	Ellie_Ride_Particle& operator=(const Ellie_Ride_Particle& _Other) = delete;
	Ellie_Ride_Particle& operator=(Ellie_Ride_Particle&& _Other) noexcept = delete;


	void Init();
	void RendererSetting();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> m_FxRenderer = nullptr;

};

