#pragma once



enum class EINTERACTION_TYPE
{
	Near,
	Far,
	None,
};

enum class EINTERACTION_BUTTONTYPE
{
	Gathering,
	Gear,
	None,
};

// Ό³Έν :
class InteractiveActor : public GameEngineActor
{
	friend class UI_InteractiveMark;
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

	void CreateAndSetCollision(ECOLLISION _Order, const float4& _Scale, const float4& _Position, ColType _Type);
	void SetInteractionButtonType(const EINTERACTION_BUTTONTYPE _Type);
	void SetInteractionType(const EINTERACTION_TYPE _Type);
	EINTERACTION_TYPE GetInteractionType() const;
	EINTERACTION_BUTTONTYPE GetInteractionButtonType() const;

	void ReachThis()
	{
		IsReach = true;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

protected:
	std::shared_ptr<GameEngineCollision> m_InteractiveCol = nullptr;
	EINTERACTION_TYPE m_InteractionType = EINTERACTION_TYPE::None;
	EINTERACTION_BUTTONTYPE m_InteractionButtonType = EINTERACTION_BUTTONTYPE::None;
	
	bool IsEnalbeActive = false;

private:
	bool IsReach = false;
};

