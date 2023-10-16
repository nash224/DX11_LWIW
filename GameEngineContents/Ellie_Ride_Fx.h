#pragma once


constexpr float BroomFxLiveTime = 0.6f;


// Ό³Έν :
class Ellie_Ride_Fx : public GameEngineActor
{
public:
	// constrcuter destructer
	Ellie_Ride_Fx();
	~Ellie_Ride_Fx();

	// delete Function
	Ellie_Ride_Fx(const Ellie_Ride_Fx& _Other) = delete;
	Ellie_Ride_Fx(Ellie_Ride_Fx&& _Other) noexcept = delete;
	Ellie_Ride_Fx& operator=(const Ellie_Ride_Fx& _Other) = delete;
	Ellie_Ride_Fx& operator=(Ellie_Ride_Fx&& _Other) noexcept = delete;


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

