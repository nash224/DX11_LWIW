#pragma once

// Ό³Έν :
class PotalObject : public GameEngineActor
{
public:
	// constrcuter destructer
	PotalObject();
	~PotalObject();

	// delete Function
	PotalObject(const PotalObject& _Other) = delete;
	PotalObject(PotalObject&& _Other) noexcept = delete;
	PotalObject& operator=(const PotalObject& _Other) = delete;
	PotalObject& operator=(PotalObject&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:

public:
	template<typename CollisionOrder>
	void CreateCollision(CollisionOrder _Order)
	{
		CreateCollision(static_cast<int>(_Order));
	}

	void CreateCollision(int _Order);

	void SetLocalPosition(const float4& _Location);
	void SetCollisionRange(const float4& _Scale);


public:
	void ActorRelease();



private:
	std::shared_ptr<GameEngineCollision> PotalCol = nullptr;
	float4 m_ColScale = float4::ZERO;


	std::function <void()> _Func;





};

