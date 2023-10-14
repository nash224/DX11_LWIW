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

// 설명 :
class InteractiveActor : public GameEngineActor
{
	friend class UI_InteractiveMark;
	friend class BackDrop;
	friend class Ellie;

public:
	// constrcuter destructer
	InteractiveActor();
	~InteractiveActor();

	// delete Function
	InteractiveActor(const InteractiveActor& _Other) = delete;
	InteractiveActor(InteractiveActor&& _Other) noexcept = delete;
	InteractiveActor& operator=(const InteractiveActor& _Other) = delete;
	InteractiveActor& operator=(InteractiveActor&& _Other) noexcept = delete;

	// 상호작용 충돌체 생성
	void CreateAndSetCollision(ECOLLISION _Order, const float4& _Scale, const float4& _Position, ColType _Type);

	// 근접 상호작용 설정
	void SetNearInteractivePositionAndRange(const float4& _InteractivePosition, float _Range);

	float4 GetInteractiveLocalPositon() const
	{
		float4 ReturnValue = m_InteractiveLocalPosition + Transform.GetLocalPosition();
		return ReturnValue;
	}

	float GetInteractiveRange() const
	{
		return m_InteractiveRange;
	}



	// 옵션
	void SetInteractionButtonType(const EINTERACTION_BUTTONTYPE _Type);
	void SetInteractionType(const EINTERACTION_TYPE _Type);

	// EINTERACTION_BUTTONTYPE  : 버튼
	// EINTERACTION_TYPE,		: 상호작용 거리 (근접이냐, 원거리냐)
	// ECOLLECTION_METHOD,		: 채집 모션(Ellie)
	// ETOOLTYPE				: 도구
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


	// 앨리전용 : 동적 대상을 정지시킨다.
	virtual void GetCaught() {}

	// 충돌: 앨리 전용
	void ReachThis()
	{
		IsReach = true;
	}


	// 위치
	void SetDepthBias(float _DepthBias)
	{
		m_DepthBias = _DepthBias;
	}

	// 깊이 적용
	void ApplyDepth(const float4& _Position);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

protected:
	std::shared_ptr<GameEngineCollision> m_InteractiveCol = nullptr;
	EINTERACTION_BUTTONTYPE m_InteractionButtonType = EINTERACTION_BUTTONTYPE::None;				// UI 상호작용시 버튼 타입
	EINTERACTION_TYPE m_InteractionType = EINTERACTION_TYPE::None;									// 상호작용시 접근 유무
	ECOLLECTION_METHOD m_CollectionMethod = ECOLLECTION_METHOD::None;								// 수집 모션타입
	ETOOLTYPE m_CollectionTool = ETOOLTYPE::None;													// 채집 도구 타입
	EINTERACTION_PRESSTYPE m_PressType = EINTERACTION_PRESSTYPE::Down;
	float4 m_InteractiveLocalPosition = float4::ZERO;											
	float m_InteractiveRange = 1.0f;


	
	// 충돌검사용 변수
	bool IsReach = false;

	// 충돌 후 처리용 변수
	bool IsEnalbeActive = false;

protected:
	// 깊이 보정
	float m_DepthBias = 0.0f;				
};

