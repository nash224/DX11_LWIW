#pragma once

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

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:



public:
	template<typename CollisionOrder>
	void CreatePortalCollision(CollisionOrder _Order)
	{
		CreatePortalCollision(static_cast<int>(_Order));
	}

	void CreatePortalCollision(int _Order);

	void SetLocalPosition(const float4& _Location);
	void SetCollisionRange(const float4& _Scale);
	void SetCollisionType(ColType _Type);

	void SetChangeLevelName(std::string_view _LevelName);

	template<typename ObjectType>
	void SetLevelChangeCallBack(ObjectType* _Actor, void(ObjectType::* _Func)())
	{
		m_CallBack = std::bind(_Func, _Actor);
	}



public:
	void ActorRelease();

public:
	void SetCollisionFlag(bool _Flag);
	bool GetCollisionFlag() const;

private:
	std::shared_ptr<GameEngineCollision> PotalCol = nullptr;
	float4 m_ColScale = float4::ZERO;
	std::function <void()> m_CallBack;

	std::string m_ChangeLevelName = "";

	bool IsColliding = false;
};

