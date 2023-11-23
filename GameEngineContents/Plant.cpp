#include "PreCompile.h"
#include "Plant.h"

Plant::Plant() 
{
	if (nullptr == GameEngineSound::FindSound("SFX_PlantsRootUp_01.wav"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Sound\\Actor\\Plant");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pfile : Files)
		{
			GameEngineSound::SoundLoad(pfile.GetStringPath());
		}
	}
}

Plant::~Plant() 
{
}


void Plant::Start()
{
	StaticEntity::Start();

	SetInteractionOption(EINTERACTION_BUTTONTYPE::Gathering, EINTERACTION_TYPE::Near, ECOLLECTION_METHOD::RootUp, ETOOLTYPE::Gloves);
	SetNearInteractivePositionAndRange(float4::ZERO, 6.0f);
}

void Plant::Update(float _Delta)
{
	StaticEntity::Update(_Delta);

	UpdateState(_Delta);
}

void Plant::Release()
{
	StaticEntity::Release();

	BodyRenderer = nullptr;
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

// 자식에서 Init


/////////////////////////////////////////////////////////////////////////////////////

void Plant::UpdateState(float _Delta)
{
	switch (m_State)
	{
	case EPLANTSTATE::Idle:						UpdateIdle(_Delta);						break;
	case EPLANTSTATE::UpRoot:					UpdateUpRoot(_Delta);					break;
	case EPLANTSTATE::None:
	{
		MsgBoxAssert("행동을 지정해주지 않았습니다.");
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
			MsgBoxAssert("해당 행동패턴으로 변경할 수 없습니다.");
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
		MsgBoxAssert("같은 상태로 바꾸려고 했습니다.");
		return;
	}
}

void Plant::ChangePlantAnimation(std::string_view _Name)
{
	if (nullptr == BodyRenderer)
	{
		MsgBoxAssert("존재하지않는 렌더러를 사용하려 했습니다.");
		return;
	}
	
	BodyRenderer->ChangeAnimation(_Name);
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
	SetInteractionButtonType(EINTERACTION_BUTTONTYPE::None);
	InteractiveCol->Off();

	PlaySFX("SFX_PlantsRootUp_01.wav");
	ChangePlantAnimation("UpRoot");
}

void Plant::UpdateUpRoot(float _Delta)
{
	if (true == BodyRenderer->IsCurAnimationEnd())
	{
		ChildRooting();
	}
}