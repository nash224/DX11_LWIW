#pragma once

enum class PortalType
{
	None,
	Instant,
	Event,
};


class PortalCollisionParameter
{
public:
	float4& Position;
	float4& Scale;
	ColType CollisionType;

	PortalCollisionParameter(float4 _Position, float4 _Scale, ColType _ColType = ColType::AABBBOX2D)
		:
		Position(_Position),
		Scale(_Scale),
		CollisionType(_ColType)
	{

	}

	~PortalCollisionParameter() {}
};


// Ό³Έν :
class PortalObject : public GameEngineActor
{
public:
	// constrcuter destructer
	PortalObject();
	~PortalObject();

	// delete Function
	PortalObject(const PortalObject& _Other) = delete;
	PortalObject(PortalObject&& _Other) noexcept = delete;
	PortalObject& operator=(const PortalObject& _Other) = delete;
	PortalObject& operator=(PortalObject&& _Other) noexcept = delete;


	template<typename CollisionOrder>
	void CreatePortalCollision(CollisionOrder _Order)
	{
		CreatePortalCollision(static_cast<int>(_Order));
	}

	void CreatePortalCollision(int _Order);

	void SetLocalPosition(const float4& _Location);
	void SetCollisionRange(const float4& _Scale);
	void SetCollisionType(ColType _Type);
	void SetCollisionData(PortalCollisionParameter _ColParameter);

	void SetChangeLevelName(std::string_view _LevelName);


	void SetCollisionFlag(bool _Flag);
	bool GetCollisionFlag() const;


protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void PortalUpdate();

	void CallFadeOut();

private:
	std::shared_ptr<GameEngineCollision> PotalCol = nullptr;
	std::string ChangeLevelName;

	PortalType PortalType = PortalType::Instant;
	float4 CollisionScale = float4::ZERO;

	bool IsColliding = false;
};

