#pragma once
#include "ContentsActor.h"

enum class EAPPROACH_TYPE
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

enum class EINTERACTION_INPUTTYPE
{
	Down,
	Press,
	None,
};

// Ό³Έν :
class InteractiveActor : public ContentsActor
{
	friend class UI_InterativeMark;
	friend class BackDrop;
	friend class Ellie;

private:
	struct InteractOption
	{
	public:
		EINTERACTION_BUTTONTYPE ButtonType = EINTERACTION_BUTTONTYPE::None;
		EAPPROACH_TYPE ApproachType = EAPPROACH_TYPE::None;
		EINTERACTIONTYPE InteractionType = EINTERACTIONTYPE::None;
		ETOOLTYPE InteractionTool = ETOOLTYPE::None;
		EINTERACTION_INPUTTYPE InputType = EINTERACTION_INPUTTYPE::Down;

		std::string GearName;

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
		return InteractiveLocalPosition + Transform.GetLocalPosition();
	}

	inline float GetInteractiveRange() const
	{
		return InteractiveRange;
	}


	inline void SetInteractionButtonType(const EINTERACTION_BUTTONTYPE _Type)
	{
		Option.ButtonType = _Type;
	}

	inline void SetApproachType(const EAPPROACH_TYPE _Type)
	{
		Option.ApproachType = _Type;
	}

	inline void SetInteractionType(const EINTERACTIONTYPE _Type)
	{
		Option.InteractionType = _Type;
	}

	inline void SetInteractionInputType(const EINTERACTION_INPUTTYPE _Type)
	{
		Option.InputType = _Type;
	}

	inline void SetGearName(std::string_view _Name)
	{
		Option.GearName = _Name;
	}

	void SetInteractionOption(
		const EINTERACTION_BUTTONTYPE _BUTTONTYPE,
		const EAPPROACH_TYPE _Type,
		const EINTERACTIONTYPE _METHODType,
		const ETOOLTYPE _TOOLType
	);


	EAPPROACH_TYPE GetApproachType() const;
	EINTERACTION_BUTTONTYPE GetInteractionButtonType() const;
	EINTERACTIONTYPE GetInteractionType() const;
	ETOOLTYPE GetInteractionToolType() const;
	EINTERACTION_INPUTTYPE GetInteractionInputType() const;


	virtual void GetCaught() {}

	inline void ReachThis()
	{
		IsReach = true;
	}

protected:
	void Start() override {}
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}


	float GetDistance2DToEllie();

protected:
	std::shared_ptr<GameEngineSpriteRenderer> BodyRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> InteractiveCol = nullptr;
	InteractOption Option;

	float4 InteractiveLocalPosition = float4::ZERO;
	float InteractiveRange = 3.0f;
	bool IsReach = false;
	bool IsEnalbeActive = false;

	float PlusDepth = 0.0f;

};

