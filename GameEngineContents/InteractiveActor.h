#pragma once





enum class EINTERACTIONTYPE
{
	Gathering,
	Gear,
	None,
};

// Ό³Έν :
class InteractiveActor : public GameEngineActor
{
	friend class UI_InteractiveMark;
	friend class Ellie;
	friend class BackDrop;

public:
	// constrcuter destructer
	InteractiveActor();
	~InteractiveActor();

	// delete Function
	InteractiveActor(const InteractiveActor& _Other) = delete;
	InteractiveActor(InteractiveActor&& _Other) noexcept = delete;
	InteractiveActor& operator=(const InteractiveActor& _Other) = delete;
	InteractiveActor& operator=(InteractiveActor&& _Other) noexcept = delete;


	//float4& Scale;
	//float4& Position;
	//ColType CollisionType;
	void CreateAndSetCollision(ECOLLISION _Order, const float4& _Scale, const float4& _Position, ColType _Type);
	void SetInteractionType(EINTERACTIONTYPE _Type);
	EINTERACTIONTYPE GetInteractionType() const;



protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


protected:
	std::shared_ptr<GameEngineCollision> m_InteractiveCol = nullptr;
	EINTERACTIONTYPE m_InteractionType = EINTERACTIONTYPE::None;
	
	bool IsReach = false;
	bool IsEnalbeActive = false;
};

