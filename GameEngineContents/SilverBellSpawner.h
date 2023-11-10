#pragma once

// Ό³Έν :
class SilverBellSpawner : public GameEngineActor
{
public:
	// constrcuter destructer
	SilverBellSpawner();
	~SilverBellSpawner();

	// delete Function
	SilverBellSpawner(const SilverBellSpawner& _Other) = delete;
	SilverBellSpawner(SilverBellSpawner&& _Other) noexcept = delete;
	SilverBellSpawner& operator=(const SilverBellSpawner& _Other) = delete;
	SilverBellSpawner& operator=(SilverBellSpawner&& _Other) noexcept = delete;

protected:
	void Start() override {}
	void Update(float _Delta) override;
	void Release() override {}
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	void UpdateSpawner(float _Delta);
	void CreatePollen();

private:
	float CreatePollenCoolTime = 0.0f;
	static constexpr const float Create_Pollen_Time = 0.2f;

	static constexpr const float Limit_CreatePollen_Time = 2.0f;

};

