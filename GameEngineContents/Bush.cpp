#include "PreCompile.h"
#include "Bush.h"

Bush::Bush() 
{
}

Bush::~Bush() 
{
}


void Bush::Start()
{
	StaticEntity::Start();
}

void Bush::Update(float _Delta)
{
	StaticEntity::Update(_Delta);

	UpdateState(_Delta);
}

void Bush::Release()
{
	StaticEntity::Release();

	m_Bush = nullptr;
	m_Bush_FX = nullptr;
}

void Bush::LevelStart(class GameEngineLevel* _NextLevel)
{
	StaticEntity::LevelStart(_NextLevel);
}

void Bush::LevelEnd(class GameEngineLevel* _NextLevel)
{
	StaticEntity::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

// �ν�Ÿ�� ����
void Bush::SetBushType(EBUSHTYPE _Type)
{
	m_BushType = _Type;
}

// ����
void Bush::Init()
{
	SetDepthBias(-30.0f);
	ApplyDepth(Transform.GetLocalPosition());
	CreateAndSetCollision(ECOLLISION::Entity, {96.0f , 96.0f }, float4::ZERO,ColType::AABBBOX2D);
	CreateBushAnimation();
	InteractiveOptionSetting();
	BushStateSetting();
}

// �ִϸ��̼� ����
void Bush::CreateBushAnimation()
{
	m_Bush_FX = CreateComponent<GameEngineSpriteRenderer>();
	if (nullptr == m_Bush_FX)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	m_Bush_FX->AutoSpriteSizeOn();
	m_Bush_FX->Off();

	m_Bush = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Effect);
	if (nullptr == m_Bush)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	m_Bush->AutoSpriteSizeOn();
	m_Bush->CreateAnimation("Normal", "Bush_0.png", 5.0f, 9, 9);					// ����


	if (EBUSHTYPE::BushApple == m_BushType)
	{
		m_Bush->CreateAnimation("Shake", "Bush_0.png", 0.1f, 0, 7, false);			// ���
		m_Bush->CreateAnimation("Apple", "Bush_0.png", 5.0f, 10, 10, true);			// ���
	}

	if (EBUSHTYPE::BushBug == m_BushType)
	{
		m_Bush->CreateAnimation("Rustle", "Bush_Animation_1.png", 0.1f, 1, 5, true);				
		m_Bush->SetStartEvent("Rustle",[=](GameEngineSpriteRenderer* _Renderer)
			{
				if (nullptr == m_Bush_FX)
				{
					MsgBoxAssert("�������� �ʴ� �������Դϴ�.");
					return;
				}
				m_Bush_FX->On();
				m_Bush_FX->ChangeAnimation("Rustle_FX", true);
			});
		m_Bush->FindAnimation("Rustle")->Inter = { 0.1f, 0.1f, 0.1f, 0.1f, 0.8f };


		m_Bush_FX->CreateAnimation("Rustle_FX", "Bush_Animation_1.png", 0.1f, 6, 13, false);		// �ν���
		m_Bush_FX->SetEndEvent("Rustle_FX", [=](GameEngineSpriteRenderer* _Renderer)
			{
				if (nullptr == m_Bush_FX)
				{
					MsgBoxAssert("�������� �ʴ� �������Դϴ�.");
					return;
				}
				m_Bush_FX->Off();
			});


		m_Bush->CreateAnimation("AppearBug", "BushBug_Appearing.png", 0.1f, 1, 18, false);	
		m_Bush->SetFrameEvent("AppearBug", 6, [=](GameEngineSpriteRenderer* _Renderer)
			{
				if (nullptr == m_Bush_FX)
				{
					MsgBoxAssert("�������� �ʴ� �������Դϴ�.");
					return;
				}
				m_Bush_FX->On();
				m_Bush_FX->ChangeAnimation("AppearBug_FX");
			});

		m_Bush_FX->CreateAnimation("AppearBug_FX", "BushBug_Appearing.png", 0.1f, 19, 24, false);	// ���� ����
		m_Bush_FX->SetEndEvent("AppearBug_FX", [=](GameEngineSpriteRenderer* _Renderer)
			{
				if (nullptr == m_Bush_FX)
				{
					MsgBoxAssert("�������� �ʴ� �������Դϴ�.");
					return;
				}
				m_Bush_FX->Off();
			});
	}
}

// ��ȣ�ۿ� �ɼ� ����
void Bush::InteractiveOptionSetting()
{
	EINTERACTION_BUTTONTYPE ButtonType = EINTERACTION_BUTTONTYPE::None;

	switch (m_BushType)
	{
	case EBUSHTYPE::Bush:
		break;
	case EBUSHTYPE::BushBug:
	case EBUSHTYPE::BushApple:
		ButtonType = EINTERACTION_BUTTONTYPE::Gear;
		break;
	case EBUSHTYPE::None:
	{
		MsgBoxAssert("Ÿ���� �������ּ���.");
		return;
	}
		break;
	default:
		break;
	}

	SetInteractionOption(ButtonType, EINTERACTION_TYPE::Far, ECOLLECTION_METHOD::None, ETOOLTYPE::Nothing);
}

// �ν� �ʱ� �ൿ ����
void Bush::BushStateSetting()
{
	switch (m_BushType)
	{
	case EBUSHTYPE::Bush:
		ChangeState(EBUSHSTATE::Normal);
		break;
	case EBUSHTYPE::BushBug:
		ChangeState(EBUSHSTATE::Rustle);
		break;
	case EBUSHTYPE::BushApple:
		ChangeState(EBUSHSTATE::Apple);
		break;
	case EBUSHTYPE::None:
		break;
	default:
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////


void Bush::UpdateState(float _Delta)
{
	switch (m_State)
	{
	case EBUSHSTATE::Normal:					UpdateNormal(_Delta);					break;
	case EBUSHSTATE::Apple:						UpdateApple(_Delta);					break;
	case EBUSHSTATE::Shake:						UpdateShake(_Delta);					break;
	case EBUSHSTATE::Rustle:					UpdateRustle(_Delta);					break;
	case EBUSHSTATE::AppearBug:					UpdateAppearBug(_Delta);				break;
	case EBUSHSTATE::None:
	{
		MsgBoxAssert("�ش� ���´� ������ �� �����ϴ�.");
		return;
	}
	break;
	default:
		break;
	}
}

void Bush::ChangeState(EBUSHSTATE _State)
{
	if (_State != m_State)
	{
		switch (_State)
		{
		case EBUSHSTATE::Normal:					StartNormal();					break;
		case EBUSHSTATE::Apple:						StartApple();					break;
		case EBUSHSTATE::Shake:						StartShake();					break;
		case EBUSHSTATE::Rustle:					StartRustle();					break;
		case EBUSHSTATE::AppearBug:					StartAppearBug();				break;
		case EBUSHSTATE::None:
		{
			MsgBoxAssert("�ش� ���´� ������ �� �����ϴ�.");
			return;
		}
			break;
		default:
			break;
		}

		m_State = _State;
	}
}


void Bush::ChangeBushAnimation(std::string_view _Name)
{
	if (nullptr == m_Bush)
	{
		MsgBoxAssert("�������� �������� �ʾҽ��ϴ�.");
		return;
	}

	m_Bush->ChangeAnimation(_Name);
}