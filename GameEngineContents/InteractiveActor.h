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

// ���� :
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

	// ��ȣ�ۿ� �浹ü ����
	void CreateAndSetCollision(ECOLLISION _Order, const float4& _Scale, const float4& _Position, ColType _Type);

	// ���� ��ȣ�ۿ� ����
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



	// �ɼ�
	void SetInteractionButtonType(const EINTERACTION_BUTTONTYPE _Type);
	void SetInteractionType(const EINTERACTION_TYPE _Type);

	// EINTERACTION_BUTTONTYPE  : ��ư
	// EINTERACTION_TYPE,		: ��ȣ�ۿ� �Ÿ� (�����̳�, ���Ÿ���)
	// ECOLLECTION_METHOD,		: ä�� ���(Ellie)
	// ETOOLTYPE				: ����
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


	// �ٸ����� : ���� ����� ������Ų��.
	virtual void GetCaught() {}

	// �浹: �ٸ� ����
	void ReachThis()
	{
		IsReach = true;
	}


	// ��ġ
	void SetDepthBias(float _DepthBias)
	{
		m_DepthBias = _DepthBias;
	}

	// ���� ����
	void ApplyDepth(const float4& _Position);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

protected:
	std::shared_ptr<GameEngineCollision> m_InteractiveCol = nullptr;
	EINTERACTION_BUTTONTYPE m_InteractionButtonType = EINTERACTION_BUTTONTYPE::None;				// UI ��ȣ�ۿ�� ��ư Ÿ��
	EINTERACTION_TYPE m_InteractionType = EINTERACTION_TYPE::None;									// ��ȣ�ۿ�� ���� ����
	ECOLLECTION_METHOD m_CollectionMethod = ECOLLECTION_METHOD::None;								// ���� ���Ÿ��
	ETOOLTYPE m_CollectionTool = ETOOLTYPE::None;													// ä�� ���� Ÿ��
	EINTERACTION_PRESSTYPE m_PressType = EINTERACTION_PRESSTYPE::Down;
	float4 m_InteractiveLocalPosition = float4::ZERO;											
	float m_InteractiveRange = 1.0f;


	
	// �浹�˻�� ����
	bool IsReach = false;

	// �浹 �� ó���� ����
	bool IsEnalbeActive = false;

protected:
	// ���� ����
	float m_DepthBias = 0.0f;				
};

