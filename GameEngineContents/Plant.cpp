#include "PreCompile.h"
#include "Plant.h"

Plant::Plant() 
{
}

Plant::~Plant() 
{
}


void Plant::Start()
{
	StaticEntity::Start();

	SetInteractionOption(EINTERACTION_BUTTONTYPE::Gathering, EINTERACTION_TYPE::Near, ECOLLECTION_METHOD::RootUp, ETOOLTYPE::Gloves);
	SetNearInteractivePositionAndRange(float4::ZERO, 3.0f);
}

void Plant::Update(float _Delta)
{
	StaticEntity::Update(_Delta);

	UpdateState(_Delta);
}

void Plant::Release()
{
	StaticEntity::Release();

	m_Plant = nullptr;
}

void Plant::LevelStart(class GameEngineLevel* _NextLevel)
{
	StaticEntity::LevelStart(_NextLevel);
}

void Plant::LevelEnd(class GameEngineLevel* _NextLevel)
{
	StaticEntity::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

// �ڽĿ��� Init


/////////////////////////////////////////////////////////////////////////////////////

void Plant::UpdateState(float _Delta)
{
	switch (m_State)
	{
	case EPLANTSTATE::Idle:						UpdateIdle(_Delta);						break;
	case EPLANTSTATE::UpRoot:					UpdateUpRoot(_Delta);					break;
	case EPLANTSTATE::None:
	{
		MsgBoxAssert("�ൿ�� ���������� �ʾҽ��ϴ�.");
		return;
	}
		break;
	default:
		break;
	}
}

void Plant::ChangeState(EPLANTSTATE _State)
{
	if (_State != m_State)
	{
		switch (_State)
		{
		case EPLANTSTATE::Idle:					StartIdle();				break;
		case EPLANTSTATE::UpRoot:				StartUpRoot();				break;
		case EPLANTSTATE::None:
		{
			MsgBoxAssert("�ش� �ൿ�������� ������ �� �����ϴ�.");
			return;
		}
			break;
		default:
			break;
		}


		m_State = _State;
	}
	else
	{
		MsgBoxAssert("���� ���·� �ٲٷ��� �߽��ϴ�.");
		return;
	}
}

void Plant::ChangePlantAnimation(std::string_view _Name)
{
	if (nullptr == m_Plant)
	{
		MsgBoxAssert("���������ʴ� �������� ����Ϸ� �߽��ϴ�.");
		return;
	}
	
	m_Plant->ChangeAnimation(_Name);
}



void Plant::StartIdle()
{
	ChangePlantAnimation("Idle");
}

void Plant::UpdateIdle(float _Delta)
{
	if (true == IsEnalbeActive)
	{
		ChangeState(EPLANTSTATE::UpRoot);
		return;
	}
}


void Plant::StartUpRoot()
{
	ChangePlantAnimation("UpRoot");
}

void Plant::UpdateUpRoot(float _Delta)
{
	if (true == m_Plant->IsCurAnimationEnd())
	{
		ChildUpRoot();
	}
}