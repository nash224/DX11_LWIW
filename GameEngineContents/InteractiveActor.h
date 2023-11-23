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

enum class EINTERACTION_PRESSTYPE
{
	Down,
	Press,
	None,
};

// Ό³Έν :
class InteractiveActor : public GameEngineActor
{
	friend class UI_InterativeMark;
	friend class BackDrop;
	friend class Ellie;

private:
	struct InteractOption
	{
	public:
		EINTERACTION_BUTTONTYPE ButtonType = EINTERACTION_BUTTONTYPE::None;
		EINTERACTION_TYPE InteractionType = EINTERACTION_TYPE::None;
		ECOLLECTION_METHOD CollectionMethod = ECOLLECTION_METHOD::None;
		ETOOLTYPE CollectionTool = ETOOLTYPE::None;
		EINTERACTION_PRESSTYPE InputType = EINTERACTION_PRESSTYPE::Down;

	};

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

	void SetNearInteractivePositionAndRange(const float4& _InteractivePosition, float _Range);

	float4 GetInteractiveLocalPositon() const
	{
		float4 ReturnValue = InteractiveLocalPosition + Transform.GetLocalPosition();
		return ReturnValue;
	}

	inline float GetInteractiveRange() const
	{
		return InteractiveRange;
	}


	void SetInteractionButtonType(const EINTERACTION_BUTTONTYPE _Type);
	void SetInteractionType(const EINTERACTION_TYPE _Type);

	inline void SetCollectionMethodType(const ECOLLECTION_METHOD _Type)
	{
		Option.CollectionMethod = _Type;
	}

	inline void SetInteractionInputType(const EINTERACTION_PRESSTYPE _Type)
	{
		Option.InputType = _Type;
	}

	void SetInteractionOption(
		const EINTERACTION_BUTTONTYPE _BUTTONTYPE,
		const EINTERACTION_TYPE _Type,
		const ECOLLECTION_METHOD _METHODType,
		const ETOOLTYPE _TOOLType
	);


	EINTERACTION_TYPE GetInteractionType() const;
	EINTERACTION_BUTTONTYPE GetInteractionButtonType() const;
	ECOLLECTION_METHOD GetCollectionMethod() const;
	EINTERACTION_PRESSTYPE GetInteractionPressType() const;
	ETOOLTYPE GetCollectionToolType() const;


	virtual void GetCaught() {}

	inline void ReachThis()
	{
		IsReach = true;
	}


	void ApplyDepth();
	inline void SetDepthBias(float _DepthBias)
	{
		PlusDepth = _DepthBias;
	}

protected:
	void Start() override {}
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

protected:
	std::shared_ptr<GameEngineSpriteRenderer> BodyRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> InteractiveCol = nullptr;

	InteractOption Option;

	float4 InteractiveLocalPosition = float4::ZERO;											
	float InteractiveRange = 3.0f;

	float PlusDepth = 0.0f;				
	
	bool IsReach = false;
	bool IsEnalbeActive = false;

};

