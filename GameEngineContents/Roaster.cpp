#include "PreCompile.h"
#include "Roaster.h"

Roaster::Roaster() 
{
}

Roaster::~Roaster() 
{
}


void Roaster::Start()
{
	StaticEntity::Start();

	InitRoaster();
}

void Roaster::Update(float _Delta)
{
	StaticEntity::Update(_Delta);

	UpdateState(_Delta);
}

void Roaster::LevelStart(class GameEngineLevel* _NextLevel)
{
	StaticEntity::LevelStart(_NextLevel);
}

void Roaster::LevelEnd(class GameEngineLevel* _NextLevel)
{
	StaticEntity::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void Roaster::InitRoaster()
{
	CreateRendererAndAnimation();
}

void Roaster::CreateRendererAndAnimation()
{
	m_Shadow = CreateComponent<GameEngineSpriteRenderer>(15);
	if (nullptr == m_Shadow)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	m_Shadow->SetSprite("Roaster_0.png", 1);



	m_Roaster = CreateComponent<GameEngineSpriteRenderer>(16);
	if (nullptr == m_Roaster)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	m_Roaster->CreateAnimation("Broken", "Roaster_0.png", 5.0f, 7, 7);
	m_Roaster->CreateAnimation("Idle", "Roaster_0.png", 0.1f, 2, 6);
	m_Roaster->CreateAnimation("Roasting", "Roaster_0.png", 0.1f, 8, 43);
	m_Roaster->AutoSpriteSizeOn();

	m_Roaster->ChangeAnimation("Roasting");



	m_RoasterFXSteam = CreateComponent<GameEngineSpriteRenderer>(17);
	if (nullptr == m_RoasterFXSteam)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	m_RoasterFXSteam->CreateAnimation("Roasting", "Roaster_0_Top.png", 0.1f, 1, 23);
	m_RoasterFXSteam->AutoSpriteSizeOn();

	m_RoasterFXSteam->ChangeAnimation("Roasting");

	ChangeState(EROASTERSTATE::Idle);
}


void Roaster::UpdateState(float _Delta)
{
	switch (m_State)
	{
	case EROASTERSTATE::None:
	{
		MsgBoxAssert("None���� �����߽��ϴ�.");
		return;
	}
	break;
	case EROASTERSTATE::Idle:
		UpdateIdle(_Delta);
		break;
	case EROASTERSTATE::Roasting:
		UpdateRoasting(_Delta);
		break;
	default:
		break;
	}
}

void Roaster::ChangeState(EROASTERSTATE _State)
{
	if (_State != m_State)
	{
		switch (_State)
		{
		case EROASTERSTATE::Idle:
			StartIdle();
			break;
		case EROASTERSTATE::Roasting:
			StartRoasting();
			break;
		default:
			break;
		}

		m_State = _State;
	}
}

void Roaster::ChangeRoasterCompositionAnimation(std::string_view _StateName)
{
	std::string AnimationName = "";
	AnimationName += _StateName.data();

	if (nullptr == m_Roaster)
	{
		MsgBoxAssert("�ϱ��� �ʰ����� �������� �������� �ʽ��ϴ�.");
		return;
	}

	m_Roaster->ChangeAnimation(AnimationName);
}


void Roaster::StartIdle()
{
	ChangeRoasterCompositionAnimation("Idle");
}

void Roaster::UpdateIdle(float _Delta)
{
	if (true == IsReach)
	{
		if (true == GameEngineInput::IsDown('Z'))
		{
			ChangeState(EROASTERSTATE::Roasting);
			return;
		}
	}
}

void Roaster::StartRoasting()
{
	ChangeRoasterCompositionAnimation("Roasting");
}

void Roaster::UpdateRoasting(float _Delta)
{

}