#pragma once

class Spawner : public GameEngineActor
{
public:
	// constrcuter destructer
	Spawner() {}
	~Spawner() {}

	// delete Function
	Spawner(const Spawner& _Other) = delete;
	Spawner(Spawner&& _Other) noexcept = delete;
	Spawner& operator=(const Spawner& _Other) = delete;
	Spawner& operator=(Spawner&& _Other) noexcept = delete;

	template<typename OrderType>
	void SetSpawnOrder(OrderType _Order)
	{
		SetSpawnOrder(static_cast<int>(_Order));
	}

	inline void SetSpawnOrder(int _Order)
	{
		SpawnOrder = _Order;
	}

	inline int GetSpawnOrder()
	{
		return SpawnOrder;
	}

	virtual void Spawn() = 0;

private:
	int SpawnOrder = 0;

};

// Ό³Έν :
class CometSpawner : public Spawner
{
public:
	// constrcuter destructer
	CometSpawner();
	~CometSpawner();

	// delete Function
	CometSpawner(const CometSpawner& _Other) = delete;
	CometSpawner(CometSpawner&& _Other) noexcept = delete;
	CometSpawner& operator=(const CometSpawner& _Other) = delete;
	CometSpawner& operator=(CometSpawner&& _Other) noexcept = delete;

	void Start() override;
	void Update(float _Delta) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

protected:
	void Spawn() override;

private:
	float SpawnTime = 0.0f;

};

